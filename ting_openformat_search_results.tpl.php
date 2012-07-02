<?php
$search_result = drupal_static('ting_search_results');
$work = $variables['results'][0]->work;
$mani = $variables['results'][0]->manifestation;
?>



<?php
if( is_object($mani) ){
  print $mani->type->{'$'};
}
elseif( is_array($mani) ){
  $set = array();
  foreach($mani as $key=>$festation) {
    if( !in_array( $festation->type->{'$'}, $set ) ) {
      print $festation->type->{'$'}.',';
    }
    $set[]=$festation->type->{'$'};
  }
}
?>

<div></div>

<div class="ting_openformat_toggle" style="border:1px solid #CCCCCC">TOGGLE ME
<div class="ting_openformat_search_result_more">
<?php
if( is_object($mani) ){
  if( isset($mani->details->contributors) ) {
    print $mani->details->contributors->{'$'};
  }
}
elseif( is_array($mani) ){
  $set = array();
  foreach($mani as $key=>$festation) {
    if( isset( $festation->details->contributors ) ){
      if( !in_array( $festation->details->contributors->{'$'}, $set ) ) {
	print $festation->details->contributors->{'$'};
      }
      $set[]=$festation->details->contributors->{'$'};
    }
  }
}
?>
</div>
</div>
<hr />


