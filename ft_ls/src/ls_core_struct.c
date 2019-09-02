/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:43:35 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/05 14:35:51 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function make_node()
** Parameters:
**		[ls]: double pointer to struct t_files
**		[name]: name of file
**		[path]: path of file
** Create a node for struct t_files. A support function for make_links.
** Cannot be used as standalone function.
** Returns:
**		void
*/

void	make_node(t_files **ls, char *name, char *path)
{
	t_stat stat;

	*ls = malloc(sizeof(t_files));
	(*ls)->name = ft_strdup(name);
	lstat(path, &stat);
	(*ls)->path = path;
	(*ls)->color = get_color(stat);
	(*ls)->fstat = stat;
	(*ls)->next = NULL;
	(*ls)->style = get_style(stat);
}

/*
** function make_links()
** Parameters:
**		[ls]: double pointer to struct t_files
**		[name]: name of file
**		[path]: path of file
** Main function to create linked list, automatically append if the head is
** not NULL.
** Returns:
**		void.
*/

void	make_links(t_files **ls, char *name, char *path)
{
	t_files *cursor;

	if (!*ls)
		make_node(ls, name, path);
	else if (*ls)
	{
		cursor = *ls;
		while (cursor->next)
			cursor = cursor->next;
		make_node(&(cursor->next), name, path);
	}
}

/*
** function split_list()
** Parameters:
**		[source]: main list to be split
**		[front]: double pointer for front of list
**		[back]: double pointer for back of list
** Split the list into half. Front points to head of list, back points to
** middle. If list has odd elements, front will get one extra.
** Returns:
**		void.
*/

void	split_list(t_files *source, t_files **front, t_files **back)
{
	t_files *fast;
	t_files *slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

/*
** function sorted_merge()
** Parameters:
**		[a]: node a (front of list)
**		[b]: node b (back of list)
**		[cmp]: a compare function chosen by merge_sort_list();
** Takes in front and back of list in two separate parameters and compare them
** node by node. The next node is the result of the function recursively call
** with updated node.
** Returns:
**		head of the list (front or back).
*/

t_files	*sorted_merge(t_files *a, t_files *b, int (*cmp)())
{
	t_files *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (cmp(a, b))
	{
		result = a;
		result->next = sorted_merge(a->next, b, cmp);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, cmp);
	}
	return (result);
}

/*
** function merge_sort_list()
** Parameters:
**		[ls]: double pointer to struct t_files
** Recursive implementation of merge sort.
** Returns:
**		void.
*/

void	merge_sort_list(t_files **ls)
{
	t_files *head;
	t_files *a;
	t_files *b;

	head = *ls;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	merge_sort_list(&a);
	merge_sort_list(&b);
	*ls = sorted_merge(a, b, select_sort);
}
