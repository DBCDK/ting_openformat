<?php

/**
 * return a search_client configuration form :
 * set name on search tab
 * disable/enable cache
 **/
function ting_openformat_client_admin_form($form_state) {
  $form = array();

  $form['openformat']['search_client_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Search client tab name'),
    '#default_value' => variable_get('search_client_name', 'HEST'),
  );

  $form['openformat']['search_client_enable_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable cache'),
    '#description' => t('Cache searchresults - very nice while testing, but might stress the system in production' ),
    '#default_value' => variable_get('search_client_enable_cache', FALSE),
  );

  $form['#submit'] = array('ting_openformat_client_admin_form_submit');

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * submit handler for search_client_admin_form
 **/
function ting_openformat_client_admin_form_submit($form, $form_state) {
  variable_set('search_client_name', $form_state['values']['search_client_name']);
  variable_set('search_client_enable_cache',  $form_state['values']['search_client_enable_cache']);
  // rebuild menu
  menu_rebuild();
  drupal_set_message(t('The changes has been saved'));
}

/**
 * Implements hook_form_FORMID_alter (ting_admin_ting_settings @see ting.admin.inc).
 * make openformat a dropdownlist.
 * add bibliotekdkWorkDisplay to ting_admin form
 */
function ting_openformat_form_ting_admin_ting_settings_alter (&$form, &$form_state) {
  if( isset ($form['ting']['ting_search_openformat'] ) ) {
    $dkabm = $form['ting']['ting_search_openformat']['#default_value'];
    $element = &$form['ting']['ting_search_openformat'];
    // change type to select
    $element['#type'] = 'select';
    // set the original option (dkabm)
    $element['#options']['dkabm'] = 'dkabm';
    // add bibliotekdkWorkDisplay to options
    $element['#options']['bibliotekdkWorkDisplay'] = 'bibliotekdkWorkDisplay';
    // set default value
    //$form['ting']['ting_search_openformat']['#default_value'] = 'bibliotekdkWorkDisplay';
  }
}
