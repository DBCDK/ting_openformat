<?php

/**
 * @file theme.inc load theme hooks
 **/




/**
 * Implements hook_theme().
 */
function ting_openformat_theme() {
  return array(
    'ting_openformat_search_results' => array(
      'variables' => array('content'=>array(),'work'=>array(), 'manifestations'=>array()),
      //'file'      => 'ting_openformat.search_pages.inc',
      'template'  => 'ting_openformat_search_results',
      'render element' => 'elements',
    ),
    'ting_openformat_search_mini_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),
    'ting_openformat_search_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),
    'ting_openformat_searchresults_view' => array(
      'variables' => array('results' => NULL, 'module'=>NULL),
      'template' => 'ting_openformat_searchresults_view',
    ),
    /*    'ting_search_display_extended_query' => array(
          'variables' => array('query_label'=>NULL,'query_string' => NULL),
          'template' => 'ting-search-display-extended-query',
          ),
          'ting_search_extended_search' => array(
          'template' => 'ting-search-extended-search',
          ),*/
  );
}

