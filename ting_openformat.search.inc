<?php

/* * ******** NOTES *************** */
/*
 * SEARCH HOOKS
 * hook_search_info
 * hook_search_execute
 * hook_search_page
 */
/* * ******** END NOTES ********** */


// load theme hooks
module_load_include('inc', 'ting_openformat', 'ting_openformat.theme');

/**
 * Implements hook_search_info().
 */
function ting_openformat_search_info() {
  return array(
    'title' => variable_get('search_client_name', 'well'),
    'path' => 'work',
    'conditions_callback' => 'ting_openformat_conditions_callback',
  );
}

function _ting_openformat_handle_conditions(&$conditions) {
  // if size is set in url - override numResults set in variable
  if (!empty($conditions['size'])) {
    $conditions['numResults'] = $conditions['size'];
  }
}

/** implements hook_search_execute */
function ting_openformat_search_execute($keys = NULL, $conditions = NULL, &$more = NULL) {

  $params = array();
  $params['query'] = $keys;

  $all_params = $conditions;

  // save query to show in search_block
  drupal_static('ting_search_query', $keys);
  // get parameters set as variables
  $variables = _ting_openformat_search_get_variables();

  if (!empty($variables)) {
    $params = array_merge($params, $variables);
  }


  // selected facets from facetbrowser (in query)
  if (isset($conditions['facets']) && $conditions['facets'] != NULL) {
    _ting_openformat_set_facets($params['query'], $conditions['facets']);
    unset($conditions['facets']);
  }

  if (isset($conditions['qe']) && $conditions['qe'] != NULL) {
    _ting_openformat_set_query_extended($params['query'], $conditions['qe']);
    unset($conditions['qe']);
  }

  if (!empty($conditions['qe'])) {
    if (!empty($params['query'])) {
      $params['query'] .= CQL_AND;
    }
    $params['query'] .= $conditions['qe'];
  }
  unset($conditions['qe']);

  if (!empty($conditions)) {
    $params = array_merge($params, $conditions);
  }

  // do the actual search via ting_client_class
  $client = new ting_client_class();
  // $result = $client->do_search($params);

  if (isset($params['query']) && empty($params['query'])) {
    return array();
  }

  if (isset($_GET['feed_me'])) {
    ting_openformat_feeds_set_params($params);
  }

  $result = $client->do_request('search', $params);
  if (!$result) {
    return array();
  }

  if (isset($_GET['feed_me'])) {
    ting_openformat_feeds_redirect($result, $params['query']);
  }

  // set facets for result .. if not by ajax
  $by_ajax = variable_get('ding_facetbrowser_by_ajax', FALSE);
  if(!$by_ajax){
  _ting_openformat_facet_cache($client, $result, $params);
  }

  if (isset($result->collections)) {
    $result->search_key = $keys;
  }

  // static cache result - used in hook_ding_facetbrowser, ting_search etc.
  drupal_static('ting_search_results', $result);
  _ting_openformat_create_collection_entities($result);
  foreach ($result->entities as $key => $entity) {
    $search_results[] = _ting_openformat_set_search_result($entity);
  }

  module_invoke_all('ting_openformat_search_results', $keys, $result, $all_params);
  $search_results['more'] = $result->more;

  // Collections may contain more works than $params['numResults'], and we don't want a pager if there's only one page
  $total = ($result->numTotalCollections < $params['numResults'] && $params['start'] < $params['numResults']) ? $result->numTotalCollections : $result->numTotalObjects;
  // Stop pager if we're at the last page of collections.
  if (!$result->more) {
    $total = $params['start'] + $result->numTotalCollections;
  }
  // init a pager. pager is global @see contenttypes/ting_openformat_pager.inc
  // pager_default_initialize($total, $params['numResults']);


  $_SESSION['latest_search']['params'] = $params;
  $_SESSION['latest_search']['cache_key'] = $result->cacheKey;
  $_SESSION['latest_search']['search_key'] = $result->search_key;
  $_SESSION['latest_search']['request_uri'] = request_uri();

  if (!empty($search_results)) {
    _ting_openformat_set_js_settings();
    drupal_get_messages('warning');
    return $search_results;
  }


  // .. default; no search results
  return array();
}

function _ting_openformat_set_js_settings() {
  drupal_add_js(array(
    'ting_openformat' => array(
      'full_view' => $_SESSION['search_settings']['full_view'],
      'ajax_callback' => url('ting_openformat/full_view/'),
      'full_view_all_loaded' => $_SESSION['search_settings']['full_view'],
      'isLoadingFullView' => FALSE,),
      ), 'setting'
  );
}

/**
 * Set collection entities
 * */
