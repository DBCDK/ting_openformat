<?php

class BibdkCollection {

  private $manifestations;
  public $ding_entity_id;
  private $collectionTypes;
  private $collectionIds;

  function __construct($manifestation) {
    $this->manifestations = $manifestation['manifestations'];
  }

  //TODO the below method should be reviewed as valid XML is expected from webservices in production
  public function parseManifestations() {
    if (isset($this->manifestations)) {
      foreach ($this->manifestations as $manifestation) {
        if (isset($manifestation) && isset($manifestation->identifier->{'$'})) {
          $id = $manifestation->identifier->{'$'};
          $type = isset($manifestation->type->{'$'}) ? $manifestation->type->{'$'} : 'Unknown';
          $this->collectionTypes[$type][] = $id;
          $this->collectionIds[] = $id;
        }
      }
    }
  }

  public function getId() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('identifier'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getTitle() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('title'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getPartOf() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('partOf'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getAuthor() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('creator'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getCollectionIds() {
    return $this->collectionIds;
  }

  public function getCollectionTypes() {
    return $this->collectionTypes;
  }

}
