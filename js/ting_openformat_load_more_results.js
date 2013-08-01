(function($) {

  Drupal.ajax.prototype.commands.add_more_results = function(ajax, response, status) {
    var loadMoreLink = $('.pane-ting-openformat-load-more-results #link');
//    TODO mmj clean up console.logs
    console.log('add_more_results');
    console.log(ajax);
    console.log(response);
    console.log(status);

    if(status === 'success') {
      if(Drupal.settings.ting_openformat_load_more_results.start < Drupal.settings.ting_openformat_load_more_results.pages) {
        Drupal.settings.ting_openformat_load_more_results.start++;
        loadMoreLink.show();
      }

      LoadMore.setSettings(loadMoreLink);
      var anchor = $("a[name='"+ response.data.anchor +"']");
      $('html,body').animate({scrollTop: anchor.offset().top}, 'slow');
    }
  };

//=======================================
//  LoadMore functionality
//=======================================

  var LoadMore = {};

  LoadMore.addAjax = function(element) {
    LoadMore.setSettings(element);

    element.click(function(e) {
      e.preventDefault();
      element = $(this);
      element.hide();
      element.trigger('load_more_results');
      element.unbind('load_more_results');
    });
  };

  LoadMore.setSettings = function(element) {
    var key = $('#edit-search-block-form--2').val();

    var element_settings = {};
    element_settings.url = Drupal.settings.basePath + 'ajax/load_more_results' + window.location.search + '&keys=' + key + '&page=' + Drupal.settings.ting_openformat_load_more_results.start;
    element_settings.event = 'load_more_results';
    element_settings.progress = { type: 'throbber'};

    if(Drupal.ajax['load_more_results'] != null) {
      Drupal.ajax['load_more_results'] = null;
    }

    Drupal.ajax['load_more_results'] = new Drupal.ajax('load_more_results', element, element_settings);
  };

//=======================================
//  LoadMore functionality - END
//=======================================

  Drupal.behaviors.ting_openformat_load_more_results = {
    attach: function(context) {
      var element = $('.pane-ting-openformat-load-more-results #link', context);
      LoadMore.addAjax(element);
    }
  };
})(jQuery);

