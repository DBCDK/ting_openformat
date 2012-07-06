<?php
class ManifestionEntityApiController extends DrupalDefaultEntityController{
  public function load ($ids = array(), $conditions = array()) {
    // basically we need this overload to get external entities

    /*
      foreach given id
      1. check if id is already in entity table
      2. insert (save) unknown ids in entity table
      3. use parent::load to load entities
    */

    /* 1. select known ids from entity table */

    foreach( $ids as $id ) {
      // check if this id is known
      $query = db_select($this->entityInfo['base table'], 'base');
      $query->addField('base', 'ding_entity_id');
      $query->condition('ding_entity_id', $id);
      // there can be only one - field is unique
      $found = $query->execute()->fetchField();

      // if not found; save
      if( !$found ) {
        $mani = (object)array(
          'ding_entity_id' =>$id,
        );
        $this->save($mani);
      }
    }
    $stdObjects = parent::load($ids, $conditions);
    foreach( $stdObjects as $key => $object ) {
      $ret[] = new manifestation($object);
    }
    return $ret;
  }


    // array to hold return values
    /*  $works = array();
    $known = (array) parent::load( $ids,$conditions );
       $known_ids = array();
    foreach($known as $key => $hest) {
      $known_ids[] = $key;
      // this id is known; add it to return array
      $work[] = new bibdkEntity ($key);
    }
    $unknown_ids = array();
    $unknown_ids = array_diff($ids,$known_ids );
    foreach( $unknown_ids as $id ) {
      $work = new bibdkEntity ($id);
      // this id is new; save it and add it to return array
      $works[] = $this->save ($works);
    }
    return $works;*/


  private function save ($manifestation) {
    drupal_write_record('ting_openformat_manifestation', $manifestation);
    field_attach_insert('ting_openformat_manifestation', $manifestation);
    // invoke hook for other modules
    module_invoke_all('entity_insert', 'ting_openformat_manifestation', $manifestation);
  }
}