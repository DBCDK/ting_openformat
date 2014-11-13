<div class="work element-wrapper <?php print $work_type; ?>">

  <div class="element">

    <div class="work-header element-section">

      <div class="element-title">
        <div>
          <h2><?php $title; ?></h2>
          <h3><?php print $author; ?></h3>
          <?php if (!empty($partOf)) : ?>
            <span>I: <?php print $partOf; ?></span>
          <?php endif; ?>
        </div>
      </div>

      <div class="element-types-actions">
        <div class="element-types">
          <?php print $types; ?>
        </div>

        <div class="element-actions">
          <?php print drupal_render($actions); ?>
        </div>
      </div>


      <div class="msg-<?php print $uid; ?> collection-msg clearfix"></div>

      <?php print $togglework; ?>

    </div>

    <!-- element-section (work-header) -->
    <?php if ( isset($work_one) ): ?>

      <div class="work-body work-body-has-cover element-section">
        <div><?php print $work_one; ?></div>
      </div>

    <?php else: ?>

      <div class="work-body work-body-has-cover element-section visuallyhidden">
        <div id="ajax_placeholder_<?php print $uid; ?>"></div>
      </div>

    <?php endif; ?>
    <!-- element-section -->
  </div>
  <!-- element -->
</div>
