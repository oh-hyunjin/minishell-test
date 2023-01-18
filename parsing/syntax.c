#include "parsing.h"

t_tree *pipe_check(t_tree *start, t_tree *end)
{
	t_tree	*cur;

	cur = end;
	while (cur != start)
	{
		if (cur->type == PIPE)
			return (cur);
		cur = cur->prev;
	}
	if (cur->type == PIPE)
		return (cur);
	return (NULL);
}

t_tree *redirect_check(t_tree *start, t_tree *end)
{
	t_tree	*cur;

	cur = start;
	while (cur != end)
	{
		if (cur->type == IN_REDIRECT || cur->type == OUT_REDIRECT || \
		cur->type == DOUBLE_OUT_REDIRECT || cur->type == HEREDOC)
			return (cur);
		cur = cur->next;
	}
	if (cur->type == IN_REDIRECT || cur->type == OUT_REDIRECT || \
		cur->type == DOUBLE_OUT_REDIRECT || cur->type == HEREDOC)
		return (cur);
	return (NULL);
}

t_tree *syntax(t_tree *start, t_tree *end)
{
	t_tree	*root;

	if (start == end)
		return (start);
	root = pipe_check(start, end);
	if (root == NULL)
	{
		root = redirect_check(start, end);
	}
	root->left = syntax(start, root->prev);
	root->right = syntax(root->next, end);
	//리다이렉션이랑 파이프 없는 경우 처리해야함
	return (root);
}