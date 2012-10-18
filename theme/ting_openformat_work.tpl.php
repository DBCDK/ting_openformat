<h2><?php print $variables['ding_id']; ?></h2>

<?php
print drupal_render($variables['fields']);
print $variables['tabs'];
echo '<div class="ting_openformat_subworks">';
foreach( $variables['subWorks'] as $type => $subworks ) {
  $manifestations = $subworks['manifestations'];  
  //$css_id = str_replace(':','-',key($manifestations));
  $css_id = key($manifestations);

  echo '<div id="ting_openformat_subwork_'.$css_id.'" class="ting_openformat_subwork">';
  echo drupal_render($subworks['fields']);
  foreach( $manifestations as $id => $manifestation ) {
    echo '<h3>'.$id.'</h3>';
    print $manifestation;
  }
  echo '</div>';
}
echo '</div>';

?>



