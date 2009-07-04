#ifndef EVAL_H
#define EVAL_H

#include "list.h"
#include "state.h"

union elem *eval(union elem *elem, struct state *state);

#endif /* EVAL_H */
