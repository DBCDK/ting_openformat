/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function($){

  if (typeof(Drupal.ajax) != 'undefined'){

    /**
     * Custom drupal ajax command
     * Replace response data and attach behavours. Is used for loading work information
     */
    Drupal.ajax.prototype.commands.add_manifestations = function(ajax, response, status){
      $(response.selector).replaceWith(response.data);
      var settings = response.settings || ajax.settings || Drupal.settings;
      //Drupal.attachBehaviors(response.data, settings);
    }
  }

  /**
   * Attach work/manifestation related behaviors ajax loaded content.
   */
  Drupal.behaviors.ting_openformat = {
    attach: function(context){
      console.log(context);
      TingOpenformat.loadManifestationsWithAjax(context);
      TingOpenformat.addFullViewButtonEvent(context);
      TingOpenformat.toggleMore(context);
      TingOpenformat.toggleWorkEventListener(context);
      TingOpenformat.toggleManifestationsEventListener(context);
      $
    }
  };

  var TingOpenformat = {};

  TingOpenformat.loadManifestationsWithAjax = function(context){

    $('[data-manifestation-toggle]', context).once().click(function(e){
      var id = $(this).attr('data-manifestation-toggle');
      var manifestation_ids = new Array();
      $('#' + id).find("[data-id]").each(function(i){
        manifestation_ids.push($(this).attr('data-id'));
        //$(this).html('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      });

      TingOpenformat.addAjaxToElement($(this), manifestation_ids);

    });

    // TODO  clean up
    $('.accordion-navigation > a', context).one('click', function(e){

      var wrapper_id = $(this).attr('href');
      // We load the first manifestation only if it has not been loaded before.
      if ($(wrapper_id + ' .manifestation').length == 0){
        var manifestation_id = $(wrapper_id).find(".manifestation-container").first()
          .attr('data-id');
        var manifestation_ids = new Array(manifestation_id);
        TingOpenformat.addAjaxToElement($(wrapper_id), manifestation_ids);
      }
    });
  };

  TingOpenformat.addAjaxToElement = function(element, manifestation_ids, event){
    if (manifestation_ids.length == 0){
      return false;
    }

    var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ting_openformat/ajax/manifestations/' + JSON.stringify(manifestation_ids);
    var element_settings = {};
    element_settings.url = url;
    element_settings.event = (typeof event != 'undefined') ? event : 'load_manifestations';
    element_settings.progress = { type: 'throbber' };

    var id = element.attr('id');
    Drupal.ajax[id] = new Drupal.ajax(id, element, element_settings);
    element.trigger('load_manifestations');
    element.unbind('load_manifestations');

  };

  TingOpenformat.addFullViewButtonEvent = function(context){
    $('.full-view-links a', context).click(function(e){
      e.preventDefault();
      if (!$(this).hasClass('inactive')){
        $('.full-view-links a').toggleClass('inactive');
      }

      if ($(this).attr('id') === 'ting-openformat-full-view-button-expanded'){
        Drupal.settings.ting_openformat.full_view = true;
        if (Drupal.settings.ting_openformat.full_view_all_loaded){
          $('.work').toggleClass('is-toggled');
          TingOpenformat.setFullViewPref('1');
        }
        else if (!Drupal.settings.ting_openformat.isLoadingFullView){
          Drupal.settings.ting_openformat.isLoadingFullView = true;

          $(this).toggleClass('ajax-progress');
          $(this).append('<span class="throbber">&nbsp;</span>');

          var search = window.location.search.replace('&full_view=1', '');
          search = search.replace('&full_view=0', '');

          var location = window.location.pathname + search;
          TingOpenformat.setFullViewPref('1', location);
        }
      }
      else {
        Drupal.settings.ting_openformat.full_view = false;
        $('.work').toggleClass('is-toggled');
        TingOpenformat.setFullViewPref('0');
      }
    });
  };

  TingOpenformat.setFullViewPref = function(pref, onSuccess){
    $.ajax({
      type: "POST",
      url: Drupal.settings.ting_openformat.ajax_callback,
      data: {full_view: pref},
      timeout: 30000,
      success: function(msg){
        if (onSuccess){
          window.location = onSuccess;
        }
      },
      complete: function(object, status){
        if (status == 'timeout' && pref == '1'){
          var full_view = (window.location.search.length == 0) ? '?full_view=1' : '&full_view=1';
          window.location = onSuccess + full_view;
        }
      }
    });
  };

  /**
   * Toggle view of multiple editions of a manifestations
   */
  TingOpenformat.toggleManifestationsEventListener = function (context) {
    $('[data-manifestation-toggle]', context).click(function(e) {
      var wrapper_id = $(this).attr('data-manifestation-toggle');
      $('#' + wrapper_id + ' .manifestations').toggleClass('is-toggled');
    });
  }

  /**
   * Toggle link for showing more text for a field
   */
  TingOpenformat.toggleMore = function(context){
    $('[data-toggle-link]', context).click(function(e){
      e.preventDefault();
      $(this).toggleClass('is-toggled');
    });
  }

  /**
   * Toggle work
   */
  TingOpenformat.toggleWorkEventListener = function(context){
    $('[data-work-toggle]', context).click(function(e){
      e.preventDefault();
      var id = '#' + $(this).attr('data-work-toggle');
      $(id).toggleClass('is-toggled');
      // This loads work information with ajax.
      $(id).find('[data-work-load]').trigger('click');
    });
  }
})
  (jQuery);
