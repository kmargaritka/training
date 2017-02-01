<?php

/**
 * @file
 * Custom template to theme user-login-block form.
 */
?>

<table>
  <tr>
    <td>
      <?php print drupal_render($form['secret_key']); ?>
    </td>
  </tr>
  <tr>
    <td>
      <?php print drupal_render($form['name']); ?>
    </td>
  </tr>
  <tr>
    <td>
      <?php print drupal_render($form['pass']); ?>
    </td>
  </tr>
</table>

<?php print drupal_render_children($form); ?>
