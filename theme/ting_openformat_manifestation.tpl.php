<article class="manifestation clearfix">
  <div class="manifestation-data medium-16 columns">
    <?php print drupal_render($fields); ?>
  </div>
  <div class="actions medium-8 columns">
    <div class="any-edition-actions">
      <?php //print drupal_render($any_edition_actions); ?>
    </div>
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
