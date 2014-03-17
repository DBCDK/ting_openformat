<?php

/**
 * @file theme.inc load theme hooks
 **/

/**
 * Implements hook_theme().
 */
function ting_openformat_theme() {
  $path = drupal_get_path('module', 'ting_openformat') . '/theme';
  return array(
    'ting_openformat_search_results' => array(
      'path' => $path,
      'variables' => array(
        'content' => array(),
        'work' => array(),
        'manifestations' => array()
      ),
      //'file'      => 'ting_openformat.search_pages.inc',
      'template'  => 'ting_openformat_search_results',
    ),
    'ting_openformat_manifestation' => array(
      'path' => $path,
      'variables' => array(
        'fields' => array(),
        'view_mode' => 'full',
        'id' => 0,
        'actions' => array()
      ),
      'template' => 'ting_openformat_manifestation',
    ),

    'ting_openformat_work' => array(
      'path' => $path,
      'variables' => array(
        'fields' => array(),
        'cover' => '',
        'work_tabs' => '',
        'tabs' => '',
        'subWorks' => array(),
        'ding_id' => 0,
      ),
      'template' => 'ting_openformat_work',
    ),

    'ting_openformat_toggle_work' => array(
      'path' => $path,
      'variables' => array(
        'uid' => '',
        'showinfo' => '',
        'full_view' => FALSE,
      ),
      'template' => 'ting_openformat_toggle_work',
    ),

    'ting_openformat_work_info' => array(
      'path' => $path,
      'variables' => array(
        'info' => array(),
      ),
      'template' => 'ting_openformat_work_info',
    ),

    'ting_openformat_collection' => array(
      'path' => $path,
      'variables' => array(
        'title' => '',
        'author' => '',
        'ids' => '',
        'work_type' => '',
        'type' => '',
        'togglework' => '',
        'work_one' => '',
      ),
      'template' => 'ting_openformat_collection',
    ),

    'ting_openformat_collection_actions' => array(
      'path' => $path,
      'variables' => array(
        'types' => array(),
      ),
      'template' => 'ting_openformat_collection_actions',
    ),

    'ting_openformat_subwork' => array(
      'path' => $path,
      'variables' => array(
        'manifestations' => array(),
        'id' => 0,
      ),
      'template' => 'ting_openformat_subwork',
    ),

    'ting_openformat_subwork_tabs' => array(
      'path' => $path,
      'variables' => array(
        'subWorks' => array(),
      ),
      'template' => 'ting_openformat_subwork_tabs',
    ),
    'ting_openformat_single_work' => array(
      'path' => $path,
      'variables' => array(
        'title' => '',
        'author' => '',
        'ids' => '',
        'work' => '',
        'uid' => '',
      ),
      'template' => 'ting_openformat_single_work',
    ),
    'ting_openformat_type_order_form' => array(
      'render element' => 'form',
      'file' => 'ting_openformat.admin.inc',
    ),

    'ting_openformat_type_order_element' => array(
      'render element' => 'element',
      'file' => 'ting_openformat.admin.inc',
    ),

    'ting_openformat_more_info' => array(
      'path' => $path,
      'variables' => array(
        'showinfoform' => '',
      ),
      'template' => 'ting_openformat_more_info',
    ),
    
    'ting_openformat_rss_feed' => array(
      'path' => $path,
      'varriables' => array(
        'item' => array(),
        'title' => '',
        'description' => '',
        'link' => '',
      ),
      'template' => 'ting_openformat_rss_feed',
    )
  );
}
