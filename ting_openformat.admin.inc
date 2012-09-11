<?php

function ting_openformat_admin_module_disable($form_state) {
  $form = array();
  $form['#submit'] = array('ting_openformat_admin_module_disable_form_submit');

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Disable this module'),
  );

  return $form;
}

function ting_openformat_admin_module_disable_form_submit($form, $form_state) {

  // @TODO
  // 1. delete fields attached to ting_openformat module
  // 2. disable modules that had any fields attached
}


/**
 * Implements hook_form
 */
function ting_openformat_type_order_form($form) {
  
  $types = variable_get("ting_openformat_types", array());
  
  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from datawell'),
    '#description' => t('Update the list of known types by asking the datawell for all types.')
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_openformat_update_types'),
  );
  
  $form['types'] = array(
    '#tree' => TRUE
  ); 
  
  
  foreach ($types as $type) {
    
    
    $form['types'][$type['type']] = array(
      'name' => array('#markup' => $type['type']),
      'count' => array('#markup' => $type['count']),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight for @title', array('@title' => $type['type'])),
        '#title_display' => 'invisible',
        '#default_value' => $type['weight']
      )
    );
  }
  
 
  $form['types']['actions'] = array('#type' => 'actions');
  $form['types']['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'), "#submt"  => array('ting_openformat_type_order_submit'));

  return $form;
}


/**
 * 
 * implements hook_form_submit
 */
function ting_openformat_type_order_form_submit($form, $form_state){
  $types = variable_get("ting_openformat_types", array());
  $weight_values = $form_state['values']['types'];
  foreach ($types as $term => $value){
    $types[$term]['weight'] = $weight_values[$term]['weight'];
    $weight[$term] = $weight_values[$term]['weight'];
  }
  array_multisort($weight, SORT_ASC, $types);
  
  variable_set("ting_openformat_types", $types);
}

/**
 * 
 * submit function: Updates types from well
 */
function ting_openformat_update_types($form, $form_state){
  _ting_openformat_fetch_types();
}

/**
 * Implements theme_hook
 */
function theme_ting_openformat_type_order_form($variables) {
  $form = $variables['form'];
  $rows = array();
  $output = drupal_render($form['update']);
  foreach (element_children($form['types']) as $id) {
    $form['types'][$id]['weight']['#attributes']['class'] = array('ting-openformat-type-order-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['types'][$id]['name']),
        drupal_render($form['types'][$id]['count']),
        drupal_render($form['types'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }

  $header = array(t('Name'), t('Count'), t('Weight'));
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'ting-openformat-type-order')));
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('ting-openformat-type-order', 'order', 'sibling', 'ting-openformat-type-order-weight');
  

  return $output;
  
}
?>