function _ting_openformat_create_collection_entities(&$result) {
  $result->entities = array();
  foreach ($result->collections as $collection) {
    $original_manifestations = array();
    $entity_id = array();

    /* @var $collection TingClientObjectCollection */
    $openformat = isset($collection->getFormattedCollection()->getBriefDisplay()->manifestation) ? $collection->getFormattedCollection()->getBriefDisplay()->manifestation : NULL;

    if (empty($openformat)) {
      $objects = $collection->getObjects();
      $id = (isset($objects[0]->id)) ? $objects[0]->id : '';
      watchdog('openformat', 'Formatted collection [id:\'%id\'] is not set', array('%id' => $id), WATCHDOG_ERROR);
      continue;
    }
    _ting_openformat_parse_collection($original_manifestations, $entity_id, $openformat);
    if (!empty($entity_id)) {
      $conditions['workOne'] = $collection->getFormattedCollection()->getWorkOne();
      $conditions['manifestations'] = $original_manifestations;
      /* @var $bibdkEntities BibdkCollection */
      $bibdkEntities = entity_load('bibdkCollection', $entity_id, $conditions, FALSE);
      $bibdkEntities->parseManifestations(); //Temporary as malformed XML is returned from OpenSearch
      $bibdkobjects = $bibdkEntities;
      $result->entities[] = $bibdkobjects;
    }
    else {
      // @TODO log errors
      watchdog('openformat', 'ID is not set', array(), WATCHDOG_ERROR);
      continue;
    }
  }
  unset($result->collections);
  $_SESSION['search_result'][$result->search_key] = $result;
}

function _ting_openformat_parse_collection(&$original_manifestations, &$entity_id, $openformat) {
  if (isset($openformat) && is_array($openformat)) {
    $entity_id = $openformat[0]->identifier->{'$'};
    foreach ($openformat as $manifestation) {
      $original_manifestations[] = $manifestation;
    }
  }
}

/**
 * Set a search result array as defined for hook_search_execute
 *
 * 'link': Required. The URL of the found item.
 * 'type': The type of item (such as the content type).
 * 'title': Required. The name of the item.
 * 'user': The author of the item.
 * 'date': A timestamp when the item was last modified.
 * 'extra': An array of optional extra information items.
 * 'snippet': An excerpt or preview to show with the result (can be generated with search_excerpt()).
 * 'language': Language code for the item (usually two characters).
 *
 * @see hook_search_execute - http://api.drupal.org/api/drupal/modules%21search%21search.api.php/function/hook_search_execute/7
 * @param BibdkCollection $bibdkobject
 * @return Array result
 */
function _ting_openformat_set_search_result($bibdkobject) {
  $result = array(
    'link' => url("work/" . $bibdkobject->getId()),
    'type' => '',
    'title' => $bibdkobject->getTitle(),
    'user' => '',
    'date' => '',
    'snippet' => ting_openformat_collection_view($bibdkobject),
  );

  return $result;
}

/**
 * Set facet for search result. Look in cache if not found do a request and set cache
 * Returns nothing, but sets facet for $result-object given as parameter
 *
 * @param $client - search_client
 * @param $params - parameters for searchrequest
 * @param $result - search result
 * */
function _ting_openformat_facet_cache($client, $result, $params) {
  // check facets; get from cache if set - else do zero search to get facets
  $local_cache_key = 'facets-' . $result->cacheKey;
  if (!$facets = cache_get($local_cache_key)) {
    // default facets
    if (module_exists('ding_facetbrowser')) {
      $facets = _ting_openformat_set_default_facets();
    }
    if (isset($facets)) {
      $params['facets'] = $facets;
      $params['numFacets'] = variable_get('ding_facetbrowser_number_requested', 25);
    }

    // do a zero search to get the facets
    $params['numResults'] = 0;
    // use DKABM .. it is fastest
    $params['objectFormat'] = 'DKABM';

    //$facet_result = $client->do_search($params);
    $facet_result = $client->do_request('search', $params);
    if (isset($facet_result->facets)) {
      $result->facets = $facet_result->facets;
      cache_set($local_cache_key, $facet_result->facets, 'cache', CACHE_TEMPORARY);
      drupal_static('ting_search_results', $result);
    }
  }
  // facets was found in cache
  else {
    $result->facets = cache_get($local_cache_key)->data;
    drupal_static('ting_search_results', $result);
  }
}

/** \brief get facets from variables
 * return array (facets)
 * */
function _ting_openformat_set_default_facets() {
  $facets = array();
  foreach (variable_get('ding_facetbrowser_facets', array()) as $facet) {
    $facets[] = $facet['name'];
  }

  return $facets;
}

/**
 * Get variables and set corresponding search parameters
 */
function _ting_openformat_search_get_variables() {
  // results pr. page (opensearch::stepValue) ... in ting-client/lib/request/TingClientSearchRequest.php this is called numResults
  $resultsPerPage = variable_get('ting_search_results_per_page', 10);
  $params['numResults'] = $resultsPerPage;
  $params['includeHoldingsCount'] = TRUE;

  global $base_root;  // page number (opensearch::start)
  $page = pager_find_page();
  $params['start'] = ($page * $resultsPerPage) + 1; // search results start at position 1
  // search profile (opensearch::profile)
  $params['profile'] = variable_get('ting_search_profile', FALSE);
  if (!($params['profile'])) {
    watchdog('openformat search', 'search profile is not set - yields no search results', array(), WATCHDOG_ERROR, url('admin/config/ting/settings'));
  }

  // agency (opensearch::agency)
  $params['agency'] = variable_get('ting_agency');
  if (!($params['agency'])) {
    watchdog('openformat search', 'agency is not set - yields no search results', array(), WATCHDOG_ERROR, url('admin/config/ting/settings'));
  }


  if (isset($_SESSION['search_settings']['full_view']) && $_SESSION['search_settings']['full_view'] == TRUE) {
    $params['collectionType'] = 'work-1';
    $params['objectFormat'][] = 'bibliotekdkWorkDisplay';
    $params['relationData'][] = 'uri';
  }

  $params['objectFormat'][] = variable_get('objectFormat', 'briefDisplay');

  return $params;
}

