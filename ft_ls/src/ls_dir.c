/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:04:35 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/24 22:02:56 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function path_to_file
** Parameters:
** 		[path]: const char pointer string path from user
**		[file]: file name to be appended to path
** Takes in path and filename. Malloc a new string with 2 extra spaces: one for
** a '/' and another for '\0'. Copies path over then append the slash follow by
** file name.
** Returns: a string of full path with file name appended.
*/

char	*path_to_file(const char *path, const char *file)
{
	char	*result;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(path) + ft_strlen(file) + 1;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len] = '\0';
	while (*path)
		result[i++] = *path++;
	result[i++] = '/';
	while (*file)
		result[i++] = *file++;
	return (result);
}

/*
** function inner_dir
** Parameters:
**		[name]: directory name
** Opens a directory and store inside contents into a linked list
** Returns:
**		allocated linked list with all the inside contents;
*/

t_files	*inner_dir(const char *name)
{
	char			*pa;
	DIR				*dir;
	struct dirent	*dp;
	t_files			*ls;

	ls = NULL;
	pa = NULL;
	if ((dir = opendir(name)) == NULL)
	{
		printf("ft_ls: %s: %s\n", name, strerror(errno));
		return (NULL);
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (!file_ignored(dp->d_name))
		{
			pa = path_to_file(name, dp->d_name);
			make_links(&ls, dp->d_name, pa);
		}
	}
	closedir(dir);
	return (ls);
}

/*
** function free_inner_dir
** Paramters:
**		[f]: linked list contains contents of a directory
** Free name and path of a linked list
** Returns:
**		void.
*/

void	free_inner_dir(t_files *f)
{
	t_files *temp;

	while (f)
	{
		if (f->name)
			free(f->name);
		if (f->path)
			free(f->path);
		temp = f->next;
		free(f);
		f = temp;
	}
}

/*
** function print_dir()
** Parameters:
**		[f]: linked list contains contents of a directory
**		[flag]: flag to print new line befor path name
** Recursively open and print all sub directory in the linked list.
** Returns:
**		void.
*/

void	print_dir(t_files *f, int flag)
{
	t_files *in_dir;

	while (f)
	{
		if (S_ISDIR(f->fstat.st_mode) &&
		(ft_strcmp(f->name, ".") && ft_strcmp(f->name, "..")))
		{
			(flag) ?
			ft_printf("\n%s:\n", f->path) : ft_printf("%s:\n", f->path);
			in_dir = inner_dir(f->path);
			if (in_dir)
			{
				ls_init_sort(&in_dir);
				ls_driver(in_dir);
				if (is_empty_dir(in_dir))
					ft_putchar('\n');
				print_dir(in_dir, 1);
				free_inner_dir(in_dir);
			}
			flag = 1;
		}
		f = f->next;
	}
}
