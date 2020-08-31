<?php

/**
 * -
 */
class Manifestation extends ManifestationMaster {

  private $briefDisplayType;
  private $subType;
  private $subtypeOrderIds;

  /**
   * @param $manifestation
   */
  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
    if (isset($this->manifestation->main)) {
      $this->fields = $this->manifestation->main;
    }
    // NB! OLD VERSION - to be removed when new bibdkWorkDisplay format is fully implemented
    $this->getAnalyticContent();
    // New bibdkWorkDisplay
    $this->getTrackContent();
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
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return string|null
   */
  public function getTitle() {
    $fields = array('titleFull');
    $elements = isset($this->getWork()->title) ? $this->getWork()->title : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return string|null
   */
  public function getTitleSpecific() {
    $fields = array('titleSpecific');
    $elements = isset($this->getWork()->title) ? $this->getWork()->title : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return array|mixed|null
   */
  public function getCreator() {
    $fields = array('creators' => array('creator' => 'searchCode'));
    $elements = $this->getWork();
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */
  public function getSubjects() {
    $fields = array('subjects' => array('subjectHeader' => 'header', 'subject' => 'searchCode'));
    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return $result;
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */
  public function getLaesekompasSubjects() {
    $fields = array('subjectsLaesekompas' => array('subjectHeader' => 'header', 'subject' => 'searchCode'));
    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return $result;
  }

  public function getAbstract() {
    $fields = array('abstract' => array('abstractElement'));

    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);

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
    return ( $this->getRequestButton() == 'true' ) ? TRUE : FALSE;
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

  public function hasDirectLink() {
    $directLinks = array('link', 'plusLink', 'linkE17', 'restrictedAccess', 'noAccess');
    return in_array($this->getInfotext(), $directLinks);
  }

  /**
   * Check if material is a special type of non-borrowable ebook
   */
  public function isEbook() {
    if ($this->getInfotext() == 'restrictedAccess' && $this->hasType('literature') && $this->hasType('online') && $this->isLink()) {
      return true;
    }
    else {
      return false;
    }
  }

  /** Check if manifestation is of a certain kind
   * @param $type
   * @return bool
   */
  public function hasType($type) {
    $manifestation_types = is_array($this->getType()) ? $this->getType() : array($this->getType());
    return in_array($type, $manifestation_types);
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

    $display_version = variable_get('ting_search_openformat', 'bibliotekdkWorkDisplay');

    if ($display_version === 'bibdkWorkDisplay' &&
        $this->getTypeGroup() !== 'online' && $this->getTypeGroup() !== 'article' &&
        $this->getHoldingsCount() === '0') {
      return 'noHoldings';
    }

    // #US-2018 and bug: 20616 - special case
    if (isset($requestMethod) && $requestMethod == 'none' && $restrictedUse == '') {
      return 'restrictedAccessNoLink';
    }

    return NULL;
  }

  /**
   * @return array|mixed|null
   */
  public function getMessageCategory() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('messageCategory'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * Distinction
   * zero or more occurence(s)
   */
  public function getDistinction() {
    $result = TingOpenformatMethods::parseFields($this->fields, array('distinction'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * requestButton
   * zero or one occurence
   */
  public function getRequestButton() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('requestButton'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * typeGroup
   * zero or one occurence
   * @return string|null
   */
  public function getTypeGroup() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('typeGroup'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * holdingsCount
   * zero or one occurence
   * @return string|null
   */
  public function getHoldingsCount() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('holdingsCount'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * requestMethod
   * zero or one occurence
   */
  public function getRequestMethod() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('requestMethod'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * restrictedUse
   * zero or one occurence
   */
  public function getRestrictedUse() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('restrictedUse'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * getRestrictedExtendedUse  url: login, proxy, onsite, hasopenUrl, restrictedAccess and hasopenUrl
   * return zero or one occurence
   */
  public function getRestrictedExtendedUse() {
    if (!isset($this->manifestation->relationsData)) {
      return '';
    }

    //priority 1  - login
    foreach ($this->manifestation->relationsData as $relation) {
      if (isset($relation->linkObject->access->{'$'})) {
        if ($relation->relationType == 'dbcaddi:hasOnlineAccess' &&($relation->linkObject->access->{'$'} == 'login')) {
          if (isset($relation->linkObject->linkTo->{'$'})) {
            if ($relation->linkObject->linkTo->{'$'} != 'webservice') {
              // extra check - only linkTo != webservice
              return $relation->relationUri;
            }
          } else {
            return $relation->relationUri;
          }
        }
      }
    }

    //priority 2  - proxy
    foreach ($this->manifestation->relationsData as $relation) {
      if (isset($relation->linkObject->access->{'$'})) {
        if ($relation->relationType == 'dbcaddi:hasOnlineAccess' &&($relation->linkObject->access->{'$'} == 'proxy')) {
          return $relation->relationUri;
        }
      }
    }
    //priority 3  - onsite
    foreach ($this->manifestation->relationsData as $relation) {
      if (isset($relation->linkObject->access->{'$'})) {
        if ($relation->relationType == 'dbcaddi:hasOnlineAccess' &&($relation->linkObject->access->{'$'} == 'onsite')) {
          return $relation->relationUri;
        }
      }
    }
    //priority 4  - hasopenUrl
    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOpenUrl') {
        if ($this->getType() == 'article') {
          if (!$this->getSingleaccessUrlDisplay() || $this->getSingleaccessUrlDisplay() != 'urlInternetPublic') {
            return $relation->relationUri;
          }
        }
      }
    }
    //priority 5  - restrictedAccess and hasopenUrl
    if ($this->getRestrictedUse() == 'restrictedAccess') {
      foreach ($this->manifestation->relationsData as $relation) {
        if ($relation->relationType == 'dbcaddi:hasOpenUrl') {
          return $relation->relationUri;
        }
      }
    }

    return '';
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
    if (!isset($this->manifestation->main)) {
      return FALSE;
    }
    $result = isset($this->subType) ? $this->subType : TingOpenformatMethods::parseFields($this->manifestation->main, array('type'));
    if (isset($result['type']) && is_array($result['type'])) {
      $result['type'] = implode(' + ', $result['type']);
    }
    return (is_array($result)) ? reset($result) : $result;
  }


  /**
   * Gets 'orsOrderMaterialType'.
   * @return array|mixed|null
   */
  public function getOrsOrderMaterialType() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('orsOrderMaterialType'));
    return (is_array($result)) ? reset($result) : $result;
  }


  /**
   * Gets 'webArchive'.
   * @return array|mixed|null
   */
  public function getWebArchive() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('webArchive'));
    return (is_array($result)) ? reset($result) : $result;
  }


  /**
   * Gets 'typeGroup'. If you need 'type' see: getSubType()
   * @return array|mixed|null
   * @see getSubType()
   */
  public function getType() {
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = (isset($this->type)) ? array($this->type) : TingOpenformatMethods::parseFields($this->manifestation->adminData, array('typeGroup'));
    // <hack>: Until openFormat is 'unfrozen', we'll use getOrsOrderMaterialType() to see if type is 'periodical'
    //         Delete once openFormat return periodical types.
    if ($result['typeGroup'] == 'none' && $this->getOrsOrderMaterialType() == 'journal') {
      return 'periodical';
    }
    // </hack>

    // <workaround>: type 'Blu-ray 4K' has typeGroup:other. Requires an update of bibliotekdkWorkDisplay
    // Delete when new openFormat is in place (and support Blu-ray 4K -> workType:movie )
    elseif ($result['typeGroup'] == 'none') {
      $type = isset($this->subType) ? $this->subType : TingOpenformatMethods::parseFields($this->manifestation->main, array('type'));
      if ($type == 'Blu-ray 4K') {
        return 'movie';
      }
    }
    // </workaround>

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * Gets schema.org CreativeWork type.
   * @return array|mixed|null
   */
  public function getSchemaOrgType() {
    $default = 'CreativeWork';
    if (!is_object($this->manifestation)) {
      return $default;
    }
    if (!isset($this->manifestation->{'@schemaType'}) || !is_object($this->manifestation->{'@schemaType'})) {
      return $default;
    }
    $result = $this->manifestation->{'@schemaType'}->{'$'};
    if (!$result) {
      return $default;
    }
    return (is_array($result)) ? reset($result) : $result;
  }


  /**
   * @return bool
   */
  public function getSpecifyArticleData() {
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('specifyArticleData'));
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

  public function getRemoteAccess(){

    if (!isset($this->manifestation->relationsData)) {
      return FALSE;
    }

    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOnlineAccess' ) {
        if($relation->linkObject->access->{'$'} == 'remote') {
          return $relation->relationUri;
        }
      }
    }
    return FALSE;
  }

  public function getlinkCollectionIdentifier() {
    if (!isset($this->manifestation->relationsData)) {
      return FALSE;
    }
    foreach ($this->manifestation->relationsData as $relation) {
      if ($relation->relationType == 'dbcaddi:hasOnlineAccess' ) {
          if(isset($relation->linkObject->linkCollectionIdentifier)) {
            if(is_array($relation->linkObject->linkCollectionIdentifier)){
              return current($relation->linkObject->linkCollectionIdentifier)->{'$'};
            }
            else{
              return $relation->linkObject->linkCollectionIdentifier->{'$'};
            }
        }
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
    if (!isset($this->manifestation->adminData)) {
      return FALSE;
    }
    $result = TingOpenformatMethods::parseFields($this->manifestation->adminData, array('hostPublicationID'));

    return (is_array($result)) ? reset($result) : $result;
  }

  /**
   * @return array|mixed|null
   */
  public function getReviewRatings() {
    $fields = array('reviewRatings');
    $elements = isset($this->getWork()->description) ? $this->getWork()->description : NULL;
    $result = TingOpenformatMethods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }



  /**
   * Return the accessUrlDisplay element in the AccessInformation Array
   * @return array|null
   */
  public function getSingleaccessUrlDisplay() {
    if (isset($this->manifestation->main->details->accessInformation)) {
      $urls = TingOpenformatMethods::parseFields($this->manifestation->main->details->accessInformation, array('accessUrlDisplay'));
      return $urls['accessUrlDisplay'];
    }
    return NULL;
  }

  /**
   * Return the first AccessUrl element in the AccessInformation Array
   * @return array|null
   */
  public function getSingleAccessUrl() {
    if (isset($this->manifestation->volume) && is_object($this->manifestation->volume)) {
      $urls = TingOpenformatMethods::parseFields($this->manifestation->volume->details->accessInformation, array('accessUrl'));
    }
    else {
      if (isset($this->manifestation->main->details->accessInformation)) {
        $urls = TingOpenformatMethods::parseFields($this->manifestation->main->details->accessInformation, array('accessUrl'));
      } else {
        return NULL;
      }
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

  /**
   * Return Get accessInformation from volume tag
   * @return result array or NULL if volume tag do not exist
   */
  public function getVolumeAccessInformation() {
    $fields = array(
      'accessInformation' => array(
        'accessUrl',
        'accessUrlDescriptor',
        'accessUrlDisplay',
      )
    );
    $VolumeTag = $this->getVolume();
    if (isset($VolumeTag)) {
      // get accessinformation from volume tag
      $result = TingOpenformatMethods::parseFields($VolumeTag->details, $fields);
      return $result;
    }
    return NULL;
  }

  public function setSubtypeOrderIds($ids) {
    $this->subtypeOrderIds = $ids;
  }

  public function getSubtypeOrderIds() {
    return $this->subtypeOrderIds;
  }

}
