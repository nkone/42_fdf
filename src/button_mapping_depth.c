/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_button_mapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:09:44 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:00:02 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	handle_depth_button(int x, int y, t_fdf *fdf)
{
	double h;

	h = 1.88;
	if (x >= WIN_W / 30 + 84 && x <= WIN_W / 30 + 117 &&
		y >= WIN_H / h + 5 && y <= WIN_H / h + 20)
	{
		ft_printf("Depth turned: ON\n");
		fdf->cam.depth = true;
	}
	if (x >= WIN_W / 30 + 152 && x <= WIN_W / 30 + 194 &&
		y >= WIN_H / h + 5 && y <= WIN_H / h + 20)
	{
		ft_printf("Depth turned: OFF\n");
		fdf->cam.depth = false;
	}
}
