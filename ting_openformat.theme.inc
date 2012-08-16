<?php

/**
 * @file theme.inc load theme hooks
 **/




/**
 * Implements hook_theme().
 */
function ting_openformat_theme() {
  $path = drupal_get_path('module', 'ting_openformat') . '/theme';
  return array(
    'ting_openformat_search_results' => array(
      'path' => $path,
      'variables' => array('content'=>array(),'work'=>array(), 'manifestations'=>array()),
      //'file'      => 'ting_openformat.search_pages.inc',
      'template'  => 'ting_openformat_search_results',
      'render element' => 'elements',
    ),
    'ting_openformat_manifestation' => array(
      'path' => $path,
      'variables' => array('fields'=>array(),'id'=>0,),
      'template' => 'ting_openformat_manifestation',
      'render elements' => 'elements',
    ),

    'ting_openformat_work' => array(
      'path' => $path,
      'variables' => array('fields' => array(),'subWorks'=>array(),'ding_id' => 0,),
      'template' => 'ting_openformat_work',
      'render elements' => 'elements',
    ),

    'ting_openformat_subwork' => array(
      'path' => $path,
      'variables' => array('manifestations' => array(),'id'=>0),
      'template' => 'ting_openformat_subwork',
      'render elements' => 'elements',
    ),

    'ting_openformat_subwork_tabs' => array(
      'path' => $path,
      'variables' => array('subWorks' => array()),
      'template' => 'ting_openformat_subwork_tabs',
      'render elements' => 'elements',
    ),

    'ting_openformat_search_mini_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),
    'ting_openformat_search_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),
    /*    'ting_openformat_searchresults_view' => array(
      'variables' => array('results' => NULL, 'module'=>NULL),
      'template' => 'ting_openformat_searchresults_view',
      ),*/
    /*    'ting_search_display_extended_query' => array(
          'variables' => array('query_label'=>NULL,'query_string' => NULL),
          'template' => 'ting-search-display-extended-query',
          ),
          'ting_search_extended_search' => array(
          'template' => 'ting-search-extended-search',
          ),*/
  );
}

