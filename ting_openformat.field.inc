<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */

function ting_openformat_field_info() {
  return array(
    /*'ting_openformat_work_title' => array(
      'label' => t('Title'),
      'description' => t('title of work'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),*/
    /*'ting_openformat_work_creators' => array(
      'label' => t('Creators'),
      'description' => t('Creators of work'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),*/
    'ting_openformat_work_subjects' => array(
      'label' => t('Subjects'),
      'description' => t('Subjects of work'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'ting_openformat_work_abstract' => array(
      'label' => t('Description'),
      'description' => t('Description of work'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_section' => array(
      'label' => t('Section'),
      'description' => t('Section of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_section_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_volume' => array(
      'label' => t('Volume'),
      'description' => t('Volume of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_title' => array(
      'label' => t('Title'),
      'description' => t('Title of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_creators' => array(
      'label' => t('Creators'),
      'description' => t('creators of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_type' => array(
      'label' => t('Manifestation type'),
      'description' => t('type of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_action_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_orig_title' => array(
      'label' => t('Original title'),
      'description' => t('Original title of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_alt_title' => array(
      'label' => t('Original title'),
      'description' => t('Alternative title of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_contribs' => array(
      'label' => t('Contributors'),
      'description' => t('contributors to manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_forms' => array(
      'label' => t('Forms'),
      'description' => t('forms of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_format' => array(
      'label' => t('Format'),
      'description' => t('Formats of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_series' => array(
      'label' => t('Series title'),
      'description' => t('Series titles of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_related_series' => array(
      'label' => t('Related title'),
      'description' => t('related titles of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_readability_indexes' => array(
      'label' => t('Readability indexes'),
      'description' => t('Readability indexes of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
     'bibdk_mani_readability_numbers' => array(
      'label' => t('Readability numbers'),
      'description' => t('Readability numbers of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_shelf' => array(
      'label' => t('Shelf'),
      'description' => t('Shelf of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_text_levels' => array(
      'label' => t('Text Levels'),
      'description' => t('Text levels of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_genre' => array(
      'label' => t('Genre'),
      'description' => t('Genre of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_audience_subjects' => array(
      'label' => t('Audience Subjects'),
      'description' => t('Audience Subjects of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_marked_audience' => array(
      'label' => t('Marked audience'),
      'description' => t('Marked audience of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_recommended_audience' => array(
      'label' => t('Recommended audience'),
      'description' => t('Recommended audience of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_used_language' => array(
      'label' => t('Used Language'),
      'description' => t('Used Language of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_actor_note' => array(
      'label' => t('Actor Note'),
      'description' => t('Actor Note of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_description_note' => array(
      'label' => t('Description Note'),
      'description' => t('Description Note of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_references' => array(
      'label' => t('References'),
      'description' => t('References of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_originals' => array(
      'label' => t('Originals'),
      'description' => t('Originals of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_context' => array(
      'label' => t('Context'),
      'description' => t('Context of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_identifiers' => array(
      'label' => t('Identifiers'),
      'description' => t('Identifiers of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_price_information' => array(
      'label' => t('Price Information'),
      'description' => t('Price Information of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_language' => array(
      'label' => t('Language'),
      'description' => t('Language of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_access_information' => array(
      'label' => t('Access Information'),
      'description' => t('Access Information of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_mani_publisher' => array(
      'label' => t('Publisher'),
      'description' => t('Publisher of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_mani_pub_year' => array(
      'label' => t('Publication Year'),
      'description' => t('Publication Year of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_mani_edition' => array(
      'label' => t('Edition'),
      'description' => t('Edition of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_mani_pub_format' => array(
      'label' => t('Publication Format'),
      'description' => t('Publication Format of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_mani_host_pub' => array(
      'label' => t('Host Publication'),
      'description' => t('Host Publication of manifestation'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  'bibdk_volume_title' => array(
      'label' => t('Volume Title'),
      'description' => t('Title of Volume'),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'ting_openformat_default_formatter',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_formatter_info
 * */
function ting_openformat_field_formatter_info() {
  $fields = ting_openformat_field_info();
  foreach($fields as $field => $data){
    $fieldtypes[$data['default_formatter']][]= $field;
  }
  return array(
    'ting_openformat_default_formatter' => array(
      'label' => t('Default'),
      'field types' => isset($fieldtypes['ting_openformat_default_formatter']) ? $fieldtypes['ting_openformat_default_formatter'] : NULL,
    ),
    'ting_openformat_section_formatter' => array(
      'label' => t('hidden'),
      'field types' => isset($fieldtypes['ting_openformat_default_formatter']) ? $fieldtypes['ting_openformat_default_formatter'] : NULL,
    ),
    'ting_openformat_button_formatter' => array(
      'label' => t('Default'),
      'field types' => isset($fieldtypes['ting_openformat_button_formatter']) ? $fieldtypes['ting_openformat_button_formatter'] : NULL,
    ),
    'ting_openformat_action_formatter' => array(
      'label' => t('Default'),
      'field types' => isset($fieldtypes['ting_openformat_action_formatter']) ? $fieldtypes['ting_openformat_action_formatter'] : NULL,
    ),
);
}

/**
 * Implements hook_field_load()
 */
function ting_openformat_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_field_formatter_view
 * NOTE; $entity is of type bibdkWork or manifestation (@see ting_openformat.entities.inc)
 * it is possible to extract values directly from bibdkWork->work or bibdkWork->manifestations, but it is preferable to
 * add a method to bibdkWork class (@see e.g ting_openformat.entities.inc::bibdkWork::getCreator().) ... there will be changes in format
 * */
function ting_openformat_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($field['field_name']) {
      // title
      case 'ting_openformat_work_title':
        $element[$delta] = array(
          '#markup' => $entity->getTitle(),
        );
        break;

      // creators
      case 'ting_openformat_work_creators':
        // one or more creators
        $creators = $entity->getCreator();
        $value = _ting_openformat_get_markup_for_field($creators);
        break;

      // subjects
      case 'ting_openformat_work_subjects':
        // one or more subjects
        $subjects = $entity->getSubjects();
        $value = _ting_openformat_get_markup_for_field($subjects, '; ', FALSE);
        break;
      
      // abstract
      case 'ting_openformat_work_abstract':
        // one or more abstracts
        $abstract = $entity->getAbstract();
        $value = _ting_openformat_get_markup_for_field($abstract);
        break;
      case 'bibdk_mani_volume':
        $volume = $entity->getVolume();
        if (isset($volume)){
          $volume_entity = entity_load('bibdkManifestationVolume', $entity->id, $volume);
          $element[$delta]['#markup'] = ting_openformat_volume_view($volume_entity, 'full', $langcode);
        }
        break;
     case 'bibdk_mani_section':
        $volume = $entity->getSection();
        if (isset($volume)){
          $volume_entity = entity_load('bibdkManifestationSection', $entity->id, $volume);
          $element[$delta]['#markup'] = ting_openformat_section_view($volume_entity, 'full', $langcode);
        }
        break;
      // type
      case 'bibdk_mani_type':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $type = $entity->getType();
        $value = _ting_openformat_get_markup_for_field($type);
        break;
      
      // Title
      case 'bibdk_mani_title':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $type = $entity->getTitle();
        $value = _ting_openformat_get_markup_for_field($type);
        break;
      // Creators
      case 'bibdk_mani_creators':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $type = $entity->getCreator();
        $value = _ting_openformat_get_markup_for_field($type);
        break;

      // original title
      case 'bibdk_mani_orig_title':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $orginalTitle = $entity->getOriginalTitle();
        $value = _ting_openformat_get_markup_for_field($orginalTitle);
        break;
      // alternative title
      case 'bibdk_mani_alternative_title':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $alternativeTitle = $entity->getAlternativeTitle();
        $value = _ting_openformat_get_markup_for_field($alternativeTitle);
        break;

      //contributors
      case 'bibdk_mani_contribs':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $contributors = $entity->getContributors();
        $value = _ting_openformat_get_markup_for_field($contributors);
        break;

      //forms
      case 'bibdk_mani_forms':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $forms = $entity->getForms();
        $value = _ting_openformat_get_markup_for_field($forms);
        break;

      //format
      case 'bibdk_mani_format':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $format = $entity->getFormat();
        $value = _ting_openformat_get_markup_for_field($format);
        break;

      // seriesTitle
      case 'bibdk_mani_series':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $seriesTitle = $entity->getSeriesTitle();
        $value = _ting_openformat_get_markup_for_field($seriesTitle);
        break;

      // relatedSeriesTitle
      case 'bibdk_mani_related_series':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $series = $entity->getRelatedSeriesTitle();
        $value = _ting_openformat_get_markup_for_field($series);
        break;

      // shelf
      case 'bibdk_mani_shelf':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $shelf = $entity->getShelf();
        $value = _ting_openformat_get_markup_for_field($shelf);
        break;

     // textLevels
      case 'bibdk_mani_text_levels':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $textLevels = $entity->getTextLevels();
        $value = _ting_openformat_get_markup_for_field($textLevels);
        break;

      // genre
      case 'bibdk_mani_genre':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $genre = $entity->getGenre();
        $value = _ting_openformat_get_markup_for_field($genre);
        break;

      // audienceSubjects
      case 'bibdk_mani_audience_subjects':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $audienceSubjects = $entity->getAudienceSubjects();
        $value = _ting_openformat_get_markup_for_field($audienceSubjects);
        break;

      // markedAudience
      case 'bibdk_mani_marked_audience':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $markedAudience = $entity->getMarkedAudience();
        $value = _ting_openformat_get_markup_for_field($markedAudience);
        break;

      // recommendedAudience
      case 'bibdk_mani_recommended_audience':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $recommendedAudience = $entity->getRecommendedAudience();
        $value = _ting_openformat_get_markup_for_field($recommendedAudience);
        break;


      // usedLanguage
      case 'bibdk_mani_used_language':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $usedLanguage = $entity->getUsedLanguage();
        $value = _ting_openformat_get_markup_for_field($usedLanguage,". ");
        break;

      // actorNote
      case 'bibdk_mani_actor_note':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $actorNote = $entity->getActorNote();
        $value = _ting_openformat_get_markup_for_field($actorNote);
        break;

      // descriptionNote
      case 'bibdk_mani_description_note':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $descriptionNote = $entity->getDescriptionNote();
        $value = _ting_openformat_get_markup_for_field($descriptionNote);
        break;

      // references
      case 'bibdk_mani_references':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $references = $entity->getReferences();
        $value = _ting_openformat_get_markup_for_field($references);
        break;

      // originals
      case 'bibdk_mani_originals':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $originals = $entity->getOriginals();
        $value = _ting_openformat_get_markup_for_field($originals);
        break;

      // context
      case 'bibdk_mani_context':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $context = $entity->getContext();
        $value = _ting_openformat_get_markup_for_field($context);
        break;

      // identifiers
      case 'bibdk_mani_identifiers':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $identifiers = $entity->getIdentifiers();
        $value = _ting_openformat_get_markup_for_field($identifiers);
        
        break;

      // priceInformation
      case 'bibdk_mani_price_information':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $priceInformation = $entity->getPriceInformation();
        $value = _ting_openformat_get_markup_for_field($priceInformation);
        break;

      // language
      case 'bibdk_mani_language':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $language = $entity->getLanguage();
        $value = _ting_openformat_get_markup_for_field($language);
        break;

 // readabilityIndexes
      case 'bibdk_mani_readability_indexes':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $readabilityIndexes = $entity->getReadabilityIndexes();
        $value = _ting_openformat_get_markup_for_field($readabilityIndexes);
        break;

// readabilityNumbers
      case 'bibdk_mani_readability_numbers':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $readabilityNumbers = $entity->getReadabilityNumbers();
        $value = _ting_openformat_get_markup_for_field($readabilityNumbers);
        break;

      // accessInformation
      case 'bibdk_mani_access_information':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $accessInformation = $entity->getAccessInformation();
        $value = _ting_openformat_get_markup_for_field($accessInformation);
        break;

     // publisher
      case 'bibdk_mani_publisher':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $publisher = $entity->getPublisher();
        $value = _ting_openformat_get_markup_for_field($publisher);
        break;

     // publicationYear
      case 'bibdk_mani_pub_year':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $publicationYear = $entity->getPublicationYear();
        $value = _ting_openformat_get_markup_for_field($publicationYear);
        break;

     // edition
      case 'bibdk_mani_edition':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $edition = $entity->getEdition();
        $value = _ting_openformat_get_markup_for_field($edition);
        break;

     // publicationFormat
      case 'bibdk_mani_pub_format':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $publicationFormat = $entity->getPublicationFormat();
        $value = _ting_openformat_get_markup_for_field($publicationFormat);
        break;

     // hostPublication
      case 'bibdk_mani_host_pub':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $hostPublication = $entity->getHostPublication();
        $value = _ting_openformat_get_markup_for_field($hostPublication);
        break;
      // hostPublication
      case 'bibdk_volume_title':
        // entity is manifestationVolume ( @see ting_openformat.entities.inc::manifestation )
        $title = $entity->getTitle();
        $value = _ting_openformat_get_markup_for_field($title);
        break;
    }
    if(isset($value))
    $element[$delta] = $value;
  }
  return $element;
}

/**
 * Creates a #markup array if content exists
 */
function _ting_openformat_get_markup_for_field($elements, $divider = ", ", $use_header = TRUE){
  $return = NULL; 
  $markup = _ting_openformat_parse_element($elements, $divider, $use_header);
   if (isset($markup))
      $return  = array(
          '#markup' => $markup,
        );
  return $return;      
}

/**
 * Parses a field array from a manifestation/work entity. returns a string.
 * searchCode and header are specialcases what generates a field-label and a link
 * @param array $elements
 * @return string
 */
function _ting_openformat_parse_element ($elements, $divider = ". ", $use_header = TRUE){
  if (!isset($elements))
    return null;
  if (!is_array($elements))
    $elements =  array($elements);
  foreach($elements as $key => $value){
    if (is_array($value)){
      $array[] = _ting_openformat_parse_element($value, $divider, $use_header);
    }
    elseif ($key === "header"){
      if($use_header)
        $header = $value;
    }
    elseif ($key === 'searchCode') {
      $array[] = l($elements['display'], 'search/work/' . $elements['searchCode']);
    }
    elseif( $key === 'accessUrl' ) {
      $array[] = l($value,$value,array('attributes'=>array('target'=>'_blank')));
    }
    elseif ($key === 'display'){/*do nothing*/}
    else{
      $array[] = $value;
    }
  }
  $string = (isset($header)) ? $header." " : " ";
  if (isset($array)){
      $string .= implode($divider, $array);
  }
  return $string;
}

//865 lines before refactoring