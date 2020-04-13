<?php

/**
 * WHEN ADDING FIELDS:
 * add update_hook_N to install file, and run updates
 * function ting_openformat_update_NN() {
 *   ding_entity_modules_enabled(array('ting_openformat'));
 * }
 */

/**
 * List of fields and their settings
 * @return array
 */
function ting_openformat_bibdk_fields() {

  $fields = array(
    'ting_openformat_work_abstract' => array(
      'label' => 'Work abstract',
      'entity_type' => array('bibdkWorkEntity'),
      'display' => array('full'),
      'description' => 'Description of work',
      'callback method' =>  'getAbstract',

    ),
    'ting_openformat_work_subjects' => array(
      'label' => 'Work subjects',
      'entity_type' => array('bibdkWorkEntity'),
      'display' => array('full'),
      'description' => 'Subjects of work',
      'callback method' =>  'getSubjects',

    ),
    'ting_openformat_work_lk_subjects' => array(
      'label' => 'Work Laesekompas subjects',
      'entity_type' => array('bibdkWorkEntity'),
      'display' => array('full'),
      'description' => 'Laesekompas Subjects of work',
      'callback method' =>  'getLaesekompasSubjects',

    ),
    /********* MANIFESTATION ************/
    'bibdk_dependent_title'  => array(
      'label' => 'DependentTitle',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'descripton for dependent title',
      'callback method' =>  'getDependentTitle',
    ),

    'bibdk_latest_reprint' => array(
      'label' => 'Latest reprint',
      'entity_type' => array('bibdkManifestation','bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => 'descripton for latest reprint',
      'callback method' =>  'getLatestReprint',
    ),


    'ting_openformat_mani_abstract' => array(
      'label' => 'Work abstract',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Description of work',
      'callback method' =>  'getAbstract',
    ),
    'ting_openformat_mani_subjects' => array(
      'label' => 'Work subjects',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Subjects of work',
      'callback method' =>  'getSubjects',
    ),
    'ting_openformat_mani_lk_subjects' => array(
      'label' => 'Work Laesekompas subjects',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Laesekompas Subjects of work',
      'callback method' =>  'getLaesekompasSubjects',

    ),
    'bibdk_mani_infotext' => array(
      'label' => 'Info text',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Info text for manifestation',
      'callback method' =>  'getInfotext',

    ),
    'bibdk_mani_distinction' => array(
      'label' => 'Distinction',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Title distinction',
      'callback method' =>  'getDistinction',
    ),
    'bibdk_mani_title' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Title',
      'display' => array('reservation', 'full', 'cart'),
      'description' => 'Title of manifestation',
      'callback method' =>  'getTitle',
    ),
    'bibdk_mani_title_specific' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Title Specific',
      'display' => array('reservation', 'full'),
      'description' => 'Specific title of manifestation',
      'callback method' =>  'getTitleSpecific',
    ),
    'bibdk_mani_creators' => array(
      'label' => 'Creators',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('reservation', 'full', 'cart'),
      'description' => 'creators of manifestation',
      'callback method' =>  'getCreator',
    ),
    'bibdk_mani_contribs' => array(
      'label' => 'Contributors',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'contributors to manifestation',
      'callback method' =>  'getContributors',
    ),
    'bibdk_mani_contribs_extra' => array(
      'label' => 'Contributors extra',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'contributors extra to manifestation',
      'callback method' =>  'getContributorExtra',
    ),
    'bibdk_mani_type' => array(
      'label' => 'Manifestation type',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full', 'reservation', 'cart'),
      'description' => 'type of manifestation',
      'callback method' =>  'getType',
    ),
    'bibdk_mani_publisher' => array(
      'label' => 'Publisher',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Publisher of manifestation',
      'callback method' =>  'getPublisher',
    ),
    'bibdk_mani_edition' => array(
      'label' => 'Edition',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Edition of manifestation',
      'callback method' =>  'getEdition',
    ),
    'bibdk_mani_pub_year' => array(
      'label' => 'Publication Year',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Publication Year of manifestation',
      'callback method' =>  'getPublicationYear',
    ),
    'bibdk_mani_host_pub' => array(
      'label' => 'Host Publication',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Host Publication of manifestation',
      'callback method' =>  'getHostPublication',
    ),
    'bibdk_mani_format' => array(
      'label' => 'Format',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Formats of manifestation',
      'callback method' =>  'getFormat',
    ),
    'bibdk_mani_series' => array(
      'label' => 'Series',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Series titles of manifestation',
      'callback method' =>  'getSeriesTitle',
    ),
    'bibdk_mani_identifiers' => array(
      'label' => 'Identifiers',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Identifiers of manifestation',
      'callback method' =>  'getIdentifiers',
    ),
    'bibdk_mani_identifiers_isbn' => array(
      'label' => 'Identifiers ISBN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'ISBN of manifestation',
      'callback method' =>  'getIdentifiersISBN',
    ),
    'bibdk_mani_identifiers_ismn' => array(
      'label' => 'Identifiers ISMN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'ISMN of manifestation',
      'callback method' =>  'getIdentifiersISMN',
    ),
    'bibdk_mani_identifiers_issn' => array(
      'label' => 'Identifiers ISSN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'ISSN of manifestation',
      'callback method' =>  'getIdentifiersISSN',
    ),
    'bibdk_mani_acquisition_info' => array(
      'label' => 'Acquisition',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Acquisition information',
      'callback method' =>  'getAcquisitionInformation',
    ),
    'bibdk_mani_alt_title' => array(
      'label' => 'Alternative title',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Alternative title of manifestation',
      'callback method' =>  'getAlternativeTitle',
    ),
    'bibdk_mani_forms' => array(
      'label' => 'Forms',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'forms of manifestation',
      'callback method' =>  'getForms',
    ),
    'bibdk_mani_text_levels' => array(
      'label' => 'Text Levels',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Text levels of manifestation',
      'callback method' =>  'getTextLevels',
    ),
    'bibdk_mani_audience_subjects' => array(
      'label' => 'Audience Subjects',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Audience Subjects of manifestation',
      'callback method' =>  'getAudienceSubjects',
    ),
    'bibdk_mani_marked_audience' => array(
      'label' => 'Marked Audience',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Marked audience of manifestation',
      'callback method' =>  'getMarkedAudience',
    ),
    'bibdk_mani_recommended_audience' => array(
      'label' => 'Recommended Audience',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Recommended audience of manifestation',
      'callback method' =>  'getRecommendedAudience',
    ),
    'bibdk_mani_pegi' => array(
      'label' => 'Audience Pegi',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Audience PEGI of manifestation',
      'callback method' =>  'getAudiencePegi',
    ),
    'bibdk_mani_related_series' => array(
      'label' => 'Related series',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'related titles of manifestation',
      'callback method' =>  'getRelatedSeriesTitle',
    ),

    'bibdk_mani_readability_indexes' => array(
      'label' => 'Readability indexes',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Readability indexes of manifestation',
      'callback method' =>  'getReadabilityIndexes',
    ),
    'bibdk_mani_readability_numbers' => array(
      'label' => 'Readability numbers',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Readability numbers of manifestation',
      'callback method' =>  'getReadabilityNumbers',
    ),
    'bibdk_mani_genre' => array(
      'label' => 'Genre',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Genre of manifestation',
      'callback method' =>  'getGenre',
    ),
    'bibdk_mani_language' => array(
      'label' => 'Language',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Language of manifestation',
      'callback method' =>  'getLanguage',
    ),
    'bibdk_mani_used_language' => array(
      'label' => 'Used Language',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Used Language of manifestation',
      'callback method' =>  'getUsedLanguage',
    ),
    'bibdk_mani_orig_title' => array(
      'label' => 'Original title',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Original title of manifestation',
      'callback method' =>  'getOriginalTitle',
    ),
    'bibdk_mani_references' => array(
      'label' => 'References',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'References of manifestation',
      'callback method' =>  'getReferences',
    ),
    'bibdk_mani_description_note' => array(
      'label' => 'Description Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Description Note of manifestation',
      'callback method' =>  'getDescriptionNote',
    ),
    'bibdk_mani_common_contributors' => array(
      'label' => 'Common contributors',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationSection', 'bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => 'Common contributors of manifestation',
      'callback method' =>  'getCommonContributors',
    ),
    'bibdk_mani_actor_note' => array(
      'label' => 'Actor Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Actor Note of manifestation',
      'callback method' =>  'getActorNote',
    ),

    'bibdk_mani_content_title' => array(
      'label' => 'Content Title',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Content Title of manifestation',
      'callback method' =>  'getContentTitle',
    ),

    'bibdk_mani_system_demand' => array(
      'label' => 'System demands',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'System demands of manifestation',
      'callback method' =>  'getSystemDemands',
    ),

    'bibdk_mani_database_ref' => array(
      'label' => 'Database references',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'External references to database',
      'callback method' =>  'getDatabaseRef',
    ),

     'bibdk_mani_access_met' => array(
      'label' => 'Access methods',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => 'Access to resource',
      'callback method' =>  'getAccessMethod',
    ),

    'bibdk_mani_content_note' => array(
      'label' => 'Content Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Content Note of manifestation',
      'callback method' =>  'getContentNote',
    ),
    'bibdk_mani_content_partial_note' => array(
      'label' => 'Content Partial Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Content Note of manifestation',
      'callback method' =>  'getContentPartialNote',
    ),
    // NB! OLD VERSION - to be removed when new bibdkWorkDisplay format is fully implemented
    'bibdk_mani_analytic_content' => array(
      'label' => 'Analytic Content',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Analytic content of manifestation',
      'callback method' =>  'getAnalyticContent',
    ),
    // New bibdkWorkDisplay
    'bibdk_mani_tracks' => array(
      'label' => 'Tracks',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Track content of manifestation',
      'callback method' =>  'getTrackContent',
    ),
    'bibdk_mani_originals' => array(
      'label' => 'Originals',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Originals of manifestation',
      'callback method' =>  'getOriginals',
    ),
    'bibdk_mani_context' => array(
      'label' => 'Context',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Context of manifestation',
      'callback method' =>  'getContext',
    ),
    'bibdk_mani_price_information' => array(
      'label' => 'Price Information',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Price Information of manifestation',
      'callback method' =>  'getPriceInformation',
    ),
    'bibdk_mani_access_information' => array(
      'label' => 'Access Information',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Access Information of manifestation',
      'callback method' =>  'getAccessInformation',
    ),
    'bibdk_mani_pub_format' => array(
      'label' => 'Publication Format',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Publication Format of manifestation',
      'callback method' =>  'getPublicationFormat',
    ),
    'bibdk_mani_shelf' => array(
      'label' => 'Shelf',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Shelf of manifestation',
      'callback method' =>  'getShelf',
    ),
    'bibdk_mani_shelf_public' => array(
      'label' => 'Shelf Public Libraries',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Shelf public libraries to manifestation',
      'callback method' =>  'getShelfPublicLibrary',
    ),
    'bibdk_mani_section' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Section',
      'custom_display' => array(
        'default' => array(
          'type' => 'default',
          'label' => 'hidden'
        ),
        'full' => array(
          'type' => 'default',
          'label' => 'hidden'
        ),
      ),
      'description' => 'Section of manifestation',
      'callback method' =>  'getSection',
    ),
    'bibdk_mani_volume' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Volume',
      'custom_display' => array(
        'default' => array(
          'type' => 'default',
          'label' => 'hidden'
        ),
        'full' => array(
          'type' => 'default',
          'label' => 'hidden'
        ),
      ),
      'description' => 'Volume of manifestation',
      'callback method' =>  'getVolume',
    ),

    'bibdk_mani_debates' => array(
      'label'           => 'Debates',
      'entity_type'     => array('bibdkManifestation'),
      'display'         => array('full'),
      'description'     => 'links to debates',
      'callback method' => 'getDebateLinks',
    ),

    //section specific
    'bibdk_section_title' => array(
      'label' => 'Section Title',
      'entity_type' => array('bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Title of Section',
      'callback method' =>  'getTitle',
    ),
    'bibdk_section_creators' => array(
      'label' => 'Section Creators',
      'entity_type' => array('bibdkManifestationSection'),
      'display' => array('full'),
      'description' => 'Creators of Section',
      'callback method' =>  'getCreator',
    ),
    //volume specific
    'bibdk_volume_title' => array(
      'label' => 'Volume Title',
      'entity_type' => array('bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => 'Title of Volume',
      'callback method' =>  'getTitle',
    ),
    'bibdk_volume_creators' => array(
      'label' => 'Volume Creators',
      'entity_type' => array('bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => 'Creators of Volume',
      'callback method' =>  'getCreator',
    ),
  );

  $hooks = module_implements('ting_openformat_fields');
  if (!empty($hooks)) {
    $fields = module_invoke_all('ting_openformat_fields', $fields);
  }
  return $fields;
}
