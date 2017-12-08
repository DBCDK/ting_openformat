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
  Drupal.behaviors.ting_openformat = {
    attach: function(context){
      loadManifestationsEventListener(context);
      toggleWorkEventListener(context);
      toggleManifestationsEventListener(context);
      toggleMoreEventListener(context);
    }
  }

  /**
   * Add eventlistener for loading manifestations
   */
  function loadManifestationsEventListener(context){
    $('[data-manifestation-toggle]', context).one('click', function(e){
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
  function toggleManifestationsEventListener(context) {
    $('[data-load-multible]', context).click(function(e) {
      $(this).siblings('.manifestations').toggleClass('is-toggled');
    });
  }

  /**
   * Toggle link for showing more text for a field
   */
  function toggleMoreEventListener(context){
    $('[data-toggle-link] .toggle-link', context).click(function(e){
      e.preventDefault();
      $(this).parents('[data-toggle-link]').toggleClass('is-toggled');
    });
  }

  /**
   * Toggle work
   */
  function toggleWorkEventListener(context){
    // Eventhandler to expand work on enter
    $('[data-work-toggle]', context).keydown(function(e) {
      if((e.keyCode || e.which) == 13) {
        $(this).click();
      }
    });

    $('[data-work-toggle]', context).click(function(e){
      e.preventDefault();
      var id = '#' + $(this).attr('data-work-toggle');
      $(id).toggleClass('is-toggled');
      // This loads work information with ajax.
      $(id).find('[data-work-load]').trigger('click');
    });
  }
})(jQuery);
