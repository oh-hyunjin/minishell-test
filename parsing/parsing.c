#include "parsing.h"
#include <string.h> //split용
#include <stdlib.h>


char	**ft_error(char **tmp, size_t i)
{
	size_t	n;

	n = 0;
	while (n < i)
	{
		free(tmp[n]);
		n++;
	}
	free(tmp);
	return (0);
}

size_t	ft_strlen_str(char *str, char charset)
{
	size_t	i;

	i = 0;
	while (str[i] != charset && str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_count_charset(char *str, char charset)
{
	size_t	cnt;
	size_t	str_jump;

	cnt = 0;
	while (*str)
	{
		while (*str && *str == charset)
			str++;
		str_jump = ft_strlen_str(str, charset);
		if (str_jump)
			cnt++;
		str += str_jump;
	}
	return (cnt);
}

char	*ft_split_cpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	size_t	i;
	size_t	str_jump;
	size_t	split_cnt;

	i = 0;
	str_jump = 0;
	split_cnt = ft_count_charset((char *)s, c);
	tmp = (char **)malloc(sizeof(char *) * (split_cnt + 1));
	if (!tmp)
		return (NULL);
	while (*s && i < split_cnt)
	{
		while (*s && *s == c)
			s++;
		str_jump = ft_strlen_str((char *)s, c);
		tmp[i] = ft_split_cpy(tmp[i], s, str_jump);
		if (!tmp[i])
			return (ft_error(tmp, i));
		s += str_jump;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}


t_lex *new_lexical(char *str)
{
    t_lex *new;

    new = (t_lex *)malloc(sizeof(t_lex));
    if (!new)
        return NULL;
    new->next = NULL;
    new->str = str;
    if (*str == '|')
        new->type = PIPE;
    //else if ((*str == '<') || (*str == '<<') || (*str == '>') || (*str == '>>'))
    else if ((*str == '<') || (*str == '>') )
        new->type = REDIRECTION;
    else if (*str == '\0')
        new->type = NULL_POINT;
    else
        new->type = WORD;
    
    return (new);
}

void add_back(t_lex **lst, t_lex *new)
{
    t_lex *tmp;

    tmp = *lst;
   if (lst == 0 || new == 0)
		return ;
	if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)-> next != NULL)
	{
		*lst = (*lst)-> next;
	}
	(*lst)-> next = new;
	*lst = tmp;
}

#include <stdio.h>

void display(t_lex *lexical)
{
    t_lex *tmp = lexical;
    while(tmp->next)
    {
        printf("%s : %d\n", tmp->str, tmp->type);
        tmp = tmp->next;
    }
}

void parsing(char *str)
{
    t_lex *lex;

    char **tmp;
    tmp = ft_split(str, ' ');
    if(!tmp)
        return ;

    int i = 0;
    while (tmp[i])
    {
        //if (tmp[i] == '\'' || tmp[i] == '\"')
        t_lex *new = new_lexical(tmp[i]);
        add_back(&lex, new);
        i++;
    }
    display(lex);
}

int main()
{
    char *str = "echo hello | a > b";
    parsing(str);
}
