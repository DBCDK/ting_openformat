<?php
class bibdkWork {
  public $id;
  public $ding_entity_id;

  private $work;
  public $manifestations = array();

  public function __construct($work){
    $this->work = $work;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function setManifestations($manifestations) {
    $this->manifestations = $manifestations;
  }
}

class manifestation {
  public $entity;
  public $manifestation;
  public function __construct($stdObject){
    $this->entity = $stdObject;
  }
}