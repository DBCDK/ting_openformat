<?php

/**
 * @file
 * Hooks provided by the bibdk_gdpr module.
 */

/**
 * Implements hook_bibdk_gdpr_items().
 *
 * @return array
 */
function ting_openformat_bibdk_gdpr_items() {
  $items['ting_openformat']['#weight'] = 80;
  $items['ting_openformat']['#header'] = t('label_gdpr_ting_openformat_view', array(), array('context' => 'bibdk_gdpr'));
  $items['ting_openformat']['#theme'] = 'bibdk_gdpr_item_theme';
  $rows[] = array(
    '#type' => 'container',
    'label' => array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#value' => t('ting_openformat_fullview_usersetting', array(), array('context' => 'bibdk_gdpr'))
    ),
    'value' => array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#value' =>(bibdk_usersettings_user_settings_get('ting_openformat_fullview_usersetting', TRUE)) ?
        t('label_action_enabled', array(), array('context' => 'bibdk_gdpr')) :
        t('label_action_disabled', array(), array('context' => 'bibdk_gdpr'))
    ),
  );
  $items['ting_openformat']['#content'] = $rows;
  return $items;
}
