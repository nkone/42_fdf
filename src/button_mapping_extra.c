/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_mapping_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:22:26 by phtruong          #+#    #+#             */
/*   Updated: 2019/08/30 13:00:29 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

void	handle_extra_button(int x, int y, t_fdf *fdf)
{
	if (x >= WIN_W / 30 && x <= WIN_W / 30 + 46 &&
		y >= WIN_H / 30 + 5 && y <= WIN_H / 30 + 20)
		exit(0);
	if (x >= WIN_W / 30 && x <= WIN_W / 30 + 160 &&
		y >= WIN_H - 45 && y <= WIN_H - 30 && fdf->cam.after_img == true)
	{
		fdf->cam.after_img = false;
		fdf->cam.brightness = 0;
	}
	else if (x >= WIN_W / 30 && x <= WIN_W / 30 + 160 &&
		y >= WIN_H - 45 && y <= WIN_H - 30 && fdf->cam.after_img == false)
		fdf->cam.after_img = true;
}
