/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:07:03 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/24 22:02:31 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function free_list_argv()
** Parameters:
**		[f]: linked list of argv
** Free nodes in linked list, free name (as name was added with ft_strdup)
** Returns:
**		void.
*/

void	free_list_argv(t_files *f)
{
	t_files *temp;

	while (f)
	{
		if (f->name)
			free(f->name);
		temp = f->next;
		free(f);
		f = temp;
	}
}

/*
** function parse_multi_argv()
** Parameters:
**		[argc]: argument counter
**		[argv]: pointer to array of char
**		[files]: double pointer to struct t_files
**		[dir]: doulbe pointer to struct t_files
** Takes then the address of the pointer and allocate the linked list according.
** files will be a linked list of files, and dir will be a linked list of
** directories.
** Returns:
**		void.
*/

void	parse_multi_argv(int argc, char *argv[], t_files **files, t_files **dir)
{
	int		i;
	t_stat	stat;

	i = g_argc;
	while (i < argc)
	{
		if (lstat(argv[i], &stat) < 0)
			ft_printf("ft_ls: %s: %s\n", argv[i], strerror(errno));
		else
		{
			if (is_regular_file(argv[i]))
				make_links(files, argv[i], argv[i]);
			else
				make_links(dir, argv[i], argv[i]);
		}
		i++;
	}
}

/*
** function multi_argv()
** Paramters:
**		[argc]: argument counter
**		[argv]: pointer to array of char
** Handles multi arguments in main. Split the arguments into files and
** directories and sort them with merge sort. Print files first with given
** settings and then print directories.
** Returns:
**		void.
*/

void	multi_argv(int argc, char *argv[])
{
	t_files *files;
	t_files *dir;

	files = NULL;
	dir = NULL;
	parse_multi_argv(argc, argv, &files, &dir);
	ls_init_sort(&files);
	ls_init_sort(&dir);
	(files) && (g_print_total = false);
	ls_driver(files);
	g_print_total = true;
	(files && dir) && ft_putchar('\n');
	if (!g_recursive)
		print_directories(dir);
	if (g_recursive)
		print_dir(dir, 0);
	free_list_argv(files);
	free_list_argv(dir);
}

/*
** function single_argv()
** Paramters:
**		[str]: a string, name of file or directory to handle
** Creates a single node and print file name only if given parameter is a file
** Handles directory printing if parameter is a directory.
** Returns:
**		void.
*/

void	single_argv(char *str)
{
	t_files *ls;

	ls = NULL;
	make_links(&ls, str, str);
	if (is_regular_file(ls->name))
		ft_printf("%s%s"P_NC"%c\n", ls->color, ls->name, ls->style);
	else
		open_print(ls->name);
	free_list_argv(ls);
	if (g_recursive && !is_regular_file(str))
	{
		ls = inner_dir(str);
		if (ls)
		{
			ls_init_sort(&ls);
			print_dir(ls, 1);
			free_inner_dir(ls);
		}
	}
}

/*
** function main()
** Parameters:
**		[argc]: argument counter
**		[argv]: pointer to array of char
** Main function of ls, handles differently depending on global starting
** argument
** Returns:
**		0 if success;
*/

int		main(int argc, char *argv[])
{
	ft_ls_init();
	if (argc > 1)
		flag_driver(argc, argv);
	if (g_argc && (g_argc < (argc - 1)))
		multi_argv(argc, argv);
	else if (g_argc && ((argc - g_argc) == 1))
		single_argv(argv[g_argc]);
	else if (!g_argc)
		single_argv(".");
	return (0);
}
