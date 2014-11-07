<?php
/**
 * @file
 * Contains all methods related to generating a work view
 */

/* * *********** VIEWS ************* */

/**
 * Creates html view for bibdkWorkEntity
 * @param Manifestation|BibdkWork|BibdkSubwork|BibdkCollection $bibdkWork
 * @param string $view_mode
 * @param null $langcode
 * @return string
 */
function ting_openformat_work_view($bibdkWork, $view_mode = 'full', $langcode = NULL) {
  if (!is_object($bibdkWork)) {
    return;
  }
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }

  $work_fields = array();
  $work_fields += _prepare_view('bibdkWorkEntity', $bibdkWork, $view_mode, $langcode);

  $subWorks = $bibdkWork->getSubWorks();

  $ordered_subworks = ting_openformat_get_ordered_subworks($subWorks);

  $ding_id = preg_replace('/[^a-zA-Z0-9]+/', '', $bibdkWork->id);
  $render_tabs = array(
    '#theme' => 'ting_openformat_subwork_tabs',
    '#subWorks' => $ordered_subworks,
    '#ding_id' => $ding_id,
  );
  $tabs = drupal_render($render_tabs);

  $render = array(
    '#theme' => 'ting_openformat_work',
    '#fields' => $work_fields,
    '#subWorks' => $ordered_subworks,
    '#tabs' => $tabs,
    '#ding_id' => $ding_id
  );
  return drupal_render($render);
}

/** Get Subworks ordered by type and subtype
 * @param $subWorks
 * @return mixed
 */
function ting_openformat_get_ordered_subworks($subWorks) {
  $sub = array();
  foreach ($subWorks as $id => $subWork) {
    $type = drupal_strtolower($subWork->getType());
    $subtype = $subWork->getSubType();
    $sub[$type][$subtype] = ting_openformat_subwork_view($subWork);
  }

  foreach ($sub as $type => $value) {
    foreach ($value as $subtype => $val) {
      $subtype_id = strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $subtype));
      // Context is added for subtype to reuse translations.
      //There is no context on type because this would clear existing translations
      $trans = array('type' => t($type), 'subtype' => t($subtype, array(), array('context' => 'material_type')));

      $type_id = $trans['type'];
      $ordered_subworks[$type_id][$subtype_id]['manifest'] = $val;
      $ordered_subworks[$type_id][$subtype_id]['translation'] = $trans;
      $ordered_subworks[$type_id][$subtype_id]['manifest']['subtype_actions'] = module_invoke_all('ting_openformat_subwork_materialtype_actions', $ordered_subworks, $type_id, $subtype_id, $val['bibdkSubwork']);
    }
  }

  return $ordered_subworks;
}

/**
 * Creates html view for bibdkSubwork
 * @param BibdkSubwork $bibdkSubwork
 * @param string $view_mode
 * @param null $langcode
 * @return mixed
 */
function ting_openformat_subwork_view($bibdkSubwork, $view_mode = 'full', $langcode = NULL) {
  $sub['fields'] = _prepare_view('bibdkSubwork', $bibdkSubwork, $view_mode, $langcode);
  $sub['bibdkSubwork'] = $bibdkSubwork;
  foreach ($bibdkSubwork->getManifestations() as $manifestation) {
    if (get_class($manifestation) == 'Manifestation') {
      // first element is parsed
      $manifestation_view = ting_openformat_manifestation_view($manifestation, $view_mode = 'full', $langcode = NULL);
    }
    else {
      // other elements are given a container
      $manifestation_view = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => 'manifestation-container',
          'data-id' => $manifestation->id,
        ),
      );
      // container for the remaining
    }
    $sub['manifestations'][$manifestation->id] = drupal_render($manifestation_view);
  }

  return $sub;
}


/**
 * Generates the collection view with an 'Order any edition' button if view is
 * implemented (requires bibdk_reservation module)
 *
 * If $_SESSION['search_settings']['full_view'] is TRUE the generated will be a
 * full view with all information visible.
 *
 * @param BibdkCollection $bibdkobject
 * @return string
 */
function ting_openformat_collection_view($bibdkobject) {
  $all_ids_in_collection = $bibdkobject->getCollectionIds();
  $uid = strtolower(strtr(reset($all_ids_in_collection), array(
    ':' => '',
    '-' => '',
    '_' => ''
  )));

  $trackId = ting_openformat_set_tracking_id();

  if(bibdk_usersettings_user_settings_get('ting_openformat_fullview_usersetting', FALSE)){
    $_SESSION['search_settings']['full_view'] = TRUE;
  }

  //Setting parameters based on a full or short view was requeseted
  if ((isset($_SESSION['search_settings']['full_view']) && $_SESSION['search_settings']['full_view'] == TRUE)) {
    $showinfoForm = '';
    $workOne = ting_openformat_load_single_full_work($bibdkobject, $all_ids_in_collection, $uid);
  }
  else {
    $form = drupal_get_form('ting_openformat_show_info_get_form', $bibdkobject, $uid, $trackId);
    $showinfoForm = drupal_render($form);
    $workOne = NULL;
  }

  $actions = _prepare_view('bibdkCollection', $bibdkobject, 'full', NULL);
  $workType = $bibdkobject->getWorkType();
  $type = $bibdkobject->getType();
  $types_classes = _ting_openformat_get_types_list($bibdkobject);

  $togglework = theme('ting_openformat_toggle_work', array(
    'uid' => $uid,
    'showinfo' => $showinfoForm,
    'full_view' => !is_null($workOne),
  ));

  return theme('ting_openformat_collection', array(
    'title' => check_plain($bibdkobject->getTitle()),
    'title_full' => check_plain($bibdkobject->getTitleFull()),
    'language' => check_plain($bibdkobject->getLanguageForBriefDisplay()),
    'partOf' => check_plain($bibdkobject->getPartOf()),
    'author' => check_plain($bibdkobject->getAuthor()),
    'work_type' => (!empty($workType)) ? 'type-' . $workType : 'type-undefined',
    'type' => $type,
    'ids' => implode(',', $all_ids_in_collection),
    'togglework' => $togglework,
    'work_one' => $workOne,
    'uid' => $uid,
    'actions' => (!empty($actions)) ? $actions : array(),
    'types' => $types_classes,
  ));
}
