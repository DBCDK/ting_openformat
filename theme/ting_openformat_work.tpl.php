<?php
/**
 * @file
 * Template for rendering a full work view
 *
 */
?>

<div class="work-information" id="<?php echo $id; ?>" selenium-id="work-<?php echo $id; ?>">
<div class="work-fields clearfix row">

  <div class="show-for-small small-16 columns">
    <?php print drupal_render($fields['ting_openformat_work_abstract']); ?>
    <?php print drupal_render($fields['ting_openformat_work_subjects']); ?>
  </div>
  <div class="work-tabs hide-for-small medium-16 large-18 columns">
    <?php print drupal_render($fields); ?>
  </div>
  <div class="work-cover-wrapper small-8 large-6 columns"><?php print $cover; ?></div>
</div>
<div class="work-accordion">
  <dl class="accordion" data-accordion>
    <?php foreach($manifestations as $key => $group) : ?>
      <?php list($tab, $manifestation, $toggle, $subwork_actions) = array_values($group); ?>
      <dd class="accordion-navigation">
        <a href="#<?php print $key; ?>">
          <?php print drupal_render($tab); ?>
        </a>
        <div id="<?php print $key; ?>" class="content">
          <div class="subwork">
            <?php print drupal_render($subwork_actions);?>
          </div>
          <div class="manifestations">
            <?php print drupal_render($manifestation); ?>
          </div>
          <?php if(!empty($toggle)) : ?>
          <div class="manifestation-toggle" data-manifestation-toggle="<?php print $key; ?>">
            <?php print drupal_render($toggle); ?>
          </div>
        <?php endif; ?>
        </div>
      </dd>
    <?php endforeach; ?>
  </dl>
</div>
