/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:00:30 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/21 15:56:47 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "ft_fdf.h"

// Goal is to return a 2D array with integers from fdf file


void	print_arr(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
	{
		printf("%s ", arr[i]);
		free(arr[i]);
	}
	free(arr);
	printf("total: %d", i);
	puts("");
}

int	count_arr_width(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_arr_width(t_read *read)
{
	int w;
	int prev_w;

	w = 0;
	perv_w = w;
	while (read)
	{
		w = count_arr_width(read->arr);
		if (!w || (prev_w && w != prev_w))
			return (0);
		prev_w = w;
		read = read->next;
	}
	return (w);
}

int		get_map_size(t_read *read)
{
	int map_w;
	int map_h;

	map_h = 0;
	map_w = check_arr_with(read);
	while (read)
	{
		map_h++;
		read = read->next;
	}
	return (map_w * map_h);
}

int		*map_coord(t_read *read)
{
	int *map;
	int i;
	int j;

	i = 0;
	map = malloc(sizeof(int) * get_map_size(read));
	while (read)
	{
		j = 0;
		while (read->arr[j])
			map[i++] = ft_atoi(read->arr[j++]);
		read = read->next;
	}
	return (map);
}
		
void	print_link_arr(t_read *read)
{
	t_read *temp;

	while (read)
	{
		temp = read;
		print_arr(read->arr);
		read = read->next;
		free(temp);
	}
}
void create_arr_node(t_read **head, char **block)
{
	*head = malloc(sizeof(t_read));
	(*head)->arr = block;
	(*head)->next = NULL;
}

void link_arr_node(t_read **head, char **block)
{
	t_read *cursor;

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
		
void parse_1(int fd)
{
	char *line;
	char **arr;
	t_read *read;
	line = NULL;
	arr = NULL;
	read = NULL;
	while (get_next_line(fd, &line))
	{
		arr = ft_strsplit(line, ' ');
		link_arr_node(&read, arr);
		free(line);
	}
	print_link_arr(read);
}

int main(int argc, char *argv[])
{
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error");
			return (-1);
		}
		parse_1(fd);
	}
	return (0);
}
