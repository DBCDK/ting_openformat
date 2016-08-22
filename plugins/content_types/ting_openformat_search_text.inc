<?php

$plugin = array(
  'title' => t('Openformat search - search results text'),
  'description' => t('Show a string with \'Showing x - y of z results'),
  'single' => TRUE,
  'content_types' => array('ting_search_text'),
  'render callback' => 'ting_openformat_search_content_type_render',
  'category' => t('Openformat'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_openformat_search_content_type_render($subtype, $conf, $panel_args, $context) {
  if ($results = drupal_static('ting_search_results')) {
    pager_default_initialize($results->numTotalObjects, 10);
    global $pager_total;
    $block = new stdClass();

    if ($pager_total[0] == TRUE) {
      $total = $results->numTotalObjects;
      $block->title = t('Search results text');
      $block->content =
          '<div class="ting-openformat-search-amount-block"><span>' .
                       ting_openformat_search_content_help_render('input-search-result',
                                                                  format_plural($total,'1 result','@count results', array()),
                                                                  t('Search_help_result', array(), array('context' => 'bibdk_theme'))) .
          '</div>';
    }
    return $block;
  }
}

/**
 * Enable admin settings page
 */
function ting_openformat_ting_openformat_search_text_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Display questionmark, search result text and text for help display
 *
 * @param  $element_id
 * element name
 * @param  $result_text
 * result text for display ex. 36 results
 * @param  $help
 * Defined helptext for display (t function)
 * @return
 * string display blok
 */
function ting_openformat_search_content_help_render($element_id, $result_text, $help ) {

 $helptxt = t('Help', array(), array('context' => 'bibdk_theme'));
 $helptext =
   "<div class='custom-search--helptext-container'>
      <span class='bibdk-pager-next'>$result_text</span>
      <p class='helptext' title='$help'>
      <a data-dropdown='custom-search-elements-help-$element_id'
         aria-controls='custom-search-elements-help-$element_id'
         aria-expanded='false'
         aria-label='$helptxt'
         role='button'>
         <svg class='svg-icon svg-question'>
           <use xlink:href='#svg-question' xmlns:xlink='http://www.w3.org/1999/xlink'>
         </svg>
      </a>
      </p>
      <div id='custom-search-elements-help-$element_id'
        data-dropdown-content
        class='f-dropdown tiny'
        aria-hidden='true'
        tabindex='-1'>
        <p class='helptext-content'>
          $help
        </p>
      </div>
    </div>";
    return $helptext;
}

