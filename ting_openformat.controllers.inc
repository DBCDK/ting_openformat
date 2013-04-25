<?php
/**
 * Entity controllers.
 *
 * there is no need to store work, subworks or manifestations on the database - they come from out'a space.
 * make lightweight entities by implementing DrupalEntityControllerInterface only.
 * we do need to attach fields though, so attachLoad() is copied from DrupalDefaultEntityController
 * furthermore the attachLoad defines a load hook (defined in hook_entity_info) that is called after attachLoad
 *
 * @ see ting_openformat.entities.inc for class implementations
 **/
class bibdkEntityApiController implements DrupalEntityControllerInterface{
  protected $entityInfo;
  protected $entityType;

  public function __construct($entityType) {
    $this->entityInfo = entity_get_info($entityType);
    $this->entityType = $entityType;
  }

  /**
   * implements DrupalEntityControllerInterface::load
   **/
  public function load ($ids = array(), $conditions = array()) {
    //$entity = new bibdkWork($conditions['work']);
    $entity = new bibdkWork();
    $entity->setManifestations($conditions['manifestations']);
    $entity->id = $entity->ding_entity_id = key($entity->getManifestations());
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);
    return $entities;
  }

  /**
   * implements DrupalEntityControllerInterface::resetCache
   **/
  public function resetCache(array $ids = NULL){ // do nothing for now
  }

  /**
   * copied from DrupalDefaultEntityController::attachLoad() with minor modifications.
   */
  protected function attachLoad(&$stdObjects) {
    // Attach fields.
    field_attach_load($this->entityType, $stdObjects);

    // Call hook_entity_load().
    foreach (module_implements('entity_load') as $module) {
      $function = $module . '_entity_load';
      $function($stdObjects, $this->entityType);
    }

    $args = array($stdObjects);
    // call load hook as defined in hook_entity_info (@see ting_openformat.module)
    foreach(module_implements($this->entityInfo['load hook']) as $module) {
      call_user_func_array($module . '_' . $this->entityInfo['load hook'], $args);
    }
  }
}


/**
 * subwork implementation; Load a group of manifestations into bibdkSubWork given by id,manifestation - NOTICE!! conditions array is deprecated in drupal 8
 **/
class subWorkEntityApiController extends bibdkEntityApiController{
  public function load( $type = '', $manifestations = array() ) {
    $entity = new bibdkSubwork($type, $manifestations);
    $entity->id = $entity->ding_entity_id = current($manifestations)->id;
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);

    return $entities[$entity->id];
  }
}

/**
 * load a single manifestation given as id(ids),manifestion(conditions) - NOTICE!! conditions array is deprecated in drupal 8
 **/
class ManifestionEntityApiController extends bibdkEntityApiController{
  public function load( $id = array(), $manifestation = array() ) {
    $entity = new manifestation($manifestation);
    $entity->id = $entity->ding_entity_id = $id;
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);

    return $entities[$entity->id];
  }

}

/**
 * load a single manifestation given as id(ids),manifestion(conditions) - NOTICE!! conditions array is deprecated in drupal 8
 **/
class CollectionEntityApiController extends bibdkEntityApiController {
  public function load( $id = array(), $manifestation = array() ) {
    $entity = new bibdkCollection($manifestation['manifestations']);
    $entity->id = $entity->ding_entity_id = $id;
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);

    return $entities[$entity->id];
  }
}

class ManifestationVolumeEntityApiController extends bibdkEntityApiController {
  public function load( $id = array(), $volume = array() ) {
    $entity = new manifestationVolume($volume);
    $entity->id = $entity->ding_entity_id = $id;
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);

    return $entities[$entity->id];
  }
}

class ManifestationSectionEntityApiController extends bibdkEntityApiController {
  public function load( $id = array(), $section = array() ) {
    $entity = new manifestationSection($section);
    $entity->id = $entity->ding_entity_id = $id;
    $entities[$entity->id] = $entity;
    // attach fields
    $this->attachLoad($entities);

    return $entities[$entity->id];
  }
}
