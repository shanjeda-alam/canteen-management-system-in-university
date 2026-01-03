/**
 * @file c  canteenmanagement.c
 * @brief Canteen Management System – Admin Module
 *
 * @author Kazi Nyeemul Islam Nibir (ID: 2024-3-60-410)
 * @author Sumia Saima (ID: 2024-3-60-355)
 * @author Shanjeda Alam (ID: 2024-3-60-425)
 * @author ________________________________ (ID: ____________)
 *
 * @version 1.0
 * @date 2025
 *
 * @details
 * This file contains the main entry point for the
 * Admin-side Canteen Management System.
 *
 * Features:
 * - User management
 * - Menu management
 * - Consumer management
 * - Order processing
 * - Undo last order
 */

#include "include/user.h"
#include "include/consumer.h"
#include "include/menuitem.h"
#include "include/order.h"
#include "include/undo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   Function Declarations
*/
void adminMenu(User *, Menu **, Consumer **,
               User **, OrderQueue *, OrderStack *);

void placeOrder(Consumer **consumerHead, Menu *menuHead, OrderQueue *queue, OrderStack *stack);

/*
   Main Function
*/
int main()
{
    /* Initialize lists */
    Menu *menuHead = NULL;
    Consumer *consumerHead = NULL;
    User *userHead = NULL;
    OrderQueue *orderQueue = createOrderQueue();
    OrderStack *undoStack = createOrderStack();

    /* Create sample users */
    addUser(&userHead, createUser("U001", "Admin", "admin", "admin123", ADMIN));
    addUser(&userHead, createUser("U001", "Nibir", "nibir", "nibir123", ADMIN));
    addUser(&userHead, createUser("U001", "Shimu", "simu", "simu123", ADMIN));
    addUser(&userHead, createUser("U001", "Saif", "saif", "saif123", ADMIN));
    addUser(&userHead, createUser("U001", "Tushi", "tushi", "tushi123", ADMIN));

    /* Sample menu */
    addMenuItem(&menuHead, 1, "Tea", DRINK, 15.0, 50);
    addMenuItem(&menuHead, 2, "Coffee", DRINK, 25.0, 50);
    addMenuItem(&menuHead, 3, "Samosa", FOOD, 20.0, 30);
    addMenuItem(&menuHead, 4, "Sandwich", FOOD, 40.0, 20);

    char username[50], password[50];
    User *currentUser = NULL;

    printf("===== CANTEEN MANAGEMENT SYSTEM =====\n");

    /* Login Loop */
    while (!currentUser)
    {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        currentUser = login(userHead, username, password);
        if (!currentUser)
        {
            printf("Invalid username or password. Try again.\n");
        }
    }

    /* Show Role based menu */
    switch (currentUser->role)
    {
    case ADMIN:
        adminMenu(currentUser, &menuHead, &consumerHead, &userHead, orderQueue, undoStack);
        break;

    default:
        printf("Unknown role.\n");
    }

    /* Free all resources */
    freeMenu(menuHead);
    freeConsumers(consumerHead);
    freeUsers(userHead);
    freeOrderQueue(orderQueue);
    freeOrderStack(undoStack);

    return 0;
}

