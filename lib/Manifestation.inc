<?php

/**
 * -
 */
class Manifestation extends ManifestationMaster {

  /**
   * @param $manifestation
   */
  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
    $this->fields = $this->manifestation->main;
    $this->getAnalyticContent();
  }

  public function getWork() {
    return isset($this->manifestation->work) ? $this->manifestation->work : NULL;
  }

  private function _getContent(){
    return isset($this->fields->content) ? $this->fields->content : NULL;
  }

  /**
   * @return array|mixed|null
   */
  public function getTitle() {
    $fields = array('titleFull');
    $elements = isset($this->getWork()->title) ? $this->getWork()->title : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return array|mixed|null
   */
  public function getCreator() {
    $fields = array('creators' => array('creator' => 'searchCode'));
    $elements = $this->getWork();
    $result = ting_openformat_methods::parseFields($elements, $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */
  public function getSubjects() {
    $fields = array('subjects' => array('subjectHeader' => 'header', 'subject' => 'searchCode'));
    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);
    return $result;
  }

  public function getAbstract() {
    $fields = array('abstract' => array('abstractElement'));

    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);
    return $result;
  }

  public function getAnalyticContent(){
    $fields = array('analyticContent' => array(
      'analyticContributor' => 'searchCode',
      'analyticTitle' => array('analyticTitleMain' => 'searchCode', 'analyticRestOfTitle')
    ));
    $result = ting_openformat_methods::parseFields($this->_getContent(), $fields);
    return $result;
  }

  /* \brief contentPartialNote
   * zero or more occurence(s)
   */

  public function getContentPartialNote() {
    $fields = array(
      'contentPartialNote' => array('contentPartialNoteDescription', 'contentPartialNoteElement')
    );
    $result = ting_openformat_methods::parseFields($this->_getContent(), $fields);
    return $result;
  }

  /* \brief contentNote
   * zero or more occurence(s)
   */

  public function getContentNote() {
    $fields = array(
      'contentNote' => array('contentNoteDescription', 'contentNoteElement')
    );
    $result = ting_openformat_methods::parseFields($this->_getContent(), $fields);
    return $result;
  }

  /*
   * Return ID as array
   */

  public function getIDs() {
    return array($this->id);
  }

  /**
   * Can a manifestation be booked
   *
   * @return Boolean
   */
  public function isReservable() {
    $requestMethod = $this->getRequestMethod();
    return (!isset($requestMethod)) ? TRUE : FALSE;
  }

  /**
   * Shall Reservation button be a link
   *
   * @return boolean
   */
  public function isLink() {
    $requestMethod = $this->getRequestMethod();
    return ($requestMethod == 'link') ? TRUE : FALSE;
  }

  public function getInfotext() {
    $restrictedUse = $this->getRestrictedUse();
    $restrictedUse = (is_array($restrictedUse)) ? reset($restrictedUse) : $restrictedUse;
    $requestMethod = $this->getRequestMethod();
    $requestMethod = (is_array($requestMethod)) ? reset($requestMethod) : $requestMethod;
    if (isset($restrictedUse)) {
      return $restrictedUse;
    }
    elseif (isset($requestMethod) && $requestMethod != 'none' && $requestMethod != 'Old') {
      return $requestMethod;
    }
    return NULL;
  }

  /* \brief requestMethod
   * zero or one occurence
   */

  public function getRequestMethod() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('requestMethod'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief restrictedUse
   * zero or one occurence
   */

  public function getRestrictedUse() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('restrictedUse'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief type of manifestation
   * 1 occurence
   */

  public function getSubType() {
    $result = ting_openformat_methods::parseFields($this->manifestation->main, array('type'));
    if (is_array($result['type'])) {
      $result['type'] = implode(' + ', $result['type']);
    }
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getOrsOrderMaterialType() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('orsOrderMaterialType'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getType() {
    // NB: gets 'typeGroup'. If you need 'type' see: getSubType()
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('typeGroup'));
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getVolume() {
    if (!isset($this->manifestation->volume)) {
      return NULL;
    }
    else {
      return $this->manifestation->volume;
    }
  }

  public function getSection() {
    if (!isset($this->manifestation->section)) {
      return NULL;
    }
    else {
      return $this->manifestation->section;
    }
  }

  public function getInfomediaLink() {
    if (!isset($this->manifestation->relationsData)) {
      return FALSE;
    }

    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOnlineAccess' && $this->manifestation->main->type->{'$'} == 'Avisartikel') {
        return $relation->relationUri;
      }
    }
    return FALSE;
  }

  public function getMaterialReview() {
    if (!isset($this->manifestation->relationsData)) {
      return array();
    }
    $reviews = array();
    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasReview' && strpos($relation->relationUri, '870976-anmeld') !== false) {
        $reviews[] = $relation->relationUri;
      }
    }

    return $reviews;
  }

}