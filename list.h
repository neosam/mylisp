#ifndef LIST_H
#define LIST_H

struct list;

struct elemInt {
        int type;
        int value;
};

struct elemList {
        int type;
        struct list *value;
};

struct elemID {
        int type;
        char *value;
};

union elem {
        int type;
        struct elemInt elemInt;
        struct elemList elemList;
        struct elemID elemID;
};

struct list {
        union elem *elem;
        struct list *next;
};

struct list *createList(union elem *elem);
struct list *appendList(struct list *list, union elem *elem);

void print(union elem *elem);

#endif /* LIST_H */
