<?php
/**
 * @file Panels block, that shows what content is filtered out.
 */

$plugin = array(
  'title' => t('Openformat Search - \'filter\' block', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_filter_admin',
  'single' => TRUE,
  'content_types' => array('ting_openformat_filter'),
  'render callback' => 'ting_openformat_filter_block',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/** Create block with filters
 * @param $subtype
 * @param $conf
 * @param $panel_args
 * @param $context
 * @return null|stdClass
 */
function ting_openformat_filter_block($subtype, $conf, $panel_args, $context) {


  $filters = module_invoke_all('ting_openformat_query_filter');

  if (empty($filters)) {

    return null;
  }

  foreach($filters as $key => $search_kode) {
    $labels[] = "<span data-search-code='$search_kode'>$key</span>";
  }

  $content['list'] = array(
    '#theme' => 'item_list',
    '#title' => t('This search filters out:') . '',
    '#items' => $labels,
    '#attributes' => array(
      'class' => array('ting_openformat_filter_list'),
    ),
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
