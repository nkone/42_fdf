/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_animate_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:13:42 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/02 16:31:33 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void		split_list(t_files *source, t_files **front, t_files **back)
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

static t_files	*sorted_merge(t_files *a, t_files *b)
{
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (ft_strcasecmp(a->name, b->name) < 0)
	{
		a->next = sorted_merge(a->next, b);
		a->next->prev = a;
		a->prev = NULL;
		return (a);
	}
	else
	{
		b->next = sorted_merge(a, b->next);
		b->next->prev = b;
		b->prev = NULL;
		return (b);
	}
}

void			shell_animate_sort(t_files **ls)
{
	t_files *head;
	t_files *a;
	t_files *b;

	head = *ls;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	shell_animate_sort(&a);
	shell_animate_sort(&b);
	*ls = sorted_merge(a, b);
}
