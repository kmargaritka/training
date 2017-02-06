/**
 * @type {Drupal~behavior}
 *
 * @prop {Drupal~behaviorAttach} attach
 *   Red rows with id = uid-[UserID].
 */
(function($){

  Drupal.behaviors.training5FileLibTable = {
    attach : function (context, settings) {
      var records = settings.training5_file_lib;
      $.each(records, function(){
        var $selector = $('.uid-' + this + ' td');
        console.log($selector);
        $selector.css('background-color', '#FFF8DC');
      });
    }
  };

})(jQuery);
