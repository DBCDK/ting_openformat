<div class="ting_openformat_subwork_tabs">
<?php
foreach( $variables['subWorks'] as $id => $subWork ) {
  echo '<div id="'.$id.'" class="ting_openformat_subwork_tab">';
  echo $subWork->getType();
  echo '</div>';
}
?>
</div>
<div class="break"></div>