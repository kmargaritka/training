<?php

/**
 * @file
 * Implements page callbacks for training5_file_lib.module.
 */

/**
 * Url with current exchange rates.
 */
define('TRAINING5_FILE_LIB_NBRB_RATES_XML', 'http://www.nbrb.by/Services/XmlExRates.aspx');

/**
 * Page callback for files.
 */
function training5_file_lib_files() {
  global $user;
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  $module_path = drupal_get_path('module', 'training5_file_lib');
  drupal_add_css($module_path . '/css/training5_file_lib.css');

  $query = db_select('file_managed', 'fm')
    ->fields('fm')
    ->condition('fm.uid', $user->uid);
  $user_files_id = $query->execute()->fetchCol();

  drupal_add_js($module_path . '/js/training5_file_lib.js');

  drupal_add_js(array('training5_file_lib' => $user_files_id), 'setting');
  $link = ctools_modal_text_button(t('Upload file'), 'files/nojs/upload_file', 'click');
  $link = theme('training5_file_lib_upload_link', array(
    'link' => $link,
  ));

  $table = training5_file_lib_table();
  $pager = theme('pager', array($table));

  return $link . $table . $pager;
}

/**
 * Page callback for files/%ctools_js/upload_file.
 */
function training5_file_lib_upload_file($js) {
  if (!$js) {
    drupal_get_form('training5_file_add_form');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'ajax' => TRUE,
    'title' => 'Upload file',
  );
  $commands = ctools_modal_form_wrapper('training5_file_lib_upload_form', $form_state);

  if (!empty($form_state['executed'])) {
    $add_link = ctools_modal_text_button(t('Upload file'), 'files/nojs/upload_file', 'click');
    $back_link = l(t('Back to the list of files'), 'files');
    $response = t('File is loaded.') . '<br>' . $add_link . '<br>' . $back_link;
    $commands = array();
    $commands[] = ctools_modal_command_display(t('File is loaded.'), $response);
  }

  print ajax_render($commands);
  drupal_exit();
}

/**
 * Function for create  upload file form.
 */
function training5_file_lib_upload_form($form, $form_state) {
  $form['upload_file'] = array(
    '#type' => 'managed_file',
    '#upload_location' => file_default_scheme() . '://files/training5_file_lib_files',
  );

  return $form;
}

/**
 * Submit handler upload form.
 */
function training5_file_lib_upload_form_submit($form, &$form_state) {
  $file = file_load($form_state['values']['upload_file']);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);

  $form_state['redirect'] = 'files';
}

/**
 * List-table of files for /files.
 */
function training5_file_lib_table() {
  $header = array(
    'fid' => array('data' => t('file ID')),
    'uid' => array('data' => t('user ID'), 'class' => 'table-uid'),
    'filename' => array('data' => t('name')),
    'path' => array('data' => t('path')),
    'status' => array('data' => t('status')),
    'link' => array('data' => t('download')),
  );
  $query = db_select('file_managed', 'fm')
    ->fields('fm')
    ->extend('PagerDefault')
    ->limit(5);
  $files = $query->execute();

  $rows = array();
  foreach ($files as $file) {
    $status = $file->status ? 'permanent' : 'temporary';
    $url = file_create_url($file->uri);
    $link = l(t('Download'), "files/download/$file->fid");

    $rows[] = array(
      'data' => array(
        'fid' => $file->fid,
        'uid' => array(
          'data' => $file->uid,
          'class' => 'table-uid',
        ),
        'filename' => $file->filename,
        'path' => $url,
        'status' => $status,
        'link' => $link,
      ),
      'class' => array('uid-' . $file->fid),
    );
  }

  if (!empty($files)) {
    return theme('table', array(
      'header' => $header,
      'rows' => $rows,
    ));
  }
  else {
    return t("Files don't exist.");
  }
}

/**
 * Page callback for files/download/%file.
 */
function training5_file_lib_download($file) {
  $headers = file_get_content_headers($file);
  $headers['Content-Disposition'] = "attachment; filename=\"$file->filename\"";

  file_transfer($file->uri, $headers);
}

/**
 * Operation function of training5_file_lib_batch().
 */
function training5_file_lib_batch_callback(&$context) {
  if (empty($context['sandbox'])) {
    $xml = training5_file_lib_get_xml_data();
    if ($xml != FALSE) {
      $rates = array();
      $xml_currency_count = count($xml->Currency);

      for ($i = 0; $i < $xml_currency_count; $i++) {
        $currencies[] = $xml->Currency[$i];
      }

      foreach ($currencies as $currency) {
        $rates[] = array(
          'code' => (string) $currency->CharCode,
          'rate' => (string) $currency->Rate,
        );
      }

      db_delete('training5_file_lib_rates')->execute();

      $context['sandbox'] = array();
      $context['sandbox']['rates'] = $rates;
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['max'] = $xml_currency_count;
    }

  }

  $limit = 5;

  $result = db_insert('training5_file_lib_rates')
    ->fields(array('code', 'rate'));

  $rates_slice = array_slice($context['sandbox']['rates'], $context['sandbox']['progress'], $limit);
  foreach ($rates_slice as $key => $rate) {
    $result->values($rate);
  }

  $result->execute();

  $context['sandbox']['progress'] += $limit;
  $context['finished'] = ($context['sandbox']['progress'] / $context['sandbox']['max']);
}

/**
 * Finished function of training5_file_lib_batch().
 */
function training5_file_lib_batch_finished($success, $results, $operations) {

  if ($success) {
    $message = t('Successfully loaded');
  }
  else {
    $message = t('Error.');
  }

  drupal_set_message($message);
}

/**
 * Transformation XML.
 *
 * @return array
 *   Return array currency.
 */
function training5_file_lib_get_xml_data() {
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, TRAINING5_FILE_LIB_NBRB_RATES_XML);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  $xml_response = curl_exec($ch);

  if ($xml_data = simplexml_load_string($xml_response)) {
    return $xml_data;
  }
  else {
    watchdog('training5_file_lib', 'Bank\'s server is not available');
    return array();
  }
}
