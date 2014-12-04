<?php
/**
 * @file
 * Template for rendering a full work view
 *
 */
?>

<div class="work"></div>
<div class="work-tabs">
  <?php print drupal_render($fields); ?>
</div>
<div class="work-accordion">
  <dl class="accordion" data-accordion>
    <?php foreach ($manifestations as $key => $group) : ?>
      <?php list($tab, $manifestation, $toggle) = array_values($group); ?>
      <dd class="accordion-navigation">
        <a href="#<?php print $key; ?>">
          <?php print $tab; ?>
        </a>
        <div id="<?php print $key; ?>" class="content">
          <?php print drupal_render($manifestation); ?>
          <div class="manifestation-toggle">
            <?php print drupal_render($toggle); ?>
          </div>
        </div>
      </dd>
    <?php endforeach; ?>
  </dl>
</div>
