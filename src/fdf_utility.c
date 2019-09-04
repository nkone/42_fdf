/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:19:25 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/02 19:59:45 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

int		abort_fdf(void)
{
	if (errno == 0)
		ft_printf(FDF_ABORT_MESSAGE);
	else
		perror("Error");
	exit(1);
	return (1);
}

void	delay(int milliseconds)
{
	unsigned long	pause;
	clock_t			now;
	clock_t			then;

	pause = milliseconds * (CLOCKS_PER_SEC / 1000);
	then = clock();
	now = then;
	while ((now - then) < pause)
		now = clock();
}
