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
        <?php print $item = '<li><a href=' . $link . '>' . $name . '</a></li>'; ?>
    <?php endforeach; ?>
  </ol>
</div>
