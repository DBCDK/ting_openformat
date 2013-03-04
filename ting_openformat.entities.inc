<?php

class bibdkWork {

  public $id;
  public $ding_entity_id;
  public $description;
  public $work;
  public $manifestations = array();
  public $subWorks = array();

  public function __construct($work = NULL) {
    $this->work = $work;
  }
  public function getId(){
    return $this->id;
  }

  public function getISBN() {
    foreach ($this->manifestations as $manifestation) {
      $isbn = $manifestation->getIdentifiersISBN();
      if (isset($isbn['identifiersISBN'][0]['identifier'])) {
        return $isbn['identifiersISBN'][0]['identifier'];
        break;
      }
    }
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function setManifestations($manifestations) {
    foreach ($manifestations as $id => $manifestation) {
      $this->manifestations[$id] = entity_load('bibdkManifestation', $id, $manifestation);
    }
    // set subworks
    foreach ($this->manifestations as $id => $manifestation) {
      $type = $manifestation->getType();
      if ($type === NULL) {
        $type = t('unknown', array(), array('context' => 'ting_openformat'));
      }
      else if (!is_array($type)) {
        $type = array($type);
      }

      $subType = (is_array($manifestation->getSubType())) ? implode(' + ', $manifestation->getSubType()) : $manifestation->getSubType();
      // note: "surplus" types, and "undefined" types are to be handled in iScrum.
      foreach ($type as $typeGroup) {
        $subWorks[$typeGroup][$subType][$id] = $manifestation;
      }
    }
    foreach ($subWorks as $type => $sub) {
      foreach ($sub as $subtype => $manifestations) {
        $bibdkSubwork = entity_load('bibdkSubwork', $type, $manifestations);
        $bibdkSubwork->setSubType($subtype);
        $this->subWorks[] = $bibdkSubwork;
      }
    }

    // @TODO; should manifestations be sorted by sortkey ??
    // rewind manifestations array
    reset($this->manifestations);
    $top_manifestation = current($this->manifestations);
    // set work part
    $this->work = current($this->manifestations)->getWork();
  }

  public function getSubWorks() {
    return $this->subWorks;
  }

  public function getTitle() {
    $fields = array('titleFull');
    $elements = $this->work->title;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  private function _getDescription(){
    return (isset($this->work->description)) ? $this->work->description : NULL;

  }
  public function getAbstract() {
    $fields = array('abstract' => array('abstractElement'));
    $elements = $this->_getDescription();
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return $result;
  }

  public function getCreator() {
    $fields = array('creators' => array('creator' => "searchCode"));
    $elements = $this->work;
    $result = ting_openformat_methods::parseFields($elements, $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */
  public function getSubjects() {
    $fields = array('subjects' => array('subjectHeader' => 'header', 'subject' => 'searchCode'));
    $elements = $this->_getDescription();
    $result = ting_openformat_methods::parseFields($elements, $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

}

class   bibdkSubwork {

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
      foreach ($this->getManifestations() as $manifistation) {
        if ($manifistation->isReservable()) {
          $this->isReservable = TRUE;
          break;
        }
      }
    }
    return $this->isReservable;
  }

  public function isLink() {
    return FALSE;
  }

}

class bibdkCollection {

  //TODO fields should be private - currently being public for debug purpose
  private $manifestations;
  public $ding_entity_id;
  private $collectionTypes;
  private $collectionIds;

  function __construct($manifestation) {
    $this->manifestations = $manifestation['manifestations'];
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
    $result = ting_openformat_methods::parseFields($this->manifestations[0], array('title'));
    return (is_array($result)) ? reset($result) : $result;
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
}

/**
 * this class handles the Volume part of the manifestation
 */
class manifestationVolume extends manifestationMaster {

  public function __construct($volume) {
    $this->fields = $volume;
  }

  public function getTitle() {
    $fields = array('titleFull');
    if (isset($this->fields->title)) {
      $element = $this->fields->title;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

  public function getCreators() {
    $fields = array('creator' => 'searchCode');
    if (isset($this->fields->creators)) {
      $element = $this->fields->creators;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }
}

/**
 * this class handles the Section part of the manifestation
 */
class manifestationSection extends manifestationMaster {

  public function __construct($section) {
    $this->fields = $section;
  }

  public function getTitle() {
    $fields = array('titleFull');
    if (isset($this->fields->title)) {
      $element = $this->fields->title;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

  public function getCreators() {
    $fields = array('creator' => 'searchCode');
    if (isset($this->fields->creators)) {
      $element = $this->fields->creators;
      $result = ting_openformat_methods::parseFields($element, $fields);
      return (is_array($result)) ? reset($result) : $result;
    }
    return NULL;
  }

}

/**
 *-
 */
class manifestation extends manifestationMaster {

  /**
   * @param $manifestation
   */
  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
    $this->fields = $this->manifestation->main;
    //dpm($manifestation);
  }

  public function getWork() {

    return isset($this->manifestation->work) ? $this->manifestation->work : NULL;
  }

  /**
   * @return array|mixed|null
   */
  public function getTitle() {
    $fields = array('titleFull');
    $elements =isset($this->getWork()->title) ? $this->getWork()->title : NULL;
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
}

class manifestationMaster {

  public $id;
  public $ding_entity_id;
  public $manifestation;
  private $isReservable;
  protected $fields;

  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
  }

  private function _getDetails(){
    return isset($this->fields->details) ? $this->fields->details : NULL;
  }

  private function _getPublicationDetails(){
    return isset($this->fields->publicationDetails) ? $this->fields->publicationDetails : NULL;
  }

  /* \brief original title
   * zero or one occurence
   */

  public function getOriginalTitle() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('originalTitle' => array('originalTitleHeader' => 'header', "originalTitleElement")));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief alternative title
   * zero or more occurences
   */

  public function getAlternativeTitle() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('alternativeTitle' => array('alternativeTitleDescriptor' => 'header', "alternativeTitleElement")));
    return $result;
  }

  /* \brief contributors
   * zero or 1 occurence
   */

  public function getContributors() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('contributors'));
    return $result;
  }

  /* \brief format
   * zero or more occurence(s)
   */

  public function getFormat() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('format'));
    return $result;
  }

  /* \brief forms
   * zero or one occurence
   * formHeader 1 occurence
   * subelement formSubject 1 or more occurence(s)
   */

  public function getForms() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('forms' => array("formSubject"=>'searchCode')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief seriesTitle
   * zero or more occurence(s)
   * seriesHeader 1 or more occurence(s)
   * series 1 or more occurence(s)
   * seriesNumber zero or more occurence(s)
   */

  public function getSeriesTitle() {
    $elements = $this->_getDetails();
    $result = ting_openformat_methods::parseFields($elements, array('seriesTitle' => array('seriesHeader' => 'header', "series" => 'searchCode', "seriesNumber")));
    return $result;
  }

  /* \brief relatedSeriesTitle
   * zero or more occurence(s)
   * relatedSeriesHeader 1 or more occurence(s)
   * relatedSeries 1 or more occurence(s)
   */

  public function getRelatedSeriesTitle() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('relatedSeriesTitles' => array('relatedSeriesTitle' => array('relatedSeriesDescription' => 'header', "relatedSeries" => 'searchCode'))));
    return $result;
  }

  /* \brief readabilityIndexes
   * zero or more occurence(s)
   */

  public function getReadabilityIndexes() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('readabilityIndexes' => array('readabilityIndex')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief readabilityNumbers
    * zero or more occurence(s)
    */

  public function getReadabilityNumbers() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('readabilityNumbers' => array('readabilityNumber')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief shelf
   * zero or 1 occurence
   * shelfHeader 1 occurence
   * shelfMusic 0 or more occurence(s)
   * shelfClassification 0 or more occurence(s)
   */

  public function getShelf() {
    $fields = array("shelf" => array(
      'shelfHeader' => 'header',
      'shelfMusic',
      'shelfClassification' => "searchCode",
    )
    );
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief textlevels
     * zero or 1 occurence
     * textLevel 1  or occurence(s)
     */

  public function getTextLevels() {
    $fields = array("textLevels" => array(
      'textLevel' => 'searchCode',
    )
    );
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief genre
   * zero or more occurence(s)
   */

  public function getGenre() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('genre'));
    return $result;
  }

  /* \brief audienceSubjects
   * zero or 1 occurence
   * audienceSubjectHeader 1 occurence
   * audienceSubject 1 or more occurence(s)
   *    searchCode zero or 1 occurence
   *    display 1 occurrence
   */

  public function getAudienceSubjects() {
    $fields = array('audienceSubjects' => array('audienceHeader' => 'header', 'audienceSubject' => 'searchCode'));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief markedAudience
   * zero or more occurence(s)
   */

  public function getMarkedAudience() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('audienceMarked'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief recommendedAudience
   * zero or more occurence(s)
   */

  public function getRecommendedAudience() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('audienceAge'=> array('audienceAgeElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief audiencePegi
     * zero or more occurence(s)
     */

  public function getAudiencePegi() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('audiencePegi'=> array('audiencePegiElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief usedLanguage
   * zero or more occurence(s)
   */

  public function getUsedLanguage() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('usedLanguage'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief actorNote
   * zero or more occurence(s)
   */

  public function getActorNote() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('actorNote' => array('actorElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief descriptionNote
   * zero or more occurence(s)
   */

  public function getDescriptionNote() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('descriptionNote'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief contentPartialNote
     * zero or more occurence(s)
     */

  public function getContentPartialNote() {
    $fields = array(
      'contentPartialNote' => array('contentPartialNoteDescription', 'contentPartialNoteElement')
    );
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief contentNote
     * zero or more occurence(s)
     */

  public function getContentNote() {
    $fields = array(
      'contentNote' => array('contentNoteDescription', 'contentNoteElement')
    );
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief references
   * zero or more occurence(s)
   */

  public function getReferences() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('references'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief originals
   * zero or more occurence(s)
   */

  public function getOriginals() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('originals'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief context
   * zero or 1 occurence
   * contextElement zero or more occurence(s)
   */

  public function getContext() {
    $fields = array('context' => array('contextElement'));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief identifiers
   * zero or more occurence(s)
   * identifierHeader zero or 1 occurence
   * identifier zero or more occurence(s)
   */
  public function getIdentifiers() {
    $fields = array('identifiers' => array(
      'identifierDescriptor' => 'header',
      'identifier',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief identifiersISBN
   * zero or more occurence(s)
   * identifier zero or more occurence(s)
   */
  public function getIdentifiersISBN() {
    $fields = array('identifiersISBN' => array(
      'identifier',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief identifiersISMN
   * zero or more occurence(s)
   * identifier zero or more occurence(s)
   */
  public function getIdentifiersISMN() {
    $fields = array('identifiersISMN' => array(
      'identifier',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief identifiersISSN
   * zero or more occurence(s)
   * identifier zero or more occurence(s)
   */
  public function getIdentifiersISSN() {
    $fields = array('identifiersISSN' => array(
      'identifier',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief priceInformation
   * priceHeader zero or 1 occurence
   * price 1 occurence
   */

  public function getPriceInformation() {
    $fields = array('priceInformation' => array(
      'priceHeader' => 'header',
      'price',
      'acquisitionTerms',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief language
   * zero or 1 occurence
   * languageHeader 1 occurence
   * languageElement 1 occurence
   */

  public function getLanguage() {
    $fields = array('language' => array(
      'languageHeader' => 'header',
      'languageElement',
    ));
    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief accessInformation
   * zero or 1 occurence
   * accessUrl 1 or more occurence(s)
   */
  public function getAccessInformation() {
    $fields = array('accessInformation' => array(
      'accessUrl',
    ));

    $result = ting_openformat_methods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief publisher
   * zero or more occurences
   */
  public function getPublisher() {
    $fields = array('publisher');
    $result = ting_openformat_methods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief publicationYear
   * zero or more occurences
   */
  public function getPublicationYear() {
    $fields = array('publicationYear');
    $result = ting_openformat_methods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief edition
     * zero or more occurences
     */
  public function getEdition() {
    $fields = array('edition');
    $result = ting_openformat_methods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief (publication)format
       * zero or more occurences
       */
  public function getPublicationFormat() {
    $fields = array('format');
    $result = ting_openformat_methods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief hostPublication
       * zero or more occurences
       */
  public function getHostPublication() {
    $fields = array('hostPublication');
    $result = ting_openformat_methods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }
}

class ting_openformat_methods {

  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form []['display','searchCode']
   */

  private static function _parseSearchCode($stdObjects) {
    if (!is_array($stdObjects)) {
      $stdObjects = array($stdObjects);
    }

    foreach ($stdObjects as $object) {
      $subject['searchCode'] = self::_getSearchCodeElement($object->searchCode);
      $subject['display'] = isset($object->display) ? $object->display->{'$'} : NULL;
      $ret[] = $subject;
    }

    return $ret;
  }

  private static function _getSearchCodeElement($stdObject) {
    $value = (isset($stdObject->{'$'})) ? $stdObject->{'$'} : NULL;

    if (isset($stdObject->{'@phrase'})) {
      $term = $stdObject->{'@phrase'}->{'$'};
    }
    elseif (isset($stdObject->{'@word'})) {
      $term = $stdObject->{'@word'}->{'$'};
    }

    if (isset($value) && isset($term)) {
      return $term . "=" . $value;
    }
    else {
      return;
    }
  }

  public static function parseFields($object, array $fields) {
    $ret = NULL;
    if (!isset($object)) {
      return NULL;
    }
    if (is_array($object)) {
      foreach ($object as $o) {
        if (isset($o)) {
          $ret[] = self::parseFields($o, $fields);
        }
      }
      return $ret;
    }

    foreach ($fields as $field => $value) {
      if (is_array($value) && isset($object->$field)) {
        $ret[$field][] = self::parseFields($object->$field, $value);
      }
      elseif ($value == 'searchCode' && isset($object->$field)) {
        $ret[$field][] = self::_parseSearchCode($object->$field);
      }
      elseif ($value == 'header' && isset($object->$field)) {
        $ret[$value] = $object->$field->{'$'};
      }
      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {

        foreach ($object->$value as $val) {
          $ret[$value][] = $val->{'$'};
        }
      }
      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value)) {
        $ret[$value] = $object->$value->{'$'};
      }
    }
    return $ret;
  }

}
