<?php
class bibdkEntity {
  public $id;
  public $ding_entity_id;

  private $work;
  private $manifestations = array();

  public function __construct($ding_entity_id){
    $this->id = $this->ding_entity_id = $ding_entity_id;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function addManifestation($manifestation) {

  }
}

class manifestation {
  public function __construct() {}
}