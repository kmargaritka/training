<?php

/**
 * @file
 * Includes page callbacks for training1_menu.module.
 */

/**
 * Page callback for training/menu.
 */
function training1_menu_display() {
  return t('This is the landing page of the Training1_menu module');
}

/**
 * Empty content.
 */
function training1_menu_content_empty() {
  return '';
}

/**
 * Page callback for menu/tabs.
 */
function training1_menu_content_tabs() {
  return t('This is the "tabs" menu entry');
}

/**
 * Page callback for menu/tabs/second, menu/tabs/third, menu/tabs/fourth .
 *
 * @param string $arg
 *   Argument which user chooses from tab-menu.
 *
 * @return string
 *   Return string with $arg value.
 */
function training1_menu_content_num_tabs($arg) {
  return t('This is the @arg tab in the basic tabs.', array(
    '@arg' => $arg,
  ));
}

/**
 * Page callback for menu/arguments/%/%.
 *
 * @param string $arg1
 *   Argument which user enters menu/arguments/%.
 * @param string $arg2
 *   Argument which user enters menu/arguments/%/%.
 *
 * @return string
 *   Return values of arguments which user enters.
 */
function training1_menu_content_arguments($arg1, $arg2) {
  return t('Argument 1 = @arg1<br/>Argument 2 = @arg2', array(
    '@arg1' => $arg1,
    '@arg2' => $arg2,
  ));
}

/**
 * Page callback for empty arguments.
 */
function training1_menu_content_arguments_empty() {
  return t('Arguments are empty');
}

/**
 * Page callback for menu/placeholder/%/display.
 *
 * @param string $arg
 *   Some value which user uses.
 *
 * @return string
 *   Return argument which user uses.
 */
function training1_menu_content_dynamic_arg($arg) {
  return $arg;
}

/**
 * Page callback for menu/default_arg/%.
 *
 * @param string $arg
 *   Input argument.
 *
 * @return string
 *   Return argument which user enters.
 */
function training1_menu_content_default_arg($arg) {
  switch ($arg) {
    case 1:
      $content = 'one';
      break;

    case 2:
      $content = 'two';
      break;

    case 3:
      $content = 'three';
      break;

    case 99:
      $content = 'Almost there';
      break;

    default:
      $content = drupal_not_found();
  }

  return $content;
}

/**
 * Page callback for menu/title.
 */
function training1_menu_dynamic_title() {
  global $user;

  if ($user->uid == 0) {
    return t('Dynamic title: username = anonymous');
  }
  else {
    return t('Dynamic title: username = @userName', array(
      '@userName' => $user->name,
    ));
  }
}

/**
 * Page callback for list of links themes theme/ and theme/list.
 */
function training1_menu_list_links() {
  $links = array(
    'List' => 'list',
    'Table' => 'table',
    'Image' => 'image',
    'Access' => 'access',
  );

  return theme('training1_menu_theme', array(
    'title' => 'Links to themes',
    'links' => $links,
  ));
}

/**
 * Page callback for theme/table.
 */
function training1_menu_table() {
  $title = 'Theme table sample';
  $attributes = array('id' => 'table-test');
  $header = array(
    'header 1',
    array('data' => 'header 2', 'colspan' => 2),
    'header 3',
  );

  $rows = array(
    array(
      'data' => array(111, 222, 333, 444),
      'class' => array('rowClass'),
    ),
    array(
      'data' => array(111, 222, 333, 444),
      'class' => array('rowClass'),
    ),
  );

  return $title . theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => $attributes,
  ));
}

/**
 * Page callback for theme/image with list of image styles.
 */
function training1_menu_image_style_list() {
  $styles = array();
  $image_styles = image_styles();
  $key = array_keys($image_styles);
  $n = count($key);
  for ($i = 0; $i < $n; $i++) {
    $styles[$i] = $image_styles[$key[$i]]['label'];
  }

  $style_list = array();
  for ($i = 0; $i < $n; $i++) {
    $style_list[$i] = $styles[$i] . '<br />';
  }

  $text = implode($style_list);

  return theme('image', array(
    'path' => 'sites/all/modules/custom/training/image/sample.png',
    'attributes' => ['class' => 'simple-image'],
  )) . '<br />' . $text;
}

/**
 * Page callback for theme/access.
 */
function training1_menu_access() {
  return user_access('custom access menu item') ? t('Custom access for rendered content') : t('Custom access inversed for rendered content');
}
