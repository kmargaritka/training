<?php

/**
 * @file
 * Implements page callbacks for training5_file_lib.module.
 */

/**
 * Url with current exchange rates.
 */
define('TRAINING2_FORM_NBRB_RATES_XML', 'http://www.nbrb.by/Services/XmlExRates.aspx');

/**
 * Page callback for files.
 */
function training5_file_lib_files() {
  global $user;
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  drupal_add_css(drupal_get_path('module', 'training5_file_lib') . '/css/training5_file_lib.css');
  drupal_add_js(drupal_get_path('module', 'training5_file_lib') . '/js/training5_file_lib.js');

  drupal_add_js(array('uid' => $user->uid), 'setting');
  $link = ctools_modal_text_button(t('Upload file'), 'files/nojs/upload_file', 'click');
  $content['link'] = array(
    '#type' => 'item',
    '#markup' => $link,
  );

  $files = entity_load('file');
  if (!empty($files)) {
    $content['file_table'] = training5_file_lib_table($files);
  }
  else {
    $content['file_table'] = array(
      '#type' => 'item',
      '#markup' => t("Files don't exist."),
    );
  }

  return $content;
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
  exit;
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
function training5_file_lib_table($files) {
  $rows = array();
  $header = array(
    'fid' => array('data' => t('file ID')),
    'uid' => array('data' => t('user ID'), 'class' => 'table_uid'),
    'filename' => array('data' => t('name')),
    'path' => array('data' => t('path')),
    'status' => array('data' => t('status')),
    'link' => array('data' => t('download')),
  );
  foreach ($files as $file) {
    $status = $file->status ? 'permanent' : 'temporary';
    $url = file_create_url($file->uri);
    $link = l(t('Download'), "files/download/$file->fid");

    $rows[] = array(
      'data' => array(
        'fid' => $file->fid,
        'uid' => array(
          'data' => $file->uid,
          'class' => 'table_uid',
        ),
        'filename' => $file->filename,
        'path' => $url,
        'status' => $status,
        'link' => $link,
      ),
      'class' => array('uid-' . $file->uid),
    );
  }
  $table = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $table;
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
 * Page callback for currency/load using batch operation.
 */
function training5_file_lib_batch() {
  $batch = array(
    'title' => t('Load currency'),
    'operations' => array(
      array('training5_file_lib_batch_callback', array()),
    ),
    'finished' => 'training5_file_lib_batch_finished',
  );
  batch_set($batch);
  batch_process('currency/view');
}

/**
 * Operation function of training5_file_lib_batch().
 */
function training5_file_lib_batch_callback() {
  $xml = training5_file_lib_get_xml_data();
  db_delete('training5_file_lib_rates')->execute();
  $rates = array();

  foreach ($xml->Currency as $currency) {
    $rates[] = array(
      'code' => (string) $currency->CharCode,
      'rate' => (string) $currency->Rate,
    );
  }

  $query = db_insert('training5_file_lib_rates')->fields(array('code', 'rate'));
  foreach ($rates as $rate) {
    $query->values($rate);
  }

  $query->execute();
}

/**
 * Finished function of training5_file_lib_batch().
 */
function training5_file_lib_batch_finished($success, $results, $operations) {

  if ($success) {
    $message = t('Successfully loaded!!!');
  }
  else {
    $message = t("Rates don't load.");
  }

  drupal_set_message($message);
}

/**
 * Transformation XML.
 *
 * @return mixed
 *   Return array currency.
 */
function training5_file_lib_get_xml_data() {
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, TRAINING2_FORM_NBRB_RATES_XML);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  $xml_response = curl_exec($ch);

  $xml_data = simplexml_load_string($xml_response);

  if ($xml_data) {
    return $xml_data;
  }
  else {
    watchdog('training5_file_lib', 'Bank\'s server is not available');
    return FALSE;
  }
}

