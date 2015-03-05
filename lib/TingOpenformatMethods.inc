<?php

class TingOpenformatMethods {

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  public static function _parseSearchCode($stdObjects) {
    $ret = Array();

    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $object) {
      if (isset($object->searchCode) || isset($object->display)) {
        $subject['searchCode'] = isset($object->searchCode) ? self::_getSearchCodeElement($object->searchCode) : NULL;
        $subject['display'] = isset($object->display) ? $object->display->{'$'} : NULL;
        $ret[] = $subject;
      }
      elseif (isset($object->{'$'})) {
        $subject = $object->{'$'};
        $ret[] = $subject;
      }
    }

    return $ret;
  }

  public static function _getSearchCodeElement($stdObject) {
    if (isset($stdObject->{'$'})) {
      if (isset($stdObject->{'@phrase'}) && isset($stdObject->{'@phrase'}->{'$'})) {
        return $stdObject->{'@phrase'}->{'$'} . '=' . $stdObject->{'$'};
      }
      elseif (isset($stdObject->{'@word'}) && isset($stdObject->{'@word'}->{'$'})) {
        return $stdObject->{'@word'}->{'$'} . '=' . $stdObject->{'$'};
      }
    }
  }

  /**
   * Link elements are of type $o->[display,url]
   * There can be one or more
   * @param $stdObjects
   * return array[url,display]
   */
  public static function _parseLinkElements($stdObjects){
    $ret = Array();

    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $object) {
      if (!isset($object->url) || !isset($object->display)) {
        continue;
      }
      $element['accessUrl'] = $object->url->{'$'};
      $element['accessUrlDisplay'] = $object->display->{'$'};
      $ret[] = $element;

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
      elseif($value == 'linkElements' && isset($object->$value)) {
        $ret[$value] = self::_parseLinkElements($object->$value);
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
