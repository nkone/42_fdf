/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:52:46 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 19:16:38 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function get_color()
** Paramters:
**		[stat]: struct stat from stat lib
** Select a MACRO from ft_ls.h for color base on file attribute
** Returns:
**		a MACRO for shell color, empty string if just normal file.
*/

char	*get_color(t_stat stat)
{
	if (S_ISSOCK(stat.st_mode))
		return (P_GREEN);
	else if (is_exe(stat))
	{
		if ((stat.st_mode & S_ISUID) || (stat.st_mode & S_ISGID))
			return (P_REVERSE);
		else
			return (P_RED);
	}
	else if (S_ISDIR(stat.st_mode))
		return (P_CYAN);
	else if (S_ISLNK(stat.st_mode))
		return (P_MAGENTA);
	else
		return ("");
}

/*
** function get_style()
** Parameters:
**		[stat]: struct stat from stat lib
** Select a corresponding char base on file attribute if indicator_style is
** classify (for -F) or slash (for -p), nul if indicator_style is none
** Returns:
**		corresponding char, based on file attributes and indicator style
*/

char	get_style(t_stat stat)
{
	if (indicator_style == classify)
	{
		if (is_exe(stat))
			return ('*');
		else if (S_ISDIR(stat.st_mode))
			return ('/');
		else if (S_ISLNK(stat.st_mode))
			return ('@');
	}
	if (indicator_style == slash)
	{
		if (S_ISDIR(stat.st_mode))
			return ('/');
	}
	return ('\0');
}

/*
** function get_file_type()
** Parameters:
**		[mode]: mode value from struct stat
** Select the file type using struct stat MACROS
** Returns:
**		corresponding char, base on MACROS return
*/

char	get_file_type(int mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

/*
** function get_acl_exe()
** Parameters:
**		[path]: path of file or folder
** Find corresponding char base on extended ACL
** Returns:
** 		corresponding char, base on return of listxattri and acl_get_link_np
*/

char	get_acl_exe(char *path)
{
	acl_t acl;

	acl = NULL;
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}
