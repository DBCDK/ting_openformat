<?php

$plugin = array(
  'title' => t('Openformat Search - \'Load more collections\' link', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_load_more_results_admin_info',
  'single' => TRUE,
  'content_types' => array('ting_openformat_load_more_results'),
  'render callback' => 'ting_openformat_load_more_results_link',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_openformat_load_more_results_link($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $result = drupal_static('ting_search_results');
  $more = isset($result->more) ? $result->more : NULL;

  if ($more) {

    $start = isset($_GET['page']) ? $_GET['page'] : 1;

    drupal_add_js(drupal_get_path('module', 'ting_openformat') . '/js/ting_openformat_load_more_results.js', 'file');
    drupal_add_js(array(
      'ting_openformat_load_more_results' => array(
        'more' => $more,
        'start' => $start,
        'loadingIsActive' => FALSE,
        'firstLoad' => TRUE,
      )
        ), 'setting');

    $block->content = l(t('load_more_results', array(), array('context' => 'ting_openformat')), '#', array(
      'attributes' => array(
        'id' => array(
          'link'
        ),
        'class' => array(),
      ),
        ));
  }

  return $block;
}

/**
 * Callback method handling the AJAX callback from
 * ting_openformat_load_more_results.js.
 * Executes a search with same parameters as the previous search, but requests
 * the next 10 works and returns to the js-script that appends it to the
 * existing display.
 */
function ting_openformat_load_more_results_ajax_callback() {
  if (isset($_GET['keys'])) {
    if (!empty($_GET['keys'])) {
      $keys = $_GET['keys'];
    }
    unset($_GET['keys']);
  }

  $unwanted_keyes = array('page_id', 'page', 'q', 'req');

  foreach ($_GET as $key => $value) {
    if (!in_array($key, $unwanted_keyes)) {
      $conditions[$key] = $value;
    }
  }

  module_load_include('inc', 'ting_openformat', 'ting_openformat.search');
  $results = ting_openformat_search_execute($keys, $conditions);

  $more = isset($results['more']) ? $results['more'] : FALSE;

  $id = 'load-more-results-' . $_GET['page'];
  $html = '<div class="load_more_res_splitter" id="' . $id . '" > </div>';

  $html .= _ting_openformat_get_search_result_html($results);

  $commands[] = ajax_command_append('.ting_openformat-results', $html);
  $commands[] = array(
    'command' => 'add_more_results',
    'data' => array(
      'anchor' => $id,
      'more' => $more,
    ),
  );

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
  exit(0);
}

/**
 * Extract the HTML formatted string from results array and concatenates it
 * into a single string and returns that string
 *
 * @param $results
 * @return string
 */
function _ting_openformat_get_search_result_html($results) {
  $html = '';
  foreach ($results as $result) {
    if (isset($result['snippet'])) {
      $html .= $result['snippet'];
    }
  }
  return $html;
}

/**
 * 'admin info' callback for panel pane.
 */
function ting_openformat_load_more_results_admin_info($subtype, $conf, $contexts) {
  $block = new stdClass;
  $block->title = t('Openformat Search - \'Load more collections\' link', array(), array('context' => 'ting_openformat'));
  $block->content = t('Link that when clicked loads 10 more collections to append', array(), array('context' => 'ting_openformat'));
  return $block;
}