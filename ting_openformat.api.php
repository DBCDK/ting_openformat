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
function hook_ting_openformat_getobject_params() {
  // example:
  return array(
    'relationData' => 'full',
  );
}


/**
 * @} End of "addtogroup hooks".
 */
