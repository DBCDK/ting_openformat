<?php
/**
 * @file
 * Contains all methods related to generating a work view
 */

/**
 * Generates the collection view with an 'Order any edition' button if view is
 * implemented (requires bibdk_reservation module)
 *
 * @param BibdkCollection $bibdkobject
 * @return array
 */
function ting_openformat_collection_view(BibdkCollection $bibdkobject, $full_view) {
  //@todo use drupal_clean_css_identifier() -> This requires a lot of py tests to be updated
  $object_ids = $bibdkobject->getCollectionIds();
  $uid = strtolower(strtr(reset($object_ids), array(
    ':' => '',
    '-' => '',
    '_' => ''
  )));
  $work = _ting_openformat_collection_full_view($bibdkobject, $uid, $full_view);

  // Get fields for Collection
  $actions = _prepare_view('bibdkCollection', $bibdkobject, 'full', NULL);

  // format part_of
  $part_of = $bibdkobject->getPartOf();
  $part_of = !empty($part_of) ? t('I: @partof', array('@partof' => $part_of), array('context' => 'ting_openformat')) : '';

  // get type icons
  $types_classes = _ting_openformat_get_types_list($bibdkobject);

  // Set classes for collection object
  $collection_classes = array('work', 'mobile-page');
  if ($full_view) {
    $collection_classes[] = 'is-toggled';
  }

  return array(
    '#theme' => 'ting_openformat_collection',
    '#title' => _ting_openformat_brief_display_title($bibdkobject),
    '#part_of' => $part_of,
    '#author' => $bibdkobject->getAuthor(),
    '#work' => $work,
    '#uid' => $uid,
    '#actions' => (!empty($actions)) ? $actions : array(),
    '#types' => $types_classes,
    '#theme_attributes' => array(
      'class' => $collection_classes,
      'id' => $uid,
    ),
  );
}

/**
 * Retrieve render array for work, depending on full/short view
 *
 * @param BibdkCollection $bibdkobject
 * @param $uid
 * @param bool $full_view
 * @return array|mixed|string
 */
function _ting_openformat_collection_full_view(BibdkCollection $bibdkobject, $uid, $full_view = true) {
  $trackId = ting_openformat_set_tracking_id();

  //Setting parameters based on a full or short view was requested
  if ($full_view) {
    $work = ting_openformat_load_single_full_work($bibdkobject, $bibdkobject->getCollectionIds(), $uid);
  }
  else {
    $work = drupal_get_form('ting_openformat_show_info_get_form', $bibdkobject, $uid, $trackId);
  }
  return $work;
}

/**
 * @param BibdkCollection $collection
 * @param $ids
 * @param $uid
 * @param int $tracking_id
 * @return array
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
      if (!isset($bibdkWork->manifestations[$briefDisplay->id])) {

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
 * Creates view for work
 *
 * @param object $bibdkWork
 * @param string $view_mode
 * @param string $langcode
 * @return array
 */
function ting_openformat_work_view($bibdkWork, $view_mode = 'full', $langcode = NULL) {
  if (!is_object($bibdkWork)) {
    return;
  }
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }

  $work_fields = _prepare_view('bibdkWorkEntity', $bibdkWork, $view_mode, $langcode);
  $cover = isset($work_fields['bibdk_cover_work']) ? $work_fields['bibdk_cover_work'] : null;
  unset($work_fields['bibdk_cover_work']);
  $subworks = ting_openformat_get_subworks($bibdkWork->getManifestations(), $bibdkWork->getId());

  // Recommender parameters.
  $pids = $material_types = array();
  foreach ($subworks as $group) {
    $pids = array_merge($pids, $group['subtype_order_ids']);
    $material_types = array_merge($material_types, array($group['recomole']['material_type']));
  }
  // Remove qualifiers. Ex.: 'Bog (Bind 19)' => 'Bog'. Lydbog (cd) (mappe 1) => Lydbog (cd).
  foreach ($material_types as $key => $material_type) {
    $material_types[$key] = preg_replace('(\s?\\([\wæøåÆØÅ]+[\s]+[\wæøåÆØÅ0-9]+\))' , '', $material_type);
  }
  $material_types = array_unique($material_types);
  return array(
    '#theme' => 'ting_openformat_work',
    '#fields' => $work_fields,
    '#cover' => $cover,
    '#subworks' => $subworks,
    '#uid' => drupal_clean_css_identifier($bibdkWork->getId()),
    '#recomole' => array(
      'pids' => $pids,
      'limit' => variable_get('bibdk_recommender_limit', 10),
      'authorflood' => variable_get('bibdk_recommender_filters_authorflood', 1),
      'types' => $material_types
    ),
  );
}

/** Get Subworks ordered by type and subtype
 *
 * @param $subWorks
 * @return mixed
 */
