<?php

class bibdkWork {

  public $id;
  public $ding_entity_id;
  public $work;
  public $manifestations = array();
  public $subWorks = array();

  public function __construct($work = NULL) {
    $this->work = $work;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function setManifestations($manifestations) {
    foreach ($manifestations as $id => $manifestation) {
      $this->manifestations[$id] = entity_load('bibdkManifestation', $id, $manifestation);
    }

    // pjo testing -- also set subworks
    foreach( $this->manifestations as $id => $manifestation ) {
      $subWorks[$manifestation->getType()][$id] = $manifestation;
    }
    foreach( $subWorks as $type => $manifestations ) {
      $this->subWorks[current($manifestations)->id] = entity_load('bibdkSubwork', $type, $manifestations);
    }
  }

  public function getSubWorks (){
    return $this->subWorks;
  }

  public function getTitle() {
    return $this->work->title->titleFull->{'$'};
  }

  public function getCreator() {
    $creators = isset($this->work->creators->creator) ? $this->work->creators->creator : NULL;

    if (empty($creators)) {
      return array();
    }

    if (!is_array($creators)) {
      $creators = array($creators);
    }

    return ting_openformat_methods::parseSearchCode($creators);
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */
  public function getSubjects() {
    $subjects = isset($this->work->description->subjects->subject) ? $this->work->description->subjects->subject : NULL;

    if (empty($subjects)) {
      return array();
    }

    if (!is_array($subjects)) {
      $subjects = array($subjects);
    }

    return ting_openformat_methods::parseSearchCode($subjects);
  }

}

class bibdkSubwork{
  public $id;
  public $ding_entity_id;
  public $manifestations = array();
  public $type;
  private$isReservable;
  
  public function __construct($type, $manifestations) {
    $this->type = $type;
    $this->manifestations = $manifestations;
  }
  
  public function getIDs(){
    $ids = array();
    foreach($this->getManifestations() as $manifistation){
      $ids[] = $manifistation->id;
  }
  return $ids;
  } 
  
  public function getManifestations() {
    return $this->manifestations;
  }

  public function getType (){
    return $this->type;
  }

  public function isReservable (){
    if (!isset($this->isReservable)){
      $this->isReservable = false;
      foreach($this->getManifestations() as $manifistation){
        if ($manifistation->isReservable()){
          $this->isReservable = true;
          break;
        }
      }
    }
    
    return $this->isReservable;
  }
  
}

class manifestation {

  public $id;
  public $ding_entity_id;
  public $manifestation;
  private $isReservable;

  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
  }
  
  /*
   * Return ID as array
   */
  public function getIDs (){
    return array($this->id); 
  }
  
  /*
   * Retuns orderability manifistation
   */
  public function isReservable(){
    return ($this->getRequestMethod() == "none")? false : true;
  } 
    
  /* \brief requestMethod
   * zero or one occurence
   */
  public function getRequestMethod(){
    return isset($this->manifestation->adminData->requestMethod->{'$'}) ? $this->manifestation->adminData->requestMethod->{'$'} : FALSE;
    
  }
  
  /* \brief restrictedUse
   * zero or one occurence
   */
  public function getRestrictedUse() {
    return isset($this->manifestation->adminData->restrictedUse->{'$'}) ? $this->manifestation->adminData->restrictedUse->{'$'} : FALSE;
  }
  
  
  /* \brief type of manifestation
   * 1 occurence
   */
  public function getType() {
    return $this->manifestation->type->{'$'};
  }

  /* \brief original title
   * zero or one occurence
   */

  public function getOriginalTitle() {
    return isset($this->manifestation->details->originalTitle->{'$'}) ? $this->manifestation->details->originalTitle->{'$'} : FALSE;
  }

  /* \brief alternative title
   * zero or more occurences
   */

  public function getAlternativeTitle() {
    $titels = isset($this->manifestation->details->alternativeTitle) ? $this->manifestation->details->alternativeTitle : NULL;

    if (empty($titles)) {
      return array();
    }

    if (!is_array($titles)) {
      $titles = array($titles);
    }

    foreach ($titles as $key => $val) {
      // zero or one occurence
      $title['Header'] = isset($val->alternativeTitleHeader->{'$'}) ? $val->alternativeTitleHeader->{'$'} : NULL;
      // 1 occurence
      $title['Element'] = $val->alternativeTitleElement->{'$'};
      $ret[] = $title;
    }
    return $ret;
  }

  /* \brief contributors
   * zero or 1 occurence
   */

  public function getContributors() {
    return isset($this->manifestation->details->contributors->{'$'}) ? $this->manifestation->details->contributors->{'$'} : FALSE;
  }

  /* \brief format
   * zero or more occurence(s)
   */

  public function getFormat() {
    $formats = isset($this->manifestation->details->format) ? $this->manifestation->details->format : NULL;

    if (empty($formats)) {
      return array();
    }

    if (!is_array($formats)) {
      $formats = array($formats);
    }

    foreach ($formats as $key => $val) {
      $ret[] = $val->format->{'$'};
    }
    return $ret;
  }

  /* \brief forms
   * zero or one occurence
   * formHeader 1 occurence
   * subelement formSubject 1 or more occurence(s)
   */

  public function getForms() {
    $forms = isset($this->manifestation->details->forms) ? $this->manifestation->details->forms : NULL;

    if (!isset($forms)) {
      return FALSE;
    }

    $ret['formHeader'] = $this->manifestation->details->format->formHeader->{'$'};
    $formSubjects = $this->manifestation->details->format->formSubject;
    if (!is_array($formSubjects)) {
      $formSubjects = array($formSubjects);
    }

    $ret['formSubjects'] = ting_openformat_methods::parseSearchCode($formSubjects);

    return $ret;
  }

  /* \brief seriesTitle
   * zero or more occurence(s)
   * seriesHeader 1 or more occurence(s)
   * series 1 or more occurence(s)
   * seriesNumber zero or more occurence(s)
   */

  public function getSeriesTitle() {
    $seriesTitles = isset($this->manifestation->details->seriesTitle) ? $this->manifestation->details->seriesTitle : NULL;
    if (!isset($seriesTitles)) {
      return FALSE;
    }

    if (!is_array($seriesTitles)) {
      $seriesTitles = array($seriesTitles);
    }

    foreach ($seriesTitles as $seriesTitle) {
      $seriesHeader = $seriesTitle->seriesHeader->{'$'};
      $series = $seriesTitle->series;
      if (!is_array($series)) {
        $series = array($series);
      }
      $series = ting_openformat_methods::parseSearchCode($series);
      $seriesNumber = isset($seriesTitle->seriesNumber) ? $seriesTitle->seriesNumber->{'$'} : NULL;
      $ret[] = array(
        'seriesHeader' => $seriesHeader,
        'series' => $series,
        'seriesNumber' => $seriesNumber,
      );
    }
    return $ret;
  }

  /* \brief relatedSeriesTitle
   * zero or more occurence(s)
   * relatedSeriesHeader 1 or more occurence(s)
   * relatedSeries 1 or more occurence(s)
   */

  public function getRelatedSeriesTitle() {
    $relatedSeries = isset($this->manifestation->details->relatedSeriesTitle) ? $this->manifestation->details->relatedSeriesTitle : NULL;

    if (!isset($relatedSeries)) {
      return FALSE;
    }

    if (!is_array($relatedSeries)) {
      $relatedSeries = array($relatedSeries);
    }

    foreach ($relatedSeries as $relatedSerie) {
      $Header = $relatedSerie->relatedSeriesHeader->{'$'};

      $rel_serie['relatedSeriesHeader'] = $Header;

      $series = $relatedSerie->relatedSeries;
      if (!is_array($series)) {
        $series = array($series);
      }

      $rel_serie['relatedSeries'] = ting_openformat_methods::parseSearchCode($series);

      $ret[] = $rel_serie;
    }

    return $ret;
  }

  /* \brief readabilityIndexes
   * zero or more occurence(s)
   */

  public function getReadabilityIndexes() {
    $readabilityIndexes = isset($this->manifestation->details->readabilityIndexes) ? $this->manifestation->details->readabilityIndexes : NULL;
    if (!is_array($readabilityIndexes)) {
      $readabilityIndexes = array($readabilityIndexes);
    }

    foreach ($readabilityIndexes as $readabilityIndex) {
      $ret[] = $readabilityIndexes->readabilityIndex->{'$'};
    }
    return $ret;
  }

  /* \brief shelf
   * zero or 1 occurence
   * shelfHeader 1 occurence
   * shelfMusic 0 or more occurence(s)
   * shelfClassification 0 or more occurence(s)
   */

  public function getShelf() {
    $fields = array(
      'shelfHeader' => 'shelfHeader',
      'shelfMusic' => 'shelfMusic',
      'shelfClassification' => array(
        'display' => 'display',
        'searchCode' => 'searchCode',
        'className' => '@className'
      )
    );

    $object = isset($this->manifestation->details->shelf) ? $this->manifestation->details->shelf : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }

  /* \brief genre
   * zero or more occurence(s)
   */

  public function getGenre() {
    return isset($this->manifestation->details->genre->{'$'}) ? $this->manifestation->details->genre->{'$'} : NULL;
  }

  /* \brief audienceSubjects
   * zero or 1 occurence
   * audienceSubjectHeader 1 occurence
   * audienceSubject 1 or more occurence(s)
   *    searchCode zero or 1 occurence
   *    display 1 occurrence
   */

  public function getAudienceSubjects() {
    $fields = array(
      'audienceHeader' => 'audienceHeader',
      'audienceSubject' => array(
        'display' => 'display',
        'searchCode' => 'searchCode',
      )
    );

    $object = isset($this->manifestation->details->audienceSubjects) ? $this->manifestation->details->audienceSubjects : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }

  /* \brief markedAudience
   * zero or more occurence(s)
   */

  public function getMarkedAudience() {
    $objects = isset($this->manifestation->details->markedAudience) ? $this->manifestation->details->markedAudience : NULL;

    if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief recommendedAudience
   * zero or more occurence(s)
   */

  public function getRecommendedAudience() {
    $objects = isset($this->manifestation->details->recommendedAudience) ? $this->manifestation->details->recommendedAudience : NULL;

    if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief usedLanguage
   * zero or more occurence(s)
   */

  public function getUsedLanguage() {
    $objects = isset($this->manifestation->details->usedLanguage) ? $this->manifestation->details->usedLanguage : NULL;

    if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief actorNote
   * zero or more occurence(s)
   */

  public function getActorNote() {
    $objects = isset($this->manifestation->details->actorNote) ? $this->manifestation->details->actorNote : NULL;

    if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief descriptionNote
   * zero or more occurence(s)
   */

  public function getDescriptionNote() {
    $objects = isset($this->manifestation->details->descriptionNote) ? $this->manifestation->details->descriptionNote : NULL;

     if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief references
   * zero or more occurence(s)
   */

  public function getReferences() {
    $objects = isset($this->manifestation->details->references) ? $this->manifestation->details->references : NULL;

     if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief originals
   * zero or more occurence(s)
   */

  public function getOriginals() {
    $objects = isset($this->manifestation->details->originals) ? $this->manifestation->details->originals : NULL;

     if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    $ret = array();

    foreach ($objects as $object){
      $ret[] = $object->{'$'};
    }

    return $ret;
  }

  /* \brief context
   * zero or 1 occurence
   * contextElement zero or more occurence(s)
   */

  public function getContext() {
    $fields = array(
      'contextElement' => 'contextElement',
    );

    $object = isset($this->manifestation->details->context) ? $this->manifestation->details->context : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }

  /* \brief identifiers
   * zero or more occurence(s)
   * identifierHeader zero or 1 occurence
   * identifier zero or more occurence(s)
   * ISSN zero or more occurence(s)
   */

  public function getIdentifiers() {
    $fields = array(
      'identifierHeader' => 'identifierHeader',
      'identifier' => 'identifier',
      'ISSN' => 'ISSN',
    );
    $objects = isset($this->manifestation->details->identifiers) ? $this->manifestation->details->identifiers : NULL;
    if (!isset($objects))
      return array();

    if (!is_array($objects))
      $objects = array($objects);

    return ting_openformat_methods::parseFields($objects, $fields);
  }

  /* \brief priceInformation
   * priceHeader zero or 1 occurence
   * price 1 occurence
   */

  public function getPriceInformation() {
    $fields = array(
      'priceHeader' => 'priceHeader',
      'price' => 'price',
    );

    $object = isset($this->manifestation->details->priceInformation) ? $this->manifestation->details->priceInformation : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }

  /* \brief language
   * zero or 1 occurence
   * languageHeader 1 occurence
   * languageElement 1 occurence
   */

  public function getLanguage() {
    $fields = array(
      'languageHeader' => 'languageHeader',
      'languageElement' => 'languageElement',
    );

    $object = isset($this->manifestation->details->language) ? $this->manifestation->details->language : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }

  /* \brief accessInformation
   * zero or 1 occurence
   * accessUrl 1 or more occurence(s)
   */

  public function getAccessInformation() {
    $fields = array(
      'accessUrl' => 'accessUrl',
    );

    $object = isset($this->manifestation->details->accessInformation) ? $this->manifestation->details->accessInformation : NULL;

    return ting_openformat_methods::parseFields($object, $fields);
  }
 

}

class ting_openformat_methods {
  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form ['display','searchCode']
   */

  public static function parseSearchCode(array $stdObjects) {
    foreach ($stdObjects as $object) {
      $subject['searchCode'] = self::parseSimpleSearchCode($object->searchCode);
      $subject['display'] = isset($object->display) ? $object->display->{'$'}: NULL;
      $ret[]=$subject;
    }
    return $ret;
  }

  public static function parseSimpleSearchCode($stdObject) {
    if (isset($stdObject->{'@phrase'}))
      $term = $stdObject->{'@phrase'}->{'$'};
    elseif (isset($stdObject->{'@word'}))
      $term = $stdObject->{'@word'}->{'$'};
    else
      return;

    $value = (isset($stdObject->{'$'})) ? $stdObject->{'$'} : NULL;

    return $term . "=" . $value;
  }

  public static function parseFields($object, array $fields) {

    if (!isset($object)) {
      return FALSE;
    }
    if (is_array($object)){
      foreach ($object as $o){
        if (isset($o))
          $ret[] = self::parseFields($o, $fields);
      }
      return $ret;
    }

    foreach ($fields as $field => $value) {

      if (is_array($value) && isset($object->$field))
        $ret[$field] = self::parseFields($object->$field, $value);

      elseif ($field == 'searchCode' && isset($object->$field))
        $ret[$field] = self::parseSimpleSearchCode($object->$field);

      elseif (!is_array($value) && isset($object->$value) && is_array($object->$value)) {

        foreach ($object->$value as $val)
          $ret[$field][] = $val->{'$'};
      }

      elseif (!is_array($value) && isset($object->$value) && is_object($object->$value))
        $ret[$field] = $object->$value->{'$'};

      else
        $ret[$field] = NULL;

    }
    return $ret;
  }

}