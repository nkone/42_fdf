/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:04:04 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/23 18:41:41 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function max()
** Parameters:
**		[a]: integer a
**		[b]: integer b
** Check between a and b to see which one is larger
** Returns:
**		a if larger than b
**		b otherwise.
*/

int		max(int a, int b)
{
	return ((a > b) ? a : b);
}

/*
** function count_nbr()
** Paramters:
**		[n]: integer n
** Count length of a number
** Returns:
**		len of an integer
*/

int		count_nbr(int n)
{
	int c;

	c = 1;
	if (!n)
		return (1);
	while (n /= 10)
		c++;
	return (c);
}

/*
** function get_usr_w()
** Parameters:
**		[w]: width of previous usr id
**		[u]: signed integer for usr id
** Get the current biggest width for user id. Count integer length if
** g_numeric_id is active. Uses ft_strlen instead if otherwise.
** Returns:
**		current biggest width.
*/

int		get_usr_w(int w, uid_t u)
{
	if (g_numeric_id)
		w = max(count_nbr(u), w);
	else
		w = max(ft_strlen(getpwuid(u)->pw_name), w);
	return (w);
}

/*
** function get_grp_w()
** Parameters:
**		[w]: width of previous grp id
**		[g]: signed integer for grp ip
** Get the current biggest width for group id. Count integer length if
** g_numeric_id is active. Uses ft_strlen isntead if otherwise.
** Returns:
**		current biggest width.
*/

int		get_grp_w(int w, gid_t g)
{
	if (g_numeric_id)
		w = max(count_nbr(g), w);
	else
		w = max(ft_strlen(getgrgid(g)->gr_name), w);
	return (w);
}

/*
** function index_details
** Paramters:
**		[ls]: linked list to all contents to be indexed
**		[i]: pointer to indexing struct
** Goes through the list and grab max length of each blocks for column printing
** Returns:
**		void.
*/

void	index_details(t_files *ls, t_idx *i)
{
	int		total;
	t_files *p_ls;

	total = 0;
	p_ls = ls;
	while (ls)
	{
		total += ls->fstat.st_blocks;
		i->ino_w = max(count_nbr(ls->fstat.st_ino), i->ino_w);
		i->lin_w = max(count_nbr(ls->fstat.st_nlink), i->lin_w);
		i->usr_w = get_usr_w(i->usr_w, ls->fstat.st_uid);
		i->grp_w = get_grp_w(i->grp_w, ls->fstat.st_gid);
		i->siz_w = max(count_nbr(ls->fstat.st_size), i->siz_w);
		if (S_ISCHR(ls->fstat.st_mode) || S_ISBLK(ls->fstat.st_mode))
		{
			i->maj_w = max(count_nbr(major(ls->fstat.st_rdev)), i->maj_w);
			i->min_w = max(count_nbr(minor(ls->fstat.st_rdev)), i->min_w);
			i->siz_w = max(i->maj_w + i->min_w + 2, i->siz_w);
		}
		ls = ls->next;
	}
	if (p_ls && g_print_total)
		ft_printf("total %d\n", total);
}
