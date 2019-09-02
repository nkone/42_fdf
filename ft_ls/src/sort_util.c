/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:09:55 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 20:10:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function cmp_alpha()
** Parameters:
**		[s1]: string 1
**		[s2]: string 2
** Uses strcmp to sort ascending or descending base on global sort reverse bool
** Returns:
**		1 if true, 0 otherwise
*/

int	cmp_alpha(const char *s1, const char *s2)
{
	if (!g_sort_reverse)
		return (ft_strcmp(s1, s2) < 0);
	return (ft_strcmp(s1, s2) > 0);
}

/*
** function casecmp_alpha()
** Parameters:
**		[s1]: string 1
**		[s2]: string 2
** Uses ft_strcasecmp to compare string not case sensitive, STRING = string
** Returns:
**		1 if true, 0 otherwise
*/

int	casecmp_alpha(const char *s1, const char *s2)
{
	if (!g_sort_reverse)
		return (ft_strcasecmp(s1, s2) < 0);
	return (ft_strcasecmp(s1, s2) > 0);
}

/*
** function cmp_time()
** Paramters:
**		[a]: time since epoch a
**		[b]: time since Epoch b
** Checks time between a and b depending on global sort reverse bool
** Returns:
**		1 if true, 0 otherwise
*/

int	cmp_time(t_files *a, t_files *b)
{
	if (!g_sort_reverse)
	{
		if (a->fstat.st_mtimespec.tv_sec == b->fstat.st_mtimespec.tv_sec)
			return (a->fstat.st_mtimespec.tv_nsec >=
					b->fstat.st_mtimespec.tv_nsec);
			return (a->fstat.st_mtime > b->fstat.st_mtime);
	}
	else
	{
		if (a->fstat.st_mtimespec.tv_sec == b->fstat.st_mtimespec.tv_sec)
			return (a->fstat.st_mtimespec.tv_nsec <=
					b->fstat.st_mtimespec.tv_nsec);
			return (a->fstat.st_mtime < b->fstat.st_mtime);
	}
}

/*
** function cmp_size()
** Paramters:
**		[a]: file size a;
**		[b]: file size b;
** Checks size between a and b depending on global sort reverse bool
** Returns:
**		1 if true, 0 otherwise
*/

int	cmp_size(off_t a, off_t b)
{
	if (!g_sort_reverse)
		return (a >= b);
	return (a <= b);
}

/*
** function select_sort()
** Paramaters:
**			[a]: pointer to struct t_files
**			[b]: pointer to struct t_files
** Select which type of sort base on global sort type
** Returns:
**		Return value of appropriate compare function, 0 if sort_type == none
*/

int	select_sort(t_files *a, t_files *b)
{
	if (sort_type == sort_name)
		return (cmp_alpha(a->name, b->name));
	else if (sort_type == sort_time)
		return (cmp_time(a, b));
	else if (sort_type == sort_size)
		return (cmp_size(a->fstat.st_size, b->fstat.st_size));
	else if (sort_type == sort_none)
		return (casecmp_alpha(a->name, b->name));
	return (1);
}
