<?php
class bibdkWork {
  public $id ;
  public $ding_entity_id;

  public $work;
  public $manifestations = array();

  public function __construct($work=NULL){
    $this->work = $work;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function setManifestations($manifestations) {
    foreach($manifestations as $id => $manifestation) {
      $this->manifestations[$id] = entity_load('bibdkManifestation',$id,$manifestation);
    }
  }

  public function getTitle() {
    return $this->work->title->titleFull->{'$'};
  }

  public function getCreator() {
    $creators = isset($this->work->creators->creator) ? $this->work->creators->creator : NULL ;

    if( empty($creators) ) {
      return array();
    }

    if( !is_array($creators) ) {
      $creators = array($creators);
    }

    foreach( $creators as $key=>$val ){
      $creator['display'] = $val->display->{'$'};
      $creator['searchCode'] = $val->searchCode->{'@phrase'}->{'$'}.'='.$val->searchCode->{'$'};
      $ret[] = $creator;
    }
    return $ret;
  }

  public function getSubjects() {
    $subjects = isset($this->work->description->subjects->subject) ? $this->work->description->subjects->subject : NULL ;

    if( empty($subjects) ) {
      return array();
    }

    if( !is_array($subjects) ) {
      $subjects = array($subjects);
    }

    foreach( $subjects as $key=>$val ){
      $subject['display'] = $val->display->{'$'};
      $subject['searchCode'] = $val->searchCode->{'@phrase'}->{'$'}.'='.$val->searchCode->{'$'};
      $ret[] = $subject;
    }
    return $ret;
  }
}

class manifestation {
  public $id ;
  public $ding_entity_id;
  public $manifestation;

  public function __construct($manifestation){
    $this->manifestation = $manifestation;
  }

  public function getType() {
    return isset($this->manifestation->type->{'$'}) ? $this->manifestation->type->{'$'} : FALSE;
  }
}