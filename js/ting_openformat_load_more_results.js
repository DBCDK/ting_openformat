(function($) {

  Drupal.ajax.prototype.commands.add_more_results = function(ajax, response, status) {
    var loadMoreLink = $('.pane-ting-openformat-load-more-results #link');
    console.log(status);
    if(status === 'success') {
      if(Drupal.settings.ting_openformat_load_more_results.start < Drupal.settings.ting_openformat_load_more_results.pages) {
        Drupal.settings.ting_openformat_load_more_results.start++;
        loadMoreLink.show();
      }

      LoadMore.setSettings(loadMoreLink);
      if(!Drupal.settings.ting_openformat_load_more_results.infiniteLoading){
        console.log('hest');
        var anchor = $("#" + response.data.anchor);
        $('html,body').animate({scrollTop: anchor.offset().top - 30}, 'slow');
      }
    } else {

    }
    Drupal.settings.ting_openformat_load_more_results.infiniteLoading = false;
  };

//=======================================
//  LoadMore functionality
//=======================================

  var LoadMore = {};

  LoadMore.addAjax = function(element) {
    LoadMore.setSettings(element);

    element.click(function(e) {
      e.preventDefault();
      if(!Drupal.settings.ting_openformat_load_more_results.loading){
        element = $(this);
        element.hide();
        element.trigger('load_more_results');
        element.unbind('load_more_results');
      }
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

  LoadMore.setInfiniteScroll = function() {
    $(window).unbind('scroll');

    $(window).scroll(function() {
      if($(window).scrollTop() + $(window).height() == $(document).height() && !Drupal.settings.ting_openformat_load_more_results.loading) {
        var element = $('.pane-ting-openformat-load-more-results #link');
        element.hide();
        element.trigger('load_more_results');
        element.unbind('load_more_results');
        Drupal.settings.ting_openformat_load_more_results.infiniteLoading = true;
      }
    });
  };

//=======================================
//  LoadMore functionality - END
//=======================================

  Drupal.behaviors.ting_openformat_load_more_results = {
    attach: function(context) {
      console.log('attach');
      var element = $('.pane-ting-openformat-load-more-results #link', context);
      LoadMore.addAjax(element);

      LoadMore.setInfiniteScroll();
    }
  };
})(jQuery);

