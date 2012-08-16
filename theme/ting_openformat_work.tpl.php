<h2><?php echo $variables['ding_id']; ?></h2>

<?php
print drupal_render($variables['fields']);
print $variables['tabs'];
foreach( $variables['subWorks'] as $type => $manifestations ) {
  echo '<div class="ting_openformat_work">';
  foreach( $manifestations as $id => $manifestation ) {
    echo '<div style="background-color:#CCCCCC">';
    print $manifestation;
    echo '</div>';
  }
  echo '</div>';
}
?>