/**
 * Set facets for request
 * */
function _ting_openformat_set_facets(&$query, $facets) {
  if (isset($facets)) {
    $op = CQL_AND;
    foreach ($facets as $facet) {
      $facet = explode(':', $facet, 2);
      if ($facet[0]) {
        $facetArray[] = $facet[0] . '="' . rawurldecode($facet[1]) . '"';
      }
    }
    if (!empty($query)) {
      $query .= $op . implode($op, $facetArray);
    }
    else {
      $query .= implode($op, $facetArray);
    }
  }
}

/** \brief Set facets for extended query
 *
 * */
function _ting_openformat_set_query_extended(&$query, $qe) {
  $cql = $preprocessed = array();

  if (!empty($query)) {
    $cql[] = $query;
  }

  if (!empty($qe) && count($qe) > 0) {

    $res = array();
    $fields = array();
    $qe = module_invoke_all('ting_openformat_qe_preprocess', $qe);

    if (isset($qe['#preprocessed'])) {
      $preprocessed = $qe['#preprocessed'];
      unset($qe['#preprocessed']);
    }

    if (isset($qe['delimiter']) && !empty($qe['delimiter'])) {
      $res[] = $qe['delimiter'];
      unset($qe['delimiter']);
    }

    $op = CQL_OR;
    foreach ($qe as $term => $group) {
      foreach ($group as $key => $val) {
        if(strpos($val, '\'') === false) {
          $group[$key] = $term . '=' . '\'' . $val . '\'';
        }
        else {
          $group[$key] = $term . '=' . '(' . $val . ')';
        }

      }
      $fields[] = '(' . implode($op, $group) . ')';
    }

    $op = CQL_AND;
    if (!empty($fields)) {
      $res[] = '(' . implode($op, $fields) . ')';
    }

    foreach ($preprocessed as $key => $term) {
      $res[] = $term;
    }

    if (count($res) > 0) {
      $cql[] = join($op, $res);
    }
  }

  $query = join($op, $cql);
}

/**
 * Search conditions callback.
 */
function ting_openformat_conditions_callback($query) {
   $_REQUEST += module_invoke_all('ting_openformat_conditions', $query);
   $conditions = array();

  // check tracking id
  if (!empty($_REQUEST['trackingId'])) {
    $conditions['trackingId'] = $_REQUEST['trackingId'];
  } else {
    $conditions['trackingId'] = date('Y-m-d\TH:i:s:') . substr((string)microtime(), 2, 6) . ':' . getmypid();
  }

  $page_id = array();
  if (!empty($_REQUEST['page_id'])) {
    $page_id['page_id'] = $_REQUEST['page_id'];
  }

  if (!empty($_REQUEST['qe'])) {
    $conditions['qe'] = $_REQUEST['qe'];
  }

  if (!empty($_REQUEST['size'])) {
    $conditions['size'] = (int) $_REQUEST['size'];
  }

  if (isset($_REQUEST['full_view'])) {
    $_SESSION['search_settings']['full_view'] = (bool) $_REQUEST['full_view'];
  }
  elseif (!isset($_SESSION['search_settings']['full_view'])) {
    $_SESSION['search_settings']['full_view'] = FALSE;
  }
  // set the sort parameter here - thus it will work when sort parameter is added to url
  if (!empty($_REQUEST['sort'])) {
    $conditions['sort'] = check_plain($_REQUEST['sort']);
  }
  else { // default sort parameter
    $conditions['sort'] = 'date_descending';
  }

  // If facets is set, check if we have to remove any, if so,
  // reload the page.
  if (!empty($_REQUEST['facets'])) {
    $remove = array();
    $redirect = FALSE;

    foreach ($_REQUEST['facets'] as $key => $facet) {
      if (preg_match('/^-facet/', $facet)) {
        $remove[] = preg_replace('/^-/', '', $facet);
        $redirect = TRUE;
        unset($_REQUEST['facets'][$key]);
      }
    }

    foreach ($_REQUEST['facets'] as $key => $facet) {
      foreach ($remove as $rem) {
        if ($facet == $rem) {
          unset($_REQUEST['facets'][$key]);
          continue;
        }
      }
    }
    $conditions['facets'] = $_REQUEST['facets'];
    if ($redirect === TRUE) {
      $facets = array();
      foreach ($conditions['facets'] as $facet) {
        $facets['facets'][] = $facet;
      }
      drupal_goto(rawurldecode($_GET['q']), array('query' => $facets + $conditions + $page_id));
    }
  }

  return $conditions;
}
