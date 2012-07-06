<?php

/* \brief
 * class depends heavily on ting-client module.
 * builds requests for opensearch, openscan, openspell, openadhl and useraccessinfomedia webservices
 */

class ting_client_class {
  private static $request_factory;
  private static $ting_client;
  private $enable_cache;

  // @TODO ; construct parameters ? -- objectFormat etc.
  public function __construct() {
    $this->enable_cache = variable_get('search_client_enable_cache',FALSE);
  }

  /**
   * initialize a search; call execute
   * method uses a TingClientSearchRequest as parameter
   **/
  public function do_search($params) {
    // get the searchrequest
    $request = self::request_factory()->getSearchRequest();
    // set parameters NOTICE: searchrequest MUST implement method e.g parameters['format'] => setFormat
    foreach ($params as $key => $value) {
      $setter = 'set' . ucfirst($key);
      if( method_exists( $request,$setter ) ){
        $request->$setter($value);
      }
      else {
        drupal_set_message('TingClientSearchRequest does not implement: '.$setter,'error');
        watchdog('Openformat search','TingClientSearchRequest does not implement %setter called from %file in line %line',array('%setter'=>$setter,'%file'=>__FILE__ ,'%line'=>__LINE__),WATCHDOG_ERROR);
      }
    }
    $result = $this->execute($request);

    if( $result ) {
    // hand cachekey to calling method
      $result->cacheKey = $request->cacheKey();
    }

    return $result;
  }

  private function get_from_cache($cacheKey) {
    $result = cache_get($cacheKey,'cache');
    if( $result ) {
      return $result->data;
    }
    return FALSE;
  }


  /**
   * execute a request
   **/
  private function execute($request) {
    $cache = $this->enable_cache;
    if( $cache && method_exists( $request, 'cacheKey') ) {
      $cached_result = $this->get_from_cache($request->cacheKey() );
    }
    else {
      $cache = FALSE;
    }
    if( !empty($cached_result) && $cache ) {
      return $cached_result;
    }
    try {
      timer_start('search_client');
      $res = self::ting_client()->execute($request);
      timer_stop('search_client');
      if( $cache ) {
        cache_set($request->cacheKey(), $res);
      }
      return $res;
    }
    catch (TingClientException $e) {
      timer_stop('search_client');
      // set message if ting-client throws an exeception
      drupal_set_message( $e->getMessage(). '. ' . self::_set_internal_error_message(),'error');
      watchdog('ting client', 'Error performing request: ' . $e->getMessage() , NULL, WATCHDOG_ERROR, 'http://' . $_SERVER["HTTP_HOST"] . request_uri());
      return FALSE;
    }
  }

  private static function _set_internal_error_message() {
    return t('Please contact site administrator if problem persists');
  }

  /* \brief
   * Initialize TingClient.
   * return TingClient. TingClient takes a logger and an adapter in constructor
   * @see ting-client/lib/TingClient.php
   * @see ting-client/lib/adapter/TingClientRequestAdapter.php
   * @see ting-client/lib/log/TingClientDrupalWatchDogLogger.php
   **/
  private static function ting_client() {
    if (!isset(self::$client)) {
      $logger = (variable_get('ting_enable_logging', FALSE)) ? new TingClientDrupalWatchDogLogger(self::request_factory()) : new TingClientVoidLogger();
      self::$ting_client = new TingClient(new TingClientRequestAdapter(), $logger);
    }
    return self::$ting_client;
  }

  /* \brief
   * initialize requestfactory
   * return TingClientRequestFactory (@see ting-client/lib/request/TingClientRequestFactory.php
   */
  private static function request_factory() {
    if (!isset(self::$request_factory)) {
      $url_variables = array(
        'search' => 'ting_search_url',
        'scan' => 'ting_scan_url',
        'object' => 'ting_search_url',
        'collection' => 'ting_search_url',
        'spell' => 'ting_spell_url',
        'recommendation' => 'ting_recommendation_url',
      );

      // TODO: This should probably be rethought.
      if (module_exists('ting_infomedia') && variable_get('ting_infomedia_url', FALSE)) {
        $url_variables['infomedia'] = 'ting_infomedia_url';
      }

      $urls = array();
      foreach ($url_variables as $name => $setting) {
        $urls[$name] = variable_get($setting, FALSE);
        if (!$urls[$name]) {
          throw new TingClientException('No Ting webservice url defined for ' . $name);
        }
      }
      self::$request_factory = new TingClientRequestFactory($urls);
    }
    return self::$request_factory;
  }


  /**
   * Attempt to quote reserved words in a search query.
   *
   * As proper quoting would require a full CQL parser, we cheat and
   * just work on the part we know is the free text part.
   *
   * Also, we don't mess with uppercase reserved words.
   */
  public static function quote($string) {
    if (preg_match('/^(.*?)(AND \(.*|$)/', $string, $rx)) {
      $keys = $rx[1];
      $new_keys = preg_replace_callback('/(?:(".*?(?<!\\\)")|\b(and|or|not|prox)\b)/i', array('ting_client_class','quote_callback'), $keys);
      $string = preg_replace('/^' . preg_quote($keys). '/', $new_keys, $string);
    }
    return $string;
  }

  /**
   *
   */
  private static function quote_callback($matches) {
    // If $matches[2] is empty, it's because the quote pattern
    // matched. Don't do anything with it.
    if (!empty($matches[2])) {
      // Boolean operator, but not uppercase, quote it.
      if ($matches[2] != drupal_strtoupper($matches[2])) {
        return '"' . $matches[2] . '"';
      }
      // Uppercase boolean operator, return as is.
      return $matches[2];
    }
    // We have a quote. Just return it.
    return $matches[1];
  }
}


