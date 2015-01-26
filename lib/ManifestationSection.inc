<?php

/**
 * this class handles the Section part of the manifestation
 */
class ManifestationSection extends ManifestationMaster {

  public function __construct($section) {
    $this->fields = $section;
  }

  public function getTitle() {
    $fields = array('titleFull');
    if (isset($this->fields->title)) {
      $element = $this->fields->title;
      $result = TingOpenformatMethods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

  public function getCreator() {
    $fields = array('creator' => 'searchCode');
    if (isset($this->fields->creators)) {
      $element = $this->fields->creators;
      $result = TingOpenformatMethods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

}
