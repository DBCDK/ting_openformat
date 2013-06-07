<?php

/**
 * @file
 * Hooks provided by the Ting openformat module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Add actions to subwork material types.
 *
 * @param $ordered_subworks
 * @param $type_id
 * @param $subtype_id
 * @return array
 *  A render array
 */
function hook_ting_openformat_subwork_materialtype_actions($ordered_subworks, $type_id, $subtype_id) {
}


/**
 * Add parameters to getObject request.
 *
 * @return array
 *  An array with getObject parameters
 */
function hook_ting_openformat_getobject_params_alter(&$params) {
  $params['relationData'] = 'uri';
}


/**
 * Add actions to the manifestation view
 *
 * @return array A rendable array, with weight specified
 */
function hook_ting_openformat_actions($type, $entity, $view_mode, $langcode) {
  if ($type == 'bibdkManifestation'){
    $actions['export'] = array(
      '#theme' => 'links',
      '#links' => bibdk_actions_refexport_links($entity->id),
      '#weight' => 1,
    );
    return $actions;
  }
}

/**
 * @} End of "addtogroup hooks".
 */
