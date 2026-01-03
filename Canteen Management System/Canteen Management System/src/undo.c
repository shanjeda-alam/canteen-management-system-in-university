#include "../include/undo.h"

OrderStack* createOrderStack(){
    OrderStack *stack = (OrderStack *)malloc(sizeof(OrderStack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

void pushOrder(OrderStack *stack, Order *order){
    OrderStackNode *newNode = (OrderStackNode *)malloc(sizeof(OrderStackNode));
    newNode->order = order;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

Order* popOrder(OrderStack *stack){
    if(stack->top == NULL){
        return NULL;
    }
    OrderStackNode *temp = stack->top;
    Order *poppedOrder = temp->order;
    stack->top = stack->top->next;
    free(temp);
    stack->count--;
    return poppedOrder;
}

/*  Undoing last order(restck item)*/
int undoLastOrder(OrderStack *stack, OrderQueue *queue){
    Order *lastOrder = popOrder(stack);
    if(lastOrder == NULL){
        printf("No order to undo.\n");
        return -1;
    }
    
    /* STEP 1: Restore stock levels FIRST */
    restoreStockLevels(lastOrder);
    
    /* STEP 2: Remove order from queue */
    Order *current = queue->front;
    Order *previous = NULL;
    int found = 0;
    
    while(current != NULL){
        if(current == lastOrder){  /* Compare pointers directly */
            if(previous == NULL){
                queue->front = current->next;
            } else {
                previous->next = current->next;
            }
            if(current == queue->rear){
                queue->rear = previous;
            }
            queue->count--;
            found = 1;
            break;
        }
        previous = current;
        current = current->next;
    }
    
    /* STEP 3: Free the order */
    if (found) {
        printf("Order ID %d undone successfully. Stock restored.\n", lastOrder->orderId);
        freeOrder(lastOrder);
        return 0;
    } else {
        printf("Error: Order not found in queue.\n");
        return -1;
    }
}

void freeOrderStack(OrderStack *stack){
    OrderStackNode *current = stack->top;
    OrderStackNode *nextNode;
    while(current != NULL){
        nextNode = current->next;
        
        free(current);
        current = nextNode;
    }
    free(stack);
}