#include <stdlib.h>
#include <string.h>
#include "state.h"

struct state *newState()
{
        struct state *res = (struct state *) malloc(sizeof(struct state));
        res->entries = (union stateEntry *) malloc(sizeof(union stateEntry) *
                                                        STATE_MAX_ENTRIES);
        return res;
}


union stateEntry *lookupState(struct state *res, char *id)
{
        int i;
        for (i = 0; i < STATE_MAX_ENTRIES; i++) {
                if (strcmp(res->entries[i].stateInfo.id, id) == 0) {
                        return res->entries + i;
                }
        }
        return NULL;
}
