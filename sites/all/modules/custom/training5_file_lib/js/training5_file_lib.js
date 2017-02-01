/**
 * training5FileLibTable behavior to table.
 *
 * @type {Drupal~behavior}
 *
 * @prop {Drupal~behaviorAttach} attach
 *   Red rows with id = uid-[UserID].
 */
;(function($){

  Drupal.behaviors.training5FileLibTable = {
    attach : function (context) {
      var rowClass = '.uid-' + Drupal.settings.uid;
      var $rows = $(rowClass);
      $rows = [].slice.call($rows);
      $rows.forEach(function (item, i, arr) {
        item.style.backgroundColor = 'red';
      });
    }
  };

})(jQuery)
