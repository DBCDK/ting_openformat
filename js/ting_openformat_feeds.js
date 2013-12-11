(function($) {
  Drupal.behaviors.ting_openformat_feeds = {
    attach: function(context) {
      var element = $('.feed-icon');
      element.attr('target','_blank');
    }
  };
})(jQuery);



