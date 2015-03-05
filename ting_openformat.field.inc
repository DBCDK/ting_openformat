<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 * @return array
 */
function ting_openformat_field_info() {

  $field_default = array(
    'default_widget' => 'text_textfield',
    'default_formatter' => 'ting_openformat_default_formatter',
    'no_ui' => TRUE,
  );

  $fields_definitions = ting_openformat_bibdk_fields();
  $fields = array();
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
      case 'bibdk_mani_creators':
        $content = _ting_openformat_default_field_view_content($field['field_name'], $entity);
        $value = _ting_openformat_get_markup_for_field($content, "<br />");
        break;
      case 'bibdk_mani_volume':
        $volume = $entity->getVolume();
        if (isset($volume)) {
          $entity = entity_load('bibdkManifestationVolume', $entity->id, $volume);
          $value = _prepare_view('bibdkManifestationVolume', $entity, 'full', $langcode);
        }
        break;
      case 'bibdk_mani_section':
        $volume = $entity->getSection();
        if (isset($volume)) {
          $entity = entity_load('bibdkManifestationSection', $entity->id, $volume);
          $value = _prepare_view('bibdkManifestationSection', $entity, 'full', $langcode);
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
      case 'bibdk_mani_access_information':
        $urls = $entity->getAccessInformation();
        $value = _ting_openformat_get_markup_for_field($urls, '<br/>');
        break;
      case 'bibdk_nami_related_series_link':
        $urls = $entity->getRelatedSeriesLink();
        $value = _ting_openformat_get_markup_for_field($urls, '<br/>');
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
 * @throws Exception
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
      '#markup' => ting_openformat_text_summary($markup, 300),
    );
  }
  return $return;
}

/**
 * Method for converting text blocks to trimmed text with a show more link.
 *
 * The text are trimmed at the last space within the range given
 *
 * @param $text
 * @param int $length
 * @return string
 */
function ting_openformat_text_summary($text, $length = 300) {
  if (strlen($text) > $length) {
    list($trimmed, $more) = ting_openformat_trim_string_by_length($text, $length);
    // We call the theme function directly so this function always can return a
    // string
    if (!empty($more)) {
      $text = theme('ting_openformat_toggle_more_content', array(
        'trimmed_text' => $trimmed,
        'more_text' => $more,
      ));
    }
  }

  return $text;
}

/**
 * Trim a textstring by length (to the nearest space)
 *
 * Returns an array with the trimmed text and the text that is trimmed off
 *
 * @param $text
 * @param $length
 * @return array
 */
function ting_openformat_trim_string_by_length($text, $length) {
  // If text is smaller than specified length return string and empty more
  // If text contains html we exclude it to make sure we don't break the html
  if(strlen($text) <= $length || strlen($text) != strlen(strip_tags($text))){
    return array($text, '');
  }
  $return = array();
  // extract substring by length
  $text_trimmed = substr($text, 0, $length);
  // Find last space
  $last_space = strrpos($text_trimmed, ' ');
  // adjust trimmed string length to last space
  $return[] = substr($text_trimmed, 0, $last_space);
  // Get the text that is trimmed away
  $return[] = substr($text, $last_space);

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
function _ting_openformat_parse_element($elements, $divider = ". ", $use_header = TRUE, $return_link = TRUE, $link_label = NULL) {
  if (!isset($elements)) {
    return NULL;
  }
  if (!is_array($elements)) {
    $elements = array($elements);
  }
  foreach ($elements as $key => $value) {
    if ( is_array($value) && array_key_exists('accessUrl', $value ) ) {
      $url = $value['accessUrl'];
      $label = ( !empty($value['accessUrlDisplay']) ) ? t($value['accessUrlDisplay'], array(), array('context' => 'bibdk_openformat')) : $url;
      $array[] = l($label, $url, array('attributes' => array('target' => '_blank'), 'html' => true));
    }
    else if (is_array($value)) {
      $array[] = _ting_openformat_parse_element($value, $divider, $use_header, $return_link, $link_label);
    }
    elseif ($key === "header") {
      if ($use_header) {
        $header = $value;
      }
    }
    elseif ($key === 'searchCode') {
      if ($return_link && isset($elements['searchCode'])) {
        $array[] = l($elements['display'], 'search/work/' . $elements['searchCode']);
      }
      else {
        $array[] = $elements['display'];
      }
    }
    elseif ($key === 'display' || $key === 'accessUrlDescriptor') { /*do nothing*/
    }
    else {
      $array[] = check_plain($value);
    }
  }
  $string = (isset($header)) ? $header . " " : "";
  if (isset($array)) {
    $string .= implode($divider, $array);
  }
  return $string;
}

/**
 * @param array $urls
 * @return null|string
 */
function _ting_openformat_parse_urls($urls) {
  if(!is_array($urls) || !isset($urls['accessInformation'][0]['accessUrl'])){
    return NULL;
  }

  $urls = $urls['accessInformation'][0]['accessUrl'];

  $links = '';
  foreach ($urls as $url) {
    $links .= l($url, $url, array('attributes' => array('target' => '_blank'))) . '<br />';
  }

  return $links;
}

/**
 * Helper function to parse analytic content
 * @param $analytic_content
 * @param null $entity
 * @param array $options
 * @return array|null
 */
function _ting_openformat_parse_analytic_content($analytic_content, $entity = NULL, $options = array()) {

  // Check variables
  if (!isset($analytic_content) || !isset($analytic_content['analyticContent'][0])) {
    return null;
  }
  $analytic_content = reset($analytic_content['analyticContent']);

  // Parse through elements
  foreach ($analytic_content as $element) {

    $element_markup = _ting_openformat_parse_analytic_content_element($element);

    // if element has analyticContributor it should start on a new line else it should be divided with ;
    if (isset($markup)){
      if (array_key_exists('analyticContributor', $element) || (isset($prevElement) && array_key_exists('analyticContributor', $prevElement))) {
        $markup .= '<br/>' . $element_markup;
      }
      else {
        $markup .= ' ; ' . $element_markup;
      }
    } else {
      $markup = $element_markup;
    }
    $prevElement = $element;
  }

  $value['#markup'] = $markup;
  return $value;
}

/**
 * @param $element
 * @return string
 */
function _ting_openformat_parse_analytic_content_element($element){
  foreach ($element as $key => $value) {
    $markup = _ting_openformat_get_markup_for_field($value, " ");
    $markup = $markup['#markup'];
    if ($key == 'analyticContributor') {
      $markup .= ":";
    }
    $element_values[] = $markup;
  }
  return implode(' ', $element_values);

}

//900 lines before refactoring
