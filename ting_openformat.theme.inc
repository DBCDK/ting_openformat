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
        'subworks' => array(),
        'ding_id' => 0,
      ),
      'template' => 'ting_openformat_work',
    ),

    'ting_openformat_collection' => array(
      'path' => $path,
      'template' => 'ting_openformat_collection',
      'variables' => array(
        'title' => '',
        'author' => '',
        'part_of' => '',
        'uid' => '',
        'actions' => array(),
        'types' => '',
        'work' => '',
        'theme_attributes' => array(),
      ),
    ),
    'ting_openformat_type_order_form' => array(
      'render element' => 'form',
      'file' => 'ting_openformat.admin.inc',
    ),

    'ting_openformat_type_order_element' => array(
      'render element' => 'element',
      'file' => 'ting_openformat.admin.inc',
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
    ),
    'ting_openformat_toggle_more_content' => array(
      'path' => $path,
      'varriables' => array(
        'trimmed_text' => '',
        'more_text' => '',
      ),
      'template' => 'ting_openformat_toggle_more_content',
    ),
    'ting_openformat_toggle_link' => array(
      'render elements' => 'element',
      'variables' => array(
        'icon' => '',
        'show' => '',
        'hide' => '',
        'attributes' => array(),
      ),
    ),
  );
}

/**
 * Implements theme_HOOK().
 * Renders a toggle link with an icon, a show text and a hide text.
 *
 * @param $variables
 * @return string
 */
function theme_ting_openformat_toggle_link($variables) {
  // Set the default theme class
  if(!isset($variables['attributes']['class'])) {
    $variables['attributes']['class'] = array();
  }
  $variables['attributes']['class'][] = 'ting-openformat-toggle-link';

  $toggle[] = array(
    '#theme' => 'html_tag',
    '#tag' => 'span',
    '#value' => '&nbsp;',
    '#attributes' =>  array(
    'class' => array('toggle-link-icon') + array($variables['icon']))
  );
  $toggle[] = array(
    '#theme' => 'html_tag',
    '#tag' => 'span',
    '#value' => $variables['show'],
    '#attributes' =>  array(
    'class' => array('toggle-text'))
  );
  $toggle[] = array(
    '#theme' => 'html_tag',
    '#tag' => 'span',
    '#value' => $variables['hide'],
    '#attributes' =>  array(
    'class' => array('toggle-text', 'toggle-hide'))
  );
  $options = array(
    'html' => TRUE,
    'fragment' => 'toggle-link',
    'external' => TRUE,
    'attributes' => $variables['attributes'] + array('data-toggle-link' => TRUE),
  );

  return l(drupal_render($toggle), '', $options);
}
