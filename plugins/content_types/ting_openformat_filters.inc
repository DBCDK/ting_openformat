<?php


$plugin = array(
  'title' => t('Openformat Search - \'filter\' block', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_filter_admin',
  'single' => TRUE,
  'content_types' => array('ting_openformat_filter'),
  'render callback' => 'ting_openformat_filter_block',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

function ting_openformat_filter_block($subtype, $conf, $panel_args, $context) {


  $filters = module_invoke_all('ting_openformat_query_filter');

  if (empty($filters)) {

    return null;
  }

  $labels = array_keys($filters);


  $content['list'] = array(
    '#theme' => 'item_list',
    '#title' => t('This search filters out:') . '',
    '#items' => $labels,
  );

  global $user;

  $content['link'] = array(
    '#theme' => 'link',
    '#path' =>  'user/' . $user->uid . '/settings',
    '#text' => t('edit settings'),
    '#options' => array(
      'attributes' => array(),
      'html' => true,
    ),
  );

  $content = drupal_render($content);
  $block = new stdClass();
  $block->content = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => $content,
    '#attributes' => array(
    ),
  );

  return $block;

}

function ting_openformat_filter_admin() {

}
