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

    return ting_openformat_methods::parseSearchCode($creators);
  }

  /** \brief subject(s) of work
   * zero or more occurences
   */

  public function getSubjects() {
    $subjects = isset($this->work->description->subjects->subject) ? $this->work->description->subjects->subject : NULL ;

    if( empty($subjects) ) {
      return array();
    }

    if( !is_array($subjects) ) {
      $subjects = array($subjects);
    }

    return ting_openformat_methods::parseSearchCode($subjects);
  }
}

class manifestation {
  public $id ;
  public $ding_entity_id;
  public $manifestation;

  public function __construct($manifestation){
    $this->manifestation = $manifestation;
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

    if( empty($titles) ) {
      return array();
    }

    if ( !is_array($titles) ) {
      $titles = array($titles);
    }

    foreach( $titles as $key => $val ) {
      // zero or one occurence
      $title['Header'] = isset($val->alternativeTitleHeader->{'$'}) ? $val->alternativeTitleHeader->{'$'} : NULL;
      // 1 occurence
      $title['Element'] = $val->alternativeTitleElement->{'$'};
      $ret[] = $title;
    }
    return $ret;
  }

  /* \brief contributors
   * zeor or 1 occurence
   */
  public function getContributors() {
    return isset($this->manifestation->details->contributors->{'$'}) ? $this->manifestation->details->contributors->{'$'} : FALSE;
  }

  /* \brief format
   * zero or more occurence(s)
   */
  public function getFormat() {
    $formats = isset($this->manifestation->details->format) ? $this->manifestation->details->format : NULL;

    if( empty($formats) ) {
      return array();
    }

    if( !is_array($formats) ) {
      $formats = array($formats);
    }

    foreach( $formats as $key => $val ) {
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
    $forms = isset($this->manifestation->details->format) ? $this->manifestation->details->format : NULL;

    if( !isset($forms) ) {
      return FALSE;
    }

    $ret['formHeader'] = $this->manifestation->details->format->formHeader->{'$'};
    $formSubjects =  $this->manifestation->details->format->formSubject;
    if( !is_array($formSubjects) ) {
      $formSubjects = array($formSubjects);
    }

    $ret['formSubjects'] = ting_openformat_methods::parseSearchCode($formSubjects);

    return $ret;
  }

  /* \brief seriesTitle
   * zero or more occurence(s)
   * relatedSeriesHeader 1 or more occurence(s)
   * relatedSeries 1 or more occurence(s)
   */
  public function getSeriesTitle() {
    $relatedSeries = isset($this->manifestation->details->relatedSeriesTitle ) ? $this->manifestation->details->relatedSeriesTitle : NULL;

    if( !isset($relatedSeries) ) {
      return FALSE;
    }

    if( !is_array($relatedSeries)) {
      $relatedSeries = array($relatedSeries);
    }

    foreach( $relatedSeries as $relatedSerie ) {
      $Header = $relatedSerie->relatedSeriesHeader->{'$'};
      /* if( !is_array($Header) ){
        $Header = array($Header);
      }

      foreach( $Header as $key => $val ) {
        $Headers[] = $val->{'$'};
        }*/
      $rel_serie['seriesHeader'] = $Header;

      $series = $relatedSerie->relatedSeries;
      if( !is_array($series) ) {
        $series = array($series);
      }

      $rel_serie['relatedSeries'] = ting_openformat_methods::parseSearchCode($series);

      $ret[] = $rel_serie;
    }

    return $ret;
  }

}

class ting_openformat_methods{
  /* \brief parse searchCode,display elements
   * @param array of stdObjects
   * return array of form ['display','searchCode']
   */
  public static function parseSearchCode(array $stdObjects) {
    foreach( $stdObjects as $key => $val ) {
      $subject['display'] = $val->display->{'$'};
      $subject['searchCode'] = $val->searchCode->{'@phrase'}->{'$'}.'='.$val->searchCode->{'$'};
      $ret[] = $subject;
    }
    return $ret;
  }
}