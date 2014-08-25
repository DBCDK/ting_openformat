<?php

/**
 * -
 */
class Manifestation extends ManifestationMaster {

  private $briefDisplayType;
  private $subType;

  /**
   * @param $manifestation
   */
  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
    if (isset($this->manifestation->main)) {
      $this->fields = $this->manifestation->main;
    }
    $this->getAnalyticContent();
  }

  /**
   * @return string|null
   */
  public function getWork() {
    return isset($this->manifestation->work) ? $this->manifestation->work : NULL;
  }

  public function getDependentTitle() {
    $fields = array('dependentTitle');
    $elements = isset($this->getWork()->title) ? $this->getWork()->title : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return string|null
   */
  public function getTitle() {
    $fields = array('titleFull');
    $elements = isset($this->getWork()->title) ? $this->getWork()->title : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return string|null
   */
  public function getTitleSpecific() {
    $fields = array('titleSpecific');
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

  /**
   * Return ID as array
   *
   * @return array
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
    return $requestMethod = ( $this->getRequestButton() == 'true' ) ? TRUE : FALSE;
    /* do we need the old method as a fallback?
    $requestMethod = $this->getRequestMethod();
    return (!isset($requestMethod) || $requestMethod == 'newMaterial' || $requestMethod == 'oldMaterial') ? TRUE : FALSE;
    */
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

  /**
   * @return array|mixed|null
   */
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

  /**
   * @return array|mixed|null
   */
  public function getMessageCategory(){
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('messageCategory'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * Distinction
   * zero or more occurence(s)
   */
  public function getDistinction() {
    $result = ting_openformat_methods::parseFields($this->fields, array('distinction'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * requestButton
   * zero or one occurence
   */
  public function getRequestButton() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('requestButton'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * requestMethod
   * zero or one occurence
   */
  public function getRequestMethod() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('requestMethod'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * restrictedUse
   * zero or one occurence
   */
  public function getRestrictedUse() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('restrictedUse'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * Set eksternal type. Typically from briefdisplay
   * @param $type
   */
  public function setBriefDisplayType($type) {
    $this->briefDisplayType = $type;
  }

  /** get external type
   * @return mixed
   */
  public function getBriefDisplayType() {
    return $this->briefDisplayType;
  }

  /**
   * Set eksternal type. Typically from briefdisplay
   * @param $type
   */
  public function setSubType($type) {
    $this->subType = $type;
  }

  /**
   * type of manifestation
   * 1 occurence
   */
  public function getSubType() {
    $result = isset($this->subType) ? $this->subType : ting_openformat_methods::parseFields($this->manifestation->main, array('type'));
    if (isset($result['type']) && is_array($result['type'])) {
      $result['type'] = implode(' + ', $result['type']);
    }

    return (is_array($result)) ? reset($result) : $result;
  }

  public function getOrsOrderMaterialType() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('orsOrderMaterialType'));

    return (is_array($result)) ? reset($result) : $result;
  }

  public function getWebArchive() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('webArchive'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * Gets 'typeGroup'. If you need 'type' see: getSubType()
   * @return array|mixed|null
   * @see getSubType()
   */
  public function getType() {
    $result = (isset($this->type)) ? array($this->type) : ting_openformat_methods::parseFields($this->manifestation->adminData, array('typeGroup'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return bool
   */
  public function getSpecifyArticleData() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('specifyArticleData'));
    return filter_var(reset($result), FILTER_VALIDATE_BOOLEAN);
  }

  /**
   * @return null|array
   */
  public function getVolume() {
    if (!isset($this->manifestation->volume)) {
      return NULL;
    }
    else {
      return $this->manifestation->volume;
    }
  }

  /**
   * @return null|array
   */
  public function getSection() {
    if (!isset($this->manifestation->section)) {
      return NULL;
    }
    else {
      return $this->manifestation->section;
    }
  }

  /**
   * @return bool
   */
  public function getInfomediaLink() {
    if (!isset($this->manifestation->relationsData)) {
      return FALSE;
    }

    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOnlineAccess' && strpos($relation->relationUri, 'useraccessinfomedia') !== FALSE) {
        return $relation->relationUri;
      }
    }

    return FALSE;
  }

  /**
   * @return bool
   */
  public function getRelationUri(){
    if (!isset($this->manifestation->relationsData)) {
      return FALSE;
    }

    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOnlineAccess' ) {
        return $relation->relationUri;
      }
    }
    return FALSE;
  }

  /**
   * @return array
   */
  public function getNewsPaperReviews() {
    if (!isset($this->manifestation->relationsData)) {
      return array();
    }
    $reviews = array();
    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasReview' && ((strpos($relation->relationUri, '870976') === FALSE))) {
        $reviews[$relation->relationUri] = $relation->relationUri;
      }
    }

    return $reviews;
  }

  /**
   * @return array
   */
  public function getMaterialReview() {

    if (!isset($this->manifestation->relationsData)) {
      return array();
    }
    $reviews = array();
    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasReview' && strpos($relation->relationUri, '870976-anmeld') !== FALSE) {
        $reviews[] = $relation->relationUri;
      }
    }

    return $reviews;
  }


  /**
   * @return array
   */
  public function getDebateLinks() {
    if ( !isset($this->manifestation->relationsData) ) {
      return NULL;
    }
    $debates = array();
    foreach ( $this->manifestation->relationsData as $relation ) {
      $debate = array();
      if ( $relation->relationType == 'dbcaddi:discussedIn' ) {
        $debate['discussed_in']['searchCode'] = 'rec.id=' . $relation->relationUri;
        $debate['discussed_in']['display'] = t('debate_discussed_in', array(), array('context' => 'ting_openformat'));
        $debates[] = $debate;
      }
      if ( $relation->relationType == 'dbcaddi:continuedIn' ) {
        $debate['continued_in']['searchCode'] = 'rec.id=' . $relation->relationUri;
        $debate['continued_in']['display'] = t('debate_continued_in', array(), array('context' => 'ting_openformat'));
        $debates[] = $debate;
      }
      if ( $relation->relationType == 'dbcaddi:discusses' ) {
        $debate['discusses']['searchCode'] = 'rec.id=' . $relation->relationUri;
        $debate['discusses']['display'] = t('debate_discusses', array(), array('context' => 'ting_openformat'));
        $debates[] = $debate;
      }
      if ( $relation->relationType == 'dbcaddi:continues' ) {
        $debate['continues']['searchCode'] = 'rec.id=' . $relation->relationUri;
        $debate['continues']['display'] = t('debate_continues_discussion', array(), array('context' => 'ting_openformat'));
        $debates[] = $debate;
      }
    }
    return empty($debates) ? NULL : $debates;
  }


  /**
   * @return array|mixed|null
   */
  public function getHostPublicationID() {
    $result = ting_openformat_methods::parseFields($this->manifestation->adminData, array('hostPublicationID'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return array|mixed|null
   */
  public function getReviewRatings() {
    $fields = array('reviewRatings');
    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }


  /**
   * Return the first AccessUrl element in the AccessInformation Array
   * @return array|null
   */
  public function getSingleAccessUrl() {
    if (isset($this->manifestation->volume) && is_object($this->manifestation->volume)) {
      $urls = ting_openformat_methods::parseFields($this->manifestation->volume->details->accessInformation, array('accessUrl'));
    }
    else {
      $urls = ting_openformat_methods::parseFields($this->manifestation->main->details->accessInformation, array('accessUrl'));
    }
    while (is_array($urls)) {
      if (isset($urls['accessUrl'])) {
        return $urls;
      }
      else {
        return reset($urls);
      }
    }

    return NULL;
  }

}
