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
      case 'ting_openformat_mani_lk_subjects':
      case 'ting_openformat_work_lk_subjects':
        // one or more laesekompas subjects
        $subjects = $entity->getLaesekompasSubjects();
        $value = _ting_openformat_get_markup_for_field($subjects, '; ', FALSE);
        break;
      case 'bibdk_mani_series':
        $content = _ting_openformat_default_field_view_content($field['field_name'], $entity);
        $value = _ting_openformat_get_markup_for_field($content, '');
        break;
      case 'bibdk_mani_related_series':
        $content = _ting_openformat_default_field_view_content($field['field_name'], $entity);
        $value = _ting_openformat_get_markup_for_field($content, '');
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
      case 'bibdk_mani_contribs':
        $contrib = $entity->getContributors();
        $value = _ting_openformat_parse_contributors($contrib);
        break;
      case 'bibdk_mani_contribs_extra':
        $contrib_extra = $entity->getContributorExtra();
        $value = _ting_openformat_get_markup_for_field($contrib_extra, " ; ");
        break;
      case 'bibdk_mani_description_note':
        $desNote = $entity->getDescriptionNote();
        $value = _ting_openformat_get_markup_for_field($desNote, "<br />");
        break;
      case 'bibdk_mani_infotext':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $infotext = $entity->getInfotext();
        $infotext = ($infotext) ? t('drupal_text_' . $infotext, array(), array('context' => 'bibdk_openformat')) : NULL;
        $value = _ting_openformat_get_markup_for_field($infotext);
        break;
      case 'bibdk_mani_tracks':
        $tracks = $entity->getTrackContent();
        $value = _ting_openformat_parse_tracks($tracks);
        break;
      case 'bibdk_mani_access_information':
        $urls = $entity->getAccessInformation();
        $value = _ting_openformat_get_markup_for_field($urls, '<br/>');
        break;
      case 'bibdk_mani_access_note':
        $urls = $entity->getAccessNote();
        $value = _ting_openformat_get_markup_for_field($urls, '<br/>');
        break;
      case 'bibdk_mani_edition':
        $edition = $entity->getEdition();
        $value = _ting_openformat_get_markup_for_field($edition, ', ');
        break;
      default :
        $content = _ting_openformat_default_field_view_content($field['field_name'], $entity);
        $value = _ting_openformat_get_markup_for_field($content);
        break;
    }
    if (isset($value)) {
      drupal_alter('openformat_field', $value, $field['field_name']);
      $element[$delta] = $value;
    }
  }
  return $element;
}


