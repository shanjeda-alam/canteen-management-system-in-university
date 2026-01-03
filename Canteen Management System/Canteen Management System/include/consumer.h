#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file consumer.h
 * @brief Declarations for Consumer management using a doubly linked list.
 *
 * This header file contains the data structures and function prototypes
 * required to create, manage, modify, display, and free Consumer records.
 */

/**
 * @enum ConsumerType
 * @brief Represents the type/category of a consumer.
 */
typedef enum {
    STUDENT,   /**< Consumer is a student */
    STAFF,     /**< Consumer is a staff member */
    FACULTY    /**< Consumer is a faculty member */
} ConsumerType;

/**
 * @struct Consumer
 * @brief Represents a consumer node in a doubly linked list.
 *
 * Each consumer has a unique ID, name, type, and pointers to the
 * previous and next consumers in the list.
 */
typedef struct Consumer {
    char *uid;                 /**< Unique identifier of the consumer */
    char *name;                /**< Name of the consumer */
    ConsumerType type;         /**< Type of the consumer */
    struct Consumer *next;     /**< Pointer to the next consumer */
    struct Consumer *prev;     /**< Pointer to the previous consumer */
} Consumer;

/**
 * @brief Creates a new Consumer node.
 *
 * Allocates memory for a Consumer structure and initializes its fields.
 *
 * @param uid  Unique identifier of the consumer.
 * @param name Name of the consumer.
 * @param type Type of the consumer.
 *
 * @return Pointer to the newly created Consumer.
 */
Consumer* createConsumer(const char *uid, const char *name, ConsumerType type);

/**
 * @brief Adds a new consumer to the beginning of the list.
 *
 * Inserts the newly created consumer node at the head of the doubly
 * linked list.
 *
 * @param head Pointer to the head pointer of the consumer list.
 * @param uid  Unique identifier of the consumer.
 * @param name Name of the consumer.
 * @param type Type of the consumer.
 */
void addConsumer(Consumer **head, const char *uid, const char *name, ConsumerType type);

/**
 * @brief Displays all consumers in the list.
 *
 * Traverses the consumer list from head to tail and prints
 * the details of each consumer.
 *
 * @param head Pointer to the head of the consumer list.
 */
void displayConsumers(Consumer *head);

/**
 * @brief Edits an existing consumer's details.
 *
 * Searches for a consumer by UID and updates its name and type.
 *
 * @param head    Pointer to the head of the consumer list.
 * @param uid     Unique identifier of the consumer to be edited.
 * @param newName New name for the consumer.
 * @param newType New type for the consumer.
 */
void editConsumer(Consumer *head, const char *uid, const char *newName, ConsumerType newType);

/**
 * @brief Frees all consumers in the list.
 *
 * Deallocates memory for all consumer nodes and their associated data.
 *
 * @param head Pointer to the head of the consumer list.
 */
void freeConsumers(Consumer *head);

#endif /* CONSUMER_H */
