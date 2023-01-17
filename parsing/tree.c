#include "parsing.h"

//데이터 삽입
t_tree	*insert(t_tree *node, int data)
{
	if (node == NULL)
	{
		t_tree *newNode = (t_tree *)malloc(sizeof(t_tree));
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		return (newNode);
	}
	if (node->data > data)
		node->left = insert(node->left, data);
	else if (node->data < data)
		node ->right = insert(node->right, data);
    //node->data == data는 중복된 데이터이므로 추가하지 않음

	return (node);
}

//데이터 수정
void modify(t_tree *node, int data, int newData)
{
	if (node == NULL)
		return ;
	if (node -> data == data)
		node->data = newData;
	else
	{
		if (node->data > data)
			modify(node->left, data, newData);
		else
			modify(node->right, data, newData);
	}
}

//데이터 탐색
t_tree *search(t_tree *node, int data)
{
	if (node == NULL)
		return NULL;
	if (node->data == data)
		return node;
	else
	{
		if (node->data > data)
			return search(node->left, data);
		else
			return search(node->right, data);
	}
}

//데이터 삭제

t_tree *findMinNode(t_tree *node, t_tree **minNode)
{
	if (node->left == NULL)
	{
		*minNode = node;
		node = node->right;
		return node;
	}
	else
	{
		node->left = 
	}
}