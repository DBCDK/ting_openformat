<div class="ting_openformat_subwork_tabs">
<?php
foreach( $variables['subWorks'] as $type => $manifestations ) {
  // use first id of manifestations as id for subwork tab
  // $css_id = str_replace(':','-',key($manifestations)); 
   $css_id = key($manifestations);
  echo '<div id="'.$css_id.'" class="ting_openformat_subwork_tab">';
  echo $type;
  echo '</div>';
}
?>
</div>
<div class="break"></div>