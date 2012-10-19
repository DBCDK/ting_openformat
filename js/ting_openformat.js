/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function ($) {
    Drupal.behaviors.ting_openformat_toggle_search = {
        attach: function(context) {
            $("div.ting_openformat_subwork_tab").click(function() {
		var id = "ting_openformat_subwork_"+this.id;
		var children =$('[id="ting_openformat_subwork_'+this.id+'"]').parent('.ting_openformat_subworks').children('.ting_openformat_subwork');
		$(children).each(function(index){
		    if( this.id != id ) {
			$(this).hide();
		    }
		    else {
			$(this).toggle('5');;
		    }
		});
	    });
	}
    };
})(jQuery);