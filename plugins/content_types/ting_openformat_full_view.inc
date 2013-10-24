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


  $content['short'] = array(
    '#theme' => 'link',
    '#text' => ' <span class="icon full-view closed"> </span> ' . t('short view', array(), array('context' => 'ting_openformat')),
    '#path' => NULL,
    '#options' => array(
      'html' => TRUE,
      'fragment' => 'full-view',
      'external' => TRUE,
      'attributes' => array(
        'id' => 'ting-openformat-full-view-button-closed',
        'class' => 'inactive',

      ),
    ),
  );

  $content['full'] = array(
    '#theme' => 'link',
    '#text' => '<span class="icon full-view expanded"> </span> ' . t('full view', array(), array('context' => 'ting_openformat')),
    '#path' => NULL,
    '#options' => array(
      'html' => TRUE,
      'fragment' => 'full-view',
      'external' => TRUE,
      'attributes' => array(
        'id' => 'ting-openformat-full-view-button-expanded'
      ),
    ),
  );


  $block->content = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => drupal_render($content),
    '#attributes' => array(
      'class' => 'full-view-links'
    ),
  );

  return $block;

}

function ting_openformat_full_view_admin() {

}
