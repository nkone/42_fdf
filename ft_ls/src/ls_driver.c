/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_driver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:28:50 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 19:06:16 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function print_long()
** Parameters:
**		[ls]: linked list with contents to be printed in long format
** Print ls in long format
** Returns:
**		void.
*/

void	print_long(t_files *ls)
{
	t_idx i;

	ft_bzero(&i, sizeof(t_idx));
	index_details(ls, &i);
	while (ls)
	{
		if (g_print_inode)
			ft_printf("%-*llu ", i.ino_w, ls->fstat.st_ino);
		print_mode(ls->fstat.st_mode, ls->path);
		ft_printf("%*u ", i.lin_w, ls->fstat.st_nlink);
		print_usr_grp(i, ls);
		if (S_ISCHR(ls->fstat.st_mode) || S_ISBLK(ls->fstat.st_mode))
		{
			ft_printf("%*d,", i.maj_w + 1, major(ls->fstat.st_rdev));
			ft_printf("%*d ", i.min_w + 1, minor(ls->fstat.st_rdev));
		}
		else
			ft_printf("%*d ", i.siz_w, ls->fstat.st_size);
		print_time(ls);
		print_long_name(ls);
		ls = ls->next;
	}
}

/*
** funciton print_list()
** Paramters:
**		[f]: linked list of contents to be printed in one per line format
** Print one per line
** Returns:
**		void.
*/

void	print_list(t_files *f)
{
	while (f)
	{
		if (g_print_inode)
			ft_printf("%llu ", f->fstat.st_ino);
		ft_printf("%s%s"P_NC"%c\n", f->color, f->name, f->style);
		f = f->next;
	}
}

/*
** function print_with_commas()
** Parameters:
**		[ls]: linked list of contents to be printed with commas
** Prints ls with comma separators
** Returns:
**		void.
*/

void	print_with_commas(t_files *ls)
{
	int				width;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	width = 0;
	while (ls)
	{
		ft_printf("%s%s"P_NC, ls->color, ls->name);
		if (indicator_style == classify)
			width += ft_printf("%c", ls->style);
		width += ft_strlen(ls->name);
		if (ls->next)
		{
			width += ft_printf(", ") - ((indicator_style == classify) ? 1 : 0);
			if ((width + ft_strlen(ls->next->name) + 1) >= w.ws_col)
			{
				ft_printf("\n");
				width = 0;
			}
		}
		ls = ls->next;
	}
	ft_putchar('\n');
}

/*
** function print_columns()
** Parameters:
**		[p]: struct t_pcol with all info needed to print in columns
** Print ls in columns format
** Returns:
**		void.
*/

void	print_columns(t_pcol p)
{
	t_files	*f;
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 0;
	while (x < p.row)
	{
		(format == many_per_line) && (i = x);
		j = 0;
		while (j < p.col && i < p.no_f)
		{
			f = g_sorted_file[i];
			(g_print_inode) && ft_printf("%llu ", f->fstat.st_ino);
			print_classify(p, f);
			i += (format == many_per_line) ? p.row : 1;
			j++;
		}
		ft_printf("\n");
		x++;
	}
}

/*
** function ls_driver()
** Paramters:
**		[ls]: linked list with contents to be printed
** A mini jump "table" to handle different format cases
** Returns:
** 		void.
*/

void	ls_driver(t_files *ls)
{
	t_pcol			p;
	struct winsize	w;

	if (format == long_format)
		print_long(ls);
	else if (format == one_per_line)
		print_list(ls);
	else if (format == with_commas)
		print_with_commas(ls);
	else if (format == many_per_line || format == horizontal)
	{
		ioctl(0, TIOCGWINSZ, &w);
		col_format(ls, &p, w.ws_col);
		ls_list_globalize(ls, p);
		print_columns(p);
		free(g_sorted_file);
	}
}
