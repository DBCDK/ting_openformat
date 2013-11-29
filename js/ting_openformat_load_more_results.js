(function($) {

  Drupal.ajax.prototype.commands.add_more_results = function(ajax, response, status) {
    Drupal.settings.ting_openformat.load_more_results.more = response.data.more;
    Drupal.settings.ting_openformat.load_more_results.link = response.data.link;
    var loadMoreLink = $('.pane-ting-openformat-load-more #selid-load-more-results');
    if(status === 'success') {
      if(Drupal.settings.ting_openformat.load_more_results.more) {
        loadMoreLink.show();
      }

      LoadMore.setSettings(loadMoreLink);
      Drupal.settings.ting_openformat.load_more_results.anchor = response.data.anchor;
      if(!Drupal.settings.ting_openformat.load_more_results.infiniteLoadingIsActive) {
        var anchor = $("#" + response.data.anchor);
        $('html,body').animate({scrollTop: anchor.offset().top - 30}, 'slow');
      }
    }

    Drupal.settings.ting_openformat.load_more_results.loadingIsActive = false;
    Drupal.settings.ting_openformat.load_more_results.infiniteLoadingIsActive = false;
  };

//=======================================
//  LoadMore functionality
//=======================================

  var LoadMore = {};

  LoadMore.addAjax = function(element) {
    LoadMore.setSettings(element);

    element.click(function(e) {
      e.preventDefault();
      if(Drupal.settings.ting_openformat.load_more_results.more) {
        element = $(this);
        element.hide();
        element.trigger('load_more_results');
        element.unbind('load_more_results');
        Drupal.settings.ting_openformat.load_more_results.loadingIsActive = true;
      }
    });
  };

  LoadMore.setSettings = function(element) {
    var element_settings = {};

    element_settings.url = Drupal.settings.ting_openformat.load_more_results.link;

    element_settings.event = 'load_more_results';
    element_settings.progress = { type: 'throbber'};

    if(Drupal.ajax['load_more_results'] != null) {
      Drupal.ajax['load_more_results'] = null;
    }

    Drupal.ajax['load_more_results'] = new Drupal.ajax('load_more_results', element, element_settings);
  };

 /* LoadMore.initInfiniteScroll = function() {
    $(window).unbind('scroll');

    $(window).scroll(function() {
      var anchor = $('#' + Drupal.settings.ting_openformat.load_more_results.anchor);
      var toScroll = (anchor.offset()) ? anchor.offset().top : $('.pane-ting-openformat-load-more-results').offset().top;
      if($(window).scrollTop() + $(window).height() >= toScroll && Drupal.settings.ting_openformat.load_more_results.more) {
        LoadMore.infiniteLoad();
      }
    });
  };*/

  LoadMore.loadingIsOk = function() {
    return !Drupal.settings.ting_openformat.load_more_results.loadingIsActive;
  };

  LoadMore.infiniteLoad = function() {
    if(LoadMore.loadingIsOk()) {
      var element = $('.pane-ting-openformat-load-more #selid-load-more-results');
      element.hide();
      element.trigger('load_more_results');
      element.unbind('load_more_results');
      Drupal.settings.ting_openformat.load_more_results.infiniteLoadingIsActive = true;
      Drupal.settings.ting_openformat.load_more_results.loadingIsActive = true;
    }
  };

//=======================================
//  LoadMore functionality - END
//=======================================

  Drupal.behaviors.ting_openformat_load_more_results = {
    attach: function(context) {
      var element = $('.pane-ting-openformat-load-more #selid-load-more-results', context);
      LoadMore.addAjax(element);

     // LoadMore.initInfiniteScroll();
      if(Drupal.settings.ting_openformat.load_more_results.firstLoad && Drupal.settings.ting_openformat.load_more_results.more) {
        Drupal.settings.ting_openformat.load_more_results.firstLoad = false;
        LoadMore.infiniteLoad();
      }
    }
  };
})(jQuery);

