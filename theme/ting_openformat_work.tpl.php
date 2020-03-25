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
 * $recomole: pids, filters etc. for Recomole AJAX call.
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
<div class="work-information <?php echo $uid; ?>_start" id="<?php echo $uid; ?>"
     selenium-id="work-<?php echo $uid; ?>">
  <div class="work-fields clearfix">
    <div class="row">
      <div class="work-description-wrapper show-for-small small-16 columns">
        <?php print drupal_render($fields['ting_openformat_work_abstract']); ?>
        <?php print drupal_render($fields['ting_openformat_work_subjects']); ?>
        <?php print drupal_render($fields['ting_openformat_work_laesekompas_subjects']); ?>
      </div>
      <div class="work-tabs hide-for-small medium-16 large-18 columns">
        <?php print drupal_render($fields); ?>
      </div>
      <div class="work-cover-wrapper small-8 large-6 columns">
        <?php print drupal_render($cover); ?>
      </div>
    </div>
  </div><!-- work-information -->
  <div class="work-accordion">
    <dl class="accordion" data-accordion>
      <?php foreach ($subworks as $key => $group) : ?>
        <dd class="accordion-navigation <?php print $group['active']; ?>">
          <a id="manifestation-toggle-button-<?php print preg_replace('/[^\00-\255]+/u', '', $key); ?>"
             href="#<?php print preg_replace('/[^\00-\255]+/u', '', $key); ?>"
             data-manifestation-toggle="<?php print preg_replace('/[^\00-\255]+/u', '', $key); ?>"
             data-subtype-orderids="<?php print implode(',', $group['subtype_order_ids']); ?>">
            <?php print drupal_render($group['tab']); ?>
          </a>
          <div id="<?php print preg_replace('/[^\00-\255]+/u', '', $key); ?>" class="content <?php print $group['active']; ?>">
            <div class="subwork">
              <?php print drupal_render($group['subwork_actions']); ?>
            </div>
            <div class="manifestations">
              <?php print drupal_render($group['manifestations']); ?>
            </div>
            <?php if (!empty($group['toggle'])) : ?>
              <div class="manifestation-toggle"
                   data-manifestation-toggle="<?php print preg_replace('/[^\00-\255]+/u', '', $key); ?>"
                   data-subtype-orderids="<?php print implode(',', $group['subtype_order_ids']); ?>"
                   data-load-multible>
                <?php print drupal_render($group['toggle']); ?>
              </div>
            <?php endif; ?>
          </div>
        </dd>
      <?php endforeach; ?>
    </dl>
  </div><!-- work-accordion -->

  <div id="<?php print 'slick-recommender-' . $uid; ?>"
       class="js-slick-recommender"
       data-recomole-pids="<?php echo implode(',', $recomole['pids']); ?>"
       data-recomole-limit="<?php echo $recomole['limit']; ?>"
       data-recomole-authorflood="<?php echo $recomole['authorflood']; ?>"
       data-recomole-types="<?php echo implode(',', $recomole['types']); ?>">
  </div>
</div>
