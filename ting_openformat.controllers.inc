<?php
class ManifestionEntityApiController extends DrupalDefaultEntityController{
  public function load ($ids = array(), $conditions = array()) {
    // array to hold return values
    $works = array();
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
    return $works;
  }



  private function save_work ($work) {
    drupal_write_record('ting_openformat_manifestation', $work);
    field_attach_insert('ting_openformat_manifestation', $work);
    module_invoke_all('entity_insert', 'ting_openformat_manifestation', $work);
    return $work;
  }

  /** \brief Get entity from cache-table (cache_ting_openformat_entities)
   * return cached_entity on success; otherwise FALSE
   *
   **/
  public static function get_from_cache($id) {
    $cached_entity = cache_get($id, 'cache_ting_openformat_entities');
    return $cached_entity;
  }
}