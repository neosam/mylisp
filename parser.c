#include <stdlib.h>
#include "parser.h"
#include "list.h"
#include "globals.h"

int intres;
char *idres;
FILE *inputFile;
char *inputString;
int inputStringPos;
int inputType;
char currentChar;
int currentToken;

union elem *read_intern();

char nextChar()
{
        switch (inputType) {
        case 0:
                currentChar = fgetc(inputFile);
                break;
        case 1:
                currentChar = inputString[inputStringPos++];
                break;
        }
        fflush(stdout);

        return currentChar;
}

void initParserFile(FILE *file)
{
        inputFile = file;
        inputType = 0;
        nextChar();
}

void initParserString(char *str)
{
        inputString = str;
        inputType = 1;
        inputStringPos = 0;
        nextChar();
}

int isWhitespace(char c)
{
        if (c == '\n' || c == ' ' || c == '\t' || c == '\0')
                return 1;
        return 0;
}


void jumpWhitespace()
{
        while (isWhitespace(currentChar) && currentChar != '\0')
                nextChar();
}

void parseNumber()
{
        intres = 0;
        while (currentChar >= '0' && currentChar <= '9') {
                intres *= 10;
                intres += currentChar - '0';
                nextChar();
        }
        jumpWhitespace();
}

void parseID()
{
        idres = (char *) malloc(sizeof(char) * 256);
        int pos = 0;
        while (!isWhitespace(currentChar) && currentChar != ')') {
                idres[pos] = currentChar;
                nextChar();
                pos++;
        }
        idres[pos] = '\0';
}

int parseToken()
{
        jumpWhitespace();
        switch (currentChar) {
        case '(':
                nextChar();
                jumpWhitespace();
                currentToken = T_LIST_BEGIN;
                return T_LIST_BEGIN;
        case ')':
                nextChar();
                jumpWhitespace();
                currentToken = T_LIST_END;
                return T_LIST_END;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
                parseNumber();
                jumpWhitespace();
                currentToken = T_INT;
                return T_INT;
        default:
                parseID();
                jumpWhitespace();
                currentToken = T_ID;
                return T_ID;
        }
}

struct list *readList()
{
        struct list *res = NULL;

        while (1) {
                switch (currentToken) {
                case T_LIST_END:
                        return res;
                default:
                        res = appendList(res, read_intern());
                        break;
                }
        }
}

union elem *read_intern()
{
        union elem *res = (union elem *) malloc(sizeof(union elem));
        switch (currentToken) {
        case T_INT:
                res->type = T_INT;
                res->elemInt.value = intres;
                parseToken();
                break;
                return res;
        case T_LIST_BEGIN:
                res->type = T_LIST;
                parseToken();
                res->elemList.value = readList();
                parseToken();
                break;
                return res;
        case T_ID:
                res->type = T_ID;
                res->elemID.value = idres;
                parseToken();
                break;
                return res;
        default:
                fprintf(stderr, "unexpected error %i\n", currentToken);
                exit(-1);
        }

//        print(res);
        return res;
}

union elem *read()
{
        parseToken();
        return read_intern();
}

