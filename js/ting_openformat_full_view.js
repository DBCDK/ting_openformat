/*
 * @file
 * JavaScript for controlling full view functionality
 *
 * @todo This needs a bit of refactoring /svi
 *
 */

(function tingOpenformatFullView($){

  /**
   * Attach work/manifestation related behaviors ajax loaded content.
   */
  Drupal.behaviors.ting_openformat_full_view = {
    attach: function(context){
      TingOpenformat.addFullViewButtonEvent(context);
    }
  };

  var TingOpenformat = {};

  TingOpenformat.addFullViewButtonEvent = function(context){
    $('.full-view-links a', context).click(function(e){
      e.preventDefault();
      if (!$(this).hasClass('inactive')){
        $('.full-view-links a').toggleClass('inactive');
      }

      if ($(this).attr('id') === 'ting-openformat-full-view-button-expanded'){
        Drupal.settings.ting_openformat.full_view = true;
        if (Drupal.settings.ting_openformat.full_view_all_loaded){
          $('.work').addClass('is-toggled');
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
        $('.work').removeClass('is-toggled');
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
      success: function(){
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

})(jQuery);
