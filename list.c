#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "globals.h"

struct list *createList(union elem *elem)
{
        struct list *res = (struct list*) malloc(sizeof(struct list));
        res->elem = elem;
        res->next = NULL;
}

struct list *duplicateList(struct list *list)
{
        struct list *res, *cur, *p;

        if (list == NULL)
                return NULL;
        res = createList(list->elem);
        cur = res;
        p = list;
        while (p->next != NULL) {
            p = p->next;
            cur->next = createList(p->elem);
            cur = cur->next;
            cur->next = NULL;
        }

        return res;
}

struct list *lastList(struct list *list)
{
        struct list *res = list;
        while (res->next != NULL)
            res = res->next;
        return res;
}

struct list *appendList(struct list *list, union elem *elem)
{
        struct list *res = duplicateList(list);

        if (list == NULL)
                return createList(elem);
        lastList(res)->next = createList(elem);
        return res;
}

void printList(struct list *list)
{
        if (list == NULL) {
                printf("()");
                return;
        }

        if (list->next == NULL) {
                printf("(");
                print(list->elem);
                printf(")");
                return;
        }

        fputc('(', stdout);
        print(list->elem);
        list = list->next;
        while (list != NULL) {
                fputc(' ', stdout);
                print(list->elem);
                fflush(stdout);
                list = list->next;
        }
        fputc(')', stdout);
}

void print(union elem *elem)
{
        switch (elem->type) {
        case T_LIST:
                printList(elem->elemList.value);
                break;
        case T_INT:
                printf("%i", elem->elemInt.value);
                break;
        case T_ID:
                printf("%s", elem->elemID.value);
                break;
        }
}
