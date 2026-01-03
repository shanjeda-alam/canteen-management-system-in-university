#include"../include/menuitem.h"


Menu* createMenuItem(int id, const char *name, ItemType type, float price, uint16_t quantity){
    Menu *newItem = (Menu *)malloc(sizeof(Menu));
    if (!newItem) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newItem->id = id;
    newItem->name = strdup(name);
    newItem->type = type;
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->prev = NULL;
    newItem->next = NULL;
    return newItem;
}
void addMenuItem(Menu **head, int id, const char *name, ItemType type, float price, uint16_t quantity){
    Menu *newItem = createMenuItem(id, name, type, price, quantity);
    if (!newItem) return;

    if (*head == NULL) {
        *head = newItem;
    } else {
        Menu *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
        newItem->prev = temp;
    }
}
Menu* findMenuItem(Menu *head, int id){
    Menu *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayMenu(Menu *head){
    Menu *current = head;
    printf("Menu Items:\n");
    printf("ID\tName\tType\tPrice\tQuantity\n");
    while (current != NULL) {
        const char *typeStr = (current->type == FOOD) ? "FOOD" : (current->type == DRINK) ? "DRINK" : "DESERT";
        printf("%d\t%s\t%s\t%.2f\t%d\n", current->id, current->name, typeStr, current->price, current->quantity);
        current = current->next;
    }
}
void editMenuItem(Menu *head, int id, const char *newName, ItemType newType, float newPrice){
    Menu *item = findMenuItem(head, id);
    if (item != NULL) {
        free(item->name);
        item->name = strdup(newName);
        item->type = newType;
        item->price = newPrice;
    } else {
        printf("Menu item with ID %d not found.\n", id);
    }
}
void updateQuantity(Menu *head, int id, int change){
    Menu *item = findMenuItem(head, id);
    if (item != NULL) {
        int newQuantity = item->quantity + change;
        if (newQuantity < 0) {
            printf("Insufficient stock for item ID %d.\n", id);
        } else {
            item->quantity = newQuantity;
        }
    } else {
        printf("Menu item with ID %d not found.\n", id);
    }
}
void freeMenu(Menu *head){
    Menu *current = head;
    Menu *nextItem;
    while (current != NULL) {
        nextItem = current->next;
        free(current->name);
        free(current);
        current = nextItem;
    }
}