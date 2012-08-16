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
      'default_widget'=>'hidden',
      'default_formatter' => 'ting_openformat_work_title_default',
      'no_ui' => TRUE,
    ),
    'ting_openformat_work_creators' => array(
      'label' => t('Creators'),
      'description' => t('Creators of work'),
      'default_widget'=>'hidden',
      'default_formatter' => 'ting_openformat_work_creators_default',
      'no_ui' => TRUE,
    ),
    'ting_openformat_work_subjects' => array(
      'label' => t('Subjects'),
      'description' => t('Subjects of work'),
      'default_widget'=>'hidden',
      'default_formatter' => 'ting_openformat_work_subjects_default',
      'no_ui' => TRUE,
    ),

    'bibdk_manifestation_type' => array(
      'label' => t('Manifestation type'),
      'description' => t('type of manifestation'),
      'default_widget'=>'hidden',
      'default_formatter' => 'bibdk_manifestation_type_default',
      'no_ui' => TRUE,
    ),


    'bibdk_manifestation_orig_title' => array(
      'label' => t('Original title'),
      'description' => t('Original title of manifestation'),
      'default_widget'=>'hidden',
      'default_formatter' => 'bibdk_manifestation_orig_title_default',
      'no_ui' => TRUE,
    ),

    'bibdk_manifestation_contribs' => array(
      'label' => t('Contributors'),
      'description' => t('contributors to manifestation'),
      'default_widget'=>'hidden',
      'default_formatter' => 'bibdk_manifestation_contribs_default',
      'no_ui' => TRUE,
    ),

    'bibdk_manifestation_series' => array(
      'label' => t('Related title'),
      'description' => t('related titles of manifestation'),
      'default_widget'=>'hidden',
      'default_formatter' => 'bibdk_manifestation_series_default',
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
 **/
function ting_openformat_field_formatter_info () {
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

    'bibdk_manifestation_type_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_manifestation_type',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),

     'bibdk_manifestation_orig_title_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_manifestation_orig_title',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),

    'bibdk_manifestation_contribs_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_manifestation_contribs',
      ),
      'settings' => array(
        'link_type' => 'none',
      ),
    ),

    'bibdk_manifestation_series_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_manifestation_series',
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
function ting_openformat_field_load ($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
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
 **/
function ting_openformat_field_formatter_view ($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
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
       if( empty($creators) ) {
         return;
       }
       $markup = '';
       foreach( $creators as $key => $val ) {
         if( strlen($markup) > 1 )   {
           $markup .= ',  ';
         }
         $markup .= l($val['display'],'search/work/'.$val['searchCode']);
       }

       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;

       // subjects
     case 'ting_openformat_work_subjects_default':
       // one or more subjects
       $subjects = $entity->getSubjects();
       if( empty($subjects) ) {
         return;
       }
       $markup = '';
       foreach( $subjects as $key => $val ) {
         if( strlen($markup) > 1 )   {
           $markup .= ',  ';
         }
         $markup .= l($val['display'],'search/work/'.$val['searchCode']);
       }

       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;

       // type
     case 'bibdk_manifestation_type_default':
       // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
       $markup = $entity->getType();
       if( !$markup ) {
         return;
       }

       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;

       // original title
     case 'bibdk_manifestation_orig_title_default':
       // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
       $markup = $entity->getOriginalTitle();
       if( !$markup ) {
         return;
       }

       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;

       //contributors
         case 'bibdk_manifestation_contribs_default':
       // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
       $markup = $entity->getContributors();
       if( !$markup ) {
         return;
       }

       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;

       // relatedSeriesTitle
     case 'bibdk_manifestation_series_default':
       // entity is manifestation ( @see ting_openformat.entities.inc::manifestation )
       $series = $entity->getSeriesTitle();

       if( !$series ) {
         return;
       }

       $markup = '';

       foreach($series as $serie ) {
         $markup .= $serie['seriesHeader'];
         foreach($serie['relatedSeries'] as  $key => $val ) {
           $markup .= l($val['display'],'search/work/'.$val['searchCode']);
           $markup .= ', ';
         }
       }
       $element[$delta] = array(
         '#markup' => $markup,
       );
       break;


   }
 }
 return $element;
}

