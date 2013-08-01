/*
 * @file
 * JavaScript for openformat search
 * toggle search result
 *
 */

(function ($) {

    var TingOpenformat = {}

    Drupal.ajax.prototype.commands.add_manifestations = function (ajax, response, status) {
        console.log(ajax);
        console.log(response);
        console.log(status);

    }

    Drupal.behaviors.ting_openformat = {
        attach: function (context) {

            TingOpenformat.activateSubWorkTabs(context);
            TingOpenformat.loadManifestationsWithAjax(context);
        }
    };

    TingOpenformat.activateSubWorkTabs = function (context) {
        $("div.ting_openformat_subwork_tab", context).click(function () {
            var id = "ting_openformat_subwork_" + this.id;
            var children = $('[id="ting_openformat_subwork_' + this.id + '"]').parent('.ting_openformat_subworks').children('.ting_openformat_subwork');
            $(children).each(function (index) {
                if (this.id != id) {
                    $(this).hide();
                }
                else {
                    $(this).toggle('5');
                }
            });
        });
    }

    TingOpenformat.loadManifestationsWithAjax = function (context) {


        $('.tabs-nav-sub a, .zebra-toggle a', context).once().each(function (e) {
            var wrapper_id = $(this).attr('href');
            var manifestation_ids = new Array();
            $(wrapper_id).find(".manifestation-container").each(function (i) {
                manifestation_ids.push($(this).attr('data-id'));
                $(this).html('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
            });

            var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ting_openformat/ajax/manifestations/' + JSON.stringify(manifestation_ids);
            TingOpenformat.addAjaxToElement($(this), url);

        });


    } // end getManifestations
    TingOpenformat.addAjaxToElement = function (element, url, event) {

        var element_settings = {};
        element_settings.url = url;
        element_settings.event = (typeof event != 'undefined') ? event : 'load_manifestations';
        element_settings.progress = { type: 'throbber' };

        var id = element.attr('id');
        Drupal.ajax[id] = new Drupal.ajax(id, element, element_settings);

        element.click(function (e) {
            e.preventDefault();
            // we make shure the ajax call is only triggered first time
            $(this).trigger('load_manifestations');
            $(this).unbind('load_manifestations');

        });
    }


})(jQuery);
