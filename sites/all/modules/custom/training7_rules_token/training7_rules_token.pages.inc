<?php

/**
 * @file
 * Implements page callbacks for training7_rules_token.module.
 */

/**
 * Page callback for /lottery.
 */
function training7_rules_token_lottery() {
  global $user;
  $role = user_role_load_by_name('authenticated user');

  if (user_has_role($role->rid)) {
    rules_invoke_event('training7_rules_token_visit_lottery');
    $link = l(t('Try again'), current_path());
    $lottery_message = cache_get($user->uid . '_winner');

    if ($lottery_message) {
      $message = $lottery_message->data . '</br>' . $link;
    }
    else {
      $message = 'You have never won. </br>' . $link;
    }

  }
  else {
    $message = 'You should log in for taking part in lottery.';
  }

  return $message;
}
