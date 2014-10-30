<?php
/**
 * @file
 * template for show-more/show-less text fields
 *
 * Available variables:
 *  $trimmed_text: the part of the text that is visible by default
 *  $more_text: the part of the text that can be toggled
 */
?>
<span class='toggle-more'>
<?php echo $trimmed_text; ?>
  <span class='toggle-more-content toggle-show'>...</span>
  <span class='toggle-more-content toggle-hide'>
    <?php echo $more_text; ?>
  </span>
  <a class='toggle-link' href='#show-more'>
    <span class="icon icon-left icon-blue-down">&nbsp;</span>
    <span class='toggle-text toggle-show'><?php echo t('show more', array(), array('context' => 'ting_openformat')); ?></span>
    <span class='toggle-text toggle-hide'><?php echo t('show less', array(), array('context' => 'ting_openformat')); ?></span>
  </a>
</span>