function ting_openformat_get_subworks($manifestations, $work_id) {
  $ordered_list = $subtype_list = array();
  $subwork_manifestations = array();
  /* @var Manifestation $manifestation */

  // Collect ids for 'order work' checkbox.
  foreach ($manifestations as $manifestation) {
    if (get_class($manifestation) == 'Manifestation') {
      $subtype = $manifestation->getSubType();
      $manifestation_ids = $manifestation->getIDs();
      foreach ($manifestation_ids as $id) {
        $subtype_list[$subtype][] = $id;
      }
    }
    else {
      if (get_class($manifestation) == 'BibdkBriefDisplay') {
        $subtype = $manifestation->manifestation->type->{'$'};
        $subtype_list[$subtype][] = $manifestation->id;
      }
    }
  }
  foreach ($manifestations as $manifestation) {
    $subtype = NULL;
    $key = drupal_clean_css_identifier($manifestation->getSubType() . '-' . $work_id);
    if (get_class($manifestation) == 'Manifestation') {
      $subtype = $manifestation->getSubType();
    }
    else if (get_class($manifestation) == 'BibdkBriefDisplay') {
      $subtype = $manifestation->manifestation->type->{'$'};
    }
    $subtype_ids = (!empty($subtype)) ? $subtype_list[$subtype] : array();
    $manifestation->setSubtypeOrderIds($subtype_ids);
    $ordered_list[$key]['tab'] = array(
      '#theme' => 'bibdk_icon',
      '#text' => t($subtype, array(), array('context' => 'material_type')),
      '#icon' => $manifestation->getType(),
    );
    // Recommender need the untranslated string.
    $ordered_list[$key]['recomole'] = array(
      'material_type' => $subtype,
    );
    $subwork_manifestations[$key][] = $manifestation;
    $ordered_list[$key]['manifestations'][] = ting_openformat_get_manifestation_for_subwork($manifestation, $view_mode = 'full', $langcode = NULL);
    $ordered_list[$key]['subtype_order_ids'] = $subtype_ids;
  }
  foreach ($ordered_list as $key => $value) {
    $ordered_list[$key]['toggle'] = ting_openformat_subwork_toggle($value['manifestations'], $value['subtype_order_ids']);
    $ordered_list[$key]['subwork_actions'] = module_invoke_all('ting_openformat_subwork_materialtype_actions', $subwork_manifestations[$key], $key);
    $ordered_list[$key]['active'] = (array_search($key, array_keys($ordered_list)) == 0) ? 'active' : '';
  }
  return $ordered_list;
}


/**
 * Get toggle button for subwork if more than 1 manifestation
 *
 * @param array $manifestations
 * @return array
 */
function ting_openformat_subwork_toggle($manifestations, $subtype_order_ids = NULL) {
  $toggle = array();
  $count = count($manifestations);
  if ($count > 1) {
    $toggle = array(
      '#theme' => 'ting_openformat_toggle_link',
      '#icon' => 'icon-blue-down',
      '#show' => t("show all (@count)", array('@count' => $count)),
      '#hide' => t('hide'),
      '#subtype_order_ids' => $subtype_order_ids,
      '#attributes' => array(
        'class' => array('manifestation-toggle-link'),
      ),
    );
  }

  return $toggle;
}

/**
 * get view or container for manifestation
 *
 * @param mixed $manifestation
 * @param string $view_mode
 * @param null $langcode
 * @return mixed
 */
function ting_openformat_get_manifestation_for_subwork($manifestation, $view_mode = 'full', $langcode = NULL) {
  if (get_class($manifestation) == 'Manifestation') {
    // first element is parsed
    $manifestation_view = ting_openformat_manifestation_view($manifestation, $view_mode, $langcode);
  }
  else {
    // other elements are given a container
    $manifestation_view = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('manifestation-container'),
        'data-id' => $manifestation->id,
        'data-subtypeIds' => implode(',', $manifestation->getSubtypeOrderIds()),
        'id' => drupal_clean_css_identifier($manifestation->id),
      ),
    );
  }
  return $manifestation_view;
}


/**
 * Generate view for a single manifestation
 *
 * @param $manifestation
 * @param string $view_mode
 * @param null $langcode
 *
 * @return array
 */
function ting_openformat_manifestation_view($manifestation, $view_mode = 'full', $langcode = NULL, $subtype_pids = array()) {
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }

  $fields = _prepare_view('bibdkManifestation', $manifestation, $view_mode, $langcode);
  $actions = ting_openformat_get_actions('bibdkManifestation', $manifestation, $view_mode, $langcode, $subtype_pids);
  return array(
    '#theme' => 'ting_openformat_manifestation',
    '#fields'  => $fields,
    '#actions' => $actions,
    '#typeof'  => $manifestation->getSchemaOrgType(), // schema.org creativework type
  );
}

