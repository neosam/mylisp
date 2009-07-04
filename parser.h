#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "list.h"

extern int intres;
extern FILE *inputFile;

void initParser(FILE *file);
int parseToken();
union elem *read();

#endif /* PARSER_H */
