<?php

/**
 * @file
 * Implements views hooks.
 */

/**
 * Implements hook_views_data().
 */
function training5_file_lib_views_data() {
  $data['training5_file_lib_rates']['table']['group'] = t('Rates table');
  $data['training5_file_lib_rates']['table']['base'] = array(
    'field' => 'id',
    'title' => t('training5_file_lib Rates table'),
    'help' => t('Contains exchange rates.'),
  );
  $data['training5_file_lib_rates']['table']['join'] = array(
    'training5_file_lib_rates' => array(
      'left_field' => 'id',
      'field' => 'id',
    ),
  );
  $data['training5_file_lib_rates']['id'] = array(
    'title' => t('id'),
    'help' => t('Id of records in table.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'relationship' => array(
      'base' => 'training5_file_lib_rates',
      'base field' => 'id',
      'handler' => 'views_handler_relationship.',
      'label' => t('Default label for the relationship.'),
      'title' => t('Title shown when adding the relationship.'),
      'help' => t('More information on this relationship.'),
    ),
  );
  $data['training5_file_lib_rates']['code'] = array(
    'title' => t('Code'),
    'help' => t('Currency code'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['training5_file_lib_rates']['rate'] = array(
    'title' => t('Rate'),
    'help' => t('Currency rate'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