/** Generic Helper function to get content elements for a speficic field
* @param $field_name
* @param $entity
* @throws Exception
* @return null
*/
function _ting_openformat_default_field_view_content($field_name, $entity) {
  $value = null;
  $field_definitions = ting_openformat_bibdk_fields();
  if (isset($field_definitions[$field_name])) {
    $field = $field_definitions[$field_name];
    $method = $field['callback method'];
    if (isset($method) && is_callable(array($entity, $method))) {
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
  if (!is_array($elements)) {
    $elements = array($elements);
  }
  $empty = TRUE;
  $callback = function($value, $key) use (&$empty) {
    if (!empty($value)) {
      $empty = FALSE;
    }
  };
  array_walk_recursive($elements, $callback);

  if ($empty) {
    return NULL;
  }

  $render_array = array();
  $render_array = _ting_openformat_parse_element($elements, $render_array, $divider, $use_header, $return_link);

  if (empty($render_array)) {
    return NULL;
  }
  $render_array = ting_openformat_text_summary($render_array);

  return $render_array;
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
function ting_openformat_text_summary($render_array, $length = 290) {
  $trimmed = $more = array();
  $text = '';
  $text_len = 0;

  foreach ($render_array as $item) {
    $text .= _ting_openformat_get_render_string($item);
  }

  if (mb_strlen($text) < $length) {
    return $render_array;
  }

  // text is longer than $length
  foreach ($render_array as $item) {
    $text = _ting_openformat_get_render_string($item);
    if (mb_strlen($text) >= $length - $text_len && $text_len < $length) {
      // add break in middle of item text
      list($item_trimmed, $item_more) = ting_openformat_trim_string_by_length($text, $length);
      $trimmed[] = array(
        '#theme' => 'ting_openformat_field',
        '#openformat_field' => array('#markup' => $item_trimmed),
      );
      $more[] = array(
        '#theme' => 'ting_openformat_field',
        '#openformat_field' => array('#markup' => $item_more),
      );
      $text_len = $length;
    }
    else if ($text_len + mb_strlen($text) < $length) {
      $text_len += mb_strlen($text);
      $trimmed[] = $item;
    }
    else {
      $more[] = $item;
    }
  }

  if (!empty($more)) {
    $render_array = array(
      '#theme' => 'ting_openformat_toggle_more_content',
      '#trimmed_text' => $trimmed,
      '#more_text' => $more,
    );
  }

  return $render_array;
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
* Recursive find value of key in array
*
* Returns value of key $needle
*
* @param $array
* @param $needle
* @return mixed
*/
function ting_openformat_recursive_find(array $array, $needle) {
  $iterator  = new RecursiveArrayIterator($array);
  $recursive = new RecursiveIteratorIterator($iterator,
  RecursiveIteratorIterator::SELF_FIRST);
  foreach ($recursive as $key => $value) {
    if ($key === $needle) {
      return $value;
    }
  }
}


/**
* Parses a field array from a manifestation/work entity. returns a render array.
* searchCode and header are specialcases what generates a field-label and a link
*
* @param array|string|null $elements
* @param string $divider
* @param bool $use_header
* @param bool $return_link If FALSE value will be returned without markup for href. Otherwise complete markup for href is returned
* @return render array
*/
function _ting_openformat_parse_element($elements = NULL, $render_array = array(), $divider = FALSE, $use_header = TRUE, $return_link = TRUE) {
  if (!$elements) {
    return array();
  }

  if (!is_array($elements)) {
    $elements = array($elements);
  }

  if ( !is_array($render_array) ) {
    $render_array = array(
      '#theme' => 'ting_openformat_field',
      '#openformat_field' => array('#markup' => $render_array),
    );
  }
  $has_search_code = FALSE;
  foreach ($elements as $key => $element) {
    if ($key === 'accessInformationNote' && is_array($element)) {
      foreach ($element as $element_key => $element_value) {
        if (array_key_exists('accessUrl', $element_value )) {
          if (!empty($element_value['accessUrlDescriptor'])) {
            $header = array(
              '#theme' => 'ting_openformat_field',
              '#openformat_header' =>  array('#markup' => check_plain($element_value['accessUrlDescriptor'])),
            );
          }
          $render_array[] = array(
            '#theme' => 'ting_openformat_field',
            '#openformat_field' => array(
              '#theme' => 'link',
              '#text' => $element_value['accessUrlDisplay'],
              '#path' => $element_value['accessUrl'],
              '#options' => array(
                'attributes' => array('target' => '_blank'),
                'html' => TRUE,
              ),
            ),
          );
        } else {
          foreach ($element_value as $k => $v) {
            if (!empty($v['accessUrlDescriptor'])) {
              $header = array(
                '#theme' => 'ting_openformat_field',
                '#openformat_header' =>  array('#markup' => check_plain($v['accessUrlDescriptor'])),
              );
            }
            $render_array[] = array(
              '#theme' => 'ting_openformat_field',
              '#openformat_field' => array(
                '#theme' => 'link',
                '#text' => $v['accessUrlDisplay'],
                '#path' => $v['accessUrl'],
                '#options' => array(
                  'attributes' => array('target' => '_blank'),
                  'html' => TRUE,
                ),
              ),
            );
          }
        }
      }
    }
    else if ( is_array($element) && array_key_exists('accessUrl', $element ) ) {
      $txt = '';
      if (!empty($element['accessUrlDescriptor'])) {
        // NOTE - pjo 200315 can this be an array ?? - for now grab the first
        if (is_array($element['accessUrlDescriptor'])) {
          $txt = reset($element['accessUrlDescriptor']);
        }
        else {
          $txt = $element['accessUrlDescriptor'];
        }
      }
      elseif (!empty($element['accessUrlDisplay'])) {
        $txt = t($element['accessUrlDisplay'], array(), array('context' => 'bibdk_openformat'));
      }
      $render_array[] = array(
        '#theme' => 'ting_openformat_field',
        '#openformat_field' => array(
          '#theme' => 'link',
          '#text' => ( !empty($txt) ) ? $txt : $element['accessUrl'],
          '#path' => $element['accessUrl'],
          '#options' => array(
            'attributes' => array('target' => '_blank'),
            'html' => TRUE,
          ),
        ),
      );
    }
    else if (is_array($element)) {
      $render_array = _ting_openformat_parse_element($element, $render_array, FALSE, $use_header, $return_link);
    }
    elseif ($key === "header") {
      if ($use_header) {
        $header = array(
          '#theme' => 'ting_openformat_field',
          '#openformat_header' =>  array('#markup' => check_plain($element)),
        );
      }
    }
    elseif ($key === 'searchCode') {
      $has_search_code = TRUE;
      if ($return_link && isset($elements['searchCode'])) {
        $render_array[] = array(
          '#theme' => 'ting_openformat_field',
          '#openformat_field' => array(
            '#theme' => 'link',
            '#text' => $elements['display'],
            '#path' => 'search/work/',
            '#options' => array(
              'query' => array('search_block_form' => $elements['searchCode']),
              'fragment' => 'content',
              'attributes' => array(),
              'html' => TRUE,
            ),
          ),
        );
      }
      else {
        $render_array[] = array(
          '#theme' => 'ting_openformat_field',
          '#openformat_field' => array('#markup' => $elements['display']),
        );
      }
    }
    elseif (!$has_search_code && $key === 'display') {
      $render_array[] = array(
        '#theme' => 'ting_openformat_field',
        '#openformat_field' => array('#markup' => $elements['display']),
      );
    }
    elseif ($key === 'display' || $key === 'accessUrlDescriptor') { /*do nothing*/
    }
    else {
      $render_array[] = array(
        '#theme' => 'ting_openformat_field',
        '#openformat_field' => array('#markup' => check_plain($element)),
      );
    }
  }
  if (sizeof($render_array) > 1 && $divider) {
    $tmp_array = array();
    foreach ($render_array as $key => $element) {
      if (sizeof($tmp_array) > 0 && !isset($tmp_array[$tmp_key]['#openformat_header'])) {
        $tmp_array[] = array(
          '#prefix' => '<span class="openformat-field-divider">',
          '#markup' => $divider,
          '#suffix' => '</span>',
        );
      }
      $tmp_array[] = $element;
      $tmp_key = key($tmp_array);
    }
    $render_array = $tmp_array;
  }

  if (isset($header)) {
    array_unshift($render_array, $header);
  }

  return $render_array;

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
* Helper function to parse contributors
* @param $contributors
* @return array
*/
function _ting_openformat_parse_contributors($contributors) {
  if ($contributors === NULL) {
    return;
  }
  $render_array = array();
  if (isset($contributors['contributor']) &&
      is_string($contributors['contributor'])) {
    return _ting_openformat_get_markup_for_field($contributors, ": ");
  }
  foreach ($contributors as $key => $contributor) {
    if (isset($contributor['contributor'])) {
      if (!isset($contributor['contributor'][0][0])) {
        $contributor['contributor'][0] = array($contributor['contributor'][0]);
      }
      $persons = $contributor['contributor'][0];
      $count = count($persons);
      $i = 0;
      foreach ($persons as $key => $value) {
        $function = (isset($value["functionSingular"])) ? $value["functionSingular"] : '';
        if ($function !== '') {
          $prev_function = ($i > 0) ? $persons[$i-1]["functionSingular"] : '';
          $i++;
          $next_function = (isset($persons[$i]) && isset($persons[$i]["functionSingular"])) ? $persons[$i]["functionSingular"] : '';
          if ($function === $prev_function) {
            if (isset($value['functionPlural'])) {
              unset($value['functionPlural']);
            }
            if (isset($value['functionSingular'])) {
              unset($value['functionSingular']);
            }
          } else if ($function === $next_function) {
            if (isset($value['functionSingular'])) {
              unset($value['functionSingular']);
            }
          } else {
            if (isset($value['functionPlural'])) {
              unset($value['functionPlural']);
            }
          }
          $markup = _ting_openformat_get_markup_for_field($value, ": ");
          if ($i < $count) {
            $markup[] = array(
              '#markup' => "; ",
            );
          }
        } else {
          $i++;
          $markup = _ting_openformat_get_markup_for_field($value, "");
          if ($i < $count) {
            $markup[] = array(
              '#markup' => "; ",
            );
          }
        }
        $render_array = isset($markup) ? array_merge($render_array, $markup) : $render_array;
      }
    }
  }
  return $render_array;
}

/**
* Helper function to parse tracks
* @param $tracks
* @param null $entity
* @param array $options
* @return array|null
*/
function _ting_openformat_parse_tracks($tracks, $entity = NULL, $options = array()) {
  if (!isset($tracks) || !isset($tracks[1]['track'])) {
    return null;
  }
  $render_array = array();
  foreach ($tracks as $element) {
    $render_array = _ting_openformat_parse_tracks_element($element['track'][0]);
  }
  return ting_openformat_text_summary($render_array);
}

/**
* Helper function to parse track elements
* @param $element
* @return string
*/
function _ting_openformat_parse_tracks_element($element) {
  $render_array = array();
  if ($element === NULL) {
    return $render_array;
  }
  $count = count($element);
  $i = 0;
  if (isset($element['title'])) {
    $element = array($element);
  }
  foreach ($element as $key => $value) {
    $i++;
    end($value);
    $last_key = key($value);
    foreach ($value as $k => $v) {
      $markup = (_ting_openformat_get_markup_for_field($v, " ") !== NULL) ? _ting_openformat_get_markup_for_field($v, " ") : [];
      if ($k === 'creator') {
        $delimiter = ': ';
      } else {
        if (isset($value['creator'])) {
          $delimiter = ($count > $i && $k === $last_key) ? '</br>' : '';
        } else {
          $delimiter = ($count > $i) ? ' ; ' : '';
        }
      }
      $markup[] = array(
        '#markup' => $delimiter,
      );
      $render_array = array_merge($render_array, $markup);
    }
  }
  return $render_array;

}

/**
* Implements hook_field_is_empty().
* @return boolean
*/
function ting_openformat_field_is_empty($item, $field) {
  return empty($item['value']) && (string) $item['value'] !== '0';
}

/**
* Helper function to return text part of a render array
* @param $render_array
* @return string
*/
function _ting_openformat_get_render_string($render_array) {
  if ( is_string($render_array)){
    return $render_array;
  }
  $item = '';
  $callback = function($value, $key) use (&$item) {
    if ($key == '#markup' || $key == '#text') {
      $item = $value;
    }
  };
  array_walk_recursive($render_array, $callback);
  return $item;
}

//900 lines before refactoring
