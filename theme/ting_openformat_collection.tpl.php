<?php
/**
 * @file
 * theme implementation for brief display of a collection
 *
 * Variables:
 * $theme_attributes: array of attributes for the wrapper div
 * $title: Title of the collection
 * $author: Author of the collection
 * $part_of: (optional) If collection is part of a series
 * $types: List of type icons
 * $actions: fields attached to the BibdkCollection object
 * $work: If in full view mode it contains a work else an ajax wrapper
 *
 */
kpr($variables);
?>

<div <?php echo drupal_attributes($theme_attributes); ?>>

  <div class="element">

    <div class="work-header element-section">

      <div class="element-title">
        <h2><?php print $title; ?></h2>

        <h3><?php print $author; ?></h3>
        <span><?php print $part_of; ?></span>

      </div>

      <div class="element-types-actions">
        <div class="element-types">
          <?php print $types; ?>
        </div>

        <div class="element-actions">
          <?php print drupal_render($actions); ?>
        </div>
      </div>
      <!-- element-types-actions -->

      <div class="toggle-work clearfix">
        <a href="#work_<?php print $uid; ?>" class="works-control work-toggle-element id="selid-<?php print $uid; ?>">
          <span class="icon icon-left icon-blue-down">&nbsp;</span>
          <span class="toggle-text"><?php print t('More info'); ?></span>
          <span class="toggle-text hidden"><?php print t('Less info'); ?></span>
        </a>
      </div>
    </div><!-- work-header-->
    <div class="work-body work-body-has-cover element-section">
      <?php drupal_render($work); ?>
    </div>
    <!-- work-body -->

  </div>
</div>
