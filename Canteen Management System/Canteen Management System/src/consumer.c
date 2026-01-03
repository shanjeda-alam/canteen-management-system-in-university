#include "../include/consumer.h"
Consumer* createConsumer(const char *uid, const char *name, ConsumerType type){
    Consumer *newConsumer = (Consumer *)malloc(sizeof(Consumer));
    if (!newConsumer) {
        fprintf(stderr, "Memory allocation failed for new consumer.\n");
        exit(EXIT_FAILURE);
    }
    newConsumer->uid = strdup(uid);
    newConsumer->name = strdup(name);
    newConsumer->type = type;
    newConsumer->next = NULL;
    newConsumer->prev = NULL;
    return newConsumer;
}
void addConsumer(Consumer **head, const char *uid, const char *name, ConsumerType type){
    Consumer *newConsumer = createConsumer(uid, name, type);
    newConsumer->next = *head;
    if (*head != NULL) {
        (*head)->prev = newConsumer;
    }
    *head = newConsumer;
}
void displayConsumers(Consumer *head){
    Consumer *current = head;
    while (current != NULL) {
        printf("UID: %s, Name: %s, Type: ", current->uid, current->name);
        switch (current->type) {
            case STUDENT:
                printf("STUDENT\n");
                break;
            case STAFF:
                printf("STAFF\n");
                break;
            case FACULTY:
                printf("FACULTY\n");
                break;
            default:
                printf("UNKNOWN\n");
        }
        current = current->next;
    }
}
void  editConsumer(Consumer *head, const char *uid, const char *newName, ConsumerType newType){
    Consumer *current = head;
    while (current != NULL) {
        if (strcmp(current->uid, uid) == 0) {
            free(current->name);
            current->name = strdup(newName);
            current->type = newType;
            return;
        }
        current = current->next;
    }
    fprintf(stderr, "Consumer with UID %s not found.\n", uid);
}
void freeConsumers(Consumer *head){
    Consumer *current = head;
    Consumer *next;
    while (current != NULL) {
        next = current->next;
        free(current->uid);
        free(current->name);
        free(current);
        current = next;
    }
}


