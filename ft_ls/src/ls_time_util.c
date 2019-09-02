/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:48:26 by phtruong          #+#    #+#             */
/*   Updated: 2019/07/24 16:03:18 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** function print_date_time()
** Parameters:
**		[s]: char pointer to string (returned by ctime_r)
** Collects date and time and store in a buffer with 14 bytes then print out.
** Months are in alpha (first three letters).
** Format: mmm dd hh:mm
** Returns:
**		void.
*/

void	print_date_time(char *s)
{
	char	buf[14];
	int		i;
	int		j;

	i = 4;
	j = 0;
	ft_bzero(buf, sizeof(buf));
	while (i < 16)
		buf[j++] = s[i++];
	buf[j] = '\0';
	ft_printf("%s ", buf);
}

/*
** function print_year()
** Paramters:
**		[s]: char pointer to string (returned by ctime_r)
** similar to print_date_time() but replaces time for year instead. Since time
** takes 5, year only takes 4 (yyyy). Buffer changed to 13 instead of 14.
** Returns:
**		void.
*/

void	print_year(char *s)
{
	char	buf[13];
	int		i;
	int		j;

	i = 4;
	j = 0;
	while (i < 11)
		buf[j++] = s[i++];
	i = 20;
	buf[j++] = ' ';
	while (i < 24)
		buf[j++] = s[i++];
	buf[j] = '\0';
	ft_printf("%s ", buf);
}

/*
** function check_timestamp()
** Parameters:
**		[f_time]: struct tm to get time info
** Check time of local file if there has been more than 6 months
** since local time, or in the future.
** Returns:
**		1 if time has been more than 6 months, or in future
**		0 otherwise
*/

int		check_timestamp(struct tm f_time)
{
	time_t		t;
	struct tm	l_time;

	time(&t);
	localtime_r(&t, &l_time);
	if ((l_time.tm_year - f_time.tm_year) > 0 ||
	(l_time.tm_year - f_time.tm_year) < 0 ||
	(l_time.tm_mon - f_time.tm_mon) > 6 || (l_time.tm_mon - f_time.tm_mon < 0))
		return (0);
	return (1);
}
