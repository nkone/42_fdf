/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_boolean_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:44:08 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/23 17:07:39 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function is_exe()
** Paramters:
**		[stat]: stat structure in sys/stat.h
** Checks to see if the file is an executable
** Returns:
**		TRUE if the file is an executable and not a directory
**		FALSE otherwise.
*/

bool	is_exe(t_stat stat)
{
	return (!S_ISLNK(stat.st_mode) && !S_ISDIR(stat.st_mode)
			&& (stat.st_mode & S_IXUSR || stat.st_mode & S_IXGRP
			|| stat.st_mode & S_IXOTH)) ? true : false;
}

/*
** function is_empty_dir()
** Paramters:
**		[f]: linked list contains dir contents
** Checks if the directory is empty of files
** Returns:
**		TRUE if dir is empty of files
**		FALSE otherwise.
*/

bool	is_empty_dir(t_files *f)
{
	while (f)
	{
		if (ft_strcmp(f->name, ".") && ft_strcmp(f->name, ".."))
			return (false);
		f = f->next;
	}
	return (true);
}

/*
** function file_ignored
** Parameters:
** 		[filename] : name of file to check
** Checks if the file should be ignored before adding to list.
** Returns:
**		TRUE if should be ignored.
**		FALSE otherwise
*/

bool	file_ignored(const char *filename)
{
	return ((ignore_mode != MINIMAL && filename[0] == '.'
	&& (ignore_mode == DEFAULT || !filename[1 + (filename[1] == '.')])));
}

/*
** function is_regular_file()
** Paramters:
**		[path]: path of file
** Check if the file is not a directory
** Returns:
**		TRUE if not a dir
**		FALSE otherwise
*/

bool	is_regular_file(const char *path)
{
	t_stat stat;

	if (lstat(path, &stat) < 0)
		return (false);
	return (!(S_ISDIR(stat.st_mode)) ? true : false);
}

/*
** function is_regular_dir()
** Parameters:
**		[path]: path of a directory
** Checks if the path is a directory
** Returns:
**		TRUE if a dir
**		FALSE otherwise
*/

bool	is_regular_dir(const char *path)
{
	t_stat stat;

	if (lstat(path, &stat) < 0)
		return (false);
	return ((S_ISDIR(stat.st_mode)) ? true : false);
}
