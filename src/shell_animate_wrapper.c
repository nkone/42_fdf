/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_animate_wrapper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:37:03 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/07 18:45:09 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	free_fdf_queue(t_files *queue)
{
	t_files *tmp;
	t_files *head;

	head = queue;
	if (queue)
	{
		queue = queue->next;
		while (queue != head)
		{
			tmp = queue->next;
			free(queue->name);
			free(queue->path);
			free(queue);
			queue = tmp;
		//	puts("free");
		}
		free(head->name);
		free(head->path);
		free(head);
	}
//	free(head->name);
//	free(head->path);
//	free(head);
	//puts("end free");
	queue = NULL;
}

static void	circular_double(t_files **head)
{
	t_files *start;
	t_files *cursor;

	start = *head;
	cursor = *head;
	while (cursor->next)
		cursor = cursor->next;
	(*head)->prev = cursor;
	while ((*head)->next)
		*head = (*head)->next;
	(*head)->next = start;
	*head = start;
}

static void	print_parsed_files(t_files *list)
{
	while (list)
	{
		ft_printf("successfully parsed: %s\n", list->path);
		list = list->next;
	}
}

void		shell_animate_wrapper(char **input, t_fdf *fdf)
{
	int		no;
	t_files	*tmp;

	no = count_arr_width(input);
	if (no < 2 || no > 2)
		ft_printf("animate [path to folder of .fdf]\n");
	else
	{
		if (fdf->fdf_queue)
			free_fdf_queue(fdf->fdf_queue);
		fdf->fdf_queue = read_multi_fdf(input[1]);
		fdf->multi_fdf = true;
		tmp = fdf->fdf_queue;
		if (tmp)
		{
			print_parsed_files(tmp);
			circular_double(&(fdf->fdf_queue));
		}
		else
			ft_printf("Error parsing: empty list\n");
	}
	free_input(input);
}
