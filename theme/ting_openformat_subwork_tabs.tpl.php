<?php
foreach( $variables['subWorks'] as $type => $manifestations ) {
  // use first id of manifestations as id for subwork tab
  echo '<div id="'.key($manifestations).'" class="ting_openformat_subwork_tab">';
  echo $type;
  echo '</div>';
}
?>