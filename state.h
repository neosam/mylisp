#ifndef STATE_H
#define STATE_H

#define STATE_MAX_ENTRIES 256
#define STATE_BUILDIN 1
#define STATE_VAR 2

struct list;

struct stateInfo
{
        int type;
        char *id;
};

struct stateBuildin
{
        int type;
        char *id;
        union elem *(*func)(struct list *lst);
};

struct stateVar
{
        int type;
        char *id;
        union elem *elem;
};

union stateEntry {
        struct stateInfo stateInfo;
        struct stateBuildin stateBuildin;
        struct stateVar stateVar;
};

struct state {
        union stateEntry *entries;
        struct state *prev;
};

struct state *newState();
union stateEntry *lookupState(struct state *state, char *id);

#endif /* STATE_H */
