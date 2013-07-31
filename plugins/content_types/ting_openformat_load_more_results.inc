<?php

$plugin = array(
  'title' => t('Openformat Search - \'Load more collections\' link', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_load_more_results_admin_info', // A function that will return the information displayed on the admin screen (optional).
  'single' => TRUE,
  'content_types' => array('ting_openformat_load_more_results'),
  'render callback' => 'ting_openformat_load_more_results_link',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_openformat_load_more_results_link($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if(_ting_openformat_get_search_result_count($panel_args)){
    drupal_add_js(drupal_get_path('module', 'ting_openformat') . '/js/load_more.js');
    $block->content = l(t('load_more_results', array(), array('context' => 'ting_openformat')), '#', array(
      'attributes' => array(
        'class' => array(
          'hest',
        ),
      ),
    ));
  }

  return $block;
}

/**
 * Finds the result count for the current search and returns the number of pages.
 * If the count is below 10 FLASE is returned as no more pages than the one
 * already being displayed should be loaded.
 *
 * @param $panel_args
 * @return bool | string
 */
function _ting_openformat_get_search_result_count($panel_args){
  $query = $panel_args[0];
  $count = isset($_SESSION['searches'][$query]['count']) ? $_SESSION['searches'][$query]['count'] : NULL;
  if($count && $count >= 11) {
    return $count;
  }
  return FALSE;
}


/**
 * 'admin info' callback for panel pane.
 */
function ting_openformat_load_more_results_admin_info($subtype, $conf, $contexts) {
  $block = new stdClass;
  $block->title = t('Openformat Search - \'Load more collections\' link', array(), array('context' => 'ting_openformat'));
  $block->content = t('Link that when clicked loads 10 more collections to append', array(), array('context' => 'ting_openformat'));
  return $block;
}