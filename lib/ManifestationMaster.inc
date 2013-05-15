<?php



class ManifestationMaster {

  public $id;
  public $ding_entity_id;
  public $manifestation;
  private $isReservable;
  protected $fields;

  public function __construct($manifestation) {
    $this->manifestation = $manifestation;
  }

  private function _getDetails() {
    return isset($this->fields->details) ? $this->fields->details : NULL;
  }

  private function _getPublicationDetails() {
    return isset($this->fields->publicationDetails) ? $this->fields->publicationDetails : NULL;
  }

  /* \brief Distinction
   * zero or more occurence(s)
   */

  public function getDistinction() {
    $result = ting_openformat_methods::parseFields($this->fields, array('distinction'));
    return (is_array($result)) ? reset($result) : $result;
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
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('forms' => array("formSubject" => 'searchCode')));
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
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('audienceAge' => array('audienceAgeElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief audiencePegi
   * zero or more occurence(s)
   */

  public function getAudiencePegi() {
    $result = ting_openformat_methods::parseFields($this->_getDetails(), array('audiencePegi' => array('audiencePegiElement')));
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


  /** Deprecated
   * @return null
   */
  public function getContentPartialNote() {
    return null;
  }

  /** Deprecated
   * @return null
   */
  public function getContentNote() {
    return null;
  }
/** Deprecated
   * @return null
   */
  public function getAnalyticContent() {
    return null;
  }

}
