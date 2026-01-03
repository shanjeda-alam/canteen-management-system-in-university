/**
 * @file consumerInterface.c
 * @brief Consumer interface module for the Canteen Management System.
 *
 * @details
 * This file provides a standalone consumer-side interface
 * where users can:
 * - View menu items
 * - Place orders
 * - Cancel last order
 * - View past orders
 *
 * This module works with shared data structures such as
 * Menu, Consumer, OrderQueue, and OrderStack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include headers */
#include "include/menuitem.h"
#include "include/consumer.h"
#include "include/order.h"
#include "include/undo.h"

/* ===============================
   Helper Functions
   =============================== */

/* Find existing consumer by UID or create a new one */
Consumer *getOrCreateConsumer(Consumer **head, const char *uid, const char *name)
{
    Consumer *temp = *head;
    while (temp)
    {
        if (strcmp(temp->uid, uid) == 0)
        {
            return temp; // Existing consumer
        }
        temp = temp->next;
    }
    // Create new consumer
    Consumer *newConsumer = createConsumer(uid, name, STUDENT); // Default type STUDENT
    addConsumer(head, newConsumer->uid, newConsumer->name, newConsumer->type);
    printf("New consumer added: %s [%s]\n", name, uid);
    return newConsumer;
}

/* Place a new order */
void placeOrder(Consumer *c, Menu *menuHead, OrderQueue *queue, OrderStack *stack, int *nextOrderId)
{
    int itemCount;
    printf("\n--- Place Order for %s [%s] ---\n", c->name, c->uid);
    displayMenu(menuHead);

    printf("How many items to order? ");
    scanf("%d", &itemCount);
    if (itemCount <= 0)
        return;

    OrderItem *itemsHead = NULL;
    OrderItem *itemsTail = NULL;
    float total = 0;

    for (int i = 0; i < itemCount; i++)
    {
        int menuId, qty;
        printf("\nItem %d - Enter Menu ID: ", i + 1);
        scanf("%d", &menuId);
        printf("Quantity: ");
        scanf("%d", &qty);

        Menu *menuItem = findMenuItem(menuHead, menuId);
        if (!menuItem)
        {
            printf("Invalid Menu ID!\n");
            i--; // retry
            continue;
        }
        if (menuItem->quantity < qty)
        {
            printf("Insufficient stock! Available: %d\n", menuItem->quantity);
            i--; // retry
            continue;
        }

        menuItem->quantity -= qty;

        OrderItem *newItem = createOrderItem(menuItem, qty);
        if (!itemsHead)
        {
            itemsHead = itemsTail = newItem;
        }
        else
        {
            itemsTail->next = newItem;
            itemsTail = newItem;
        }
        total += menuItem->price * qty;
    }

    if (!itemsHead)
    {
        printf("No valid items ordered.\n");
        return;
    }

    // Create order and enqueue
    enqueueOrder(queue, (*nextOrderId)++, c->name, c->uid, itemsHead, total);
    pushOrder(stack, queue->rear); // Push last order for undo
    printf("Order placed successfully! Total: %.2f\n", total);
}

/* Undo last order for this consumer */
void cancelLastOrder(Consumer *c, OrderStack *stack, OrderQueue *queue)
{
    if (!stack->top)
    {
        printf("No order to cancel.\n");
        return;
    }

    Order *lastOrder = stack->top->order;
    if (strcmp(lastOrder->consumerUID, c->uid) != 0)
    {
        printf("Last order does not belong to you. Cannot cancel.\n");
        return;
    }

    printf("\nCancelling Order ID: %d\n", lastOrder->orderId);
    printf("Total Amount: %.2f\n", lastOrder->totalAmount);

    int result = undoLastOrder(stack, queue);
    if (result == 0)
    {
        printf("Order cancelled successfully! Amount refunded.\n");
    }
    else
    {
        printf("Failed to cancel order.\n");
    }
}
/* View all past orders for this consumer */
void viewConsumerOrders(Consumer *c, OrderQueue *queue)
{
    printf("\n--- Past Orders for %s [%s] ---\n", c->name, c->uid);
    Order *temp = queue->front;
    int found = 0;
    while (temp)
    {
        if (strcmp(temp->consumerUID, c->uid) == 0)
        {
            found = 1;
            printBill(temp);
        }
        temp = temp->next;
    }
    if (!found)
    {
        printf("No past orders.\n");
    }
}

/* ===============================
   Main Consumer Interface
   =============================== */
void consumerInterface(Consumer **consumerHead, Menu *menuHead,
                       OrderQueue *queue, OrderStack *stack, int *nextOrderId)
{
    char name[50], uid[20];
    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    printf("Enter your UID: ");
    scanf("%s", uid);

    Consumer *c = getOrCreateConsumer(consumerHead, uid, name);

    int choice;
    do
    {
        printf("\n--- Consumer Menu ---\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. Cancel Last Order\n");
        printf("4. View My Orders\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMenu(menuHead);
            break;
        case 2:
            placeOrder(c, menuHead, queue, stack, nextOrderId);
            break;
        case 3:
            cancelLastOrder(c, stack, queue);
            break;
        case 4:
            viewConsumerOrders(c, queue);
            break;
        case 0:
            printf("Exiting Consumer Interface...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* ===============================
   Standalone Main
   =============================== */
int main()
{
    Consumer *consumerHead = NULL;
    Menu *menuHead = NULL;
    OrderQueue *queue = createOrderQueue();
    OrderStack *stack = createOrderStack();
    int nextOrderId = 1;

    /* Sample Menu Items */
    addMenuItem(&menuHead, 1, "Burger", FOOD, 150.0, 10);
    addMenuItem(&menuHead, 2, "Coke", DRINK, 50.0, 20);
    addMenuItem(&menuHead, 3, "Cake", DESERT, 120.0, 5);

    consumerInterface(&consumerHead, menuHead, queue, stack, &nextOrderId);

    /* Free memory */
    freeConsumers(consumerHead);
    freeMenu(menuHead);
    freeOrderQueue(queue);
    freeOrderStack(stack);

    return 0;
}
