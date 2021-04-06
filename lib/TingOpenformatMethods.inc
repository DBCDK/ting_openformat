<?php

class TingOpenformatMethods {

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  public static function _parseSearchCode($stdObjects) {
    $ret = array();
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }
    foreach ($stdObjects as $key => $object) {
      if (isset($object->searchCode) || isset($object->value)) {
        if (is_array($object->searchCode)) {
          $object->searchCode = $object->searchCode[0];
        }
        if (isset($object->searchCode->{'$'}) && isset($object->searchString->{'$'})) {
          $subject['searchCode'] = $object->searchCode->{'$'} . '="' . $object->searchString->{'$'} . '"';
        }
        $subject['display'] = isset($object->value->{'$'}) ? $object->value->{'$'} : NULL;
        $subject['display'] = isset($object->name->{'$'}) ? $object->name->{'$'} : $subject['display'];
        $ret[] = $subject;
      }
      elseif (isset($object->{'$'})) {
        $subject = $object->{'$'};
        $ret[] = $subject;
      }
    }
    return $ret;
  }

  // <workaround>
  // type 'Blu-ray 4K' has worktype:other. Requires an update of briefDisplay
  // Delete when new briefDisplay is in place (and support Blu-ray 4K -> workType:movie )
  /* \brief parse workType
   * @param array of stdObjects
   * return string
   */
  public static function _parseWorkType($stdObject) {
    $type = $stdObject->type->{'$'};
    return ($type == 'Blu-ray 4K') ? 'movie' : $stdObject->workType->{'$'};
  }
  // </workaround>

  /**
   * Link elements are of type $o->[display,url]
   *
   * @param $stdObject
   * return array[url,display]
   */
  public static function _parseLinkElement($stdObjects) {
    $ret = array();
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $key => $object) {
      if (isset($object->url) && isset($object->display)) {
        $subject['accessUrl'] = $object->url->{'$'};
        $subject['accessUrlDisplay'] = $object->display->{'$'};
        $ret[] = $subject;
      }
    }

    return $ret;
  }

  /**
   * @param $object
   * @param array $fields
   * @return array|null
   */
  public static function parseFields($object, array $fields) {
    $ret = NULL;
    if (!isset($object)) {
      return $ret;
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
      elseif ($value == 'searchCode' && isset($object->$value)) {
        $ret[$field][] = self::_parseSearchCode($object);
      }
      elseif ($value == 'linkElements' && isset($object->$value)){
        $ret[$field][] = self::_parseLinkElement($object->$value);
      }
      // <workaround>
      // type 'Blu-ray 4K' has worktype:other. Requires an update of briefDisplay
      // Delete when new briefDisplay is in place (and support Blu-ray 4K -> workType:movie )
      elseif ($value == 'workType' && isset($object->workType)) {
        $ret['workType'] = self::_parseWorkType($object);
      }
      // </workaround>
      elseif ($value == 'header' && isset($object->$field)) {
        if (isset($object->$field->{'$'})) {
           $ret[$value] = $object->$field->{'$'};
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {
        foreach ($object->$value as $val) {
          if (isset($val->{'$'})) {
            $ret[$value][] = $val->{'$'};
          }
        }

        // When using briefDisplay as format sometimes an array is encapsulating the value
        // But are there situation where the array with one element is required?
        if (count($ret[$value]) == 1) {
          $ret[$value] = $ret[$value][0];
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value)) {
        if (isset($object->$value->{'$'})) {
          $ret[$value] = $object->$value->{'$'};
        }
      }
    }
    return $ret;
  }

}
