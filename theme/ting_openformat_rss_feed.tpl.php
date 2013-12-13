<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<?php echo '<?xml version="1.0" encoding="UTF-8" ?>'; ?> 
<rss version="2.0">
<channel>
 <title><?php print $variables['title'];?></title>
 <description><?php print $variables['description'];?></description>
 <link><?php print $variables['link'];?></link>
 <?php foreach($variables['items'] as $item) : ?>
 <item>
  <title><?php print $item['dc:title'];?></title>
  <?php if(isset($item['dc:description'])):?>
  <description><?php print $item['dc:description'];?></description>
  <?php else:?>
  <description><?php print isset($item['dcterms:abstract']) ? $item['dcterms:abstract'] : '';?></description>
  <?php endif;?>
  <link><?php echo url('work/'.$item['pid'],array('absolute'=>TRUE));?></link>
  <guid><?php print $item['pid'];?></guid>
  <pubDate><?php print $item['date'];?></pubDate>
 </item>
 <?php endforeach; ?>
</channel>
</rss>
