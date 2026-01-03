#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"


/*
   Create a new user node
*/
User* createUser(const char *uid, const char *name, const char *username,
                 const char *password, Role role) {
    User *user = (User*)malloc(sizeof(User));
    if (!user) return NULL;

    user->uid = strdup(uid);
    user->name = strdup(name);
    user->username = strdup(username);
    user->password = strdup(password);
    user->role = role;
    user->next = NULL;

    return user;
}

/* 
   Add user to the list (at head)
*/
void addUser(User **head, User *user) {
    if (!head || !user) return;

    user->next = *head;
    *head = user;
}

/*
   Find user by username
*/
User* findUserByUsername(User *head, const char *username) {
    while (head) {
        if (strcmp(head->username, username) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

/* 
   Verify login
 */
User* login(User *head, const char *username, const char *password) {
    User *user = findUserByUsername(head, username);
    if (!user) return NULL;

    if (strcmp(user->password, password) == 0)
        return user;

    return NULL; // password mismatch
}

/* 
   Display all users
*/
void displayUsers(User *head) {
    if (!head) {
        printf("No users registered.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-10s\n", "UID", "Name", "Username", "Role");
    printf("-----------------------------------------------\n");

    while (head) {
        const char *roleStr = "UNKNOWN";
        if (head->role == ADMIN) roleStr = "ADMIN";
        else if (head->role == MANAGER) roleStr = "MANAGER";
        else if (head->role == CASHIER) roleStr = "CASHIER";

        printf("%-5s %-20s %-15s %-10s\n",
               head->uid, head->name, head->username, roleStr);

        head = head->next;
    }
}

/* 
   Edit user details
*/
void editUser(User *head, const char *uid, const char *newName,
              const char *newUsername, const char *newPassword, Role newRole) {
    if (!head) return;

    while (head) {
        if (strcmp(head->uid, uid) == 0) {
            free(head->name);
            head->name = strdup(newName);

            free(head->username);
            head->username = strdup(newUsername);

            free(head->password);
            head->password = strdup(newPassword);

            head->role = newRole;
            return;
        }
        head = head->next;
    }
}


/*
   Free user list
*/
void freeUsers(User *head) {
    while (head) {
        User *temp = head;
        head = head->next;

        free(temp->uid);
        free(temp->name);
        free(temp->username);
        free(temp->password);
        free(temp);
    }
}
