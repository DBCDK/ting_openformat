<?php

module_load_include('inc', 'ting_openformat', 'lib/BibdkCollection');
module_load_include('inc', 'ting_openformat', 'lib/BibdkSubwork');
module_load_include('inc', 'ting_openformat', 'lib/BibdkWork');
module_load_include('inc', 'ting_openformat', 'lib/ManifestationMaster');
module_load_include('inc', 'ting_openformat', 'lib/Manifestation');
module_load_include('inc', 'ting_openformat', 'lib/ManifestationSection');
module_load_include('inc', 'ting_openformat', 'lib/ManifestationVolume');

class ting_openformat_methods {

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  private static function _parseSearchCode($stdObjects) {
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $object) {
      if (isset($object->searchCode)){
        $subject['searchCode'] = self::_getSearchCodeElement($object->searchCode);
        $subject['display'] = isset($object->display) ? $object->display->{'$'} : NULL;
      } elseif (isset($object->{'$'})){
        $subject = $object->{'$'};
      }
      $ret[] = $subject;
    }

    return $ret;
  }

  private static function _getSearchCodeElement($stdObject) {
    $value = (isset($stdObject->{'$'})) ? $stdObject->{'$'} : NULL;

    if (isset($stdObject->{'@phrase'})) {
      $term = $stdObject->{'@phrase'}->{'$'};
    }
    elseif (isset($stdObject->{'@word'})) {
      $term = $stdObject->{'@word'}->{'$'};
    }

    if (isset($value) && isset($term)) {
      return $term . "=" . $value;
    }
    else {
      return;
    }
  }

  /**
   * @param $object
   * @param array $fields
   * @return array|null
   */
  public static function parseFields($object, array $fields) {
    $ret = NULL;
    if (!isset($object)) {
      return NULL;
    }
    if (is_array($object)) {
      foreach ($object as $o) {
        if (isset($o)) {
          $ret[] = self::parseFields($o, $fields);
        }
      }
      return $ret;
    }

    foreach ($fields as $field => $value) {
      if (is_array($value) && isset($object->$field)) {
        $ret[$field][] = self::parseFields($object->$field, $value);
      }
      elseif ($value == 'searchCode' && isset($object->$field)) {
        $ret[$field][] = self::_parseSearchCode($object->$field);
      }
      elseif ($value == 'header' && isset($object->$field)) {
        $ret[$value] = $object->$field->{'$'};
      }
      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {

        foreach ($object->$value as $val) {
          $ret[$value][] = $val->{'$'};
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value)) {
        $ret[$value] = $object->$value->{'$'};
      }
    }
    return $ret;
  }

}
