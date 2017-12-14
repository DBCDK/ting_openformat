<?php

class BibdkBriefDisplay {

  public $id;
  private $subtypeOrderIds;

  function __construct($manifestation){
    $this->manifestation = $manifestation;
    $this->id = $manifestation->identifier->{'$'};
  }

  public function getType(){
    //worktype
    $type = array();
    if ($this->manifestation->accessType->{'$'} == 'online'){
      $type[] = 'online';
    }
    $type[] = $this->manifestation->workType->{'$'};
    return $type;
  }

  public function getBriefDisplayType(){
    //worktype
    return $this->getType();
  }

  public function getSubtype(){
    //type
    return $this->manifestation->type->{'$'};
  }

  public function getHostPublicationID(){
    //type
    return $this->id;
  }
  
  public function setSubtypeOrderIds($ids) {
    $this->subtypeOrderIds = $ids;
  }

  public function getSubtypeOrderIds() {
    return $this->subtypeOrderIds;
  }

}
