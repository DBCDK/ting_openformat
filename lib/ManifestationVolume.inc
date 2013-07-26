<?php

/**
 * this class handles the Volume part of the manifestation
 */
class ManifestationVolume extends ManifestationMaster {

  public function __construct($volume) {
    $this->fields = $volume;
  }

  public function getTitle() {
    $fields = array('titleFull');
    if (isset($this->fields->title)) {
      $element = $this->fields->title;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

  public function getCreator() {
    $fields = array('creator' => 'searchCode');
    if (isset($this->fields->creators)) {
      $element = $this->fields->creators;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

}
