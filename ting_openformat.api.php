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
 * Add extended query elements parameters to searchRequest.
 *
 * @return array
 *  An array with preprocessed query elements
 *  Example:
 *  Param $qe = array(
 *      ['term.type'][0] => 'book',
 *      ['year.op'][0] => 'year_lt',
 *      ['year.value'][0] => '2001',
 *  Return $qe = array(
 *      ['term.type'][0] => 'book',
 *      ['#preprocessed'][0] => 'dkcclterm.year<2013',
 */
hook_ting_openformat_qe_preprocess($extended_query_elements) {
}

/**
 * @} End of "addtogroup hooks".
 */
