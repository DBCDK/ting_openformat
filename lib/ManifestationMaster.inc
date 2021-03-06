<?php

/**
 * Class ManifestationMaster
 */
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

  /**
   * Get tracks from bibdkWorkDisplay.
   *
   * @return array|null
   *
   */
  private function _getTracks() {
    return $this->fields->tracks ?? NULL;
  }

  private function _getContent() {
    return isset($this->fields->content) ? $this->fields->content : NULL;
  }


  /* \brief Distinction
   * zero or more occurence(s)
   */

  public function getDistinction() {
    $result = TingOpenformatMethods::parseFields($this->work, array('distinction'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief original title
   * zero or one occurence
   */

  public function getOriginalTitle() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('originalTitle' => array('originalTitleHeader' => 'header', "originalTitleElement")));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief alternative title
   * zero or more occurences
   */

  public function getAlternativeTitle() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('alternativeTitle' => array('alternativeTitleDescriptor' => 'header', "alternativeTitle")));
    return $result;
  }

  /* \brief contributors
   * zero or 1 occurence
   */

  public function getContributors() {
    $elements = $this->_getDetails();
    $fields = array(
      'contributors' => array(
        'contributor' => array(
          'functionSingular',
          'functionPlural',
          'searchCode'
        )
      )
    );
    $result = TingOpenformatMethods::parseFields($elements, $fields);
    return $result['contributors'];
  }

  /* \brief contributors without functionCode
   * zero or 1 occurence
   */

  public function getContributorsNoFunction() {
    $elements = $this->_getDetails();
    $fields = array(
      'contributors' => array(
        'contributor' => array(
          'searchCode'
        )
      )
    );
    $result = TingOpenformatMethods::parseFields($elements, $fields);
    return $result['contributors'];
  }

  /* \brief format
   * zero or more occurence(s)
   */

  public function getContributorExtra() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('contributors' => array('contributorExtra')));
    return $result;
  }

  /* \brief format
   * zero or more occurence(s)
   */

  public function getFormat() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('format'));
    return $result;
  }

  /* \brief forms
   * zero or one occurence
   * formHeader 1 occurence
   * subelement formSubject 1 or more occurence(s)
   */

  public function getForms() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('forms' => array("formSubject" => 'searchCode')));
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
    $display_version = variable_get('ting_search_openformat', 'bibliotekdkWorkDisplay');
    $fields = ($display_version === 'bibdkWorkDisplay') ?
    array(
      'seriesTitle' => array(
        'series' => array(
          'seriesHeader' => 'seriesDescription',
          'titles' => array('searchCode')
        )
      )
    ) :
    array(
      'seriesTitle' => array(
        'seriesHeader' => 'header',
        'series' => array('searchCode'),
        'seriesNumber'
      )
    );
    return TingOpenformatMethods::parseFields($elements, $fields);
  }

  /* \brief relatedSeriesTitle
   * zero or more occurence(s)
   * relatedSeriesHeader 1 or more occurence(s)
   * relatedSeries 1 or more occurence(s)
   */

  public function getRelatedSeriesTitle() {
    $elements = $this->_getDetails();
    $display_version = variable_get('ting_search_openformat', 'bibliotekdkWorkDisplay');
    $description = ($display_version === 'bibdkWorkDisplay') ? 'seriesDescription' : 'header';
    $titles = ($display_version === 'bibdkWorkDisplay') ? 'titles' : 'relatedSeries';
    $fields = array(
      'relatedSeriesTitles' => array(
        'relatedSeriesTitle' => array(
          'relatedSeriesDescription' => $description,
          $titles => array( 'linkElements','searchCode'),
        ),
      ),
    );

    return TingOpenformatMethods::parseFields($elements, $fields);
  }

  /* \brief readabilityIndexes
   * zero or more occurence(s)
   */

  public function getReadabilityIndexes() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('readabilityIndexes' => array('readabilityIndex')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief readabilityNumbers
   * zero or more occurence(s)
   */

  public function getReadabilityNumbers() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('readabilityNumbers' => array('readabilityNumber')));
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief shelfPublicLibrary
   * zero or more occurence(s)
   */

  public function getShelfPublicLibrary() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('shelf' => array('shelfPublicLibrary')));
    return $result;
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief genre
   * zero or more occurence(s)
   */

  public function getGenre() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('genre'));
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief markedAudience
   * zero or more occurence(s)
   */

  public function getMarkedAudience() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('audienceMarked' => array('audienceMarkedElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief recommendedAudience
   * zero or more occurence(s)
   */

  public function getRecommendedAudience() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('audienceAge' => array('audienceAgeElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief audiencePegi
   * zero or more occurence(s)
   */

  public function getAudiencePegi() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('audiencePegi' => array('audiencePegiElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief usedLanguage
   * zero or more occurence(s)
   */

  public function getUsedLanguage() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('usedLanguage'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief actorNote
   * zero or more occurence(s)
   */

  public function getActorNote() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('actorNote' => array('actorElement')));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief descriptionNote
   * zero or more occurence(s)
   */

  public function getDescriptionNote() {
    $elements = $this->_getDetails();
    $display_version = variable_get('ting_search_openformat', 'bibliotekdkWorkDisplay');
    if ($display_version === 'bibliotekdkWorkDisplay') {
      $fields = array(
        'descriptionNoteLink' => array(
          'descriptionNoteLink' => 'descriptionNoteLinkElement'
        ),
      );
    } else {
      $fields = array('descriptionNote');
    }
    $result = TingOpenformatMethods::parseFields($elements, $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief references
   * zero or more occurence(s)
   */

  public function getReferences() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('references'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief originals
   * zero or more occurence(s)
   */

  public function getOriginals() {
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), array('originals'));
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief context
   * zero or 1 occurence
   * contextElement zero or more occurence(s)
   */

  public function getContext() {
    $fields = array('context' => array('contextElement'));
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /* \brief acquisition information
   * zero or more occurences
   */
  public function getAcquisitionInformation() {
    $fields = array('acquisitionInformation' => array(
        'acquisitionTerms',
        ));
    $result = tingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
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
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return (is_countable($result['language'][0]['languageElement']) && count($result['language'][0]['languageElement']) > 1) ? array() : $result;
  }

  /**
   * Checks accessInformation on the manifestation and returns any URL's found.
   * Returning NULL if none is found.
   *
   * accessInformation zero or 1 occurence
   * accessUrl 1 or more occurence(s)
   *
   * @return array|null
   */
  public function getAccessInformation() {
    $fields = array(
      'accessInformation' => array(
        'accessUrl',
        'accessUrlDescriptor',
        'accessUrlDisplay',
      )
    );
    return TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
  }

  /**
   * Checks accessInformationNote on the manifestation and returns any URL's found.
   * Returning NULL if none is found.
   *
   * accessInformation zero or 1 occurence
   * accessUrl 1 or more occurence(s)
   *
   * @return array|null
   */
  public function getAccessNote() {
    $fields = array(
      'accessInformationNote' => array(
        'accessUrl',
        'accessUrlDescriptor',
        'accessUrlDisplay',
      )
    );
    return TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
  }

  /* \brief publisher
   * zero or more occurences
   */
  public function getPublisher() {
    $fields = array('publisher');
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief publicationYear
   * zero or more occurences
   */
  public function getPublicationYear() {
    $fields = array('publicationYear');
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief edition
   * zero or more occurences
   */
  public function getEdition() {
    $fields = array('edition', 'editionPerson');
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? $result : array($result);
  }

  /* \brief (publication)format
   * zero or more occurences
   */

  public function getPublicationFormat() {
    $fields = array('format');
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  /* \brief hostPublication
   * zero or more occurences
   */
  public function getHostPublication() {
    $fields = array(
      'hostPublicationLink' => array(
        'hostPublicationSeries' => 'searchCode',
        'hostPublicationElement',
      ),
    );
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

  public function getContentTitle() {
    $fields = array('content' => 'contentTitle');
    $result = TingOpenformatMethods::parseFields($this->_getContent(), $fields);

    return $result;
  }

  public function getSystemDemands() {
    $fields = array('systemDemands' => array('systemDemandsDescriptor', 'systemDemandsElement'));
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  public function getDatabaseRef() {
    $fields = array('referencesExternal');
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  public function getAccessMethod() {
    $fields = array('accessMethod' => array('accessMethodDescription','accessMethodElement'));
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return $result;
  }

  /**
   * Get track elements from bibdkWorkDisplay.
   *
   * @return array
   *
   */
  public function getTrackContent() {
    $fields = array(
      'track' => array(
        'creator' => 'searchCode',
        'title' => 'title',
        'details' => 'details'
      )
    );
    return TingOpenformatMethods::parseFields($this->_getTracks(), $fields);
  }


  /* \brief contentPartialNote
   * zero or more occurence(s)
   */

  public function getContentPartialNote() {
    $fields = array(
      'contentPartialNote' => array('contentPartialNoteDescription', 'contentPartialNoteElement')
    );
    $result = TingOpenformatMethods::parseFields($this->_getContent(), $fields);
    return $result;
  }

  /* \brief contentNote
   * zero or more occurence(s)
   */

  public function getContentNote() {
    $fields = array(
      'contentNote' => array('contentNoteDescription', 'contentNoteElement')
    );
    $result = TingOpenformatMethods::parseFields($this->_getContent(), $fields);
    return $result;
  }

  public function getLatestReprint() {
    $fields = array(
      'latestReprint' => array('latestReprint' => 'latestReprintElement'),
    );
    $result = TingOpenformatMethods::parseFields($this->_getPublicationDetails(), $fields);

    return $result;
  }

  public function getCommonContributors() {
    $fields = array(
      'commonContributors'
    );
    $result = TingOpenformatMethods::parseFields($this->_getDetails(), $fields);
    return (is_array($result)) ? reset($result) : $result;
  }

}
