#include <stdlib.h>
#include "eval.h"
#include "globals.h"

union elem *evalList(union elem *elem, struct state *state)
{

}

union elem *eval(union elem *elem, struct state *state)
{
        union elem *res = (union elem*) malloc(sizeof(union elem));
        union stateEntry *tmp;
        struct list *ltmp;
        struct list *args = NULL;
        switch (elem->type) {
        case T_INT:
                res->type = T_INT;
                res->elemInt = elem->elemInt;
                break;
        case T_ID:
                tmp = lookupState(state, elem->elemID.value);
                res = tmp->stateVar.elem;
                break;
        case T_LIST:
                ltmp = elem->elemList.value;
                tmp = lookupState(state, ltmp->elem->elemID.value);
                ltmp = ltmp->next;
                while (ltmp != NULL) {
                    args = appendList(args, eval(ltmp->elem, state));
                    ltmp = ltmp->next;
                }
                if (tmp->stateInfo.type == STATE_BUILDIN)
                        res = tmp->stateBuildin.func(args);
                break;
        default:
                return NULL;
        }

        return res;
}
