<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */

function ting_openformat_field_info() {

  $field_default = array(
    'default_widget' => 'text_textfield',
    'default_formatter' => 'ting_openformat_default_formatter',
    'no_ui' => TRUE,
  );

  $fields_definitions = ting_openformat_bibdk_fields();

  foreach($fields_definitions as $name => $field){
    $fields[$name]['label'] = t($field['label']);
    $fields[$name]['description'] = $field['description'];
    $fields[$name]['default_widget'] = isset($field['default_widget']) ? $field['default_widget'] : $field_default['default_widget'];
    $fields[$name]['default_formatter'] = isset($field['default_formatter']) ? $field['default_formatter'] : $field_default['default_formatter'];
    $fields[$name]['no_ui'] = isset($field['no_ui']) ? $field['no_ui'] : $field_default['no_ui'];
  }

  return $fields;
}

/**
 * Implements hook_field_formatter_info
 * */
function ting_openformat_field_formatter_info() {
  $fields = ting_openformat_field_info();
  foreach ($fields as $field => $data) {
    $fieldtypes[$data['default_formatter']][] = $field;
  }
  return array(
    'ting_openformat_default_formatter' => array(
      'label' => t('Default'),
      'field types' => isset($fieldtypes['ting_openformat_default_formatter']) ? $fieldtypes['ting_openformat_default_formatter'] : NULL,
    ),
  );
}

/**
 * Implements hook_field_load()
 */
function ting_openformat_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_field_formatter_view
 * it is possible to extract values directly from bibdkWork->work or bibdkWork->manifestations, but it is preferable to
 * add a method to bibdkWork class e.g
 *
 * @see  ting_openformat.entities.inc::bibdkWork::getCreator().) ... there will be changes in format
 *
 * @param $entity_type
 * @param BibdkWork | Manifestation $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 * @return array
 * @see  ting_openformat.entities.inc
 */
function ting_openformat_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($field['field_name']) {

      case 'ting_openformat_mani_subjects':
      case 'ting_openformat_work_subjects':
        // one or more subjects
        $subjects = $entity->getSubjects();
        $value = _ting_openformat_get_markup_for_field($subjects, '; ', FALSE);
        break;
      case 'bibdk_mani_volume':
        $volume = $entity->getVolume();
        if (isset($volume)) {
          $volume_entity = entity_load('bibdkManifestationVolume', $entity->id, $volume);
          $element[$delta]['#markup'] = ting_openformat_volume_view($volume_entity, 'full', $langcode);
        }
        break;
      case 'bibdk_mani_section':
        $volume = $entity->getSection();
        if (isset($volume)) {
          $volume_entity = entity_load('bibdkManifestationSection', $entity->id, $volume);
          $element[$delta]['#markup'] = ting_openformat_section_view($volume_entity, 'full', $langcode);
        }
        break;
      // usedLanguage
      case 'bibdk_mani_used_language':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $usedLanguage = $entity->getUsedLanguage();
        $value = _ting_openformat_get_markup_for_field($usedLanguage, ". ");
        break;
      // contentPartialNote
      case 'bibdk_mani_content_partial_note':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $descriptionNote = $entity->getContentPartialNote();
        $value = _ting_openformat_get_markup_for_field($descriptionNote, "<br />");
        break;
      case 'bibdk_mani_infotext':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $infotext = $entity->getInfotext();
        $infotext = ($infotext) ? t('drupal_text_' . $infotext, array(), array('context' => 'bibdk_openformat')) : NULL;
        $value = _ting_openformat_get_markup_for_field($infotext);
        break;
      case 'bibdk_mani_analytic_content':
        $analytic = $entity->getAnalyticContent();
        $value = _ting_openformat_parse_analytic_content($analytic);
        break;
      default :
        $content = _ting_openformat_default_field_view_content($field['field_name'], $entity);
        $value = _ting_openformat_get_markup_for_field($content);
        break;
    }
    if (isset($value)) {
      $element[$delta] = $value;
    }
  }
  return $element;
}

/** Generic Helper function to get content elements for a speficic filed
 * @param $field_name
 * @param $entity
 * @return null
 */
function _ting_openformat_default_field_view_content($field_name, $entity){
  $value = null;
  $field_definitions = ting_openformat_bibdk_fields();
  if (isset($field_definitions[$field_name])){
    $field = $field_definitions[$field_name];
    $method = $field['callback method'];

    if(isset($method) && is_callable(array($entity, $method))){
      $value = $entity->$method();
    }
    else {
      throw new Exception(format_string('Method @method does not excist on object @object', array(
       '@method' => $method,
        '@object' => get_class($entity),
      )));
    }
  }
  return $value;
}

/**
 * @param $elements
 * @param string $divider
 * @param bool $use_header
 * @param bool $return_link If FALSE value will be returned without markup for href. Otherwise complete markup for href is returned
 * @return array|null
 */
function _ting_openformat_get_markup_for_field($elements, $divider = ", ", $use_header = TRUE, $return_link = TRUE) {
  $return = NULL;
  $markup = _ting_openformat_parse_element($elements, $divider, $use_header, $return_link);
  if (isset($markup)) {
    $return = array(
      '#markup' => $markup,
    );
  }
  return $return;
}

/**
 * Parses a field array from a manifestation/work entity. returns a string.
 * searchCode and header are specialcases what generates a field-label and a link
 *
 * @param array|string|null $elements
 * @param string $divider
 * @param bool $use_header
 * @param bool $return_link If FALSE value will be returned without markup for href. Otherwise complete markup for href is returned
 * @return string
 */
function _ting_openformat_parse_element($elements, $divider = ". ", $use_header = TRUE, $return_link = TRUE) {

  if (!isset($elements)) {
    return NULL;
  }
  if (!is_array($elements)) {
    $elements = array($elements);
  }

  foreach ($elements as $key => $value) {
    if (is_array($value)) {
      $array[] = _ting_openformat_parse_element($value, $divider, $use_header, $return_link);
    }
    elseif ($key === "header") {
      if ($use_header) {
        $header = $value;
      }
    }
    elseif ($key === 'searchCode') {
      if ($return_link) {
        $array[] = l($elements['display'], 'search/work/' . $elements['searchCode']);
      }
      else {
        $array[] = $elements['display'];
      }
    }
    elseif ($key === 'accessUrl') {
      $array[] = l($value, $value, array('attributes' => array('target' => '_blank')));
    }
    elseif ($key === 'display') { /*do nothing*/
    }
    else {
      $array[] = $value;
    }
  }
  $string = (isset($header)) ? $header . " " : "";
  if (isset($array)) {
    $string .= implode($divider, $array);
  }
  return $string;
}

/** Helper function to parse analytic content
 * @param $analytic_content
 * @return array|null
 */
function _ting_openformat_parse_analytic_content($analytic_content, $entity = NULL, $options = array()){
  if (!isset($analytic_content))
    return null;
  if (isset($analytic_content['analyticContent'][0])){
    $value['#markup'] = '';
    foreach ($analytic_content['analyticContent'][0] as $content){
      $element_values = array();
      $break = ' ; ';
      foreach ($content as $key => $element) {
        $element_markup = _ting_openformat_get_markup_for_field($element, " ");

        if ($key == 'analyticContributor'){
          $element_markup['#markup'] .= ":";
          $break = '<br />';
        }


        $element_values[] = $element_markup['#markup'];
      }

      $value['#markup'] .= implode(' ', $element_values) . $break;
    }

  }
  return $value;
}

//900 lines before refactoring
