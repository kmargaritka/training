/**
 * training6_i18n behavior to table.
 *
 * @type {Drupal~behavior}
 *
 * @prop {Drupal~behaviorAttach} attach
 */
;(function($){
  Drupal.behaviors.training6i18nDate = {
    attach : function (context_date) {
      console.log(Drupal.t(Drupal.settings.registration_date));
      console.log(Drupal.t(Drupal.settings.days_till_new_year));
    }
  };
  Drupal.behaviors.training6i18nTextarea = {
    attach : function (context_textarea) {
      $('#button').click(function (e) {
        var textarea = $('#textarea')[0];
        textarea.value = Drupal.checkPlain(textarea.value);
      });
    }
  };
})(jQuery);
