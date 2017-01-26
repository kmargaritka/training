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
    $content['list_table'] = training4_db_entity_access_table();
  }
  else {
    $content = t('Messages are empty.');
  }

  return $content;
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
    'id' => array('data' => t('ID'), 'field' => 'ttm.id', 'sort' => 'asc'),
    'author' => array('data' => t('Author'), 'field' => 'ttm.uid'),
    'title' => array('data' => t('Title'), 'field' => 'ttm.title'),
    'body' => array('data' => t('Body'), 'field' => 'ttm.body'),
    t('Actions'),
  );

  $query = db_select('training4_text_message', 'ttm')
    ->extend('TableSort')
    ->extend('PagerDefault')->limit(1)
    ->fields('ttm')
    ->orderByHeader($header);
  $entities = $query->execute();

  $rows = array();
  foreach ($entities as $entity) {
    $user = user_load($entity->uid);
    $rows[] = array(
      'data' => array(
        'id' => $entity->id,
        'author' => $user->name,
        'title' => $entity->title,
        'body' => $entity->body,
        'actions' => l(t('Edit'), 'message/' . $entity->id . '/edit'),
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
function training4_db_entity_access_title($entity) {
  return t('@title', array('@title' => $entity->title));
}

/**
 * Page callback for message/%.
 */
function training4_db_entity_access_view($entity) {
  if (!empty($entity)) {
    $content = array(
      'body' => array(
        '#type' => 'item',
        '#markup' => $entity->body,
      ),
    );
  }
  else {
    $content = t("Message doesn\'t load");
  }

  return $content;
}

/**
 * Page callback for articles.
 */
function training4_db_entity_access_articles_access() {
  $articles = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('type', 'article')
    ->execute()
    ->fetchAllAssoc('nid');

  if ($articles) {
    $links = array();
    foreach ($articles as $item) {
      $links[] = array(
        'title' => $item->title,
        'href' => 'node/' . $item->nid,
      );
    }
    $content = array(
      '#theme' => 'links',
      '#links' => $links,
    );
  }
  else {
    $content = t("Articles doesn\'t exist");
  }

  return $content;
}
