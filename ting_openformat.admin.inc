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
    '#description' => t('overall caching - very nice while testing, but might stress the system in production.
    disable this if you wish NO caching for any webservices'),
    '#default_value' => variable_get('search_client_enable_cache', FALSE),
  );


  $cache_classes =  ting_client_class::get_all_cache_classes();
  // suffixes to use for variables
  $cache_lifetime = TingClientRequest::$cache_lifetime;
  $cache_enable = TingClientRequest::$cache_enable;

  // make cache configuration foreach request that implements ITingClientRequestCache
  foreach( $cache_classes as $cache_class ) {
    $element_name = $cache_class['element_name'];
    $form['openformat'][$element_name] = array(
      '#type' => 'fieldset',
      '#title' => $element_name,
    );

     $form['openformat'][$element_name][$element_name.$cache_enable] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable cache'),
    '#description' => t('Enable cache for this type of request' ),
    '#default_value' => variable_get($element_name.$cache_enable, FALSE),
  );

    $form['openformat'][$element_name][$element_name.$cache_lifetime] = array(
      '#type' => 'textfield',
      '#title' => t('Cache lifetime'),
      '#description' => t('For how many minutes do you wish to cache results'),
      '#default_value' => variable_get($element_name.$cache_lifetime,'10'),
    );
  }

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

  $cache_classes =  ting_client_class::get_all_cache_classes();
  // suffixes for variables
  $cache_lifetime = TingClientRequest::$cache_lifetime;
  $cache_enable = TingClientRequest::$cache_enable;

  foreach( $form_state['values'] as $key => $val ) {
    if( strpos($key, $cache_lifetime) || strpos($key, $cache_enable ) ) {
      variable_set($key, $val);
    }
  }

  // overall caching
  variable_set('search_client_name', $form_state['values']['search_client_name']);
  variable_set('search_client_enable_cache',  $form_state['values']['search_client_enable_cache']);
  // rebuild menu to show search_client_name on search-tab
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
