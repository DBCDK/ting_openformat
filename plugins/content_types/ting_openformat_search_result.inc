<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
if (module_exists('search')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'title' => t('Openformat search - Search results'),
    #'icon' => 'icon_search.png',
    'description' => t('The results of a search using keywords.'),
    'required context' => new ctools_context_required(t('Keywords'), 'string'),
    'category' => t('Openformat'),
    'content_types' => array('ting_openformat_search_result'),
    'defaults' => array(
      'type' => 'ting_openformat',
      'log' => TRUE,
      'override_empty' => FALSE,
      'empty_title' => '',
      'empty' => '',
      'empty_format' => filter_fallback_format(),
      'override_no_key' => FALSE,
      'no_key_title' => '',
      'no_key' => '',
      'no_key_format' => filter_fallback_format(),
    ),
  );
}

/**
 * Render the custom content type.
 */
function ting_openformat_ting_openformat_search_result_content_type_render($subtype, $conf, $args, $pane_context, $incoming_content) {
  $search_info = search_get_info();
  /* if (empty($search_info[$conf['type']])) {
    return;
    }*/
  $info = $search_info['ting_openformat'];

  $keys = NULL;
  if (!empty($pane_context) && isset($pane_context->data)) {
    $keys = $pane_context->data;
  }

  $conditions =  NULL;
  if (isset($info['conditions_callback']) && function_exists($info['conditions_callback'])) {
    // Build an optional array of more search conditions.
    $conditions = $info['conditions_callback']($keys);
  }
  $search_result=search_data($keys, $info['module'], $conditions);

  $output = "<ol class=\"search-results $conf[type]-results\">\n";
  if( isset($search_result['#results']) ) {
    foreach ($search_result['#results'] as $result) {    // $build = ting_collection_view($collection, 'teaser');
      $output .= theme('search_result', array('result' => $result, 'module' => $conf['type']));
    }
  }
  $output .= "</ol>\n";
  // $output .= theme('ting_search_pager', array('tags' => NULL,));

  $block->title = t('Search results');
  $block->content = $output;

  return $block;
}