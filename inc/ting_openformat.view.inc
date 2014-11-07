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

/**
 * Genrates a list with classes based on the material types in the given
 * collection
 *
 * @param BibdkCollection $bibdkobject
 * @return String html
 */
function _ting_openformat_get_types_list($bibdkobject) {
  $types = $bibdkobject->getWorkTypes();
  $items = array();
  foreach ($types as $type => $ids) {
    $items[$type] = '<span class="materialtype ' . $type . '-icon-small " title="' . t($type) . '">' . t($type) . '&nbsp;</span>';
  }

  if ($bibdkobject->isOnline()) {
    $items['net-icon-small'] = '<span class="materialtype online-icon-small" title="' . t('online') . '">' . t('online') . '&nbsp;</span>';
  }

  $list = array(
    '#type' => 'ol',
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array(
      'class' => 'material-types-list',
    ),
  );


  return drupal_render($list);
}

/**
 * Generates form for 'View more info' on search results page
 *
 * @param $form
 * @param array $form_state
 * @param BibdkCollection $bibdkObject
 * @param $uid
 * @param int $trackId
 * @return array
 */
function ting_openformat_show_info_get_form($form, $form_state, $bibdkObject, $uid, $trackId = 0) {
  $all_ids_in_collection = $bibdkObject->getCollectionIds();
  $form['info'] = array(
    '#trackId' => $trackId,
    '#type' => 'button',
    '#value' => '',
    '#ids' => $all_ids_in_collection,
    '#uid' => $uid,
    '#collection' => $bibdkObject,
    '#id' => 'work_' . $uid,
    '#prefix' => "<span id='ajax-$uid'>",
    '#suffix' => "</span>",
    '#attributes' => array('class' => array('visuallyhidden')),
    '#ajax' => array(
      'callback' => 'ting_openformat_show_info_ajax_callback',
      'wrapper' => 'ajax_placeholder_' . $uid,
      'method' => 'replace',
      'event' => 'click',
    ),
  );

  return $form;
}

/**
 * Ajax callback. Called when user clicks 'view more information' on a work on search results page
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function ting_openformat_show_info_ajax_callback(&$form, $form_state) {
  $ids = $form_state['clicked_button']['#ids'];
  $uid = $form_state['clicked_button']['#uid'];
  $collection = $form_state['clicked_button']['#collection'];

  $tracking_id = $form_state['clicked_button']['#trackId'];

  $view = ting_openformat_load_single_full_work($collection, $ids, $uid, $tracking_id);

  $view = theme('status_messages') . $view;

  $commands = array();
  $commands[] = ajax_command_remove("#ajax-$uid");
  $commands[] = ajax_command_replace(NULL, $view);

  return array('#type' => 'ajax', '#commands' => $commands);
}


/**
 * @param BibdkCollection $collection
 * @param $ids
 * @param $uid
 * @param int $tracking_id
 * @return string
 */
function ting_openformat_load_single_full_work($collection, $ids, $uid, $tracking_id = 0) {
  module_invoke_all('show_manifestation_info_prerender', $ids, $uid);

  foreach ($collection->manifestations as $manifestation) {
    $briefDisplay = new BibdkBriefDisplay($manifestation);
    if (!isset($bibdkWork)) {
      if ($bibdkWork = $collection->getWorkOne()) {
        $bibdkWork = _ting_openformat_get_bibdk_work_entity(array($bibdkWork));
      }
      else {
        $bibdkWork = ting_openformat_get_manifestations($briefDisplay->id, array('trackingId' => $tracking_id));
      }

      $bibdkWork = current($bibdkWork);

      /*
       * If manifestation with $briefDisplay->id does not exists, the result
       * from openSearch is not rendered correctly and we send a message to the
       * user that the object could not be shown, and log it to the watchdog
       * */
      if (!isset($bibdkWork->manifestations[$briefDisplay->id])){

        drupal_set_message(t('This record could not be generated properly. A message have been send to the site administrators', array(), array('context' => 'ting_openformat')), 'warning');
        watchdog('ting_openformat', 'ERROR manifestation with id @id failed generate bibdkWorkDisplay', array('@id' => $briefDisplay->id), WATCHDOG_ERROR);
        return;
      }

      $bibdkWork->manifestations[$briefDisplay->id]->setBriefDisplayType($briefDisplay->gettype());
      $bibdkWork->manifestations[$briefDisplay->id]->setSubType($briefDisplay->getSubtype());
    }
    else {
      $bibdkWork->manifestations[$briefDisplay->id] = $briefDisplay;
    }
  }

  return ting_openformat_work_view($bibdkWork);
}


/**
 * @param $manifestation
 * @param string $view_mode
 * @param null $langcode
 * @return array
 */
function ting_openformat_manifestation_view($manifestation, $view_mode = 'full', $langcode = NULL) {
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }

  $fields = _prepare_view('bibdkManifestation', $manifestation, $view_mode, $langcode);

  $actions = ting_openformat_get_actions('bibdkManifestation', $manifestation, $view_mode, $langcode);

  $build = array(
    '#theme' => 'ting_openformat_manifestation',
    '#view_mode' => $view_mode,
    '#language' => $langcode,
    '#fields' => $fields,
    '#actions' => $actions,
  );

  return $build;
}


/** Invokes hook_ting_openformat_actions
 * @param $type
 * @param $entity
 * @param string $view_mode
 * @param null $langcode
 * @return array
 */
function ting_openformat_get_actions($type, $entity, $view_mode = 'full', $langcode = NULL) {

  $actions = module_invoke_all('ting_openformat_actions', $type, $entity, $view_mode, $langcode);

  if (!empty($actions)) {
    uasort($actions, 'element_sort');
  }

  return $actions;
}

/**
 * Create view for manifestation volume fields
 * @param $volume
 * @param string $view_mode
 * @param null $langcode
 * @return bool|string
 */
function ting_openformat_volume_view($volume, $view_mode = 'full', $langcode = NULL) {
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }
  $field_content = _prepare_view('bibdkManifestationVolume', $volume, $view_mode, $langcode);

  return drupal_render($field_content);
}

/**
 * Create view for manifestation section fields
 * @param $volume
 * @param string $view_mode
 * @param null $langcode
 * @return bool|string
 */
function ting_openformat_section_view($volume, $view_mode = 'full', $langcode = NULL) {
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }
  $field_content = _prepare_view('bibdkManifestationSection', $volume, $view_mode, $langcode);

  return drupal_render($field_content);
}

/**
 * attach entity fields to a single entity. Return a renderable array
 * @param $entity_type
 * @param Manifestation|BibdkWork|BibdkSubwork|BibdkCollection $object
 * @param $view_mode
 * @param $langcode
 * @return array
 */
function _prepare_view($entity_type, $object, $view_mode, $langcode) {
  field_attach_prepare_view($entity_type, array($object->id => $object), $view_mode, $langcode);
  entity_prepare_view($entity_type, array($object->id => $object), $langcode);
  $fields = field_attach_view($entity_type, $object, $view_mode, $langcode);

  return $fields;
}
