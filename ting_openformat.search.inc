<?php

/********** NOTES ****************/
/*
 * SEARCH HOOKS
 * hook_search_info
 * hook_search_execute
 * hook_search_page
 */
/********** END NOTES ********** */


// load theme hooks
module_load_include('inc','ting_openformat','ting_openformat.theme');
// load search client
module_load_include('inc', 'ting_openformat','ting_openformat.search_client');


/**
 * Implements hook_search_info().
 */
function ting_openformat_search_info() {
  return array(
    //'title' => t('Bibliotek.dk'),
    'title' => variable_get('search_client_name', 'TESTHEST'),
    'path' => 'work',
    'conditions_callback' => 'ting_openformat_conditions_callback',);
}

/** implements hook_search_execute */
function ting_openformat_search_execute($keys = NULL, $conditions = NULL){
  $params = array();
  // search phrase (query)
  $params['query'] = $keys;

  // get parameters set as variables
  $variables = _ting_openformat_search_get_variables($conditions);

  if( !empty($variables) ) {
    $params = array_merge($params,$variables);
  }

  // selected facets from facetbrowser (in query)
  if( isset($conditions['facets']) && $conditions['facets'] != NULL ) {
    _ting_openformat_set_facets($params['query'],$conditions['facets']);
  }

  // do the actual search via ting_client_class
  $client = new ting_client_class();
  $result = $client->do_search($params);

  if( !$result ) {
    return array();
  }

  // set facets for result
  _ting_openformat_facet_cache($client, $result, $params);

  if (isset($result->collections)) {
      $result->search_key = $keys;
  }

  // initialize entities
  _ting_openformat_load_entities($result);

  // static cache result - used in hook_ding_facetbrowser, ting_search etc.
  drupal_static('ting_search_results', $result);

  foreach($result->collections as $collection) {
    $search_results[] = _ting_openformat_set_search_result($collection);
    }

  // set searchhistory
  if(module_exists('bibdk_searchhistory')){
    module_invoke('bibdk_searchhistory', 'set_search_results', $keys, $result);
  }

  if( !empty($search_results) ) {
    return $search_results;
  }

  // .. default; no search results
  return array();
}

/** \brief set entities
 * replace TingClientObjectCollection (returned from ting-client) with bibdkEntity(work)
 **/
function _ting_openformat_load_entities( $result ) {
  if( is_array($result->collections) ) {
    $ids = array();
    foreach ($result->collections as &$collection) {
      /* if (isset($collection->objects[0])) {
        $ids[] = $collection->objects[0]->id;
        }*/
      $openformat = $collection->formattedCollection;
      $bibdkobject = new bibdkWork($openformat->formattedCollection->work);
      if( is_array($openformat->formattedCollection->manifestation) ) {
        foreach($openformat->formattedCollection->manifestation as $key=>$manifestation) {
          $entity_ids[] = $manifestation->adminData->pid->{'$'};
        }
      }
      elseif( isset($openformat->formattedCollection->manifestation) ) {
        $entity_ids[] = $openformat->formattedCollection->manifestation->adminData->pid->{'$'};
      }
     $manifestations = entity_load('ting_openformat_manifestation',$entity_ids,array(),TRUE);

     $bibdkobject->setManifestations($manifestations);
     $bibdkobjects[] = $bibdkobject;
    }
  }
  unset($result->collections);
  $result->collections = $bibdkobjects;
}


/**** TODO this method needs to handle bibdkObject and NOT formattedCollections ******/

/** \brief Set a search result array as defined for hook_search_execute
 *
    'link': Required. The URL of the found item.
    'type': The type of item (such as the content type).
    'title': Required. The name of the item.
    'user': The author of the item.
    'date': A timestamp when the item was last modified.
    'extra': An array of optional extra information items.
    'snippet': An excerpt or preview to show with the result (can be generated with search_excerpt()).
    'language': Language code for the item (usually two characters).

 **/

function _ting_openformat_set_search_result($bibdkobject) {

  $variables['results'] = array($bibdkobject);

  //************** TODO handle bibdkobject *************/

  $result = array(
    'link' => 'HEST',
    'type' => '',
    // 'title' => $formattedCollection->formattedCollection->work->title->titleFull->{'$'},
    'title' => 'HEST',
    'user' => '',
    'date' => '',
    //snippet' => '<div style="color:red; font-size:3em">TESTHEST</div>',
     'snippet' => theme('ting_openformat_search_results', $variables),
  );
  return $result;
}

