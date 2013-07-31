(function($) {
    Drupal.behaviors.load_more = {
        attach: function(context) {
            $('.hest', context).click(function(e){
                e.preventDefault();
                console.log('hest clicked');
            });
        }
    };
})(jQuery);

