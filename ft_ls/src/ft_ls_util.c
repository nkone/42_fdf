/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:15:05 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 19:40:47 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function open_print()
** Parameters:
**		[name]: name of path to be open
** Open a directory and print the contents inside
** Returns:
**		void.
*/

void	open_print(char *name)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;
	t_files			*ls;

	ls = NULL;
	if ((dir = opendir(name)) == NULL)
		ft_printf("ft_ls: %s: %s\n", name, strerror(errno));
	else
	{
		while ((dp = readdir(dir)) != NULL)
		{
			if (!file_ignored(dp->d_name))
			{
				path = path_to_file(name, dp->d_name);
				make_links(&ls, dp->d_name, path);
			}
		}
		closedir(dir);
	}
	ls_init_sort(&ls);
	ls_driver(ls);
	free_inner_dir(ls);
}

/*
** function print_directories()
** Parameters:
**		[f]: linked list contains name of directories
** Printing out the path of the directories follow by their contents
** Returns:
**		void.
*/

void	print_directories(t_files *f)
{
	while (f)
	{
		ft_printf("%s:\n", f->path);
		open_print(f->name);
		f = f->next;
		if (!f)
			break ;
		ft_putchar('\n');
	}
}

/*
** function ls_init_sort()
** Parameters:
**		[f]: double pointer to linked list contains content for sorting
** Sort by name first then sort by user select option
** Returns:
**		void.
*/

void	ls_init_sort(t_files **f)
{
	int s;

	s = sort_type;
	if (sort_type == sort_none)
		merge_sort_list(f);
	else
	{
		sort_type = sort_name;
		merge_sort_list(f);
		sort_type = s;
		merge_sort_list(f);
	}
}
