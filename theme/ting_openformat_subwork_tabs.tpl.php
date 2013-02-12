<div class="ting_openformat_subwork_tabs">
  <?php
  $count = 0;
  foreach ($variables['subWorks'] as $type => $subWork) {
    echo '<div id="' . $subWork['id'] . '" class="ting_openformat_subwork_tab">';
    echo $subWork['type'];
    echo '</div>';
  }
  ?>
</div>
<div class="break"></div>
