/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:36:36 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 19:14:24 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function print_mode()
** Paramters:
**		[mode]: a number with mode assigned in by bitwise
**		[path]: path to file or directories
** Collects the mode and store them in the buffer to print
** Returns:
**		void.
*/

void	print_mode(int mode, char *path)
{
	char buf[12];

	buf[0] = get_file_type(mode);
	buf[1] = (mode & S_IRUSR) ? 'r' : '-';
	buf[2] = (mode & S_IWUSR) ? 'w' : '-';
	buf[3] = (mode & S_IXUSR) ? 'x' : '-';
	buf[4] = (mode & S_IRGRP) ? 'r' : '-';
	buf[5] = (mode & S_IWGRP) ? 'w' : '-';
	buf[6] = (mode & S_IXGRP) ? 'x' : '-';
	buf[7] = (mode & S_IROTH) ? 'r' : '-';
	buf[8] = (mode & S_IWOTH) ? 'w' : '-';
	buf[9] = (mode & S_IXOTH) ? 'x' : '-';
	if (mode & S_ISUID)
		buf[3] = (buf[3] == '-') ? 'S' : 's';
	if (mode & S_ISGID)
		buf[6] = (buf[6] == '-') ? 'S' : 's';
	if (mode & S_ISVTX)
		buf[9] = (buf[9] == '-') ? 'T' : 't';
	buf[10] = get_acl_exe(path);
	buf[11] = '\0';
	ft_printf("%s ", buf);
}

/*
** function print_classify()
** Paramters:
**		[p]: struct t_pcol for p.max
**		[f]: linked list with contents
** Handles printing classify cases, expand the width correctly if there is a
** classify character
** Returns:
**		void.
*/

void	print_classify(t_pcol p, t_files *f)
{
	if (!(indicator_style == none))
	{
		ft_printf("%s%s"P_NC, f->color, f->name);
		if (!f->style)
			ft_printf("%-*c", p.max - ft_strlen(f->name) + 2, f->style);
		else
			ft_printf("%-*c", p.max - ft_strlen(f->name) + 1, f->style);
	}
	else if (!g_print_inode)
		ft_printf("%s%-*s"P_NC, f->color, p.max + 1, f->name);
	else if (g_print_inode)
		ft_printf("%s%-*s"P_NC, f->color, (p.max + 1) -
				(count_nbr(f->fstat.st_ino) + 1), f->name);
}

/*
** function print_usr_grp()
** Parameters:
**		[i]: struct t_idx, for max width
**		[f]: linked list with contents
** A helper function to point group and user ID, if g_numeric_id is true
** then print them as number instead
** Returns:
**		void.
*/

void	print_usr_grp(t_idx i, t_files *f)
{
	if (g_numeric_id)
	{
		ft_printf("%-*d ", i.usr_w + 1, f->fstat.st_uid);
		ft_printf("%-*d ", i.grp_w + 1, f->fstat.st_gid);
	}
	else
	{
		ft_printf("%-*s ", i.usr_w + 1, getpwuid(f->fstat.st_uid)->pw_name);
		ft_printf("%-*s ", i.grp_w + 1, getgrgid(f->fstat.st_gid)->gr_name);
	}
}

/*
** function print_long_name()
** Parameters:
**		[f]: linked list with contents
** Print name of the file after all columns are printed
** Returns:
**		void.
*/

void	print_long_name(t_files *f)
{
	char link[NAME_MAX + 1];

	if (S_ISLNK(f->fstat.st_mode))
	{
		ft_bzero(link, NAME_MAX + 1);
		readlink(f->path, link, NAME_MAX);
		ft_printf("%s%s"P_NC"%c -> %s\n", f->color, f->name, f->style, link);
	}
	else
		ft_printf("%s%s"P_NC"%c\n", f->color, f->name, f->style);
}

/*
** function print_time()
** Parameters:
**		[f]: linked list with contents
** Print time columns in long format. ctime_r requires buffer to be minimum 26.
** Returns:
**		void.
*/

void	print_time(t_files *f)
{
	time_t		t;
	struct tm	t_info;
	char		buf[26];

	t = f->fstat.st_mtime;
	localtime_r(&t, &t_info);
	if (!check_timestamp(t_info))
		print_year(ctime_r(&t, buf));
	else
		print_date_time(ctime_r(&t, buf));
}
