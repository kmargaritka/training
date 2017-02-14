<?php

/**
 * @file
 * Rule for /lottery page.
 */

/**
 * Implements hook_rules_event_info().
 */
function training7_rules_token_rules_event_info() {
  $items = array(
    'training7_rules_token_visit_lottery' => array(
      'label' => t('User is on lottery page'),
      'group' => t('Training7'),
      'access callback' => TRUE,
    ),
  );
  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function training7_rules_token_rules_condition_info() {
  $items = array(
    'training7_rules_token_result' => array(
      'label' => t('Lottery is won'),
      'group' => t('Training7'),
    ),
  );
  return $items;
}

/**
 * Implements hook_rules_action_info().
 */
function training7_rules_token_rules_action_info() {
  $items = array(
    'training7_rules_token_win_message' => array(
      'label' => t('Display a lottery win message'),
      'group' => t('Training7'),
      'access callback' => TRUE,
    ),
  );
  return $items;
}

/**
 * Callback function for rule condition.
 */
function training7_rules_token_result() {
  $rand = rand(1, 8);
  global $user, $base_url;
  $server = url($base_url . '/xmlrpc.php', array('external' => TRUE));
  $options = array(
    'training7_rules_token_run_lottery.generate' => array($rand),
  );
  $lottery_code = xmlrpc($server, $options);
  if ($lottery_code === FALSE) {
    drupal_set_message(
      t('Error from xmlrpc(): Error: @errno, Message: @message',
        array('@errno' => xmlrpc_errno(), '@message' => xmlrpc_error_msg())),
      'error'
    );
  }

  $lottery_id = cache_get('current_lottery_id');
  $lottery_id = $lottery_id ? $lottery_id->data : 0;
  $data = cache_get('lottery_list');
  $data = $data ? $data->data : array();

  $lottery_id++;
  $data[] = array(
    'lottery_id' => $lottery_id,
    'time' => format_date(REQUEST_TIME, 'custom', 'm/d/Y H:i:s'),
    'user_name' => $user->name,
    'result' => $lottery_code,
  );
  cache_set('lottery_list', $data);
  cache_set('current_lottery_id', $lottery_id);

  return $lottery_code === 'win';
}

/**
 * Callback function for rule action.
 */
function training7_rules_token_win_message() {
  global $user;
  $msg = t("[lottery:user_name], you are winning in lottery! 
    Your winning lottery #[lottery:id] was on [lottery:time].");
  $id = cache_get('current_lottery_id');
  $lottery = (object) array(
    'user_name' => $user->name,
    'id' => $id->data,
    'time' => format_date(REQUEST_TIME, 'long'),
  );
  $needs_data = array('lottery' => $lottery);
  $result = token_replace($msg, $needs_data);

  cache_set($user->uid . '_winner', $result);

  drupal_set_message($result);
}
