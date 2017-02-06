<?php

/**
 * @file
 * Implements page callbacks for training6_i18n.module.
 */

/**
 * Page callback for /i18n.
 */
function training6_i18n_page_callback() {
  return format_plural(rand(0, 50), '1 task', '@count tasks');
}

/**
 * Page callback for /registration_date.
 */
function training6_i18n_registration_date() {
  global $user;
  $registration_date = format_date($user->created, 'custom', 'd F Y', $user->timezone);

  $new_year = mktime(0, 0, 0, 1, 1, (date("Y") + 1));
  $time_till_new_year = getdate($new_year - REQUEST_TIME);
  $days_till_new_year = $time_till_new_year['yday'];

  $header = array(
    'action' => array('data' => t('Action')),
    'date' => array('data' => t('Date')),
  );

  $rows = array(
    'data' => array(
      'action' => t('!user. You signed up:', array('!user' => $user->name)),
      'date' => $registration_date,
    ),
    'new_year' => array(
      'action' => t('Days till New Year:'),
      'date' => $days_till_new_year,
    ),
  );

  $data_to_js = array(
    'registration_date' => $registration_date,
    'days_till_new_year' => $days_till_new_year,
  );

  drupal_add_js(drupal_get_path('module', 'training6_i18n') . '/js/training6_i18n.js');
  drupal_add_js($data_to_js, 'setting');

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
}

/**
 * Page callback for /textarea.
 */
function training6_i18n_textarea_and_button() {
  drupal_add_js(drupal_get_path('module', 'training6_i18n') . '/js/training6_i18n.js');

  $form = array(
    'textarea' => array(
      '#type' => 'textarea',
      '#value' => t('Textarea'),
      '#attributes' => array('id' => 'textarea'),
    ),
    'button' => array(
      '#type' => 'button',
      '#value' => t('Button'),
      '#attributes' => array('id' => 'button'),
    ),
  );

  return $form;
}

