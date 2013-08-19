<?php

/**
 * Class bibdkWork
 */
class BibdkWork {

  public $id;
  public $ding_entity_id;
  public $description;
  public $work;
  public $manifestations = array();
  public $subWorks;

  public function __construct($work = NULL) {
    $this->work = $work;
  }

  public function getId() {
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

  public function getMaterialReview(){

    $reviews = array();

    foreach ($this->manifestations as $manifestation) {
      if (method_exists($manifestation, 'getMaterialReview'))
        $reviews += $manifestation->getMaterialReview();
    }
    return $reviews;
  }

  public function getManifestations() {
    return $this->manifestations;
  }

  public function setManifestations($manifestations) {
    foreach ($manifestations as $id => $manifestation) {
      $this->manifestations[$id] = entity_load('bibdkManifestation', $id, $manifestation);
    }


    // set work part
    $this->work = reset($this->manifestations)->getWork();
  }

  public function getSubWorks() {
    if (isset($this->subWorks)){
      return $this->subWorks;
    }
    $this->subWorks = array();
    foreach ($this->manifestations as $id => $manifestation) {
      $type = $manifestation->getBriefDisplayType();
      if ($type === NULL) {
        $type = array(t('unknown', array(), array('context' => 'ting_openformat')));
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

    return $this->subWorks;
  }

  public function getTitle() {
    $fields = array('titleFull');
    $elements = $this->work->title;
    $result = ting_openformat_methods::parseFields($elements, $fields);

    return (is_array($result)) ? reset($result) : $result;
  }

  private function _getDescription() {
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

  /**
   * @return array|mixed|null
   */
  public function getFurtherSearches() {
    $fields = array('furtherSearchType' => 'searchCode', 'furtherSearchFiction' => 'searchCode', 'furtherSearchElement' => 'searchCode');
    $manifestations = $this->getManifestations();

    $elements = array();
    foreach ($manifestations as $manifestation) {
      if (isset($manifestation->manifestation->work->description->furtherSearches)) {
        $elements[] = $manifestation->manifestation->work->description->furtherSearches;
      }
    }

    $parsedFields = ting_openformat_methods::parseFields($elements, $fields);
    return (!empty($parsedFields)) ? $this->_parseFurtherSearches($parsedFields) : array();
  }

  /**
   * @param $parsedFields
   * @return array
   */
  private function _parseFurtherSearches($parsedFields) {
    $ret = array();
    foreach ($parsedFields as $furtherSearches) {
      foreach ($furtherSearches as $key => $value) {
        foreach ($value[0] as $elemnt) {
          $ret[$key][$elemnt['display']]['searchCode'] = $elemnt['searchCode'];
          $ret[$key][$elemnt['display']]['display'] = $elemnt['display'];
        }
      }
    }
    return $ret;
  }
}