/**
 * Check if user has loaded full or short view
 *
 * If $_SESSION['search_settings']['full_view'] is TRUE the generated will be a
 * full view with all information visible.
 *
 * @return bool
 */
function _ting_openformat_init_full_view() {
  if (bibdk_usersettings_user_settings_get('ting_openformat_fullview_usersetting', FALSE)) {
    $_SESSION['search_settings']['full_view'] = TRUE;
  }
  if (isset($_SESSION['search_settings']['full_view']) && $_SESSION['search_settings']['full_view'] == TRUE) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Create title element for brief display view
 *
 * @param BibdkCollection $collection
 * @return array|mixed|null|string
 */
function _ting_openformat_brief_display_title(BibdkCollection $collection) {
  $title = $collection->getTitleFull();
  if (empty($title)) {
    $title = $collection->getTitle();
  }
  if ($language = $collection->getLanguageForBriefDisplay()) {
    $title .= " ($language)";
  }
  return $title;
}

/**
 * Genrates a list with classes based on the material types in the given
 * collection
 *
 * @param BibdkCollection $bibdkobject
 * @return array
 */
function _ting_openformat_get_types_list($bibdkobject) {
  $list = $bibdkobject->getWorkTypes();
  if ($bibdkobject->isOnline()) {
    $list['online'] = 'online';
  }

  return array(
    '#type' => 'ol',
    '#theme' => 'item_list',
    '#items' => $list,
    '#attributes' => array(
      'class' => array('material-types-list'),
    ),
  );
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
  $form = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => array('ajax_placeholder_' . $uid),
    ),
  );
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
    '#attributes' => array(
      'class' => array('visuallyhidden'),
      'data-work-load' => TRUE
    ),
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
 * @param array $form
 * @param array $form_state
 * @return array
 */
function ting_openformat_show_info_ajax_callback(&$form, $form_state) {
  $ids = $form_state['clicked_button']['#ids'];
  $uid = $form_state['clicked_button']['#uid'];
  $collection = $form_state['clicked_button']['#collection'];
  $tracking_id = $form_state['clicked_button']['#trackId'];

  $view = ting_openformat_load_single_full_work($collection, $ids, $uid, $tracking_id);
  $view = theme('status_messages') . drupal_render($view);

  $commands = array();
  $commands[] = ajax_command_replace(NULL, $view);

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Invokes hook_ting_openformat_actions().
 *
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
 * attach entity fields to a single entity. Return a renderable array
 *
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


/**
 * Implements hook_worktabs_items
 *
 * Add description and subjects to a work-information tab
 *
 * @param BibdkWork $entity
 * @return array
 */
function ting_openformat_worktabs_items(BibdkWork $entity) {
  $elements = array();
  $tabs = array();

  if ($abstract = _ting_openformat_parse_element($entity->getAbstract())) {
    $elements['abstract'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('work-abstract'),
      ),
      'summary' => ting_openformat_text_summary($abstract),
    );
  }

  if ($subjects = _ting_openformat_parse_element($entity->getSubjects())) {
    $divider = array('#markup' => ', ');
    $subjects_divider = array();
    foreach ($subjects as $key => $arr) {
      if ( $subjects_divider ) {
        $subjects_divider[] = $divider;
      }
      $subjects_divider[] = $arr;
    }
    $label = t('subjects_label', array(), array('context' => 'ting_openformat'));
    $elements['subject'] = array(
      '#type' => 'container',
      '#prefix' => '<div class="field-label work-field-label">' . $label . '</div>',
      '#attributes' => array(
        'class' => array('work-subject'),
      ),
      'subjects' => $subjects_divider,
    );
  }

  if ($subjects = _ting_openformat_parse_element($entity->getLaesekompasSubjects())) {
    $divider = array('#markup' => ', ');
    $subjects_divider = array();
    foreach ($subjects as $key => $arr) {
      if ( $subjects_divider ) {
        $subjects_divider[] = $divider;
      }
      $subjects_divider[] = $arr;
    }
    $label = t('lk_subjects_label', array(), array('context' => 'ting_openformat'));
    $elements['laesekompassubject'] = array(
      '#type' => 'container',
      '#prefix' => '<div class="field-label work-field-label">' . $label . '</div>',
      '#attributes' => array(
        'class' => array('work-subject'),
      ),
      'subjects' => $subjects_divider,
    );
  }

  if (empty($elements)) {
    $elements = array(
      '#markup' => t('no_description_for_work', array(), array('context' => 'ting_openformat')),
    );
  }

  $tabs['basic-information']['work-information'] = array(
    '#content' => drupal_render($elements),
    'weight' => -1,
  );

  return $tabs;
}
