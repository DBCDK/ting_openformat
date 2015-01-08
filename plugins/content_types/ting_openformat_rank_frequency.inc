<?php

/**
 * Plugin definition of rank_frequency explanation box
 */
$plugin = array(
  'title' => t('Openformat Search - \'rank frequency\' explanation box', array(), array('context' => 'ting_openformat')),
  'content_types' => array('ting_openformat_rank_frequency'),
  'admin info' => 'ting_openformat_rank_frequency_admin_info',
  'single' => TRUE,
  'render callback' => 'ting_openformat_rank_frequency',
  'category' => 'Openformat',
  'render last' => TRUE,
);

/**
 * 'admin info' callback for panel pane.
 */
function ting_openformat_rank_frequency_admin_info($subtype, $conf, $contexts = NULL) {
}

/**
 * Content for the rank_frequency explanation box
 */
function ting_openformat_rank_frequency($subtype, $conf, $args, $context) {
  $sort = isset($_GET['sort']) ? $_GET['sort'] : '';
  $result = drupal_static('ting_search_results');
  $block = new stdClass();

  if ($result) {
    if ($sort == 'rank_frequency') {
      $rank_method = t($result->sortUsed, array(), array('content' => 'ting_openformat'));
      $block->content = t('You have used rank_frequency so you might be looking for @rank_method. Otherwise select another option in the dropdown above.', array('@rank_method' => $rank_method), array('context' => 'ting_openformat'));
    }
  }

  return $block;
}
