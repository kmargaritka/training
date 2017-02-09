(function($){

  Drupal.behaviors.training5FileLibTable = {
    attach : function (context, settings) {
      var records = Drupal.settings.training5_file_lib;
      $.each(records, function(){
        var $selector = $('.uid-' + this + ' td');
        console.log($selector);
        $selector.css('background-color', '#FFF8DC');
      });
    }
  };

})(jQuery);
