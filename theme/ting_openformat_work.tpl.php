<?php
/**
 * @file
 * Template for rendering a full work view
 *
 * Variables
 * $id: ID for a work
 * $fields: Fields for a work; contains the work tabs
 * $cover: Cover for a work
 * $subworks: Information about manifestations in work, grouped by type
 *  @see information about manifestation variables
 *
 * Manifestation variables
 * $tab: Type tab information
 * $manifestation: Contains manifestation view or container if manifestation is
 *  not loaded
 * $toggle: If a work contains more than 1 manifestation a toggle button is
 *  provided
 * $subwork_actions: actions related to a manifestation type (subwork)
 *
 */
?>
<div class="work-information" id="<?php echo $id; ?>"
     selenium-id="work-<?php echo $id; ?>">
  <div class="work-fields clearfix">
    <div class="row">
      <div class="show-for-small small-16 columns">
        <?php print drupal_render($fields['ting_openformat_work_abstract']); ?>
        <?php print drupal_render($fields['ting_openformat_work_subjects']); ?>
      </div>
      <div class="work-tabs hide-for-small medium-16 large-18 columns">
        <?php print drupal_render($fields); ?>
      </div>
      <div class="work-cover-wrapper small-8 large-6 columns">
        <?php print $cover; ?>
      </div>
    </div>
  </div><!-- work-information -->
  <div class="work-accordion">
    <dl class="accordion" data-accordion>
      <?php foreach ($subworks as $key => $group) : ?>
        <?php list($tab, $manifestation, $toggle, $subwork_actions) = array_values($group); ?>
        <dd class="accordion-navigation">
          <a href="#<?php print $key; ?>" data-manifestation-toggle="<?php print $key; ?>">
            <?php print drupal_render($tab); ?>
          </a>
          <div id="<?php print $key; ?>" class="content">
            <div class="subwork">
              <?php print drupal_render($subwork_actions); ?>
            </div>
            <div class="manifestations">
              <?php print drupal_render($manifestation); ?>
            </div>
            <?php if (!empty($toggle)) : ?>
              <div class="manifestation-toggle"
                   data-manifestation-toggle="<?php print $key; ?>" data-load-multible>
                <?php print drupal_render($toggle); ?>
              </div>
            <?php endif; ?>
          </div>
        </dd>
      <?php endforeach; ?>
    </dl>
  </div><!-- work-accordion -->
</div>
