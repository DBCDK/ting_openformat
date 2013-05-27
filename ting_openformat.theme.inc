<?php

/**
 * @file theme.inc load theme hooks
 **/

/**
 * Implements hook_theme().
 */
function ting_openformat_theme() {
  $path = drupal_get_path('module', 'ting_openformat') . '/theme';
  return array(
    'ting_openformat_search_results' => array(
      'path' => $path,
      'variables' => array('content'=>array(),'work'=>array(), 'manifestations'=>array()),
      //'file'      => 'ting_openformat.search_pages.inc',
      'template'  => 'ting_openformat_search_results',
      'render element' => 'elements',
    ),
    'ting_openformat_manifestation' => array(
      'path' => $path,
      'variables' => array('fields'=> array(), 'view_mode' => 'full', 'id'=>0,),
      'template' => 'ting_openformat_manifestation',
      'render elements' => 'elements',
    ),

    'ting_openformat_work' => array(
      'path' => $path,
      'variables' => array('fields' => array(),'cover' => '', 'work_tabs' => '', 'subWorks'=>array(),'ding_id' => 0,),
      'template' => 'ting_openformat_work',
      'render elements' => 'elements',
    ),

    'ting_openformat_work_info' => array(
      'path' => $path,
      'variables' => array('info' => array()),
      'template' => 'ting_openformat_work_info',
      'render elements' => 'elements',
    ),

    'ting_openformat_collection' => array(
      'path' => $path,
      'variables' => array('title' => '','author'=> '','ids' => '', 'show_info' => ''),
      'template' => 'ting_openformat_collection',
      'render elements' => 'elements',
    ),

    'ting_openformat_collection_actions' => array(
      'path' => $path,
      'variables' => array('types' => array()),
      'template' => 'ting_openformat_collection_actions',
      'render elements' => 'elements',
    ),

    'ting_openformat_subwork' => array(
      'path' => $path,
      'variables' => array('manifestations' => array(),'id'=>0),
      'template' => 'ting_openformat_subwork',
      'render elements' => 'elements',
    ),

    'ting_openformat_subwork_tabs' => array(
      'path' => $path,
      'variables' => array('subWorks' => array()),
      'template' => 'ting_openformat_subwork_tabs',
      'render elements' => 'elements',
    ),
    'ting_openformat_single_work' => array(
      'path' => $path,
      'variables' => array('title' => '','author'=> '','ids' => '', 'work' => '', 'uid' => ''),
      'template' => 'ting_openformat_single_work',
      'render elements' => 'elements',
    ),

    'ting_openformat_mini_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),
    'ting_openformat_pager' => array(
      'variables' => array('tags' => array(), 'element' => 0, 'parameters' => array(), 'quantity' => 9),
    ),

    'ting_openformat_type_order_form' => array(
      'render element' => 'form',
      'file' => 'ting_openformat.admin.inc',
    ),

    'ting_openformat_type_order_element' => array(
      'render element' => 'element',
      'file' => 'ting_openformat.admin.inc',
    ),

    'ting_openformat_more_info' => array(
      'path' => $path,
      'variables' => array('showinfoform' => ''),
      'template' => 'ting_openformat_more_info',
      'render elements' => 'elements',
    ),
  );
}


/**
 * Theme a pager
 */
function theme_ting_openformat_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  $hide_list = isset($variables['hide_list']) ? $variables['hide_list'] : FALSE;
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('< previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));

  if (empty($li_previous)) {
    $li_previous = "&nbsp;";
  }

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('<< first')), 'element' => $element, 'parameters' => $parameters));

  if (empty($li_first)) {
    $li_first = "&nbsp;";
  }

  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next >')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  if (empty($li_next)) {
    $li_next = "&nbsp;";
  }

  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last >>')), 'element' => $element, 'parameters' => $parameters));

  if (empty($li_last)) {
    $li_last = "&nbsp;";
  }

  if ($pager_total[$element] > 1) {
    if ($pager_current > 2) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }

    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous,
    );

    // When there is more than one page, create the pager list.
    if (!$hide_list && $i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '>>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '<<',
        );
      }
    }
    else {
      $items[] = array(
        'class' => array('pager-current'),
        'data' => $pager_current,
      );
    }

    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );

    if ($pager_current + 1 < $pager_max && $li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    return theme('item_list', array('items' => $items, 'type' => 'ul', 'attributes' => array('class' => array('pager'))));
  }
}

/**
 * Theme a mini pager with only first, previous and next links.
 */
function theme_ting_openformat_mini_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  if ($pager_total[$element] > 1) {

    // Now generate the actual pager piece.
    for ($i = 1; $i <= $pager_current && $i <= $pager_max; $i++) {
      if ($i < $pager_current) {
        $items[] = array(
          'class' => array('pager-item'),
          'data' => theme('pager_previous', array('text' => t('page ') . $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
        );
      }
      if ($i == $pager_current) {
        $items[] = array(
          'class' => array('pager-current current'),
          'data' => theme('pager_previous', array('text' => t('page ') . $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
        );
      }
      if ($i > $pager_current) {
        $items[] = array(
          'class' => array('pager-item'),
          'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
        );
      }
    }

    $output =  array(
      '#prefix' => '<div class="works-control-wrapper-right">',
      '#suffix' => '</div>',
      'previous' => array(
        '#text' => '',
        '#element' => $element,
        '#interval' => 1,
        '#parameters' => $parameters,
        '#theme' => 'pager_previous',
      ),
      'dropdown_wrapper' => array(
        '#prefix' => '<div class="dropdown-wrapper">',
        '#suffix' => '</div>',
        'current' => array(
          '#text' => t('page') . ' ' . $pager_current,
          '#element' => $element,
          '#parameters' => $parameters,
          '#theme' => 'pager_first',
        ),
        'items' => array(
          '#items' => $items,
          '#theme' => 'item_list',
          '#attributes' => array('class' => array('dropdown-menu','dropdown-leftalign','visuallyhidden')),
        ),
      ),
      'next' => array(
        '#text' => '',
        '#element' => $element,
        '#interval' => 1,
        '#parameters' => $parameters,
        '#theme' => 'pager_next',
      ),
    );

    return $output;

  }
}
