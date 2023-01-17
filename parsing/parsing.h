#ifndef PARSING_H
#define PARSING_H


#define SMALL_QUOTE 39
#define BIG_QUOTE 34
#define BLANK 32


#include "../libft/libft.h"
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

typedef struct s_tree
{
	int data;
	struct s_tree *left;
	struct s_tree *right;
}	t_tree;

typedef struct s_flag
{
	int small_quote;
	int big_quote;
} t_flag;

#include <unistd.h>

int main();

#endif