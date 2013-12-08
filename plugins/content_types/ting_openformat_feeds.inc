<?php

$plugin = array(
  'title' => t('Openformat Search - \'feed\' link', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_feeds_admin',
  'single' => TRUE,
  'content_types' => array('ting_openformat_feeds'),
  'render callback' => 'ting_openformat_feeds_link',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

function ting_openformat_feeds_link($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $url = 'http://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
  //check if request parameters are set
  $params_not_set = strpos($url, '?') === FALSE;
  
  if ($params_not_set){
    $url .= '?feed_me=1';
  }
  else{
    $url .= '&feed_me=1';
  }
  
  $feeds = drupal_add_feed($url, t('Search feed',array(), array('context'=>'feeds')));

  $block->content = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => $feeds[$url],
    '#attributes' => array(
      'class' => 'ting-openformat-feeds'
    ),
  );
  return $block;
}

