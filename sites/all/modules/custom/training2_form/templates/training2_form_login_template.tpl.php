<?php

/**
 * @file
 * Render an custom user-login_block form.
 */
?>

<table>
  <tr>
    <td>
      <?php print(drupal_render($form['secret_key'])); ?>
    </td>
  </tr>
  <tr>
    <td>
      <?php print(drupal_render($form['name'])); ?>
    </td>
  </tr>
  <tr>
    <td>
      <?php print(drupal_render($form['pass'])); ?>
    </td>
  </tr>
</table>

<?php print(drupal_render_children($form)); ?>
