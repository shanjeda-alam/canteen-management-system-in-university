#ifndef UNDO_H
#define UNDO_H

#include "order.h"

/**
 * @file undo.h
 * @brief Stack-based undo system for orders.
 *
 * This header file defines data structures and function prototypes
 * for implementing an undo feature using a stack. It allows the
 * most recently placed order to be undone, removed from the order
 * queue, and its stock restored.
 */

/* ===============================
   Data Structures
   =============================== */

/**
 * @struct OrderStackNode
 * @brief Node of the undo stack.
 *
 * Each node stores a pointer to an order and links to
 * the next node in the stack.
 */
typedef struct OrderStackNode {
    Order *order;                 /**< Pointer to the last placed order */
    struct OrderStackNode *next;  /**< Pointer to the next stack node */
} OrderStackNode;

/**
 * @struct OrderStack
 * @brief Stack structure for undo operations.
 *
 * Implements a LIFO (Last-In, First-Out) stack to
 * track recently placed orders.
 */
typedef struct {
    OrderStackNode *top;          /**< Pointer to the top of the stack */
    int count;                    /**< Number of orders in the stack */
} OrderStack;

/* ===============================
   Function Declarations
   =============================== */

/**
 * @brief Creates and initializes an empty order stack.
 *
 * @return Pointer to the newly created OrderStack.
 */
OrderStack* createOrderStack(void);

/**
 * @brief Pushes an order onto the undo stack.
 *
 * Stores the order so it can be undone later.
 *
 * @param stack Pointer to the undo stack.
 * @param order Pointer to the order to be pushed.
 */
void pushOrder(OrderStack *stack, Order *order);

/**
 * @brief Pops the most recent order from the stack.
 *
 * Removes and returns the top order without freeing it.
 *
 * @param stack Pointer to the undo stack.
 *
 * @return Pointer to the popped order, or NULL if the stack is empty.
 */
Order* popOrder(OrderStack *stack);

/**
 * @brief Undoes the most recently placed order.
 *
 * Restores stock levels, removes the order from the order queue,
 * and frees the order memory.
 *
 * @param stack Pointer to the undo stack.
 * @param queue Pointer to the order queue.
 *
 * @return 0 on success, -1 on failure.
 */
int undoLastOrder(OrderStack *stack, OrderQueue *queue);

/**
 * @brief Frees the undo stack.
 *
 * Deallocates all stack nodes and the stack itself.
 * Orders are not freed here, as they are managed by the order queue.
 *
 * @param stack Pointer to the undo stack.
 */
void freeOrderStack(OrderStack *stack);

#endif /* UNDO_H */
