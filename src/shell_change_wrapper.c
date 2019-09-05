/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_change_wrapper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 18:51:47 by phtruong          #+#    #+#             */
/*   Updated: 2019/09/04 19:31:13 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fdf.h"

static void	shell_change_map(char *file, t_fdf *fdf)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		fdf->data->map_color = false;
		free(fdf->data->map);
		free(fdf->data->c_map);
		fdf->data->map = parse_fdf(fd, fdf);
		close(fd);
		fdf_zoom_magic(fdf);
	}
	else
		abort_fdf();
	fdf->multi_fdf = false;
}

static void	shell_change_z_zoom(char *z, t_fdf *fdf)
{
	int n;

	n = ft_atoi(z);
	ft_printf(P_YELLOW"z_zoom set to: %d\n"P_NC, n);
	fdf->cam.z_zoom = n;
}

static void	shell_change_brightness(char *brightness, t_fdf *fdf)
{
	int n;

	n = ft_atoi(brightness);
	if (n < 0 && fdf->cam.after_img == false)
	{
		ft_printf(P_RED"after image mode must be enabled for negative\n"P_NC);
		return ;
	}
	else
	{
		ft_printf(P_YELLOW"Brightness set to: %d\n"P_NC, n);
		fdf->cam.brightness = n;
	}
}

static void	shell_change_after_image(char *mod, t_fdf *fdf)
{
	if (ft_strcasecmp(mod, "on") == 0)
	{
		ft_printf("After image mode: "P_GREEN"ON\n"P_NC);
		fdf->cam.after_img = true;
	}
	else if (ft_strcasecmp(mod, "off") == 0)
	{
		ft_printf("After image mode: "P_RED"OFF\n"P_NC);
		ft_printf(P_YELLOW"Brightness set back to 0:\n"P_NC);
		fdf->cam.brightness = 0;
		fdf->cam.after_img = false;
	}
	else
		ft_printf(P_RED"Invalid input\n"P_NC);
}

static void	shell_change_delay(char *delay, t_fdf *fdf)
{
	int n;

	n = ft_atoi(delay);
	ft_printf(P_YELLOW"delay set to: %d milliseconds\n", n);
	fdf->multi_delay = n;
}

void		shell_change_wrapper(char **input, t_fdf *fdf)
{
	int no;

	no = count_arr_width(input);
	if (no > 3 || no < 3)
		ft_printf("change [variable] [value]\n");
	else if (ft_strcasecmp(input[1], "map") == 0)
		shell_change_map(input[2], fdf);
	else if (ft_strcasecmp(input[1], "z_zoom") == 0)
		shell_change_z_zoom(input[2], fdf);
	else if (ft_strcasecmp(input[1], "brightness") == 0)
		shell_change_brightness(input[2], fdf);
	else if (ft_strcasecmp(input[1], "after_image") == 0)
		shell_change_after_image(input[2], fdf);
	else if (ft_strcasecmp(input[1], "delay") == 0)
		shell_change_delay(input[2], fdf);
	free_input(input);
}
