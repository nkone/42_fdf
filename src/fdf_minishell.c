/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:27:36 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/01 17:14:40 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	shell_in(t_fdf *fdf)
{
	char *line;
	char **input;

	line = NULL;
	while (1)
	{
		ft_printf(P_FG_256_154"phtruong@42us_fdf_minishell: "P_NC);
		get_next_line(1, &line);
		input = ft_strsplit(line, ' ');
		free(line);
		if (!check_input(input, fdf))
			break ;
	}
}

void	shell_help(char **input)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(FDF_SHELL_HELP_PATH, O_RDONLY);
	if (fd > 0)
	{
		while (get_next_line(fd, &line) == 1)
		{
			ft_printf("%s\n", line);
			free(line);
		}
	}
	else
		perror("Check shell_help.txt in read_me folder");
	close(fd);
	free_input(input);
}

int		check_input(char **input, t_fdf *fdf)
{
	if (ft_strcasecmp(input[0], "change") == 0)
		shell_change_wrapper(input, fdf);
	else if (ft_strcasecmp(input[0], "info") == 0)
		shell_info_wrapper(fdf);
	else if (ft_strcasecmp(input[0], "resume") == 0)
	{
		free_input(input);
		return (0);
	}
	else if (ft_strcasecmp(input[0], "ls") == 0)
		shell_ls_wrapper(input);
	else if (ft_strcasecmp(input[0], "animate") == 0)
		shell_animate_wrapper(input, fdf);
	else if (ft_strcasecmp(input[0], "help") == 0)
		shell_help(input);
	else if (ft_strcasecmp(input[0], "quit") == 0)
		exit(0);
	else
		free_input(input);
	return (1);
}

void	free_input(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		ft_strdel(&input[i]);
		i++;
	}
	free(input);
	input = NULL;
}
