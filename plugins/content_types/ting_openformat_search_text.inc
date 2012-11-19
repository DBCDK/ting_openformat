<?php

$plugin = array(
  'title' => t('Openformat search - search results text'),
  'description' => t('Show a string with \'Showing x - y of z results'),
  'single' => TRUE,
  'content_types' => array('ting_search_text'),
  'render callback' => 'ting_openformat_search_content_type_render',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_openformat_search_content_type_render($subtype, $conf, $panel_args, $context) {
  global $pager_page_array, $pager_total;
  $block = new stdClass();

  if ($pager_total[0] == TRUE) {
    $results = drupal_static('ting_search_results');
    $total = $results->numTotalObjects;
    $block->title = t('Search results text');
    $block->content = '<div class="ting-openformat-search-amount-block">' . format_plural(
      $total,
      '1 result',
      '@count results', array()) . '</div>';
  }
  return $block;
}

/**
 * Enable admin settings page
 */
function ting_openformat_ting_openformat_search_text_content_type_edit_form($form, &$form_state) {
  return $form;
}

