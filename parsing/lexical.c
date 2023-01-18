#include "parsing.h"

t_tree *new_lexical(char *str)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		return NULL;
	new->prev = NULL;
	new->next = NULL;
	new->left = NULL;
	new->right = NULL;
	new->str = str;
	if (*str == '|')
		new->type = PIPE;
	else if (*str == '<')
	{
		if (*(str + 1) != '\0' && *(str + 1) == '<')
			new->type = HEREDOC;
		else
			new->type = IN_REDIRECT;
	}
	else if (*str == '>')
	{
		if (*(str + 1) != '\0' && *(str + 1) == '>')
			new->type = DOUBLE_OUT_REDIRECT;
		else
			new->type = OUT_REDIRECT;
	}
	else if (*str == '\0')
		new->type = NULL_POINT;
	else
		new->type = WORD;
	return (new);
}

void add_back(t_tree **lst, t_tree *new)
{
	t_tree *tmp;

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
	new->prev = *lst;
	(*lst)-> next = new;
	*lst = tmp;
}

#include <stdio.h> //

void display(t_tree *tree)
{
	t_tree *tmp;
	
	tmp = tree;
	while(tmp)
	{
		printf("%s : %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void display_syntax(t_tree *tree)
{
	if (tree)
	{
		display_syntax(tree->left);
		printf("%s\n", tree->str);
		display_syntax(tree->right);

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
	else if (c == '<')
		return IN_REDIRECT;
	else if (c == '>')
		return OUT_REDIRECT;
	return 0;
}

void init_flag(t_flag *flag)
{
	flag->big_quote = 0;
	flag->small_quote = 0;
}

void	lexical(char *str)
{
	t_tree	*tree;
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
				add_back(&tree, new_lexical(ft_substr(str, start, end)));
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
				add_back(&tree, new_lexical(ft_substr(str, start, end)));
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
				add_back(&tree, new_lexical(ft_substr(str, start, end)));
				start = end - 1;
				i += end + 1;
			}
			else
				flag.big_quote = -1;
			
		}
		else if (check_str(str[i]) == IN_REDIRECT)
		{
			if (start != i)
			{
				end = ft_indexof(str + start, '<');
				add_back(&tree, new_lexical(ft_substr(str, start, end)));
				start = end;
			}
			if (str[i + 1] != '\0' && str[i + 1] == '<')
			{
				add_back(&tree, new_lexical(ft_substr(str, i, 2)));
				start++;
				i++;
			}
			else
				add_back(&tree, new_lexical(ft_substr(str, i, 1)));
			start++;
		}
		else if (check_str(str[i]) == OUT_REDIRECT)
		{
			if (start != i)
			{
				end = ft_indexof(str + start, '>');
				add_back(&tree, new_lexical(ft_substr(str, start, end)));
				start = end;
			}
			if (str[i + 1] != '\0' && str[i + 1] == '>')
			{
				add_back(&tree, new_lexical(ft_substr(str, i, 2)));
				start++;
				i++;
			}
			else
				add_back(&tree, new_lexical(ft_substr(str, i, 1)));
			start++;
		}
		i++;
	}
	
	if (flag.small_quote == -1 || flag.big_quote == -1)
		printf("quote error\n");

	display(tree);
	t_tree *tmp;
	tmp = tree;
	while (tmp->next != NULL)
		tmp = tmp->next;
	t_tree *result = syntax(tree, tmp);
	display_syntax(result);
}

int main()
{
	char *str = "ls > a | grep ";
	lexical(str);
}
