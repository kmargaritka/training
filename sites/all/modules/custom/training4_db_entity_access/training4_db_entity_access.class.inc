<?php

include_once('training4_db_entity_access.interface.inc');

/**
 * Training4TextMessageController extends DrupalDefaultEntityController.
 */
class Training4TextMessageController
  extends DrupalDefaultEntityController
  implements Training4TextMessageControllerInterface {

  /**
   * Create and return a new training4_text_message entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->id = 0;
    $entity->uid = 0;
    $entity->type = rand(1, 100);
    $entity->title = '';
    $entity->body = '';

    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record().
   */
  public function save($entity) {

    global $user;
    db_merge('training4_text_message')
      ->key(array('id' => $entity->id))
      ->fields(array(
        'uid' => $user->uid,
        'type' => $entity->type,
        'title' => $entity->title,
        'body' => $entity->body,
      ))
      ->execute();
  }

}