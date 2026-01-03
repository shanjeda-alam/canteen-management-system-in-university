#ifndef MENUITEM_H
#define MENUITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * @file menuitem.h
 * @brief Menu item management using a doubly linked list.
 *
 * This header file defines the Menu structure, item types,
 * and function prototypes for creating, managing, displaying,
 * modifying, and freeing menu items.
 */

/**
 * @enum ItemType
 * @brief Represents the category of a menu item.
 */
typedef enum {
    FOOD,    /**< Food item */
    DRINK,   /**< Drink item */
    DESERT   /**< Dessert item */
} ItemType;

/**
 * @struct Menu
 * @brief Represents a menu item in a doubly linked list.
 *
 * Each menu item contains identifying information, pricing,
 * stock quantity, and pointers to adjacent items.
 */
typedef struct Menu {
    int id;                   /**< Unique menu item ID */
    char *name;               /**< Name of the menu item */
    ItemType type;            /**< Type/category of the item */
    float price;              /**< Price of the item */
    uint16_t quantity;        /**< Available stock quantity */
    struct Menu *prev;        /**< Pointer to the previous item */
    struct Menu *next;        /**< Pointer to the next item */
} Menu;

/* ===============================
   Menu item creation and insertion
   =============================== */

/**
 * @brief Creates a new menu item.
 *
 * Allocates memory and initializes a Menu structure
 * with the provided data.
 *
 * @param id       Unique menu item ID.
 * @param name     Name of the menu item.
 * @param type     Category/type of the menu item.
 * @param price    Price of the menu item.
 * @param quantity Initial stock quantity.
 *
 * @return Pointer to the newly created Menu item, or NULL on failure.
 */
Menu* createMenuItem(int id, const char *name, ItemType type, float price, uint16_t quantity);

/**
 * @brief Adds a menu item to the menu list.
 *
 * Inserts the new item at the end of the doubly linked list.
 *
 * @param head     Pointer to the head pointer of the menu list.
 * @param id       Unique menu item ID.
 * @param name     Name of the menu item.
 * @param type     Category/type of the menu item.
 * @param price    Price of the menu item.
 * @param quantity Initial stock quantity.
 */
void addMenuItem(Menu **head, int id, const char *name, ItemType type, float price, uint16_t quantity);

/* ===============================
   Menu item search and display
   =============================== */

/**
 * @brief Finds a menu item by ID.
 *
 * Searches the menu list for an item with the specified ID.
 *
 * @param head Pointer to the head of the menu list.
 * @param id   ID of the menu item to search for.
 *
 * @return Pointer to the found Menu item, or NULL if not found.
 */
Menu* findMenuItem(Menu *head, int id);

/**
 * @brief Displays all menu items.
 *
 * Prints menu item details including ID, name, type,
 * price, and available quantity.
 *
 * @param head Pointer to the head of the menu list.
 */
void displayMenu(Menu *head);

/* ===============================
   Menu item modification
   =============================== */

/**
 * @brief Edits an existing menu item.
 *
 * Updates the name, type, and price of the specified menu item.
 *
 * @param head     Pointer to the head of the menu list.
 * @param id       ID of the menu item to be edited.
 * @param newName  New name of the menu item.
 * @param newType  New category/type of the menu item.
 * @param newPrice New price of the menu item.
 */
void editMenuItem(Menu *head, int id, const char *newName, ItemType newType, float newPrice);

/**
 * @brief Updates the stock quantity of a menu item.
 *
 * Adjusts the quantity by a specified amount. Prevents
 * negative stock values.
 *
 * @param head   Pointer to the head of the menu list.
 * @param id     ID of the menu item.
 * @param change Quantity change (positive or negative).
 */
void updateQuantity(Menu *head, int id, int change);

/* ===============================
   Memory cleanup
   =============================== */

/**
 * @brief Frees all menu items.
 *
 * Deallocates memory used by the menu list and its contents.
 *
 * @param head Pointer to the head of the menu list.
 */
void freeMenu(Menu *head);

#endif /* MENUITEM_H */
