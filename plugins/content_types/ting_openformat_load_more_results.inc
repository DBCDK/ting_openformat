<?php

$plugin = array(
  'title' => t('Openformat Search - \'Load more collections\' link', array(), array('context' => 'ting_openformat')),
  'admin info' => 'ting_openformat_load_more_results_admin_info', // A function that will return the information displayed on the admin screen (optional).
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
  $results_per_page = variable_get('ting_search_results_per_page', 10);

  if ($count = _ting_openformat_get_search_result_count($panel_args, $results_per_page)) {
    $pages_count = ceil($count / $results_per_page);

    $start = isset($_GET['page']) ? $_GET['page'] : 2;

    drupal_add_js(drupal_get_path('module', 'ting_openformat') . '/js/ting_openformat_load_more_results.js', 'file');
    drupal_add_js(array(
        'ting_openformat_load_more_results' => array(
          'pages' => $pages_count,
          'start' => $start,
          'loadingIsActive' => FALSE,
        )
      ),
      'setting');

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
 * Finds the result count for the current search and returns the number of pages.
 * If the count is below 10 FLASE is returned as no more pages than the one
 * already being displayed should be loaded.
 *
 * @param $panel_args array
 * @param $results_per_page int
 * @return bool | string
 */
function _ting_openformat_get_search_result_count($panel_args, $results_per_page) {
  $query = $panel_args[0];
  $count = isset($_SESSION['searches'][$query]['count']) ? $_SESSION['searches'][$query]['count'] : NULL;

  if ($count && ($count - $results_per_page) >= 1) {
    return $count;
  }
  return FALSE;
}

function ting_openformat_load_more_results_ajax_callback() {
  if (empty($_GET['keys'])) {
    $commands[] = ajax_command_alert(t('No search keys provided and the search request can not be completed. Try make your search again from the beginning.', array(), array('context' => 'ting_openformat:error')));
    ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
    exit(0);
  }

  $keys = $_GET['keys'];
  unset($_GET['keys']);

  $unwanted_keyes = array('page_id', 'page', 'q');

  foreach ($_GET as $key => $value) {
    if (!in_array($key, $unwanted_keyes)) {
      $conditions[$key] = $value;
    }
  }

  module_load_include('inc', 'ting_openformat', 'ting_openformat.search');

  $results = ting_openformat_search_execute($keys, $conditions);

  $id = 'load-more-results-' . $_GET['page'];
  $html = '<div class="load_more_res_splitter" id="' . $id . '" > </div>';

  $html .= _ting_openformat_get_search_result_html($results);

  $commands[] = ajax_command_append('.ting_openformat-results', $html);

  $commands[] = _ting_openformat_get_add_more_results_data($id, $html);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
  exit(0);
}

function _ting_openformat_get_search_result_html($results){
  $html = '';
  foreach ($results as $result) {
    $html .= $result['snippet'];
  }
  return $html;
}

function _ting_openformat_get_add_more_results_data($id = NULL, $html = NULL){
  return array(
    'command' => 'add_more_results',
    'data' => array(
      'anchor' => $id,
    ),
  );
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