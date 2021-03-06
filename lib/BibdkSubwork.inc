<?php
class BibdkSubwork {

  public $id;
  public $ding_entity_id;
  public $manifestations = array();
  public $type;
  private $subType;
  private $isReservable;

  public function __construct($type, $manifestations) {
    $this->type = $type;
    $this->manifestations = $manifestations;
  }

  public function getIDs() {
    $ids = array();
    foreach ($this->getManifestations() as $manifistation) {
      $ids[] = $manifistation->id;
    }
    return $ids;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function getType() {
    return $this->type;
  }

  public function setSubType($subType) {
    $this->subType = $subType;
  }

  public function getSubType() {
    return $this->subType;
  }

  public function isReservable() {
    if (!isset($this->isReservable)) {
      $this->isReservable = FALSE;
      foreach ($this->getManifestations() as $manifestation) {
        if ($manifestation->isReservable()) {
          $this->isReservable = TRUE;
          break;

        }
      }
    }
    return $this->isReservable;
  }

  public function showLocalizationLink(){
    foreach($this->getManifestations() as $manifestation){
      if( get_class($manifestation) == 'Manifestation'){
        $method = $manifestation->getRequestMethod();
        $use = $manifestation->getRestrictedUse();
        if ($method != 'oldMaterial' && $method != 'newMaterial'  && $use != 'oldSBTB'){
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  public function isLink() {
    return FALSE;
  }

  public function getHostPublicationID(){
    $ids = array();
    foreach ($this->getManifestations() as $manifestation) {
      $id = $manifestation->getHostPublicationID();
      $id = isset($id) ? $id : $manifestation->id;
      $ids[$id] = $id;
    }

    return $ids;
  }


}

