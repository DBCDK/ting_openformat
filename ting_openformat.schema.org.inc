<?php

/* * ******** NOTES *************** */
/*
 */
/* * ******** END NOTES ********** */


function log_to_file($text) {
  $f = fopen('/home/jgn/jgn.ding/sites/default/files/log.txt', 'a');
  fwrite($f, date('Ymd H:i:s - ') . print_r($text,1) . "\n");
  fclose($f);
}

/**
 * Implements hook_field_attach_view_alter().
 */
function ting_openformat_field_attach_view_alter(&$output, $context) {
  if ( $context['entity_type'] == 'bibdkManifestation' ) {
    // dpm(__FUNCTION__);
    // dpm($output);
    // dpm($context);
  }
}

/**
 * Implements hook_field_display_alter().
 */
function ting_openformat_field_display_alter(&$output, $context) {
  // static $hit = 0;
  // if ( $hit < 5) {
  //   dpm(__FUNCTION__);
  //   dpm($output);
  //   dpm($context);
  // }
  // $hit++;
}









/**
 * Implements hook_field_widget_form_alter().
 */
function ting_openformat_field_widget_form_alter(&$output, $context) {
  // log_to_file(__FUNCTION__);
  // log_to_file($context);
  // log_to_file($output);
}

/**
 * Implements hook_field_prepare_view().
 */
function ting_openformat_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
  // dpm(__FUNCTION__);
  // dpm($entity_type);
  // dpm($entities);
  // dpm($field);
  // dpm($instances);
  // dpm($langcode);
  // dpm($items);
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function ting_field_formatter_prepare_view(&$vars) {
  // dpm(__FUNCTION__);
  // log_to_file($vars);
  // log_to_file($output);
}


