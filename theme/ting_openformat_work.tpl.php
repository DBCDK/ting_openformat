<h2><?php echo $variables['ding_id']; ?></h2>

<?php
print drupal_render($variables['fields']);
print $variables['tabs'];
echo '<div class="ting_openformat_subworks">';
foreach( $variables['subWorks'] as $type => $manifestations ) {
  //$css_id = str_replace(':','-',key($manifestations));
  $css_id = key($manifestations);

  echo '<div id="ting_openformat_subwork_'.$css_id.'" class="ting_openformat_subwork">';
  foreach( $manifestations as $id => $manifestation ) {
    print $manifestation;
  }
  echo '</div>';

}
  echo '</div>';

?>



