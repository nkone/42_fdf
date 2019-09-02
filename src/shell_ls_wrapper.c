/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ls_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:55:17 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 14:04:25 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	shell_ls_wrapper(char **input)
{
	int	pid;
	int err;

	pid = fork();
	if (pid == 0)
		err = execve(LS_PATH, input, 0);
	else if (pid < 0)
	{
		perror("Error:");
		return ;
	}
	else
		wait(0);
	free_input(input);
}
