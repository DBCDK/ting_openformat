<div class="toggle-work">
  <a href="#work_<?php print $uid; ?>" class="works-control work-toggle-element <?php ($full_view == TRUE) ? print "toggled" : print ""; ?>" id="selid-<?php print $uid; ?>">
    <span class="icon icon-left icon-blue-down">&nbsp;</span>
    <span class="toggle-text <?php ($full_view == TRUE) ? print "hidden" : print ""; ?>"><?php print t('More info'); ?></span>
    <span class="toggle-text <?php (!$full_view) ? print "hidden" : print "" ?>"><?php print t('Less info'); ?></span>
  </a>
  <?php print $showinfo; ?>
</div>