<?php

/**
 * Danger, Will Robinson!
 *
 * You can't test parsing of elements by expecting NULL or the empty string!
 * So don't even try, that even includes copy/pasting.
 *
 * Two thirds of the test results below are bogus.
 */
function ting_openformat_test_results() {
  return array(
    'ting_openformat_work_abstract' =>
    array(
      'method' => 'getAbstract',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_system_demand' =>
    array(
      'method' => 'getSystemDemands',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_dependent_title' =>
    array(
      'method' => 'getDependentTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
      ),
    'bibdk_mani_access_met' =>
    array(
      'method' => 'getAccessMethod',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_mani_database_ref' =>
    array(
      'method' => 'getDatabaseRef',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_mani_content_title' =>
    array(
      'method' => 'getContentTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_mani_title_specific' =>
    array(
      'method' => 'getTitleSpecific',
      '_ting_openformat_default_field_view_content' => 'Rigoletto (Giulini)',
      '_ting_openformat_parse_element' => 'Rigoletto (Giulini)',
    ),
    'ting_openformat_work_subjects' =>
    array(
      'method' => 'getSubjects',
      '_ting_openformat_default_field_view_content' =>
      array(
        'subjects' =>
        array(
          0 =>
          array(
            'subject' =>
            array(
              0 =>
              array(
                0 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="romantik"',
                  'display' => 'romantik',
                ),
                1 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="opera"',
                  'display' => 'opera',
                ),
                2 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="vokal"',
                  'display' => 'vokal',
                ),
                3 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="1850-1859"',
                  'display' => '1850-1859',
                ),
                4 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="Italien"',
                  'display' => 'Italien',
                ),
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/dkcclphrase.lem%3D%22romantik%22">romantik</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22opera%22">opera</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22vokal%22">vokal</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%221850-1859%22">1850-1859</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22Italien%22">Italien</a>',
    ),
    'ting_openformat_mani_abstract' =>
    array(
      'method' => 'getAbstract',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'ting_openformat_mani_subjects' =>
    array(
      'method' => 'getSubjects',
      '_ting_openformat_default_field_view_content' =>
      array(
        'subjects' =>
        array(
          0 =>
          array(
            'subject' =>
            array(
              0 =>
              array(
                0 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="romantik"',
                  'display' => 'romantik',
                ),
                1 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="opera"',
                  'display' => 'opera',
                ),
                2 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="vokal"',
                  'display' => 'vokal',
                ),
                3 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="1850-1859"',
                  'display' => '1850-1859',
                ),
                4 =>
                array(
                  'searchCode' => 'dkcclphrase.lem="Italien"',
                  'display' => 'Italien',
                ),
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/dkcclphrase.lem%3D%22romantik%22">romantik</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22opera%22">opera</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22vokal%22">vokal</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%221850-1859%22">1850-1859</a>. <a href="[base_path]search/work/dkcclphrase.lem%3D%22Italien%22">Italien</a>',
    ),
    'bibdk_mani_infotext' =>
    array(
      'method' => 'getInfotext',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_distinction' =>
    array(
      'method' => 'getDistinction',
      '_ting_openformat_default_field_view_content' => 'Giulini',
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_mani_title' =>
    array(
      'method' => 'getTitle',
      '_ting_openformat_default_field_view_content' => 'Rigoletto',
      '_ting_openformat_parse_element' => 'Rigoletto',
    ),
    'bibdk_mani_creators' =>
    array(
      'method' => 'getCreator',
      '_ting_openformat_default_field_view_content' =>
      array(
        0 =>
        array(
          'creator' =>
          array(
            0 =>
            array(
              0 =>
              array(
                'searchCode' => 'phrase.creator="Giuseppe Verdi"',
                'display' => 'Giuseppe Verdi',
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/phrase.creator%3D%22Giuseppe%20Verdi%22">Giuseppe Verdi</a>',
    ),
    'bibdk_mani_contribs' =>
    array(
      'method' => 'getContributors',
      '_ting_openformat_default_field_view_content' =>
      array(
        'contributors' => 'solister: Kostas Paskalis, Renata Scotto, Luciano Pavarotti, Bianca Bartoluzzi, Paolo Washington, Plinio Clabassi m. fl. ; Roms Operas Kor og Orkester ; dirigent: Carlo Maria Giulini',
      ),
      '_ting_openformat_parse_element' => 'solister: Kostas Paskalis, Renata Scotto, Luciano Pavarotti, Bianca Bartoluzzi, Paolo Washington, Plinio Clabassi m. fl. ; Roms Operas Kor og Orkester ; dirigent: Carlo Maria Giulini',
    ),
    'bibdk_mani_type' =>
    array(
      'method' => 'getType',
      '_ting_openformat_default_field_view_content' => 'music',
      '_ting_openformat_parse_element' => 'music',
    ),
    'bibdk_mani_publisher' =>
    array(
      'method' => 'getPublisher',
      '_ting_openformat_default_field_view_content' => 'L\'Estro Armonico',
      '_ting_openformat_parse_element' => 'L\'Estro Armonico',
    ),
    'bibdk_mani_edition' =>
    array(
      'method' => 'getEdition',
      '_ting_openformat_default_field_view_content' => array('0' => ''),
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_pub_year' =>
    array(
      'method' => 'getPublicationYear',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_host_pub' =>
    array(
      'method' => 'getHostPublication',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_format' =>
    array(
      'method' => 'getFormat',
      '_ting_openformat_default_field_view_content' =>
      array(
        'format' => '3 plader, mono',
      ),
      '_ting_openformat_parse_element' => '3 plader, mono',
    ),
    'bibdk_mani_series' =>
    array(
      'method' => 'getSeriesTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_identifiers' =>
    array(
      'method' => 'getIdentifiers',
      '_ting_openformat_default_field_view_content' =>
      array(
        0 =>
        array(
          'identifier' => 'L\'Estro Armonico EA 020',
        ),
      ),
      '_ting_openformat_parse_element' => 'L\'Estro Armonico EA 020',
    ),
    'bibdk_mani_identifiers_isbn' =>
    array(
      'method' => 'getIdentifiersISBN',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_identifiers_ismn' =>
    array(
      'method' => 'getIdentifiersISMN',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_identifiers_issn' =>
    array(
      'method' => 'getIdentifiersISSN',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_acquisition_info' =>
    array(
      'method' => 'getAcquisitionInformation',
      '_ting_openformat_default_field_view_content' =>
      array(
        'acquisitionInformation' => array(
          0 => array(
            'acquisitionTerms' => 'kun for medlemmer'
          )
        )
      ),
      '_ting_openformat_parse_element' => 'kun for medlemmer',
    ),
    'bibdk_mani_alt_title' =>
    array(
      'method' => 'getAlternativeTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_forms' =>
    array(
      'method' => 'getForms',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_text_levels' =>
    array(
      'method' => 'getTextLevels',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_audience_subjects' =>
    array(
      'method' => 'getAudienceSubjects',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_marked_audience' =>
    array(
      'method' => 'getMarkedAudience',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_recommended_audience' =>
    array(
      'method' => 'getRecommendedAudience',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_pegi' =>
    array(
      'method' => 'getAudiencePegi',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_related_series' =>
    array(
      'method' => 'getRelatedSeriesTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_readability_indexes' =>
    array(
      'method' => 'getReadabilityIndexes',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_readability_numbers' =>
    array(
      'method' => 'getReadabilityNumbers',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_genre' =>
    array(
      'method' => 'getGenre',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_language' =>
    array(
      'method' => 'getLanguage',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_used_language' =>
    array(
      'method' => 'getUsedLanguage',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_orig_title' =>
    array(
      'method' => 'getOriginalTitle',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_references' =>
    array(
      'method' => 'getReferences',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    // pjo 230519 outcommented failing test
    'bibdk_mani_description_note' =>
    array(
      'method' => 'getDescriptionNote',
      '_ting_openformat_default_field_view_content' => array(
        0 => array(
          0 => array(
            'descriptionNoteLinkElement' => 'Kan downloades i EPUB-format'
          ),
        ),
      ),
      '_ting_openformat_parse_element' => 'Live-optagelser, 19. november 1966 (Rigoletto) og 1945 (Rigoletto (uddrag)). Sunget på italiensk',
    ),
    'bibdk_mani_actor_note' =>
    array(
      'method' => 'getActorNote',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_content_note' =>
    array(
      'method' => 'getContentNote',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_content_partial_note' =>
    array(
      'method' => 'getContentPartialNote',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_analytic_content' =>
    array(
      'method' => 'getAnalyticContent',
      '_ting_openformat_default_field_view_content' =>
      array(
        'analyticContent' =>
        array(
          0 =>
          array(
            'analyticContributor' =>
            array(
              0 =>
              array(
                0 =>
                array(
                  'searchCode' => 'phrase.creator="Giuseppe Verdi"',
                  'display' => 'Giuseppe Verdi',
                ),
              ),
            ),
            'analyticTitle' =>
            array(
              0 =>
              array(
                'analyticTitleMain' =>
                array(
                  0 =>
                  array(
                    0 =>
                    array(
                      'searchCode' => 'dkcclphrase.lti="Rigoletto uddrag"',
                      'display' => 'Rigoletto (uddrag)',
                    ),
                  ),
                ),
                'analyticRestOfTitle' => '/ Jussi Björling, tenor ; Leonard Warren, baryton ; orkester ; dirigent: Cesare Sordero',
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/phrase.creator%3D%22Giuseppe%20Verdi%22">Giuseppe Verdi</a>. <a href="[base_path]search/work/dkcclphrase.lti%3D%22Rigoletto%20uddrag%22">Rigoletto (uddrag)</a>. / Jussi Björling, tenor ; Leonard Warren, baryton ; orkester ; dirigent: Cesare Sordero',
    ),
    'bibdk_mani_originals' =>
    array(
      'method' => 'getOriginals',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_context' =>
    array(
      'method' => 'getContext',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_price_information' =>
    array(
      'method' => 'getPriceInformation',
      '_ting_openformat_default_field_view_content' =>
      array(
        'priceInformation' =>
        array(
          0 =>
          array(
            'price' => 'kr. 139.00',
          ),
        ),
      ),
      '_ting_openformat_parse_element' => 'kr. 139.00',
    ),
    'bibdk_mani_access_information' =>
    array(
      'method' => 'getAccessInformation',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_pub_format' =>
    array(
      'method' => 'getPublicationFormat',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_shelf' =>
    array(
      'method' => 'getShelf',
      '_ting_openformat_default_field_view_content' =>
      array(
        0 =>
        array(
          'shelfMusic' => 'Operaer',
        ),
      ),
      '_ting_openformat_parse_element' => 'Operaer',
    ),
    'bibdk_mani_section' =>
    array(
      'method' => 'getSection',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_mani_volume' =>
    array(
      'method' => 'getVolume',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => '',
    ),
    'bibdk_section_title' =>
    array(
      'method' => 'getTitle',
      '_ting_openformat_default_field_view_content' => 'Rigoletto',
      '_ting_openformat_parse_element' => 'Rigoletto',
    ),
    'bibdk_section_creators' =>
    array(
      'method' => 'getCreator',
      '_ting_openformat_default_field_view_content' =>
      array(
        0 =>
        array(
          'creator' =>
          array(
            0 =>
            array(
              0 =>
              array(
                'searchCode' => 'phrase.creator="Giuseppe Verdi"',
                'display' => 'Giuseppe Verdi',
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/phrase.creator%3D%22Giuseppe%20Verdi%22">Giuseppe Verdi</a>',
    ),
    'bibdk_volume_title' =>
    array(
      'method' => 'getTitle',
      '_ting_openformat_default_field_view_content' => 'Rigoletto',
      '_ting_openformat_parse_element' => 'Rigoletto',
    ),
    'bibdk_volume_creators' =>
    array(
      'method' => 'getCreator',
      '_ting_openformat_default_field_view_content' =>
      array(
        0 =>
        array(
          'creator' =>
          array(
            0 =>
            array(
              0 =>
              array(
                'searchCode' => 'phrase.creator="Giuseppe Verdi"',
                'display' => 'Giuseppe Verdi',
              ),
            ),
          ),
        ),
      ),
      '_ting_openformat_parse_element' => '<a href="[base_path]search/work/phrase.creator%3D%22Giuseppe%20Verdi%22">Giuseppe Verdi</a>',
    ),
    'bibdk_latest_reprint' =>
    array(
      'method' => 'getLatestReprint',
      '_ting_openformat_default_field_view_content' => NULL,
      '_ting_openformat_parse_element' => NULL,
    ),
    'bibdk_mani_common_contributors' =>
    array(
      'method' => 'getCommonContributors',
      '_ting_openformat_default_field_view_content' => 'The Muppets ; Kermit ; Miss Piggy',
      '_ting_openformat_parse_element' => 'The Muppets ; Kermit ; Miss Piggy',
    ),
  );
}
