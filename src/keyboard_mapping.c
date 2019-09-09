/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_mapping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:04:13 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/09 12:27:42 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	handle_esc_key(t_fdf *fdf)
{
	if (fdf->help)
		fdf->help = false;
	else
		exit(0);
}

static void	handle_zoom_key(int key, t_fdf *fdf)
{
	fdf->help = false;
	fdf->cam.zoom += (key == KEY_I) ?
		fdf->cam.zoom_accel : -fdf->cam.zoom_accel;
	if (fdf->cam.zoom < 3.0)
		fdf->cam.zoom = 3.0;
}

static void	handle_arrow_key(int key, t_fdf *fdf)
{
	fdf->help = false;
	if (key == KEY_L_ARROW)
		fdf->cam.x_offset -= 5;
	else if (key == KEY_R_ARROW)
		fdf->cam.x_offset += 5;
	else if (key == KEY_U_ARROW)
		fdf->cam.y_offset -= 5;
	else if (key == KEY_D_ARROW)
		fdf->cam.y_offset += 5;
}

static void	handle_multi_fdf(int key, t_fdf *fdf)
{
	if (key == KEY_W && fdf->multi_fdf)
	{
		delay(fdf->multi_delay);
		if (fdf->fdf_queue->next)
			fdf->fdf_queue = fdf->fdf_queue->next;
	}
	else if (key == KEY_Q && fdf->multi_fdf)
	{
		delay(fdf->multi_delay);
		if (fdf->fdf_queue->prev)
			fdf->fdf_queue = fdf->fdf_queue->prev;
	}
}

int			mlx_while(t_fdf *fdf)
{
	if (fdf->multi_fdf_con == true)
	{
		delay(fdf->multi_delay);
		if (fdf->multi_fdf && fdf->fdf_queue->next)
			fdf->fdf_queue = fdf->fdf_queue->next;
		else
			return (0);
		draw_multi_fdf(fdf, fdf->fdf_queue);
	}
	return (0);
}

int			key_control(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		handle_esc_key(fdf);
	else if (key == KEY_I || key == KEY_K)
		handle_zoom_key(key, fdf);
	else if (key == KEY_H && fdf->help == false)
		fdf->help = true;
	else if (key == KEY_H && fdf->help == true)
		fdf->help = false;
	else if (key == KEY_L_ARROW || key == KEY_R_ARROW
			|| key == KEY_U_ARROW || key == KEY_D_ARROW)
		handle_arrow_key(key, fdf);
	else if (key == KEY_S && fdf->help == false)
		shell_in(fdf);
	else if ((key == KEY_W || key == KEY_Q) && fdf->multi_fdf)
		handle_multi_fdf(key, fdf);
	else if (key == KEY_E && fdf->multi_fdf_con == false)
		fdf->multi_fdf_con = true;
	else if (key == KEY_E && fdf->multi_fdf_con == true)
		fdf->multi_fdf_con = false;
	else
		fdf->help = false;
	if (!fdf->multi_fdf)
		draw(fdf, fdf->data);
	if (fdf->multi_fdf)
		draw_multi_fdf(fdf, fdf->fdf_queue);
	if (fdf->help)
		draw_help_menu(fdf);
	return (0);
}
