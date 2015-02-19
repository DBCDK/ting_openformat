<?php


$plugin = array(
  'title' => t('Openformat Search - \'full view\' button', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_full_view_admin',
  'single' => TRUE,
  'content_types' => array('ting_openformat_full_view'),
  'render callback' => 'ting_openformat_full_view_button',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

function ting_openformat_full_view_button($subtype, $conf, $panel_args, $context) {

  $block = new stdClass();

  $content = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('full-view-links'),
    ),
  );

  $short_view_text = t('short view', array(), array('context' => 'ting_openformat'));
  $content['short'] = array(
    '#theme' => 'link_with_svg',
    '#text' => $short_view_text,
    '#path' => NULL,
    '#options' => array(
      'html' => TRUE,
      'fragment' => 'full-view',
      'external' => TRUE,
      'attributes' => array(
        'id' => 'ting-openformat-full-view-button-closed',
        'class' => (!$_SESSION['search_settings']['full_view']) ? 'inactive' : '',
        'title' => $short_view_text,
      ),
    ),
    '#svg' => 'svg-view-list',
  );

  $full_view_text = t('full view', array(), array('context' => 'ting_openformat'));
  $content['full'] = array(
    '#theme' => 'link_with_svg',
    '#text' => $full_view_text,
    '#path' => NULL,
    '#options' => array(
      'html' => TRUE,
      'fragment' => 'full-view',
      'external' => TRUE,
      'attributes' => array(
        'id' => 'ting-openformat-full-view-button-expanded',
        'class' => ($_SESSION['search_settings']['full_view']) ? 'inactive' : '',
        'title' => $full_view_text,
      ),
    ),
    '#svg' => 'svg-view-details',
  );

  $block->content = $content;

  return $block;

}

function ting_openformat_full_view_admin() {

}