/*
   Admin Menu
*/
void adminMenu(User *user, Menu **menuHead, Consumer **consumerHead,
               User **userHead, OrderQueue *orderQueue, OrderStack *undoStack)
{
    int choice;
    char uid[50], name[50];
    do
    {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Add Menu Item\n2. Edit Menu Item\n3. Display Menu\n");
        printf("4. Add Consumer\n5. Edit Consumer\n6. Display Consumers\n");
        printf("7. Add User\n8. Edit User\n9. Display Users\n");
        printf("10. Place Order\n11. Undo Last Order\n12. Display Orders\n");
        printf("0. Logout\nChoose option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Enter ID, Name, Type(0-FOOD,1-DRINK,2-DESERT), Price, Quantity: ");
            int typeInt;
            float price;
            int qty;
            int id;
            scanf("%d %s %d %f %d", &id, name, &typeInt, &price, &qty);
            addMenuItem(menuHead, id, name, typeInt, price, qty);
            break;
        case 2:
            printf("Enter Menu ID to edit: ");
            scanf("%d", &id);
            printf("Enter New Name, Type(0-FOOD,1-DRINK,2-DESERT), Price: ");
            scanf("%s %d %f", name, &typeInt, &price);
            editMenuItem(*menuHead, id, name, typeInt, price);
            break;
        case 3:
            displayMenu(*menuHead);
            break;
        case 4:
            printf("Enter UID, Name, Type(0-STUDENT,1-STAFF,2-FACULTY): ");
            int ctype;
            scanf("%s %s %d", uid, name, &ctype);
            addConsumer(consumerHead, uid, name, ctype);
            break;
        case 5:
            printf("Enter UID to edit: ");
            scanf("%s", uid);
            printf("Enter New Name, Type(0-STUDENT,1-STAFF,2-FACULTY): ");
            scanf("%s %d", name, &ctype);
            editConsumer(*consumerHead, uid, name, ctype);
            break;
        case 6:
            displayConsumers(*consumerHead);
            break;
        case 7:
            printf("Enter UID, Name, Username, Password, Role(0-ADMIN,1-MANAGER,2-CASHIER): ");
            char username[50], password[50];
            scanf("%s %s %s %s %d", uid, name, username, password, &ctype);
            addUser(userHead, createUser(uid, name, username, password, ctype));
            break;
        case 8:
            printf("Enter UID to edit: ");
            scanf("%s", uid);
            printf("Enter New Name, Username, Password, Role(0-ADMIN,1-MANAGER,2-CASHIER): ");
            scanf("%s %s %s %d", name, username, password, &ctype);
            editUser(*userHead, uid, name, username, password, ctype);
            break;
        case 9:
            displayUsers(*userHead);
            break;
        case 10:
            placeOrder(consumerHead, *menuHead, orderQueue, undoStack);
            break;
        case 11:
            if (undoLastOrder(undoStack, orderQueue))
                printf("Last order undone successfully.\n");
            else
                printf("No order to undo.\n");
            break;
        case 12:
            displayOrders(orderQueue);
            break;
        case 0:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/*
   Place Order Function
*/
void placeOrder(Consumer **consumerHead, Menu *menuHead, OrderQueue *queue, OrderStack *stack)
{
    char uid[50];
    displayConsumers(*consumerHead);
    printf("Enter Consumer UID: ");
    scanf("%s", uid);
    Consumer *c = *consumerHead;
    while (c && strcmp(c->uid, uid) != 0)
        c = c->next;
    if (!c)
    {
        printf("Consumer not found!\n");
        return;
    }

    displayMenu(menuHead);
    int n, menuId, qty;
    printf("How many items? ");
    scanf("%d", &n);

    OrderItem *head = NULL, *tail = NULL;
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Item %d - Enter Menu ID and Quantity: ", i + 1);
        scanf("%d %d", &menuId, &qty);
        Menu *m = findMenuItem(menuHead, menuId);
        if (!m)
        {
            printf("Invalid Menu ID!\n");
            i--;
            continue;
        }
        if (m->quantity < qty)
        {
            printf("Insufficient stock!\n");
            i--;
            continue;
        }
        m->quantity -= qty;

        OrderItem *item = createOrderItem(m, qty);
        if (!head)
            head = tail = item;
        else
        {
            tail->next = item;
            tail = item;
        }
        total += m->price * qty;
    }

    Order *order = (Order *)malloc(sizeof(Order));
    order->orderId = rand() % 10000 + 1;
    order->consumerName = strdup(c->name);
    order->consumerUID = strdup(c->uid);
    order->items = head;
    order->totalAmount = total;
    order->orderTime = time(NULL);
    order->next = NULL;

    enqueueOrder(queue, order->orderId, order->consumerName, order->consumerUID, head, total);
    pushOrder(stack, order);
    printf("Order placed successfully!\n");
}