/** \brief theming function for ting_openformat_searchresults_view
 *
 **/

/** \brief set facet for search result. Look in cache if not found do a request and set cache
 * @param $client - search_client
 * @param $params - parameters for searchrequest
 * @param $result - search result
 *
 * @return nothing, but sets facet for $result-object given as parameter
 **/
function _ting_openformat_facet_cache($client,$result, $params) {
  // check facets; get from cache if set - else do zero search to get facets
  $local_cache_key = 'facets-'.$result->cacheKey;
  if( !$facets = cache_get($local_cache_key) ) {
    // default facets
    if( module_exists('ding_facetbrowser') ) {
      $facets = _ting_openformat_set_default_facets();
    }
    if( isset($facets) ) {
      $params['facets'] = $facets;
      $params['numFacets'] = variable_get('ding_facetbrowser_number_shown',25);
    }

    // do a zero search to get the facets
    $params['numResults'] = 0;
    $facet_result = $client->do_search($params);
    if( isset($facet_result->facets) ) {
      $result->facets = $facet_result->facets;
      cache_set($local_cache_key, $facet_result->facets, 'cache', CACHE_TEMPORARY);
    }
  }
  // facets was found in cache
  else{
    $result->facets = cache_get($local_cache_key)->data;
  }
}

/** \brief get facets from variables
 * return array (facets)
 **/
function _ting_openformat_set_default_facets() {
  foreach (variable_get('ding_facetbrowser_facets', array()) as $facet) {
    $facets[] = $facet['name'];
  }
  return $facets;
}

/** \brief get variables and set corresponding search parameters
 * @param $conditions array with parameters set in _REQUEST
 **/
function _ting_openformat_search_get_variables($conditions) {
  // page number (opensearch::start)
  $page = pager_find_page();
  $params['start'] = $page;

  // results pr. page (opensearch::stepValue) ... in ting-client/lib/request/TingClientSearchRequest.php this is called numResults
  $resultsPerPage = variable_get('ting_search_results_per_page', 10);
  // if size is set; - override
  if (!empty($conditions['size'])) {
    $resultsPerPage = $conditions['size'];
  }
  $params['numResults'] = $resultsPerPage;

  // search profile (opensearch::profile)
  $params['profile'] =  variable_get('ting_search_profile', FALSE);
  if( !($params['profile']) ) {
    watchdog('openformat search','search profile is not set - yields no search results',array(),WATCHDOG_ERROR,url('admin/config/ting/settings'));
  }

  // agency (opensearch::agency)
  $params['agency'] = variable_get('ting_agency');
  if( !($params['agency']) ) {
    watchdog('openformat search','agency is not set - yields no search results',array(),WATCHDOG_ERROR,url('admin/config/ting/settings'));
  }

  // objectformat (opensearch::objectFormat)
  $params['objectFormat'] = variable_get('ting_search_openformat','dkabm');

  return $params;
}

/** \brief Set facets for request
 *
 **/
function _ting_openformat_set_facets(&$query,$facets) {
  if (isset($facets) ) {
    foreach ($facets as $facet) {
      $facet = explode(':', $facet, 2);
      if ($facet[0]) {
        $facetArray[] = $facet[0] . '="' . rawurldecode($facet[1]) . '"';
      }
    }
    $query .= ' AND ' . implode(' AND ', $facetArray);
  }
}

/**
 * Search conditions callback.
 */
function ting_openformat_conditions_callback($keys) {
  $conditions = array();

  if (!empty($_REQUEST['keys'])) {
    $conditions['keys'] = check_plain($_REQUEST['keys']);
  }

  if (!empty($_REQUEST['size'])) {
    $conditions['size'] = (int)$_REQUEST['size'];
  }


  if (!empty($_REQUEST['sort'])) {
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
        $facets['facets'][] =  $facet;
      }
      drupal_goto(rawurldecode($_GET['q']), array('query' => $facets));
    }
  }
  return $conditions;
}