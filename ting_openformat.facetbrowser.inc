<?php

/**
 * @file
 * Code for ting_openformat facets
 */

/**
 * Implements hook_bibdk_facetbrowser().
 * initialize facetbrowser
 */
function ting_openformat_bibdk_facetbrowser() {
  $results = new stdClass();
  $results->show_empty = FALSE;
  $search_result = drupal_static('ting_search_results');

  if ($search_result) {
    $results->facets = ($search_result instanceof TingClientSearchResult) ? $search_result->facets : array();
    $results->searchkey = $search_result->search_key;

    return $results;
  }
}


/**
 * Set facets for search request
 * */
function _ting_openformat_set_facets(&$query, $facets) {

  if ( isset($facets) ) {

    // sort the facets
    $facets_temp = array();
    foreach ( $facets as $facet ) {
      $facet = explode(':', $facet, 2);
      if ( $facet[0] ) {
        $op = ( substr($facet[0], 0, 1) == '!' ) ? CQL_NOT : CQL_AND;
        if ( $op == CQL_NOT ) {
           $facet[0] = substr( $facet[0], 1);
        }
        $facet_val['val'] = rawurldecode($facet[1]);
        $facet_val['op'] = $op;
        $facets_temp[ $facet[0] ][] = $facet_val;
      }
    }

    foreach ( $facets_temp as $facet_name => $facet ) {
      $facet_not = array();
      $facet_or = array();
      foreach ( $facet as $item ) {
        if ( $item['op'] == CQL_NOT ) {
          $facet_not[] = $facet_name . '="' . rawurldecode($item['val']) . '"';
        }
        else {
          $facet_or[] = $facet_name . '="' . rawurldecode($item['val']) . '"';
        } 
      }
      if ( !empty($facet_not) ) {
        $facet_array_not[] = '(' . implode(CQL_OR, $facet_not) . ')';
      }
      if ( !empty($facet_or) ) {
        $facet_array_or[] = '(' . implode(CQL_OR, $facet_or) . ')';
      }
    }

    if ( !empty($query) ) {
      if ( !empty($facet_array_or) ) {
        $query .= CQL_AND . implode(CQL_AND, $facet_array_or);
      }
      if ( !empty($facet_array_not) ) {
        $query .= CQL_NOT . implode(CQL_NOT, $facet_array_not);
      }
    }
    else {
      if ( !empty($facet_array_or) ) {
        $query .= implode(CQL_AND, $facet_array_or);
      }
      if ( !empty($facet_array_not) ) {
        $query .= CQL_NOT . implode(CQL_NOT, $facet_array_not);
      }
    }

  }
}

/**
 * Get a single facetgroup from webservice and update cache.
 * @param $facet_name
 * @return bool|\stdClass|string
 */
function ting_openformat_get_facet_group($facet_name) {
  $result = new stdClass();
  $result->cacheKey = $_SESSION['latest_search']['cache_key'];
  $result->searchKey = $_SESSION['latest_search']['search_key'];
  $client = new ting_client_class();
  $params = $_SESSION['latest_search']['params'];
  // make sure facets are set
  _ting_openformat_facet_cache($client, $result, $params );
  // get current result
  $current_cache = drupal_static('ting_search_results');
  // set parameters to get the whole facetgroup
  $params['facets'] = array($facet_name);
  $params['numFacets'] = variable_get('bibdk_facetbrowser_number_requested', 25);
  // do a zero search to get the facets
  $params['numResults'] = 0;
  // use DKABM .. it is fastest
  $params['objectFormat'] = 'DKABM';
 // do the request
  $facet_result = $client->do_request('search', $params);
  // replace cached facetgroup
  $current_cache->facets[$facet_name] = $facet_result->facets[$facet_name];
  ting_openformat_do_set_facet_cache($current_cache);
  return $facet_result;
}

/**
 * Set facetcache.
 * @param $result
 */
function ting_openformat_do_set_facet_cache($result) {
  // do NOT cache empty facets
  if (empty($result->facets)) {
    return;
  }
  $local_cache_key = ting_openformat_get_facet_cachekey($result);
  cache_set($local_cache_key, $result->facets, 'cache', CACHE_TEMPORARY);
  drupal_static('ting_search_results', $result);
}


/**
 * Get a cachekey for the facets.
 * @param $result
 * @return string
 */
function ting_openformat_get_facet_cachekey($result) {
  $cache_key = 'facets-' . $_SESSION['latest_search']['search_key'];
  return $cache_key;
}
/**
 * Set facet for search result. Look in cache; if not found do a request and set cache
 * Returns nothing, but sets facet for $result-object given as parameter
 *
 * @param $client - search_client
 * @param $params - parameters for searchrequest
 * @param $result - search result
 * */
function _ting_openformat_facet_cache($client, $result, $params) {
  // check facets; get from cache if set - else do zero search to get facets
  $local_cache_key = ting_openformat_get_facet_cachekey($result);

  if (!$facets = cache_get($local_cache_key)) {
    // default facets
    if (module_exists('bibdk_facetbrowser')) {
      $facets = _ting_openformat_set_default_facets();
    }
    if (isset($facets)) {
      $params['facets'] = $facets;
      $params['numFacets'] = variable_get('bibdk_facetbrowser_number_shown', 25);
    }

    // do a zero search to get the facets
    $params['numResults'] = 0;
    // use DKABM .. it is fastest
    $params['objectFormat'] = 'DKABM';

    // pjo 080515 added FALSE to override configuration cache for search
    $facet_result = $client->do_request('search', $params);
    if (isset($facet_result->facets)) {
      $result->facets = $facet_result->facets;
      ting_openformat_do_set_facet_cache($result);
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
  foreach (variable_get('bibdk_facetbrowser_facets', array()) as $facet) {
    $facets[] = $facet['name'];
  }

  return $facets;
}

