#ifndef PARSING_H
#define PARSING_H


enum e_lexical
{
    PIPE = 0,
    REDIRECTION = 1,
    WORD = 2,
    NULL_POINT = 3
};

typedef struct s_lex
{
    char *str;
    int type;
    struct s_lex *next;
}   t_lex;

#include <unistd.h>

int main();

#endif