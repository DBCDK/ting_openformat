<!-- cover -->
<?php print $cover ?>
<!-- cover -->

<div class="wrapper">
  <?php print drupal_render($fields); ?>
  <?php print $work_tabs ?>
    <!-- tabs -->
</div>
<!-- wrapper -->
</div>
<!-- work-share-data -->
<div class="bibdk-tabs bibdk-tabs-heavy">
  <?php print $tabs; ?>
    <!-- tabs-nav -->
    <div class="tabs-sections">
      <?php $count = 0; ?>
      <?php foreach ($subWorks as $type) : ?>
      <?php foreach ($type as $subtype => $manifest) : $count++; ?>
            <div id="<?php print $subtype; ?><?php print $ding_id; ?>"
                 class="subwork tabs-section <?php print ($count != 1) ? "visuallyhidden" : ""  ?>">
                <div class="padded text clearfix">
                    <div class="actions">
                        <div class="primary-actions">
                            <div class="btn-wrapper">
                            </div>
                          <?php print drupal_render($manifest['manifest']['subtype_actions']['cart']); ?>
                        </div>
                    </div>
                  <?php echo drupal_render($manifest['manifest']['subtype_actions']); ?>
                </div>
                <!-- tabs-content -->
                <div class="manifestations zebra-wrapper">
                    <div class="zebra-content">
                      <?php $count_manifestation = 0; ?>
                      <?php foreach ($manifest['manifest']['manifestations'] as $manifestation) : $count_manifestation++; ?>
                        <div class="manifestation zebra <?php print ($count_manifestation > 2) ? "visuallyhidden toggle" : ""  ?>">
                          <?php print $manifestation; ?>
                        </div>
                      <?php endforeach; ?>

                    </div>
                    <!-- end zebra-content -->
                  <?php if (count($manifest['manifest']['manifestations']) > 2) : ?>
                    <div class="zebra-toggle">
                        <a href="#<?php print $subtype; ?><?php print $ding_id; ?>">
                            <span class="icon icon-left icon-blue-down">?</span>
                            <span class="toggle-text"><?php print t("show all (@count)", array('@count' => count($manifest['manifest']['manifestations']))); ?></span>
                            <span class="toggle-text hidden"><?php print t("hide"); ?></span>
                        </a>
                    </div>
                  <?php endif; ?>
                </div>
                <!-- manifestations -->
            </div>
        <?php endforeach; ?>
      <?php endforeach; ?>
        <!-- tabs-section -->
    </div>
    <!-- tabs-sections -->

</div>
<!-- tabs -->
