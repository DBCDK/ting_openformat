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
    'ting_openformat_work_title' => array(
      'label' => t('Title'),
      'description' => t('title of work'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_openformat_work_title_default',
      'no_ui' => TRUE,
    ),
    'ting_openformat_work_creators' => array(
      'label' => t('Creators'),
      'description' => t('Creators of work'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_openformat_work_creators_default',
      'no_ui' => TRUE,
    ),
    'ting_openformat_work_subjects' => array(
      'label' => t('Subjects'),
      'description' => t('Subjects of work'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_openformat_work_subjects_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_type' => array(
      'label' => t('Manifestation type'),
      'description' => t('type of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_type_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_orig_title' => array(
      'label' => t('Original title'),
      'description' => t('Original title of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_orig_title_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_alt_title' => array(
      'label' => t('Original title'),
      'description' => t('Alternative title of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_alternative_title_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_contribs' => array(
      'label' => t('Contributors'),
      'description' => t('contributors to manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_contribs_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_series' => array(
      'label' => t('Series title'),
      'description' => t('Series titles of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_series_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_related_series' => array(
      'label' => t('Related title'),
      'description' => t('related titles of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_related_series_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_readability_indexes' => array(
      'label' => t('Readability indexes'),
      'description' => t('Readability indexes of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_readability_indexes_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_shelf' => array(
      'label' => t('Shelf'),
      'description' => t('Shelf of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_shelf_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_genre' => array(
      'label' => t('Genre'),
      'description' => t('Genre of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_genre_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_audience_subjects' => array(
      'label' => t('Audience Subjects'),
      'description' => t('Audience Subjects of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_audience_subjects_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_marked_audience' => array(
      'label' => t('Marked audience'),
      'description' => t('Marked audience of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_marked_audience_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_recommended_audience' => array(
      'label' => t('Recommended audience'),
      'description' => t('Recommended audience of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_recommended_audience_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_used_language' => array(
      'label' => t('Used Language'),
      'description' => t('Used Language of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_used_language_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_actor_note' => array(
      'label' => t('Actor Note'),
      'description' => t('Actor Note of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_actor_note_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_description_note' => array(
      'label' => t('Description Note'),
      'description' => t('Description Note of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_description_note_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_references' => array(
      'label' => t('References'),
      'description' => t('References of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_references_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_originals' => array(
      'label' => t('Originals'),
      'description' => t('Originals of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_originals_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_context' => array(
      'label' => t('Context'),
      'description' => t('Context of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_context_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_identifiers' => array(
      'label' => t('Identifiers'),
      'description' => t('Identifiers of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_identifiers_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_price_information' => array(
      'label' => t('Price Information'),
      'description' => t('Price Information of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_price_information_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_language' => array(
      'label' => t('Language'),
      'description' => t('Language of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_language_default',
      'no_ui' => TRUE,
    ),
    'bibdk_mani_access_information' => array(
      'label' => t('Access Information'),
      'description' => t('Access Information of manifestation'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_mani_access_information_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 * pjo notes; if this hook is implemented hook_field_formatter_settings_summary() should be implemented too
 */
function ting_openformat_field_formatter_settings_form($field, $instance, $view_mode, $form, $form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = NULL;

  return $element;
}

/**
 * Implements hook_field_formatter_info
 * */
function ting_openformat_field_formatter_info() {
  return array(
    'ting_openformat_work_title_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_openformat_work_title',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'ting_openformat_work_creators_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_openformat_work_creators',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'ting_openformat_work_subjects_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_openformat_work_subjects',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_type_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_type',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_orig_title_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_orig_title',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_alternative_title_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_alt_title',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_contribs_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_contribs',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_series_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_series',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_related_series_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_related_series',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_readability_indexes_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_related_series',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_shelf_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_shelf',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_genre_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_genre',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_audience_subjects_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_audience_subjects',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_marked_audience_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_marked_audience',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_recommended_audience_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_recommended_audience',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_used_language_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_used_language',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_actor_note_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_actor_note',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_description_note_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_description_note',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_references_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_references',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_originals_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_originals',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_context_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_context',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_identifiers_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_identifiers',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_price_information_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_price_information',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_language_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_language',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),
    'bibdk_mani_access_information_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_mani_access_information',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
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
 * NOTE; $entity is of type bibdkWork (@see ting_openformat.entities.inc)
 * it is possible to extract values directly from bibdkWork->work or bibdkWork->manifestations, but it is preferable to
 * add a method to bibdkWork class (@see e.g ting_openformat.entities.inc::bibdkWork::getCreator().) ... there will be changes in format
 * */
function ting_openformat_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      // entity is bibdkWork ( @see ting_openformat.entities.inc::bibdkWork )
      // title
      case 'ting_openformat_work_title_default':
        $element[$delta] = array(
          '#markup' => $entity->getTitle(),
        );
        break;

      // creators
      case 'ting_openformat_work_creators_default':
        // one or more creators
        $creators = $entity->getCreator();
        if (empty($creators) || !isset($creators['creator'])) {
          return;
        }
        $markup = '';
        foreach ($creators['creator'] as $key => $val) {
          if (strlen($markup) > 1) {
            $markup .= ',  ';
          }
          $markup .= l($val['display'], 'search/work/' . $val['searchCode']);
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // subjects
      case 'ting_openformat_work_subjects_default':
        // one or more subjects
        $subjects = $entity->getSubjects();
        if (empty($subjects)) {
          return;
        }
        $markup = '';
        foreach ($subjects['subject'] as $key => $val) {
          if (strlen($markup) > 1) {
            $markup .= ',  ';
          }
          $markup .= l($val['display'], 'search/work/' . $val['searchCode']);
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // type
      case 'bibdk_mani_type_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $markup = $entity->getType();
        if (!$markup) {
          return;
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // original title
      case 'bibdk_mani_orig_title_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $orginalTitle = $entity->getOriginalTitle();
        if (!$orginalTitle) {
          return;
        }
        $element[$delta] = array(
          '#markup' => isset($orginalTitle['originalTitleElement']) ? $orginalTitle['originalTitleElement'] : null,
        );
        break;
      // alternative title
      case 'bibdk_mani_alternative_title_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $markup = $entity->getAlternativeTitle();
        if (!$markup) {
          return;
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      //contributors
      case 'bibdk_mani_contribs_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $markup = $entity->getContributors();
        if (!$markup) {
          return;
        }

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // seriesTitle
      case 'bibdk_mani_series_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $seriesTitle = $entity->getSeriesTitle();
        if (!$seriesTitle) {
          return;
        }

        $markup = array();

        foreach ($seriesTitle as $serie) {
          foreach ($serie['series'] as $key => $val) {
            $markup[] = l($val['display'], 'search/work/' . $val['searchCode']);
          }
        }
        $element[$delta] = array(
          '#markup' => implode(", ", $markup),
        );
        break;

      // relatedSeriesTitle
      case 'bibdk_mani_related_series_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $series = $entity->getRelatedSeriesTitle();

        if (!$series) {
          return;
        }

        $markup = '';
        foreach ($series as $serie) {
          $markup .= isset($serie['relatedSeriesHeader']) ? $serie['relatedSeriesHeader'] : "";
          if (isset($serie['relatedSeries'])) {
            foreach ($serie['relatedSeries'] as $key => $val) {
              $markup .= l($val['display'], 'search/work/' . $val['searchCode']);
              $markup .= ', ';
            }
          }
        }
        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // shelf
      case 'bibdk_mani_shelf_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $shelf = $entity->getShelf();

        if (!$shelf) {
          return;
        }

        $markup = '';

        $markup .= $shelf['shelfHeader'] . ' ';

        if (isset($shelf['shelfMusic']))
          $markup .= $shelf['shelfMusic'];


        if (isset($shelf['shelfClassification']) && isset($shelf['shelfClassification']['display']) && isset($shelf['shelfClassification']['searchCode']))
          $markup .= l($shelf['shelfClassification']['display'], 'search/work/' . $shelf['shelfClassification']['searchCode']);

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // genre
      case 'bibdk_mani_genre_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $genre = $entity->getGenre();
        if (!$genre)
          return;
        $markup = (is_array($genre)) ? implode(", ", $genre) : $genre;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // audienceSubjects
      case 'bibdk_mani_audience_subjects_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $audienceSubjects = $entity->getAudienceSubjects();

        if (!$audienceSubjects) {
          return;
        }

        if (isset($audienceSubjects['audienceSubject'])) {
          foreach ($audienceSubjects['audienceSubject'] as $audienceSubject) {
            if (isset($audienceSubject['searchCode']))
              $links[] = l($audienceSubject['display'], 'search/work/' . $audienceSubject['searchCode']);
          }
          $markup = isset($links) ? implode(",", $links) : null;
        }
        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // markedAudience
      case 'bibdk_mani_marked_audience_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $markedAudience = $entity->getMarkedAudience();
        if (!$markedAudience)
          return;
        $markup = (is_array($markedAudience)) ? implode(", ", $markedAudience) : $markedAudience;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // recommendedAudience
      case 'bibdk_mani_recommended_audience_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $recommendedAudience = $entity->getRecommendedAudience();
        if (!$recommendedAudience)
          return;
        $markup = (is_array($recommendedAudience)) ? implode(", ", $recommendedAudience) : $recommendedAudience;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;


      // usedLanguage
      case 'bibdk_mani_used_language_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $usedLanguage = $entity->getUsedLanguage();
        if (!$usedLanguage)
          return;
        $markup = (is_array($usedLanguage)) ? implode(", ", $usedLanguage) : $usedLanguage;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;


      // actorNote
      case 'bibdk_mani_actor_note_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $actorNote = $entity->getActorNote();
        if (!$actorNote)
          return;
        $markup = (is_array($actorNote)) ? implode(", ", $actorNote) : $actorNote;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // descriptionNote
      case 'bibdk_mani_description_note_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $descriptionNote = $entity->getDescriptionNote();
        if (!$descriptionNote)
          return;

        $markup = (is_array($descriptionNote)) ? implode(", ", $descriptionNote) : $descriptionNote;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // references
      case 'bibdk_mani_references_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $references = $entity->getReferences();
        if (!$references)
          return;
        $markup = (is_array($references)) ? implode(", ", $references) : $references;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // originals
      case 'bibdk_mani_originals_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $originals = $entity->getOriginals();
        if (!$originals)
          return;
        $markup = (is_array($originals)) ? implode(", ", $originals) : $originals;

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // context
      case 'bibdk_mani_context_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $context = $entity->getContext();
        if (!$context)
          return;
        $markup = (is_array($context['contextElement'])) ? implode(", ", $context['contextElement']) : $context['contextElement'];

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // identifiers
      case 'bibdk_mani_identifiers_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $identifiers = $entity->getIdentifiers();
        if (!count($identifiers))
          return;

        foreach ($identifiers as $identifier) {

          $markup = isset($identifier['identifierHeader']) ? $identifier['identifierHeader'] : "";
          $markup .= isset($identifier['identifier']) ? $identifier['identifier'] : "";
          $markup .= isset($identifier['ISSN']) ? $identifier['ISSN'] : "";
          $markups[] = $markup;
        }
        $element[$delta] = array(
          '#markup' => implode(", ", $markups),
        );
        break;

      // priceInformation
      case 'bibdk_mani_priceInformation_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $priceInformation = $entity->getPriceInformation();
        if (!$priceInformation)
          return;

        $markup = $priceInformation['PriceHeader'];
        $markup .= $priceInformation['price'];

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // language
      case 'bibdk_mani_language_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $language = $entity->getLanguage();
        if (!$language)
          return;

        $markup = $language['languageHeader'];
        $markup .= $language['languageElement'];

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;

      // accessInformation
      case 'bibdk_mani_access_information_default':
        // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
        $accessInformation = $entity->getAccessInformation();
        if (!$accessInformation)
          return;

        $markup = (is_array($accessInformation['accessUrl'])) ? implode(", ", $accessInformation['accessUrl']) : $accessInformation['accessUrl'];

        $element[$delta] = array(
          '#markup' => $markup,
        );
        break;
    }
  }
  return $element;
}

