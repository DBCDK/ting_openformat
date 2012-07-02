/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function ($) {
    Drupal.behaviors.ting_openformat_toggle_search = {
        attach: function(context) {
            $("div.ting_openformat_toggle").click(function() {
		$(this).find("div.ting_openformat_search_result_more").toggle();
	    });
	}
    };
})(jQuery);








