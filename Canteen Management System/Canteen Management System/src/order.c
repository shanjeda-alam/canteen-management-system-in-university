#include "../include/order.h"

OrderQueue* createOrderQueue() {
    OrderQueue *queue = (OrderQueue *)malloc(sizeof(OrderQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

OrderItem* createOrderItem(Menu *menuItem, int quantity) {
    OrderItem *newItem = (OrderItem *)malloc(sizeof(OrderItem));
    newItem->menuItem = menuItem;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}


Order* enqueueOrder(OrderQueue *queue, int orderId, const char *consumerName,
                    const char *consumerUID, OrderItem *items, float totalAmount){
    Order *newOrder = (Order *)malloc(sizeof(Order));
    newOrder->orderId = orderId;
    newOrder->consumerName = strdup(consumerName);
    newOrder->consumerUID = strdup(consumerUID);
    newOrder->items = items;
    newOrder->totalAmount = totalAmount;
    newOrder->orderTime = time(NULL);
    newOrder->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newOrder;
        queue->rear = newOrder;
    } else {
        queue->rear->next = newOrder;
        queue->rear = newOrder;
    }
    queue->count++;
    
    return newOrder; 
}

Order* dequeueOrder(OrderQueue *queue){
    if (queue->front == NULL) {
        return NULL;
    }
    Order *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->count--;
    return temp;
}

void restoreStockLevels(Order *order){
    OrderItem *item = order->items;
    while (item != NULL) {
        item->menuItem->quantity += item->quantity;
        item = item->next;
    }
}

void displayOrders(OrderQueue *queue){
    if (queue->count == 0) {
        printf("No orders in queue.\n");
        return;
    }
    
    Order *current = queue->front;
    while (current != NULL) {
        printf("\n=== Order ID: %d ===\n", current->orderId);
        printf("Consumer: %s [%s]\n", current->consumerName, current->consumerUID);
        printf("Total Amount: %.2f\n", current->totalAmount);
        printf("Order Time: %s", ctime(&current->orderTime));
        printf("Items:\n");
        OrderItem *item = current->items;
        while (item != NULL) {
            printf("  - %s x%d @ %.2f each\n", 
                   item->menuItem->name, item->quantity, item->menuItem->price);
            item = item->next;
        }
        printf("========================\n");
        current = current->next;
    }
}

void printBill(Order *order) {
    printf("\n========================================\n");
    printf("           BILL\n");
    printf("========================================\n");
    printf("Order ID: %d\n", order->orderId);
    printf("Customer: %s [%s]\n", order->consumerName, order->consumerUID);
    printf("Date: %s", ctime(&order->orderTime));
    printf("----------------------------------------\n");
    printf("%-20s %5s %8s %10s\n", "Item", "Qty", "Price", "Total");
    printf("----------------------------------------\n");
    
    OrderItem *item = order->items;
    while (item != NULL) {
        float itemTotal = item->menuItem->price * item->quantity;
        printf("%-20s %5d %8.2f %10.2f\n", 
               item->menuItem->name, item->quantity, 
               item->menuItem->price, itemTotal);
        item = item->next;
    }
    
    printf("----------------------------------------\n");
    printf("%s %.2f\n" , "TOTAL:", order->totalAmount);
    printf("========================================\n");
    printf("      Thank you! Visit again!\n\n");
}

void freeOrderItems(OrderItem *items){
    OrderItem *current = items;
    OrderItem *nextItem;
    while (current != NULL) {
        nextItem = current->next;
        free(current);
        current = nextItem;
    }
}

void freeOrderQueue(OrderQueue *queue){
    Order *current = queue->front;
    Order *nextOrder;
    while (current != NULL) {
        nextOrder = current->next;
        free(current->consumerName);
        free(current->consumerUID);
        freeOrderItems(current->items);
        free(current);
        current = nextOrder;
    }
    free(queue);
}

void freeOrder(Order *order) {
    if (order) {
        free(order->consumerName);
        free(order->consumerUID);
        freeOrderItems(order->items);
        free(order);
    }
}