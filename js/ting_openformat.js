/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function tingOpenformat($){

  if (typeof(Drupal.ajax) != 'undefined'){

    /**
     * Custom drupal ajax command
     * Replace response data and attach behavours. Is used for loading work information
     */
    Drupal.ajax.prototype.commands.add_manifestations = function(ajax, response, status){
      var $articles = $(response.data);
      $(response.selector).replaceWith($articles);
      var settings = response.settings || ajax.settings || Drupal.settings;
      Drupal.attachBehaviors($articles, settings);
    }
  }

  /**
   * Attach work/manifestation related behaviors ajax loaded content.
   */

  /**
   * Toggle work
   */
  Drupal.behaviors.ting_openformat_toggle_work = {
    attach: function(context) {
      $('[data-work-toggle]', context).once('data-work-toggle').each(function(index, element) {
        toggleWorkEventListener($(this));
      });
    }
  };
  
  function toggleWorkEventListener(element){
    // Eventhandler to expand work on enter
    element.on( "keydown", function(e) {
      if ((e.keyCode || e.which) == 13) {
        element.click();
      }
    });
    element.on( "click", function(e) {
      e.preventDefault();
      var id = '#' + element.attr('data-work-toggle');
      $(id).toggleClass('is-toggled');
      // This loads work information with ajax.
      $(id).find('[data-work-load]').trigger('click');
    });
  }
  
  /**
   * Add eventlistener for loading manifestations
   */
  Drupal.behaviors.ting_openformat_load_manifestations = {
    attach: function(context) {
      $('[data-manifestation-toggle]', context).once('data-manifestation-toggle').each(function(index, element) {
        loadManifestationsEventListener($(this));
      });
    }
  };
  
  function loadManifestationsEventListener(element){
    element.one('click', function(e){
      var wrapper_id = '#' + this.getAttribute('data-manifestation-toggle');
      var manifestation_ids = getManifestationIds(wrapper_id, this.hasAttribute('data-load-multible'));
      var subtype_order_ids = this.getAttribute('data-subtype-orderids').split(',');
      loadManifestationsWithAjax($(wrapper_id), manifestation_ids, subtype_order_ids);
    });
  }

  /**
   * Get Ids for manifestations to be loaded with ajax
   */
  function getManifestationIds(wrapper_id, load_multible) {
    var manifestation_ids = new Array();
    if (load_multible) {
      $(wrapper_id + " .manifestation-container").each(function(i, element){
        manifestation_ids.push(element.getAttribute('data-id'));
      });
    }
    else if (!$(wrapper_id + ' .manifestation').length) {
      var manifestation_id = $(wrapper_id + " .manifestation-container").attr('data-id');
      manifestation_ids.push(manifestation_id);
    }
    return manifestation_ids;
  }

  /**
   * Get manifestations via ajax
   *
   * this method uses Drupals way of doing ajax, by binding a custom eventtype,
   * trigger the event and unbinding
   *
   * @todo consider rewriting this to use standard jQuery ajax, for better
   * readability
   */
  function loadManifestationsWithAjax(element, manifestation_ids, subtype_order_ids){
    if (manifestation_ids.length == 0 || subtype_order_ids.length == 0){
      return false;
    }

    var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ting_openformat/ajax/manifestations/' + JSON.stringify(manifestation_ids) + '/' + JSON.stringify(subtype_order_ids);
    var element_settings = {
      url: url,
      event: 'load_manifestations',
      progress: {
        type: 'throbber'
      }
    };
    var id = element.attr('id');
    Drupal.ajax[id] = new Drupal.ajax(id, element, element_settings);
    element.trigger('load_manifestations');
    element.unbind('load_manifestations');

  };

  /**
   * Toggle view of multiple editions of a manifestations
   */
  Drupal.behaviors.ting_openformat_toggle_manifestations = {
    attach: function(context) {
      $('[data-load-multible]', context).once('data-load-multible').each(function(index, element) {
        toggleManifestationsEventListener($(this));
      });
    }
  };
  
  function toggleManifestationsEventListener(element) {
    element.on( "click", function(e) {
      $(this).siblings('.manifestations').toggleClass('is-toggled');
    });
  }

  /**
   * Toggle link for showing more text for a field
   */
  Drupal.behaviors.ting_openformat_toggle_nore = {
    attach: function(context) {
      $('[data-toggle-link] .toggle-link', context).once('data-toggle-link').each(function(index, element) {
        toggleMoreEventListener($(this));
      });
    }
  };
  
  function toggleMoreEventListener(element){
    element.click(function(e){
      e.preventDefault();
      element.parents('[data-toggle-link]').toggleClass('is-toggled');
    });
  }

})(jQuery);
