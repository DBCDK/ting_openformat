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
 * Add fields to ting_openformat entitites
 *
 * @param $fields
 *   Array of field definitions. Each definition is an associative array with
 *   at least the following keys:
 *     'label' : label on the administration pages. Should not be wrapped in t()
 *     'entity_type' : It is possible to define more than one entity type with an array
 *     'display' : the different display types are defined in ting_openformat.install
 *     'description' : description for the field_ui
 *     'callback method' : method to get content from the field entity.
 * @return array
 *   Array of field descriptions.
 */
function hook_ting_openformat_fields($fields) {
  $fields = array(
    'ting_openformat_work_abstract' => array(
      'label' => 'Work abstract',
      'entity_type' => 'bibdkWorkEntity',
      'display' => array('full'),
      'description' => t('Description of work'),
      'callback method' =>  'getAbstract',
    ),
  );

  return $fields;
}



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
* Add extended query elements parameters to searchRequest.
* @return array
* An array with preprocessed query elements
* Example: Combine year.op & year.value to new search expression
* Param $qe = array(
* ['term.type'][0] => 'book',
* ['year.op'][0] => 'year_lt',
* ['year.value'][0] => '2001',
* Return $qe = array(
* ['term.type'][0] => 'book',
* ['#preprocessed'][0] => 'dkcclterm.year<2013',
*/
function hook_ting_openformat_qe_preprocess($extended_query_elements) {
}


/**
 * Lets other modules add conditions to a search query
 * @param $query
 * @return array
 */
function hook_ting_openformat_conditions($query) {

}

/**
 * hook for filtering search requests
 *
 * * @return array
 */
function hook_ting_openformat_query_filter() {

  return array(
    'books' => 'term.workType=literature',
    'articles' => '(term.type=artikel ELLER term.workType=article)'
  );

}



/**
 * @} End of "addtogroup hooks".
 */
