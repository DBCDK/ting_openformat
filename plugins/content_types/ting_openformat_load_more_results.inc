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
  dpm(func_get_args(), 'ting_openformat_load_more_results_link');

  $block = new stdClass();
  $block->content = 'hest';

  return $block;
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