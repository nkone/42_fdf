/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:26:02 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/25 20:22:22 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function ft_ls_init()
** Parameters:
**		NONE
** Creates the initial settings for ft_ls.
** Settings here are default unless changed by collected flags.
** Returns:
**		void.
*/

void	ft_ls_init(void)
{
	format = many_per_line;
	sort_type = sort_name;
	indicator_style = none;
	g_sort_reverse = false;
	g_recursive = false;
	g_print_inode = false;
	g_numeric_id = false;
	g_print_total = true;
	ignore_mode = DEFAULT;
}

/*
** function get_flags()
** Parameters:
**		[argv]: char pointer to stream of argument values.
**		[c]: index to access a specific argument value.
** Parses through an argument, with given index (c), checks for illegal flags,
** alters settings for legal flags.
** Returns:
**			value of c if argument does not start with '-' follow by a character
** 			0 if success.
*/

int		get_flags(char *argv[], int c)
{
	int		i;
	char	*ref;

	i = 0;
	if (argv[c][i] == '-' && argv[c][i + 1] != '\0')
		i++;
	else if (argv[c][i])
		return (c);
	while (argv[c][i])
	{
		if (!(ref = ft_strchr(LS_FLAGS, argv[c][i])))
		{
			ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-%s]"
					" [file ...]\n", argv[c][i], LS_FLAGS);
			exit(1);
		}
		g_ls_flags[(ptrdiff_t)(ref - LS_FLAGS)]();
		i++;
	}
	return (0);
}

/*
** function flag_driver
** Parameters:
**		[argc]: total number of arguments in main
**		[argv]: char pointer to argument values
** Loop through all the arguments and update global starting argument.
** If argument consists of flags only, then starting argument will be zero
** as the get_flags() returns 0.
** Stop collecting flags when encounters a non flag argument.
** Returns:
**		void.
*/

void	flag_driver(int argc, char *argv[])
{
	int c;

	c = 0;
	while (++c <= (argc - 1))
	{
		g_argc = get_flags(argv, c);
		if (g_argc != 0)
			break ;
	}
}
