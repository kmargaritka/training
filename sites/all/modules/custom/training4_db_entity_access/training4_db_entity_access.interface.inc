<?php

/**
 * Training4TextMessageControllerInterface definition.
 */
interface Training4TextMessageControllerInterface
  extends DrupalEntityControllerInterface {

  /**
   * Create an entity.
   */
  public function create();

  /**
   * Save an entity.
   *
   * @param object $entity
   *   The entity to save.
   */
  public function save($entity);

}