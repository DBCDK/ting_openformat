<?php

/**
 * List of fields and their settings
 * @return array
 */
function ting_openformat_bibdk_fields() {

  $fields = array(
    'ting_openformat_work_abstract' => array(
      'label' => 'Work abstract',
      'entity_type' => 'bibdkWorkEntity',
      'display' => array('full'),
      'description' => t('Description of work'),
      'callback method' =>  'getAbstract',

    ),
    'ting_openformat_work_subjects' => array(
      'label' => 'Work subjects',
      'entity_type' => 'bibdkWorkEntity',
      'display' => array('full'),
      'description' => t('Subjects of work'),
      'callback method' =>  'getSubjects',
      'callback options' => array('delimiter' => '; ', 'header' => FALSE)

    ),
    /********* MANIFESTATION ************/
    'bibdk_latest_reprint' => array(
      'label' => 'Latest reprint',
      'entity_type' => array('bibdkManifestation','bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => t('descripton for latest reprint'),
      'callback method' =>  'getLatestReprint',
    ),
    
    
    'ting_openformat_mani_abstract' => array(
      'label' => 'Work abstract',
      'entity_type' => 'bibdkManifestation',
      'display' => array('full'),
      'description' => t('Description of work'),
      'callback method' =>  'getAbstract',
    ),
    'ting_openformat_mani_subjects' => array(
      'label' => 'Work subjects',
      'entity_type' => 'bibdkManifestation',
      'display' => array('full'),
      'description' => t('Subjects of work'),
      'callback method' =>  'getSubjects',
    ),
    'bibdk_mani_infotext' => array(
      'label' => 'Info text',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => t('Info text for manifestation'),
      'callback method' =>  'getInfotext',
      'callback function' =>  '_ting_openformat_parse_bibdk_mani_infotext',

    ),
    'bibdk_mani_distinction' => array(
      'label' => 'Distinction',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full'),
      'description' => t('Title distinction'),
      'callback method' =>  'getDistinction',
    ),
    'bibdk_mani_title' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Title',
      'display' => array('reservation', 'full'),
      'description' => t('Title of manifestation'),
      'callback method' =>  'getTitle',
    ),
    'bibdk_mani_title_specific' => array(
      'entity_type' => array('bibdkManifestation'),
      'label' => 'Title Sepcific',
      'display' => array('reservation', 'full'),
      'description' => t('Specific title of manifestation'),
      'callback method' =>  'getTitleSpecifc',
    ),
    'bibdk_mani_creators' => array(
      'label' => 'Creators',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('reservation', 'full'),
      'description' => t('creators of manifestation'),
      'callback method' =>  'getCreator',
    ),
    'bibdk_mani_contribs' => array(
      'label' => 'Contributors',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('contributors to manifestation'),
      'callback method' =>  'getContributors',

    ),
    'bibdk_mani_type' => array(
      'label' => 'Manifestation type',
      'entity_type' => array('bibdkManifestation'),
      'display' => array('full', 'reservation'),
      'description' => t('type of manifestation'),
      'callback method' =>  'getType',
    ),
    'bibdk_mani_publisher' => array(
      'label' => 'Publisher',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Publisher of manifestation'),
      'callback method' =>  'getPublisher',
    ),
    'bibdk_mani_edition' => array(
      'label' => 'Edition',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Edition of manifestation'),
      'callback method' =>  'getEdition',
    ),
    'bibdk_mani_pub_year' => array(
      'label' => 'Publication Year',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Publication Year of manifestation'),
      'callback method' =>  'getPublicationYear',
    ),
    'bibdk_mani_host_pub' => array(
      'label' => 'Host Publication',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Host Publication of manifestation'),
      'callback method' =>  'getHostPublication',
    ),
    'bibdk_mani_format' => array(
      'label' => 'Format',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Formats of manifestation'),
      'callback method' =>  'getFormat',
    ),
    'bibdk_mani_series' => array(
      'label' => 'Series',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Series titles of manifestation'),
      'callback method' =>  'getSeriesTitle',
    ),
    'bibdk_mani_identifiers' => array(
      'label' => 'Identifiers',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Identifiers of manifestation'),
      'callback method' =>  'getIdentifiers',
    ),
    'bibdk_mani_identifiers_isbn' => array(
      'label' => 'Identifiers ISBN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('ISBN of manifestation'),
      'callback method' =>  'getIdentifiersISBN',
    ),
    'bibdk_mani_identifiers_ismn' => array(
      'label' => 'Identifiers ISMN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('ISMN of manifestation'),
      'callback method' =>  'getIdentifiersISMN',
    ),
    'bibdk_mani_identifiers_issn' => array(
      'label' => 'Identifiers ISSN',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('ISSN of manifestation'),
      'callback method' =>  'getIdentifiersISSN',
    ),
    'bibdk_mani_alt_title' => array(
      'label' => 'Alternative title',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Alternative title of manifestation'),
      'callback method' =>  'getAlternativeTitle',
    ),
    'bibdk_mani_forms' => array(
      'label' => 'Forms',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('forms of manifestation'),
      'callback method' =>  'getForms',
    ),
    'bibdk_mani_text_levels' => array(
      'label' => 'Text Levels',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Text levels of manifestation'),
      'callback method' =>  'getTextLevels',
    ),
    'bibdk_mani_audience_subjects' => array(
      'label' => 'Audience Subjects',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Audience Subjects of manifestation'),
      'callback method' =>  'getAudienceSubjects',
    ),
    'bibdk_mani_marked_audience' => array(
      'label' => 'Marked Audience',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Marked audience of manifestation'),
      'callback method' =>  'getMarkedAudience',
    ),
    'bibdk_mani_recommended_audience' => array(
      'label' => 'Recommended Audience',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Recommended audience of manifestation'),
      'callback method' =>  'getRecommendedAudience',
    ),
    'bibdk_mani_pegi' => array(
      'label' => 'Audience Pegi',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Audience PEGI of manifestation'),
      'callback method' =>  'getAudiencePegi',
    ),
    'bibdk_mani_related_series' => array(
      'label' => 'Related series',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('related titles of manifestation'),
      'callback method' =>  'getRelatedSeriesTitle',
    ),
    'bibdk_mani_readability_indexes' => array(
      'label' => 'Readability indexes',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Readability indexes of manifestation'),
      'callback method' =>  'getReadabilityIndexes',
    ),
    'bibdk_mani_readability_numbers' => array(
      'label' => 'Readability numbers',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Readability numbers of manifestation'),
      'callback method' =>  'getReadabilityNumbers',
    ),
    'bibdk_mani_genre' => array(
      'label' => 'Genre',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Genre of manifestation'),
      'callback method' =>  'getGenre',
    ),
    'bibdk_mani_language' => array(
      'label' => 'Language',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Language of manifestation'),
      'callback method' =>  'getLanguage',
    ),
    'bibdk_mani_used_language' => array(
      'label' => 'Used Language',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Used Language of manifestation'),
      'callback method' =>  'getUsedLanguage',
      'callback options' => array('delimiter' => '. ')
    ),
    'bibdk_mani_orig_title' => array(
      'label' => 'Original title',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Original title of manifestation'),
      'callback method' =>  'getOriginalTitle',
    ),
    'bibdk_mani_references' => array(
      'label' => 'References',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('References of manifestation'),
      'callback method' =>  'getReferences',
    ),
    'bibdk_mani_description_note' => array(
      'label' => 'Description Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Description Note of manifestation'),
      'callback method' =>  'getDescriptionNote',
    ),
    'bibdk_mani_actor_note' => array(
      'label' => 'Actor Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Actor Note of manifestation'),
      'callback method' =>  'getActorNote',
    ),
    'bibdk_mani_content_note' => array(
      'label' => 'Content Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Content Note of manifestation'),
      'callback method' =>  'getContentNote',
    ),
    'bibdk_mani_content_partial_note' => array(
      'label' => 'Content Partial Note',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Content Note of manifestation'),
      'callback method' =>  'getContentPartialNote',
      'callback options' => array('delimiter' => '<br />')
    ),
    'bibdk_mani_analytic_content' => array(
      'label' => 'Analytic Content',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Analytic content of manifestation'),
      'callback method' =>  'getAnalyticContent',
      'callback function' =>  '_ting_openformat_parse_analytic_content',
    ),
    'bibdk_mani_originals' => array(
      'label' => 'Originals',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Originals of manifestation'),
      'callback method' =>  'getOriginals',
    ),
    'bibdk_mani_context' => array(
      'label' => 'Context',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Context of manifestation'),
      'callback method' =>  'getContext',
    ),
    'bibdk_mani_price_information' => array(
      'label' => 'Price Information',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Price Information of manifestation'),
      'callback method' =>  'getPriceInformation',
    ),
    'bibdk_mani_access_information' => array(
      'label' => 'Access Information',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Access Information of manifestation'),
      'callback method' =>  'getAccessInformation',
    ),
    'bibdk_mani_pub_format' => array(
      'label' => 'Publication Format',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Publication Format of manifestation'),
      'callback method' =>  'getPublicationFormat',
    ),
    'bibdk_mani_shelf' => array(
      'label' => 'Shelf',
      'entity_type' => array('bibdkManifestation', 'bibdkManifestationVolume', 'bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Shelf of manifestation'),
      'callback method' =>  'getShelf',
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
      'description' => t('Section of manifestation'),
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
      'description' => t('Volume of manifestation'),
      'callback method' =>  'getVolume',
    ),
    //section specific
    'bibdk_section_title' => array(
      'label' => 'Section Title',
      'entity_type' => array('bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Title of Section'),
      'callback method' =>  'getTitle',
    ),
    'bibdk_section_creators' => array(
      'label' => 'Section Creators',
      'entity_type' => array('bibdkManifestationSection'),
      'display' => array('full'),
      'description' => t('Creators of Section'),
      'callback method' =>  'getCreator',
    ),
    //volume specific
    'bibdk_volume_title' => array(
      'label' => 'Volume Title',
      'entity_type' => array('bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => t('Title of Volume'),
      'callback method' =>  'getTitle',
    ),
    'bibdk_volume_creators' => array(
      'label' => 'Volume Creators',
      'entity_type' => array('bibdkManifestationVolume'),
      'display' => array('full'),
      'description' => t('Creators of Volume'),
      'callback method' =>  'getCreator',
    ),
  );

  module_invoke_all('ting_openformat_field', $fields);

  return $fields;
}
