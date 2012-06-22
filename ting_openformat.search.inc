<?php

/**
 * Implements hook_search_info().
 */

function ting_openformat_search_info() {
  return array(
    'title' => t('Bibliotek.dk'),
    'path' => 'ting',
    'conditions_callback' => 'ting_openformat_conditions_callback',
  );
}
/**
 * implements hook_search_execute
 **/
function ting_openformat_search_execute() {
  return array();
}


function ting_openformat_conditions_callback($keys) {
  $conditions = array();

  if (!empty($_REQUEST['keys'])) {
    $conditions['keys'] = check_plain($_REQUEST['keys']);
  }

  if (!empty($_REQUEST['size'])) {
    $conditions['size'] = (int)$_REQUEST['size'];
  }


  if (!empty($_REQUEST['sort'])) {
    $conditions['sort'] = check_plain($_REQUEST['sort']);
  }

  // If facets is set, check if we have to remove any, if so,
  // reload the page.
  if (!empty($_REQUEST['facets'])) {
    $remove = array();
    $redirect = FALSE;
    foreach ($_REQUEST['facets'] as $key => $facet) {
      if (preg_match('/^-facet/', $facet)) {
        $remove[] = preg_replace('/^-/', '', $facet);
        $redirect = TRUE;
        unset($_REQUEST['facets'][$key]);
      }
    }

    foreach ($_REQUEST['facets'] as $key => $facet) {
      foreach ($remove as $rem) {
        if ($facet == $rem) {
          unset($_REQUEST['facets'][$key]);
          continue;
        }
      }
    }
    $conditions['facets'] = $_REQUEST['facets'];
    if ($redirect === TRUE) {
      $facets = array();
      foreach ($conditions['facets'] as $facet) {
        $facets['facets'][] =  $facet;
      }
      //   drupal_goto(rawurldecode($_GET['q']), array('query' => $facets));
    }
  }
  return $conditions;
}


