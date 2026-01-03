#ifndef USER_H
#define USER_H

#include <time.h>

/**
 * @file user.h
 * @brief User management and authentication.
 *
 * This header file defines user roles, user data structures,
 * and function prototypes for creating, managing, authenticating,
 * displaying, editing, and freeing users stored in a linked list.
 */

/* ===============================
   User Role
   =============================== */

/**
 * @enum Role
 * @brief Defines user roles in the system.
 */
typedef enum {
    ADMIN,     /**< Administrator with full access */
    MANAGER,   /**< Manager with operational access */
    CASHIER    /**< Cashier with limited access */
} Role;

/* ===============================
   User Node (linked list)
   =============================== */

/**
 * @struct User
 * @brief Represents a system user.
 *
 * Stores user identification, login credentials,
 * role information, and linkage for a singly linked list.
 */
typedef struct User {
    char *uid;            /**< User ID (dynamically allocated) */
    char *name;           /**< Full name of the user */
    char *username;       /**< Login username */
    char *password;       /**< Login password */
    Role role;            /**< Role of the user */
    struct User *next;    /**< Pointer to the next user */
} User;

/* ===============================
   Function Declarations
   =============================== */

/**
 * @brief Creates a new user.
 *
 * Allocates memory and initializes a User structure
 * with the provided details.
 *
 * @param uid       Unique user ID.
 * @param name      Full name of the user.
 * @param username  Login username.
 * @param password  Login password.
 * @param role      Role of the user.
 *
 * @return Pointer to the newly created User, or NULL on failure.
 */
User* createUser(const char *uid, const char *name,
                 const char *username, const char *password, Role role);

/**
 * @brief Adds a user to the user list.
 *
 * Inserts the user at the head of the linked list.
 *
 * @param head Pointer to the head pointer of the user list.
 * @param user Pointer to the user to be added.
 */
void addUser(User **head, User *user);

/**
 * @brief Finds a user by username.
 *
 * Searches the user list for a matching username.
 *
 * @param head     Pointer to the head of the user list.
 * @param username Username to search for.
 *
 * @return Pointer to the matching User, or NULL if not found.
 */
User* findUserByUsername(User *head, const char *username);

/**
 * @brief Authenticates a user login.
 *
 * Verifies username and password credentials.
 *
 * @param head     Pointer to the head of the user list.
 * @param username Login username.
 * @param password Login password.
 *
 * @return Pointer to the authenticated User, or NULL on failure.
 */
User* login(User *head, const char *username, const char *password);

/**
 * @brief Displays all registered users.
 *
 * Prints user information including UID, name,
 * username, and role.
 *
 * @param head Pointer to the head of the user list.
 */
void displayUsers(User *head);

/**
 * @brief Edits an existing user's details.
 *
 * Updates name, username, password, and role
 * for the specified user.
 *
 * @param head        Pointer to the head of the user list.
 * @param uid         UID of the user to edit.
 * @param newName     New name of the user.
 * @param newUsername New username.
 * @param newPassword New password.
 * @param newRole     New role.
 */
void editUser(User *head, const char *uid, const char *newName,
              const char *newUsername, const char *newPassword, Role newRole);

/**
 * @brief Frees all users.
 *
 * Deallocates memory used by the user list and
 * all associated user data.
 *
 * @param head Pointer to the head of the user list.
 */
void freeUsers(User *head);

#endif /* USER_H */
