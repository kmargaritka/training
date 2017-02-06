(function($){
  Drupal.behaviors.training6i18nDate = {
    attach : function () {
      console.log(Drupal.t(Drupal.settings.registration_date));
      console.log(Drupal.t(Drupal.settings.days_till_new_year));
      $('#button').click(function (e) {
        var textarea = $('#textarea')[0];
        textarea.value = Drupal.checkPlain(textarea.value);
      });
    }
  };
})(jQuery);
