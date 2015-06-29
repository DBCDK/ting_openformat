<?php
/**
 * @file
 * theme implementation for manifestation
 *
 * Variables
 * $fields: main information fields for manifestation
 * $actions: Actions for a specific manifestation
 *
 * Additional variables
 * $secondary actions: bibdk_theme divides actions into actions and secondary actions
 */
?>
<article class="manifestation clearfix" property="about" vocab="http://schema.org/" typeof="<?php print drupal_render($typeof); ?>">
  <div class="manifestation-data medium-16 columns">
    <?php print drupal_render($fields); ?>
  </div>
  <div class="actions medium-8 columns">
    <div class="reservation-button">
      <?php print isset($actions['reservation']) ? drupal_render($actions['reservation']) : ''; ?>
    </div>
    <div class="primary-actions hide-for-small">
      <?php print drupal_render($actions); ?>
    </div>
    <div class="secondary-actions hide-for-small">
      <ul>
        <?php print drupal_render($secondary_actions); ?>
      </ul>
    </div>
  </div>
  <!-- .actions -->
</article>
