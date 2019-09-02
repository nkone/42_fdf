/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:43:46 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:03:55 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	create_arr_node(t_read **head, char **block)
{
	*head = malloc(sizeof(t_read));
	(*head)->arr = block;
	(*head)->next = NULL;
}

void	link_arr_node(t_read **head, char **block)
{
	t_read	*cursor;

	if (!*head)
		create_arr_node(head, block);
	else
	{
		cursor = *head;
		while (cursor->next)
			cursor = cursor->next;
		create_arr_node(&(cursor->next), block);
	}
}

int		*parse_fdf(int fd, t_fdf *fdf)
{
	char	*line;
	char	**arr;
	int		*map;
	t_read	*read;

	line = NULL;
	arr = NULL;
	read = NULL;
	map = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		arr = ft_strsplit(line, ' ');
		link_arr_node(&read, arr);
		free(line);
	}
	if (read)
		map = map_coord(read, fdf);
	else
		abort_fdf();
	return (map);
}
