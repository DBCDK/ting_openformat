<?php

class BibdkCollection {

  public $manifestations;
  /* @var stdClass $workOne */
  private $workOne;
  public $ding_entity_id;
  private $collectionTypes;
  private $collectionIds;

  function __construct($conditions) {
    $this->manifestations = isset($conditions['manifestations']) ? $conditions['manifestations'] : NULL;
    $this->workOne = isset($conditions['workOne']) ? $conditions['workOne'] : NULL;
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
    $language = $this->getLanguage();
    if(!empty($language) && $language != 'Dansk' && $language != 'Sproget kan ikke bestemmes'){
      $language = '<span> ('. $language.')</span>' ;
    }
    else {
      $language = NULL;
    }

    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('title'));
    $title = (is_array($result)) ? reset($result) : $result;
    $dependent_title = $this->getDependentTitle();
    $ret = (!empty($dependent_title)) ? $title . " <br /> " . implode('. ', $dependent_title) : $title;
    if (!empty($language)) {
      $ret .= $language;
    }
    return $ret;
  }

  public function getTitleFull() {
    $language = $this->getLanguage();
    if(!empty($language) && $language != 'Dansk' && $language != 'Sproget kan ikke bestemmes'){
      $language = '<span> ('. $language.')</span>' ;
    }
    else {
      $language = NULL;
    }

    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('titleFull'));
    $title = ( is_array($result) ) ? reset($result) : $result;
    $dependent_title = $this->getDependentTitle();
    $ret = ( !empty($dependent_title) ) ? $title . " <br /> " . implode('. ', $dependent_title) : $title;
    if (!empty($language)) {
      $ret .= $language;
    }
    return $ret;
  }

  public function getLanguage(){
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('language'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getDependentTitle() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('dependentTitle'));
    return $result;
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

  public function getWorkType() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('workType'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return \stdClass
   */
  public function getWorkOne() {
    return isset($this->workOne) ? $this->workOne : NULL;
  }

  public function getAccessType(){
    $result = ting_openformat_methods::parseFields($this->manifestations, array('accessType'));
    return (is_array($result)) ? $result : array();
  }

  /**
   * @return bool
   */
  public function isOnline(){
    $manifestations = $this->getAccessType();
    if(is_array($manifestations)){
      foreach ($manifestations as $manifestation) {
        if($manifestation['accessType'] === 'online'){
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  public function getWorkTypes() {
    $result = ting_openformat_methods::parseFields($this->manifestations, array('workType'));
    $res = array();
    if(is_array($result)){
      foreach ($result as $index => $type) {
        $res[$type['workType']] = $type['workType'];
      }
    }
    return $res;
  }

  public function getType() {
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('type'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getManifestations(){
    return $this->manifestations;
  }

}
