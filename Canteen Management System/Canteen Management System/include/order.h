#ifndef ORDER_H
#define ORDER_H

#include <time.h>
#include <stdint.h>
#include "menuitem.h"

/**
 * @file order.h
 * @brief Order, order item, and order queue management.
 *
 * This header file defines data structures and function declarations
 * for handling customer orders using a FIFO queue. It supports
 * multiple items per order, billing, undo support, and memory cleanup.
 */

/* ===============================
   Order Item (multiple items per order)
   =============================== */

/**
 * @struct OrderItem
 * @brief Represents a single item within an order.
 *
 * Each OrderItem stores a reference to a menu item
 * and the quantity ordered.
 */
typedef struct OrderItem {
    Menu *menuItem;           /**< Pointer to the menu item */
    int quantity;             /**< Quantity ordered */
    struct OrderItem *next;   /**< Pointer to the next order item */
} OrderItem;

/* ===============================
   Order Node (Queue node)
   =============================== */

/**
 * @struct Order
 * @brief Represents a customer order.
 *
 * Stores consumer information, ordered items, billing details,
 * timestamp, and linkage for queue management.
 */
typedef struct Order {
    uint16_t orderId;         /**< Unique order ID */
    char *consumerName;       /**< Consumer name (dynamically allocated) */
    char *consumerUID;        /**< Consumer UID (dynamically allocated) */
    OrderItem *items;         /**< Linked list of order items */
    float totalAmount;        /**< Total order amount */
    time_t orderTime;         /**< Order timestamp */
    struct Order *next;       /**< Pointer to the next order in queue */
} Order;

/* ===============================
   Order Queue (FIFO)
   =============================== */

/**
 * @struct OrderQueue
 * @brief FIFO queue for managing orders.
 *
 * Orders are processed in the order they are placed.
 */
typedef struct {
    Order *front;             /**< Pointer to the front of the queue */
    Order *rear;              /**< Pointer to the rear of the queue */
    int count;                /**< Number of orders in the queue */
} OrderQueue;

/* ===============================
   Function Declarations
   =============================== */

/**
 * @brief Creates and initializes an empty order queue.
 *
 * @return Pointer to the newly created OrderQueue.
 */
OrderQueue* createOrderQueue(void);

/**
 * @brief Creates a new order item.
 *
 * @param menuItem Pointer to the menu item.
 * @param quantity Quantity ordered.
 *
 * @return Pointer to the newly created OrderItem.
 */
OrderItem* createOrderItem(Menu *menuItem, int quantity);

/**
 * @brief Enqueues a new order into the order queue.
 *
 * Adds an order to the rear of the queue and assigns
 * the current timestamp.
 *
 * @param queue        Pointer to the order queue.
 * @param orderId      Unique order ID.
 * @param consumerName Name of the consumer.
 * @param consumerUID  UID of the consumer.
 * @param items        Linked list of order items.
 * @param totalAmount  Total order amount.
 *
 * @return Pointer to the created Order.
 */
Order* enqueueOrder(OrderQueue *queue, int orderId,
                    const char *consumerName,
                    const char *consumerUID,
                    OrderItem *items,
                    float totalAmount);

/**
 * @brief Dequeues an order from the front of the queue.
 *
 * @param queue Pointer to the order queue.
 *
 * @return Pointer to the dequeued Order, or NULL if queue is empty.
 */
Order* dequeueOrder(OrderQueue *queue);

/**
 * @brief Restores stock levels after undoing an order.
 *
 * Adds back the quantities of ordered items to the menu stock.
 *
 * @param order Pointer to the order.
 */
void restoreStockLevels(Order *order);

/**
 * @brief Displays all orders in the queue.
 *
 * Prints detailed information including items and totals.
 *
 * @param queue Pointer to the order queue.
 */
void displayOrders(OrderQueue *queue);

/**
 * @brief Prints a formatted bill for a specific order.
 *
 * @param order Pointer to the order.
 */
void printBill(Order *order);

/**
 * @brief Frees a linked list of order items.
 *
 * @param items Pointer to the head of the order item list.
 */
void freeOrderItems(OrderItem *items);

/**
 * @brief Frees the entire order queue.
 *
 * Deallocates all orders, their items, and the queue itself.
 *
 * @param queue Pointer to the order queue.
 */
void freeOrderQueue(OrderQueue *queue);

/**
 * @brief Frees a single order.
 *
 * @param order Pointer to the order.
 */
void freeOrder(Order *order);

#endif /* ORDER_H */
