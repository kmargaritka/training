<?php

/**
 * @file
 * Implements token hooks for training7_rules_token module.
 */

/**
 * Implements hook_token_info().
 */
function training7_rules_token_token_info() {
  $info['types']['lottery'] = array(
    'name' => t('Lottery'),
    'description' => t('Tokens related to lottery'),
    'needs-data' => 'lottery',
  );
  $info['tokens']['lottery']['id'] = array(
    'name' => t('id'),
    'description' => t('ID of the lottery'),
  );
  $info['tokens']['lottery']['time'] = array(
    'name' => t('time'),
    'description' => t('Date of the lottery'),
  );
  $info['tokens']['lottery']['user_name'] = array(
    'name' => t('user_name'),
    'description' => t('User name'),
    'needs-data' => 'user',
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function training7_rules_token_tokens($type, $tokens, $data = array()) {
  $replacements = array();

  if ($type == 'lottery' && !empty($data['lottery'])) {
    $lottery = $data['lottery'];

    foreach ($tokens as $name => $token) {
      switch ($name) {
        case 'id':
          $replacements[$token] = $lottery->id;
          break;

        case 'time':
          $replacements[$token] = $lottery->time;
          break;

        case 'user_name':
          $replacements[$token] = $lottery->user_name;
          break;
      }
    }

  }

  return $replacements;
}
