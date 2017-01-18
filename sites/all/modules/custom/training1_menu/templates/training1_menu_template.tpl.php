<?php

/**
 * @file
 * Template for list of links on pages theme/ and theme/list.
 */
?>

<h2><?php print $title; ?></h2>
<div>
  <ol>
    <?php foreach ($links as $name => $link): ?>
      <?php $link = l($name, $link); ?>
      <li>
        <?php print $link; ?>
      </li>
    <?php endforeach; ?>
  </ol>
</div>
