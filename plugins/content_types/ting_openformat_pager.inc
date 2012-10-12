<?php

$plugin = array(
  'title' => t('Openformat search - pager'),
  'description' => t('Pager for Openformat search results'),
  'single' => TRUE,
  'content_types' => array('ting_openformat_pager'),
  'render callback' => 'ting_openformat_pager_content_type_render',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_openformat_pager_content_type_render($subtype, $conf, $panel_args, $context) {
  global $pager_page_array, $pager_total;
  $block = new stdClass();

  $block->title = t('Openformat search pager');
  $block->content = theme('ting_openformat_pager', array('tags' => NULL,));

  return $block;
}

/**
 * Enable admin settings page
 */
function ting_openformat_ting_openformat_pager_content_type_edit_form($form, &$form_state) {
  return $form;
}

