<?php
/**
 * Created by IntelliJ IDEA.
 * User: pjo
 * Date: 5/26/14
 * Time: 5:07 PM
 */

$plugin = array(
  'title' => t('Openformat Search - \'pager\' link', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_pager_admin',
  'single' => TRUE,
  'content_types' => array('ting_openformat_pager'),
  'render callback' => 'ting_openformat_pager',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

function ting_openformat_pager($subtype, $conf, $panel_args, $context) {
  // get search results
  if ($results = drupal_static('ting_search_results')) {
    // initialize pager
    pager_default_initialize($results->numTotalObjects, 10);
    // get current pagenumber
    $page_no = pager_find_page();

    $block = new stdClass();

    if ($page_no > 1) {
      $block->content['first'] = array(
        '#theme' => 'pager_first',
        '#prefix' => '<span class="bibdk-pager-first">',
        '#suffix' => '</span>',
      );
    }

    if ($page_no > 0) {
      $block->content['prev'] = array(
        '#theme' => 'pager_previous',
        '#prefix' => '<span class="bibdk-pager-previous">',
        '#suffix' => '</span>',
      );
    }

    if ($results->more) {
      $block->content['next'] = array(
        '#theme' => 'pager_next',
        '#prefix' => '<span class="bibdk-pager-next">',
        '#suffix' => '</span>',
      );
    }

    return $block;
  }

}

