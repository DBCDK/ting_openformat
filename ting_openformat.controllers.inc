<?php
/**
 * there is no need to store work or manifestations on the database - they come from out'a space.
 * make a lightweight entity by implementing DrupalEntityControllerInterface only.
 * we do need to attach fields though, so attachLoad() is copied from DrupalDefaultEntityController
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
    $entity = new bibdkWork($conditions['work']);
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
  public function resetCache(array $ids = NULL){}

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


