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

  if ($keys) {
    $params['query'] = ting_openformat_string_to_cql($keys);
  }

  $all_params = $conditions;

  // save query to show in search_block
  drupal_static('ting_search_query', !empty($conditions['qe']['query']) ? $conditions['qe']['query'] : $keys);

  // get parameters set as variables
  $variables = _ting_openformat_search_get_variables();

  if (!empty($variables)) {
    $params = array_merge($params, $variables);
  }

  if (isset($conditions['qe']) && $conditions['qe'] != NULL) {
    _ting_openformat_set_query_extended($params['query'], $conditions['qe']);
    unset($conditions['qe']);
  }

  // selected facets from facetbrowser (in query). Do last because we may use a NOT operator
  if (isset($conditions['facets']) && $conditions['facets'] != NULL) {
    _ting_openformat_set_facets($params['query'], $conditions['facets']);
    unset($conditions['facets']);
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
  $by_ajax = variable_get('bibdk_facetbrowser_by_ajax', FALSE);
  if (!$by_ajax) {
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

  $query = isset($params['query']) ? $params['query'] : array();
  module_invoke_all('ting_openformat_search_results', $keys, $result, $all_params, $query);
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
  $_SESSION['latest_search']['search_key'] = $result->searchKey;
  $_SESSION['latest_search']['request_uri'] = request_uri();

  if (!empty($search_results)) {
    _ting_openformat_set_js_settings();
    drupal_get_messages('warning');
    return $search_results;
  }

  // .. default; no search results
  return array();
}


/**
 * Setting the JavaScript object Drupal.settings.ting_openformat
 */
function _ting_openformat_set_js_settings() {
  global $user;
  drupal_add_js(array(
      'ting_openformat' => array(
        'full_view' => $_SESSION['search_settings']['full_view'],
        'ajax_callback' => url('ting_openformat/full_view/'),
        'full_view_all_loaded' => $_SESSION['search_settings']['full_view'],
        'isLoadingFullView' => FALSE,
        'search_key' => $_SESSION['latest_search']['search_key'],
        'isAdmin' => in_array('administrator', $user->roles),
      ),
    ), 'setting');
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
  $full_view = _ting_openformat_init_full_view();

  $render_view = ting_openformat_collection_view($bibdkobject, $full_view);
  $result = array(
    'link' => url("work/" . $bibdkobject->getId()),
    'title' => $bibdkobject->getTitle(),
    'snippet' => drupal_render($render_view),
  );

  return $result;
}


/**
 * Get variables and set corresponding search parameters
 */
function _ting_openformat_search_get_variables() {
  // results pr. page (opensearch::stepValue) ... in ting-client/lib/request/TingClientSearchRequest.php this is called numResults
  $resultsPerPage = variable_get('ting_search_results_per_page', 10);
  $params['numResults'] = $resultsPerPage;
  $params['includeHoldingsCount'] = TRUE;

  global $base_root; // page number (opensearch::start)
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
 * Set facets for extended query
 **/
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
        $val = urldecode($val);
        $group[$key] = $term . '=' . '(' . ting_openformat_string_to_cql($val) . ')';
      }

      $fields[] = '(' . join($op, $group) . ')';
    }

    $op = CQL_AND;
    if (!empty($fields)) {
      $res[] = '(' . join($op, $fields) . ')';
    }

    foreach ($preprocessed as $key => $term) {
      $res[] = $term;
    }

    if (count($res) > 0) {
      $cql[] = join($op, $res);
    }
  }
  $query = join($op, $cql);

  $filters = ting_openformat_filters();
  if (isset($filters)) {
    $query .= $filters;
  }
}

/** Returns cql parsed filters invoked by hook_ting_openformat_query_filter
 * @return null|string
 */
function ting_openformat_filters() {
  $op = ' or ';
  $filters = module_invoke_all('ting_openformat_query_filter');
  $not = ' not ';
  $return = null;
  if (!empty($filters)) {
    $return = "$not(" . implode($op, $filters) . ")";
  }
  return $return;
}


/**
 * Parsing the search string for search codes that define a sort ranking
 * @param $query
 * @param $conditions
 * @return string
 */
function _ting_openformat_set_sort_ranking($query = '', $conditions = array()) {

  require('ting_openformat.ranking_definitions.inc'); // nb: require_once() cause unit tests to fail.
  
  // remove multiple whitespaces
  $query = preg_replace('/\s+/', '', $query);

  foreach ($ranking_definitions as $sort => $sort_triggers) {
    foreach ($sort_triggers as $key => $search_code) {
      $pos = strpos($query, $search_code . '=');
      if ( $pos !== FALSE ) {
        return $sort;
      }
      if (!empty($conditions['qe']) && _ting_openformat_sort_ranking_array_search($conditions['qe'], $search_code)) {
        return $sort;
      }
    }
  }

  return $sort;

}


/**
 * recursive search for search code that trigger ranking
 * @param $query
 * @param $search_code
 * @return boolan
 */
function _ting_openformat_sort_ranking_array_search($query, $search_code) {
  if (is_array($query)) {
    if (array_key_exists($search_code,$query)) {
      return TRUE;
    }
    foreach ($query as $elem) {
      if (_ting_openformat_sort_ranking_array_search($elem, $search_code)) {
        return TRUE;
      }
    }
  } else {
    // remove multiple whitespaces
    $query = preg_replace('/\s+/', '', $query);
    $pos = strpos(urldecode($query), $search_code . '=');
    if ( $pos !== FALSE ) {
      return TRUE;
    }
  }
  return FALSE;
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
  }
  else {
    $conditions['trackingId'] = date('Y-m-d\TH:i:s:') . substr((string) microtime(), 2, 6) . ':' . getmypid();
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
  if (empty($_REQUEST['sort']) || $_REQUEST['sort'] == 'rank_frequency') {
    $conditions['sort'] = _ting_openformat_set_sort_ranking($query, $conditions);
  }
  else { // default sort parameter ('rank_frequency')
    $conditions['sort'] = check_plain($_REQUEST['sort']);
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

/** Method to convert a string to strict cql (Basically by adding quotes when needed)
 * @param $string
 * @return string
 */
function ting_openformat_string_to_cql($string) {
  $string = trim($string);
  if (isset($string) && !_ting_openformat_string_is_cql($string)) {
    $string = _ting_openformat_convert_string_to_cql($string);
  }
  return $string;
}

/** Add quotes to string and escapes existing quotes
 * @param $string
 * @return string
 */
function _ting_openformat_convert_string_to_cql($string) {
  // Escape quotes
  $string = str_replace('"', '\"', $string);
  // qoute forward slash -it is a boolean modifier ??
  // are there more to qoute ??
  $string = str_replace('/', ' "/" ', $string);
  // remove multiple whitespaces
  $string = preg_replace('/\s+/', ' ', $string);
  // explode string by whitespace
  $expressions = explode(' ', $string);
  // join expressions with 'and' operator
  return implode(' and ', $expressions);
}

/** Tests if a string is cql
 * @param $string
 * @return bool|int
 */
function _ting_openformat_string_is_cql($string) {
  if(strpos($string, '"') !== false && (!preg_match('@ and | or | not |=@', $string) && !(substr($string, 0, 1) === '"' && substr($string, -1) === '"'))){
    return false;
  }
  return preg_match('@"|\(|\)|=@', $string);
}
