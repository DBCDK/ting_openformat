<?php

class TingOpenformatMethods {

  /* \brief parse searchCode,display elements
   * NB! OLD VERSION
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  public static function _parseSearchCodeOld($stdObjects) {
    $ret = Array();
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }
    foreach ($stdObjects as $key => $object) {
      if (isset($object->searchCode) || isset($object->display)) {
        $subject['searchCode'] = isset($object->searchCode) ? self::_getSearchCodeElementOld($object->searchCode) : NULL;
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

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */
  public static function _parseSearchCode($stdObjects) {
    $ret = Array();
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }
    foreach ($stdObjects as $key => $object) {
      if (isset($object->searchCode) || isset($object->value)) {
        if (isset($object->searchCode) && isset($object->searchString)) {
          if (!is_array($object->searchString)) {
            $object->searchString = array($object->searchString);
          }
          foreach ($object->searchString as $searchString) {
            $subject['searchCode'] = $object->searchCode->{'$'} . '="' . $searchString->{'$'} . '"';
          }
        }
        // Remove this when shelf from OpenFormat outputs 'searchString' instead of 'value'
        elseif (isset($object->searchCode) && isset($object->value)) {
          $subject['searchCode'] = $object->searchCode->{'$'} . '="' . $object->value->{'$'} . '"';
        }
        $subject['display'] = isset($object->value->{'$'}) ? $object->value->{'$'} : NULL;
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

  /* \brief parse search code elements
   * NB! OLD VERSION
   * @param array of stdObjects
   * return string
   */
  public static function _getSearchCodeElementOld($stdObject) {
    if (isset($stdObject->{'$'})) {
      if (isset($stdObject->{'@phrase'}) && isset($stdObject->{'@phrase'}->{'$'})) {
        $fisk = $stdObject->{'@phrase'}->{'$'} . '=' . $stdObject->{'$'};
        return $stdObject->{'@phrase'}->{'$'} . '=' . $stdObject->{'$'};
      }
      elseif (isset($stdObject->{'@word'}) && isset($stdObject->{'@word'}->{'$'})) {
        $hest = $stdObject->{'@word'}->{'$'} . '=' . $stdObject->{'$'};
        return $stdObject->{'@word'}->{'$'} . '=' . $stdObject->{'$'};
      }
    }
  }

  /**
   * Link elements are of type $o->[display,url]
   *
   * @param $stdObject
   * return array[url,display]
   */
  public static function _parseLinkElement($stdObjects) {
    $ret = Array();
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
    $display_version = variable_get('ting_search_openformat', 'bibliotekdkWorkDisplay');
    foreach ($fields as $field => $value) {
      if (is_array($value) && isset($object->$field)) {
        $ret[$field][] = self::parseFields($object->$field, $value);
      }
      elseif ($value == 'searchCode' && isset($object->$field)) {
        $ret[$field][] = ($display_version === 'bibdkWorkDisplay') ?
          self::_parseSearchCode($object->$field) :
          self::_parseSearchCodeOld($object->$field);
      }
      elseif ($value == 'searchCode' && isset($object->$value)) {
        $ret[$field][] = ($display_version === 'bibdkWorkDisplay') ?
        self::_parseSearchCode($object) :
        self::_parseSearchCodeOld($object);
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
        $ret[$value] = $object->$field->{'$'};
      }
      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {
        foreach ($object->$value as $val) {
          $ret[$value][] = $val->{'$'};
        }

        // When using briefDisplay as format sometimes an array is encapsulating the value
        // But are there situation where the array with one element is required?
        if (count($ret[$value]) == 1) {
          $ret[$value] = $ret[$value][0];
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value)) {
        $ret[$value] = $object->$value->{'$'};
      }
    }
    return $ret;
  }

}
