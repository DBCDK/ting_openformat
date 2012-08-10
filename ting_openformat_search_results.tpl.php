<?php
$search_result = drupal_static('ting_search_results');
?>

<?php
echo drupal_render($variables['work']);
echo theme('item_list', array('items' => $variables['manifestations']), NULL, 'ul', array('class' => 'manifestation'));
?>

<hr />


