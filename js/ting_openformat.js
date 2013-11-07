/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function($) {

  if(typeof(Drupal.ajax) != 'undefined') {
    Drupal.ajax.prototype.commands.add_manifestations = function(ajax, response, status) {
      // We don't know what response.data contains: it might be a string of text
      // without HTML, so don't rely on jQuery correctly iterpreting
      // $(response.data) as new HTML rather than a CSS selector. Also, if
      // response.data contains top-level text nodes, they get lost with either
      // $(response.data) or $('<div></div>').replaceWith(response.data).
      var new_content_wrapped = $('<div></div>').html(response.data);
      var new_content = new_content_wrapped.contents();
      if(new_content.length != 1 || new_content.get(0).nodeType != 1) {
        new_content = new_content_wrapped;
      }

      var elements = $(response.selector);
      $(elements[0]).replaceWith(new_content);

      if(new_content.parents('html').length > 0) {
        // Apply any settings from the returned JSON if available.
        var settings = response.settings || ajax.settings || Drupal.settings;
        Drupal.attachBehaviors(new_content, settings);
      }
    }
  }

  Drupal.behaviors.ting_openformat = {
    attach: function(context) {
      TingOpenformat.activateSubWorkTabs(context);
      TingOpenformat.loadManifestationsWithAjax(context);
      TingOpenformat.loadWorkEvent(context);
      TingOpenformat.addFullViewButtonEvent(context);
    }
  };

  var TingOpenformat = {};

  TingOpenformat.activateSubWorkTabs = function(context) {
    $("div.ting_openformat_subwork_tab", context).click(function() {
      var id = "ting_openformat_subwork_" + this.id;
      var children = $('[id="ting_openformat_subwork_' + this.id + '"]').parent('.ting_openformat_subworks').children('.ting_openformat_subwork');
      $(children).each(function(index) {
        if(this.id != id) {
          $(this).hide();
        }
        else {
          $(this).toggle('5');
        }
      });
    });
  };

  TingOpenformat.loadManifestationsWithAjax = function(context) {

    $('.zebra-toggle a', context).once().click(function(e) {
      var wrapper_id = $(this).attr('href');
      var manifestation_ids = new Array();
      $(wrapper_id).find(".manifestation-container").each(function(i) {
        manifestation_ids.push($(this).attr('data-id'));
        $(this).html('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      });

      TingOpenformat.addAjaxToElement($(this), manifestation_ids);

    });

    $('.tabs-nav-sub a', context).one('click', function(e) {

      var wrapper_id = $(this).attr('href');
      // We load the first manifestation only if it has not been loaded before.
      if($(wrapper_id).find('.manifestation').first().find('.manifestation-container').length > 0) {
        var manifestation_id = $(wrapper_id).find(".manifestation-container").first()
          .html('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>')
          .attr('data-id');

        var manifestation_ids = new Array(manifestation_id);

        TingOpenformat.addAjaxToElement($(this), manifestation_ids);
      }
    });
  };

  TingOpenformat.addAjaxToElement = function(element, manifestation_ids, event) {
    if(manifestation_ids.length == 0) {
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

  TingOpenformat.addFullViewButtonEvent = function(context) {
    $('.full-view-links a', context).click(function(e) {
      e.preventDefault();
      if(!$(this).hasClass('inactive')) {
        $('.full-view-links a').toggleClass('inactive');
      }

      if($(this).attr('id') === 'ting-openformat-full-view-button-expanded') {
        Drupal.settings.ting_openformat.full_view = true;
        if(Drupal.settings.ting_openformat.full_view_all_loaded) {
          $('.work-toggle-element').trigger('show-work');
          TingOpenformat.setFullViewPref('1');
        } else if(!Drupal.settings.ting_openformat.isLoadingFullView) {
          Drupal.settings.ting_openformat.isLoadingFullView = true;

          $(this).toggleClass('ajax-progress');
          $(this).append('<span class="throbber">&nbsp;</span>');

          var full_view = '&full_view=1';

          var search = window.location.search.replace('&full_view=1', '');
          search = search.replace('&full_view=0', '');

          window.location = window.location.pathname + search + full_view;
          return false;
        }
      }
      else {
        Drupal.settings.ting_openformat.full_view = false;
        $('.work-toggle-element').trigger('hide-work');
        TingOpenformat.setFullViewPref('0');
      }
    });
  };

  TingOpenformat.setFullViewPref = function(pref){
    $.ajax({
      type: 'GET',
      url: Drupal.settings.ting_openformat.ajax_callback + pref,
      success: function() {
        return false;
      }
    });
  };

  TingOpenformat.loadWorkEvent = function(context) {
    $('.work-toggle-element', context).bind('show-work', function(e) {
      var id = $(this).attr('href');
      $(id).trigger('click');
    });
  }

})
  (jQuery);