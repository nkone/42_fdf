/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:57:23 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/29 18:58:11 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "ft_fdf.h"
#include "libft/libft.h"
#include "libft/ft_printf.h"

int		check_input(char **input, t_fdf *fdf)
{
	if (ft_strcasecmp(input[0], "change") == 0)
		shell_change_wrapper(input, fdf);
	else if (ft_strcasecmp(input[0], "info") == 0)
		shell_info(fdf);
	else if (ft_strcasecmp(input[0], "resume") == 0)
	{
		free_input(input);
		return (0);
	}
	else if (ft_strcasecmp(input[0], "ls") == 0)
		shell_ls_wrapper(input);
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
