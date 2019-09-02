/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_col_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:56:10 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 16:22:49 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function col_format()
** Parameters:
**		[f]: linked list of contents
**		[p]: pointer to struct t_pcol (helper struct for printing columns)
**		[wcol]: current window columns from terminal
** Find the columns and row needed to be printed in.
** Returns:
**		void.
*/

void	col_format(t_files *f, t_pcol *p, unsigned short wcol)
{
	int len;

	len = 0;
	p->max = 0;
	p->no_f = 0;
	while (f)
	{
		len = (int)ft_strlen(f->name);
		len += !(indicator_style == none) ? 1 : 0;
		len += (g_print_inode) ? count_nbr(f->fstat.st_ino) + 1 : 0;
		p->max = (len > p->max) ? len : p->max;
		p->no_f += 1;
		f = f->next;
	}
	p->col = (wcol >= (p->max + 1)) ? (wcol / (p->max + 1)) : 1;
	p->row = (p->no_f % p->col) ? (p->no_f / p->col + 1) : (p->no_f / p->col);
}

/*
** function ls_list_globalize()
** Paramters:
**		[f]: linked list to be globalize via void pointer
**		[p]: struct t_pcol, to find total number of files for malloc
** Malloc the pointer with given number of files. By doing so, similar to array
** each node of the linked list can be access as an index.
** Returns:
**		void.
*/

void	ls_list_globalize(t_files *f, t_pcol p)
{
	int i;

	i = 0;
	g_sorted_file = malloc(sizeof(*g_sorted_file) * (p.no_f + 1));
	while (f)
	{
		g_sorted_file[i++] = f;
		f = f->next;
	}
	g_sorted_file[i] = NULL;
}
