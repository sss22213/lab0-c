#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* if malloc is fail, return NULL */
    if (!q)
        return NULL;

    /* initial q->head and q->tail to NULL */
    q->head = NULL;
    q->tail = NULL;
    q->queue_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* if q is invaild, return NULL */
    if (!q)
        return;

    /* free all of string */
    list_ele_t *cur = q->head;
    if (!cur)
        return;

    while (q->head) {
        cur = q->head;
        q->head = cur->next;
        free(cur->value);
        cur->value = NULL;
        free(cur);
        cur = NULL;
    }


    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* if allocate is invaild, return false */
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        goto allocate_fail;

    /* allocate space for the string and copy it */
    int s_size = strlen(s) + 1;
    newh->value = calloc(s_size, sizeof(char));
    if (!newh->value)
        goto allocate_fail;

    /* copy string */
    memcpy(newh->value, s, (s_size) * sizeof(char));

    /* increase quese size */
    q->queue_size = q->queue_size + 1;

    newh->next = q->head;
    q->head = newh;

    /* if tail is NULL, assign newh to tail */
    if (!q->tail)
        q->tail = newh;

    return true;

allocate_fail:
    return false;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* if q is NULL, return false */
    if (!q)
        goto allocate_fail;

    list_ele_t *newt = NULL;
    newt = calloc(1, sizeof(list_ele_t));

    /* allocate space for the string and copy it */
    int s_size = strlen(s) + 1;
    newt->value = calloc(s_size, sizeof(char));
    if (!newt->value)
        goto allocate_fail;

    /* copy string */
    memcpy(newt->value, s, (s_size) * sizeof(char));

    list_ele_t *tmp = q->tail;
    if (!q->head) {
        q->head = newt;
    } else {
        newt->next = NULL;
        tmp->next = newt;
    }
    q->tail = newt;

    q->queue_size = q->queue_size + 1;

    return true;

allocate_fail:
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !(q->head))
        return false;

    /** If sp is non-NULL and an element is removed,
     * copy the removed string to *sp
     * (up to a maximum of bufsize-1 characters, plus a null terminator.)
     */
    int string_size = strlen(q->head->value);
    bufsize = bufsize - 1;
    if (string_size <= bufsize) {
        memcpy(sp, q->head->value, sizeof(string_size));
    } else {
        memcpy(sp, q->head->value, sizeof(bufsize));
    }
    sp[bufsize] = '\0';

    /* free head */
    list_ele_t *head_next = q->head->next;

    /* head pointer to next */
    q->head = head_next;

    q->queue_size = q->queue_size - 1;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;

    return q->queue_size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head)
        return;

    list_ele_t *list_prev = q->head;
    list_ele_t *list_next = q->head->next;

    q->tail = q->head;
    q->head->next = NULL;

    while (list_next) {
        q->head = list_next;
        list_next = list_next->next;
        q->head->next = list_prev;
        list_prev = q->head;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q) {}
