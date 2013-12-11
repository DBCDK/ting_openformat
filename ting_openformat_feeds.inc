<?php
/** Output header + rss feed and exit
 *
 * @param string $result; xml from the search defining the feed
 * (@see ting_openformat_search_execute)
 */
function ting_openformat_feeds_redirect($result,$query) {
  if (isset($_GET['feed_me'])) {
    if (arg(0) == 'search') {
      $feed = ting_openformat_feed_set_rss_items($result,$query);
      if (!empty($feed)) {
        header('Content-Type: application/rss+xml; charset=utf-8');
        echo $feed;
        exit;
      }
    }
  }
}

/** parse the xml into an array; pass the array for theming
 *
 * @param string $xml
 * @return string; rss feed (@see ting_openformat_rss_feed.tpl.php)
 */
function ting_openformat_feed_set_rss_items($xml,$query) {
  $items = ting_openformat_feed_parse_result($xml);
  $title = $query;
  $description = t('feed_from_bibliotek',array(),array('context'=>'feeds'));
  $url = url(NULL, array('absolute'=>TRUE));
  $link = $url;
  if(empty($items)){
    return NULL;
  }
  return theme('ting_openformat_rss_feed', array('items' => $items, 'title' => $title, 'description' => $description, 'link' => $link));
}

/** Parse the xml
 *
 * @param type $xml
 * @return type 
 */
function ting_openformat_feed_parse_result($xml) {
  $xpath = ting_openformat_feeds_get_xpath($xml);
  if (!is_object($xpath)) {
    watchdog('openformat', 'could not load xml: %xml', array('%xml' => $xml), WATCHDOG_ERROR);
    return array();
  }
  // get objects
  $query = '//os:object';
  $nodelist = $xpath->query($query);
  $items = array();
  foreach ($nodelist as $node) {
    // parse the dkabm:record
    $item = ting_openformmat_feeds_parse_nodes($node->getElementsByTagName('record'));
    
    if(empty($item)){
      continue;
    }
    // get additional fields
    $item['pid'] = $node->getElementsByTagNameNS('http://oss.dbc.dk/ns/opensearch', 'identifier')->item(0)->nodeValue;
    $item['date'] = $node->getElementsByTagNameNS('http://oss.dbc.dk/ns/opensearch', 'creationDate')->item(0)->nodeValue;    
    $items[] = $item;
  }
  return $items;
}

/** Parse the DKABM part of the record
 *
 * @param domNodelist $nodelist
 * @return array [nodeName=>nodeValue] 
 */
function ting_openformmat_feeds_parse_nodes($nodelist) {
  $ret = array();
  foreach ($nodelist as $node) {
    foreach ($node->childNodes as $element) {
      // use htmlspecialchars - especially for encoding the ampersand (&) which
      // fucks up the xml.
      $ret[$element->nodeName] = check_plain($element->nodeValue);
    }
  }
  return $ret;
}

/** Alter search paramters as fit for feed
 *
 * @param array $params; parameters set in ting_openformat_search_execute 
 */
function ting_openformat_feeds_set_params(&$params) {
  // set outputtype to xml
  $params['outputType'] = 'xml';
  // use dkabm
  $params['objectFormat'] = 'dkabm';
  // set collection type
  $params['collectionType'] = 'manifestation';
}

/** Initialize an x-path object for parsing xml.
 *
 * @param string $xml
 * @return \DOMXPath 
 */
function ting_openformat_feeds_get_xpath($xml) {
  $dom = new DOMDocument();
  if (!@$dom->loadXML($xml)) {
    return NULL;
  }
  $xpath = new DOMXPath($dom);
  $xpath->registerNamespace('dkabm', 'http://biblstandard.dk/abm/namespace/dkabm/');
  $xpath->registerNamespace('dc', 'http://purl.org/dc/elements/1.1/');
  $xpath->registerNamespace('os', 'http://oss.dbc.dk/ns/opensearch');
  return $xpath;
}

?>
