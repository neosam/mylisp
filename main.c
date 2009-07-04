#include <stdlib.h>
#include "parser.h"
#include "eval.h"
#include "globals.h"

struct state *globalState;

union elem *add(struct list *lst)
{
        union elem *res = (union elem *) malloc(sizeof(union elem));
        int sum = 0;
        res->type = T_INT;
        while (lst != NULL) {
                sum += lst->elem->elemInt.value;
                lst = lst->next;
        }
        res->elemInt.value = sum;
        return res;
}

union elem *sub(struct list *lst)
{
        union elem *res = (union elem *) malloc(sizeof(union elem));
        int sum;
        res->type = T_INT;
        if (lst == NULL) {
                res->elemInt.value = 0;
                return res;
        }
        sum = lst->elem->elemInt.value;
        lst = lst->next;
        while (lst != NULL) {
                sum -= lst->elem->elemInt.value;
                lst = lst->next;
        }
        res->elemInt.value = sum;
        return res;
}

union elem *mul(struct list *lst)
{
        union elem *res = (union elem *) malloc(sizeof(union elem));
        int mul = 1;
        res->type = T_INT;
        while (lst != NULL) {
                mul *= lst->elem->elemInt.value;
                lst = lst->next;
        }
        res->elemInt.value = mul;
        return res;
}

void repl()
{
        char input[256];
        while (1) {
                printf("> ");
                fflush(stdout);
                fgets(input, 255, stdin);
                initParserString(input);
                print(eval(read(), globalState));
                printf("\n");
        }
}

int main()
{
        union elem *one = (union elem *) malloc(sizeof(union elem));
        one->type = T_INT;
        one->elemInt.value = 1;

        globalState = newState();
        globalState->entries[0].stateInfo.type = STATE_BUILDIN;
        globalState->entries[0].stateInfo.id = "+";
        globalState->entries[0].stateBuildin.func = add;
        globalState->entries[1].stateInfo.type = STATE_BUILDIN;
        globalState->entries[1].stateInfo.id = "-";
        globalState->entries[1].stateBuildin.func = sub;
        globalState->entries[2].stateInfo.type = STATE_BUILDIN;
        globalState->entries[2].stateInfo.id = "*";
        globalState->entries[2].stateBuildin.func = mul;
        globalState->entries[3].stateInfo.type = STATE_VAR;
        globalState->entries[3].stateInfo.id = "one";
        globalState->entries[3].stateVar.elem = one;

        repl();

        return 0;
}
