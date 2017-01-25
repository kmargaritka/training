<?php

/**
 * @file
 * Includes page callbacks for training1_menu.module.
 */

/**
 * Page callback for message message.
 */
function training4_db_entity_access_page() {
  $entities = training4_db_entity_access_load_all();

  if (!empty($entities)) {
    $form['list_table'] = training4_db_entity_access_table();
    return $form;
  }
  else {
    $text = t('Messages are empty.');
    return $text;
  }
}

/**
 * Load all the entities of the type training4_text_message.
 */
function training4_db_entity_access_load_all($ids = FALSE, $conditions = array(), $reset = FALSE) {
  return entity_load('training4_text_message', $ids, $conditions, $reset);
}

/**
 * Create a sortable table of messages.
 */
function training4_db_entity_access_table() {

  $header = array(
    'id' => array('data' => t('ID'), 'field' => 't_m.id', 'sort' => 'asc'),
    'author' => array('data' => t('Author'), 'field' => 't_m.uid'),
    'type'  => array('data' => t('Type'), 'field' => 't_m.type'),
    'title' => array('data' => t('Title'), 'field' => 't_m.title'),
    'body' => array('data' => t('Body'), 'field' => 't_m.body'),
    t('Actions'),
  );

  $query = db_select('training4_text_message', 't_m')
    ->extend('TableSort')
    ->extend('PagerDefault')->limit(5)
    ->fields('t_m')
    ->orderByHeader($header);
  $entities = $query->execute();

  $rows = array();
  foreach ($entities as $entity) {
    $user = user_load($entity->uid);
    $rows[] = array(
      'data' => array(
        'id' => $entity->id,
        'author' => $user->name,
        'type' => $entity->type,
        'title' => $entity->title,
        'body' => $entity->body,
        'actions' => l(t('Edit'), 'message/' . $entity->id),
      ),
    );
  }

  $table[] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  $table[] = array(
    '#theme' => 'pager',
  );

  return $table;
}

/**
 * Page callback for message/add.
 */
function training4_db_entity_access_message_add() {
  $entity = entity_get_controller('training4_text_message')->create();

  return drupal_get_form('training4_db_entity_access_form', $entity);
}

/**
 * Page callback for title message/%.
 */
function training4_db_entity_access_title($id) {
  $entity = training4_db_entity_access_message_load($id);
  return t('@title', array('@title' => $entity->title));
}

/**
 * Page callback for message/%.
 */
function training4_db_entity_access_view($id) {
  $entity = training4_db_entity_access_message_load($id);
  $content = array(
    'body' => array(
      '#type' => 'item',
      '#markup' => $entity->body,
    ),
  );

  return $content;
}

/**
 * Load one entity of the type training4_text_message.
 */
function training4_db_entity_access_message_load($id, $reset = FALSE) {

  $ids = (isset($id) ? array($id) : array());
  $entity = training4_db_entity_access_load_all($ids, array(), $reset);

  return $entity ? reset($entity) : FALSE;
}

