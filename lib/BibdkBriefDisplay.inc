<?php

class BibdkBriefDisplay {

  public $id;

  function __construct($manifestation){
    $this->manifestation = $manifestation;
    $this->id = $manifestation->identifier->{'$'};
  }

  public function getType(){
    //worktype
    return $this->manifestation->workType->{'$'};
  }

  public function getSubtype(){
    //type
    return $this->manifestation->type->{'$'};
  }

}
