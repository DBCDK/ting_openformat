<?php
/**
 * @file
 * template for openformat fields
 *
 * Available variables:
 *  $field: foo bar bas
 */
?>
<span class="openformat-field">
  <?php echo drupal_render($element['#openformat_header']); ?>
  <?php echo drupal_render($element['#openformat_field']); ?>
</span>