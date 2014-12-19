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
?>
<div <?php echo drupal_attributes($theme_attributes); ?>>
    <div class="work-header clearfix" data-work-toggle="<?php print $uid; ?>">

      <div class="work-title">
        <h2><?php print $title; ?></h2>
        <div class="title-meta">
          <h3><?php print $author; ?></h3>
          <span><?php print $part_of; ?></span>
        </div>
      </div>

      <div class="work-types-actions">
        <div class="work-types">
          <?php print drupal_render($types); ?>
        </div>
        <div class="work-actions">
          <?php print drupal_render($actions); ?>
        </div>
      </div>
      <!-- element-types-actions -->
    </div>
    <!-- work-header -->
    <div class="work-body work-hidden">
      <?php print drupal_render($work); ?>
    </div>
    <!-- work-body -->
</div>
