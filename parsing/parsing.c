#include "parsing.h"
#include <string.h> //split용
#include <stdlib.h>

/*
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
*/
int	ft_indexof(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
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
	t_lex *tmp;
	
	tmp = lexical;
	while(tmp)
	{
		printf("%s : %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

int check_str(char c)
{
	if (c == ' ')
		return BLANK;
	else if (c == '\'')
		return SMALL_QUOTE;
	else if (c == '\"')
		return BIG_QUOTE;
	return 0;
}

void init_flag(t_flag *flag)
{
	flag->big_quote = 0;
	flag->small_quote = 0;
}

void	parsing(char *str)
{
	t_lex	*lex;
	int		i;
	int		start;
	int		end;
	t_flag	flag;

	init_flag(&flag);
	i = 0;
	start = 0;
	while (str[i])
	{
		if (check_str(str[i]) == BLANK)
		{
			end = ft_indexof(str + start, BLANK);
			if (str[start] != ' ') //공백 다음에 공백이 나오는 경우 대비
			{
				add_back(&lex, new_lexical(ft_substr(str, start, end)));
				if (str[i + 1] != '\0') //segfault 뜰 경우 대비
					start = i + 1;
			}
			else
				start++;
		}
		else if (check_str(str[i]) == SMALL_QUOTE)
		{
			start = i + 1;
			end = ft_indexof(str + i + 1, SMALL_QUOTE);
			if (str[i + 1] != '\0' && end != -1)
			{
				add_back(&lex, new_lexical(ft_substr(str, start, end)));
				start += end  + 1 ;
				i += end + 1;
			}
			else
				flag.small_quote = -1;
		}
		else if (check_str(str[i]) == BIG_QUOTE)
		{
			start = i + 1;
			end = ft_indexof(str + i + 1, BIG_QUOTE);
			if (str[i + 1] != '\0' && end != -1)
			{
				add_back(&lex, new_lexical(ft_substr(str, start, end)));
				start = end - 1;
				i += end + 1;
			}
			else
				flag.big_quote = -1;
			
		}
		i++;
	}
	
	if (flag.small_quote == -1 || flag.big_quote == -1)
		printf("quote error\n");

	display(lex);
}

int main()
{
	char *str = "\n hi test ";
	parsing(str);
}
