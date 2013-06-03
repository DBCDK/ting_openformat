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
// load search client
//module_load_include('inc', 'ting_openformat','ting_openformat.search_client');

/**
 * Implements hook_search_info().
 */
function ting_openformat_search_info() {
  return array(
    //'title' => t('Bibliotek.dk'),
    'title' => variable_get('search_client_name', 'well'),
    'path' => 'work',
    'conditions_callback' => 'ting_openformat_conditions_callback',);
}

function _ting_openformat_handle_conditions(&$conditions) {
  // if size is set in url - override numResults set in variable
  if (!empty($conditions['size'])) {
    $conditions['numResults'] = $conditions['size'];
  }
}

/** implements hook_search_execute */
function ting_openformat_search_execute($keys = NULL, $conditions = NULL) {
  $params = array();
  // search phrase (query)
  $params['query'] = $keys;
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

  if (!empty($conditions)) {
    $params = array_merge($params, $conditions);
  }
  // do the actual search via ting_client_class
  $client = new ting_client_class();
 // $result = $client->do_search($params);

  if (isset($params['query']) && empty($params['query']) )
    return array();
  $result = $client->do_request('search',$params);
  if (!$result) {
    return array();
  }

  // set facets for result
  _ting_openformat_facet_cache($client, $result, $params);

  if (isset($result->collections)) {
    $result->search_key = $keys;
  }

  // static cache result - used in hook_ding_facetbrowser, ting_search etc.
  drupal_static('ting_search_results', $result);
  _ting_openformat_create_collection_entities($result);
  foreach ($result->entities as $key => $entity) {
    $search_results[] = _ting_openformat_set_search_result($entity);
  }

   module_invoke_all('ting_openformat_search_results', $keys, $result);

  // Collections may contain more works than $params['numResults'], and we don't want a pager if there's only one page
  $total = ($result->numTotalCollections < $params['numResults'] && $params['start'] < $params['numResults']) ? $result->numTotalCollections : $result->numTotalObjects;
  // Stop pager if we're at the last page of collections.
  if (!$result->more) {
    $total = $params['start'] + $result->numTotalCollections;
  }
  pager_default_initialize($total, $params['numResults']);

  if (!empty($search_results)) {
    return $search_results;
  }

  // .. default; no search results
  return array();
}

/**
 * Set collection entities
 * */
function _ting_openformat_create_collection_entities(&$result) {
  $result->entities = array();
  foreach ($result->collections as $collection) {
    $bibdkobjects = array();
    $original_manifestations = array();
    $entity_id = array();

    // error check
    $openformat = isset($collection->formattedCollection->formattedCollection->manifestation) ? $collection->formattedCollection->formattedCollection->manifestation : NULL;

    if( empty($openformat) ) {
      watchdog('openformat','Formatted collection is not set',array(),WATCHDOG_ERROR);
      continue;
    }
    _ting_openformat_parse_collection($original_manifestations, $entity_id, $openformat);
    if (!empty($entity_id)) {
      $conditions['manifestations'] = $original_manifestations;
      $bibdkEntities = entity_load('bibdkCollection', $entity_id, $conditions, FALSE);
      $bibdkEntities->parseManifestations(); //Temporary as malformed XML is returned from OpenSearch
      $bibdkobjects = $bibdkEntities;
      //unset($entity_id);
       $result->entities[] = $bibdkobjects;
    }
    else{
      // @TODO log errors
      watchdog('openformat','ID is not set',array(),WATCHDOG_ERROR);
      continue;
    }
  }
  unset($result->collections);
}

function _ting_openformat_parse_collection(&$original_manifestations, &$entity_id, $openformat) {
  if (isset($openformat) && is_array($openformat)) {
    $entity_id = $openformat[0]->identifier->{'$'};
    foreach ($openformat as $manifestation) {
      $original_manifestations[] = $manifestation;
    }
  }
}

/** Set a search result array as defined for hook_search_execute
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

/** \brief set facet for search result. Look in cache if not found do a request and set cache
 *
 * @param $client - search_client
 * @param $params - parameters for searchrequest
 * @param $result - search result
 *
 * @return nothing, but sets facet for $result-object given as parameter
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
      $params['numFacets'] = variable_get('ding_facetbrowser_number_shown', 25);
    }

    // do a zero search to get the facets
    $params['numResults'] = 0;
    $params['objectFormat'] = 'DKABM';

    //$facet_result = $client->do_search($params);
    $facet_result = $client->do_request('search',$params);
    if (isset($facet_result->facets)) {
      $result->facets = $facet_result->facets;
      cache_set($local_cache_key, $facet_result->facets, 'cache', CACHE_TEMPORARY);
    }
  }
  // facets was found in cache
  else {
    $result->facets = cache_get($local_cache_key)->data;
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

/** \brief get variables and set corresponding search parameters
 * */
function _ting_openformat_search_get_variables() {
  // results pr. page (opensearch::stepValue) ... in ting-client/lib/request/TingClientSearchRequest.php this is called numResults
  $resultsPerPage = variable_get('ting_search_results_per_page', 10);
  $params['numResults'] = $resultsPerPage;
  $params['includeHoldingsCount'] = true;

  // page number (opensearch::start)
  $page = pager_find_page();
  $params['start'] = ( $page * $resultsPerPage ) + 1; // search results start at position 1

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

  // set Object Format
  $params['objectFormat'] = variable_get('objectFormat', 'briefDisplay');

  //Set queryLanguage
  $params['queryLanguage'] = ting_openformat_get_cql_language();
  return $params;
}

/** \brief Set facets for request
 *
 * */
function _ting_openformat_set_facets(&$query, $facets) {
  if (isset($facets)) {
    foreach ($facets as $facet) {
      $facet = explode(':', $facet, 2);
      if ($facet[0]) {
        $facetArray[] = $facet[0] . '="' . rawurldecode($facet[1]) . '"';
      }
    }
    $op = ting_openformat_get_cql_commando('AND');
    $query .= $op . implode($op, $facetArray);
  }
}

/**
 * Search conditions callback.
 */
function ting_openformat_conditions_callback($query) {
  $conditions = array();

  if (!empty($_REQUEST['size'])) {
    $conditions['size'] = (int)$_REQUEST['size'];
  }


// set the sort parameter here - thus it will work when sort parameter is added to url
  if (!empty($_REQUEST['sort'])) {
    $conditions['sort'] = check_plain($_REQUEST['sort']);
  }
  // default sort parameter
  else {
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
      drupal_goto(rawurldecode($_GET['q']), array('query' => $facets));
    }
  }
  return $conditions;
}
