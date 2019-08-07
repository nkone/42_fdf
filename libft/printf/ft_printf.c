/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phtruong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:13:19 by phtruong          #+#    #+#             */
/*   Updated: 2019/06/03 11:41:05 by phtruong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	collect_argv(t_print *p)
{
	const char	*s;

	s = p->str;
	while (ft_isdigit(*s))
		s++;
	if (*s != '$')
		return (0);
	else
		p->argv = ft_atoi(p->str);
	while (ft_isdigit(*p->str))
		p->str++;
	return (1);
}

int	collector_driver(t_print *p)
{
	(collect_argv(p)) && p->str++;
	while (collect_flag(p))
		p->str++;
	(collect_width(p)) && p->str++;
	(collect_pcn(p)) && p->str++;
	(collect_size(p)) && p->str++;
	(collect_type(p)) && p->str++;
	if (!p->type)
		return (0);
	return (1);
}

int	ft_printf_con(t_print *p)
{
	if (*p->str == '%')
	{
		p->str++;
		if (!*p->str)
			return (0);
		if (!collector_driver(p))
			return (0);
		g_print_table[p->type - 1](p);
		if (p->done > INT_MAX)
			return (-1);
	}
	else
	{
		if (p->done == INT_MAX)
			return (-1);
		p->done++;
		ft_putchar(*p->str++);
	}
	return (1);
}

int	ft_printf_(const char *str, va_list ap)
{
	t_print	p;
	int		check;

	reset_print(&p);
	va_copy(p.ap, ap);
	p.str = str;
	while (*p.str)
	{
		reset_collector(&p);
		if (!(check = ft_printf_con(&p)))
			return (p.done);
		else if (check == -1)
			return (-1);
	}
	va_end(p.ap);
	return (p.done);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		done;

	va_start(ap, str);
	done = ft_printf_(str, ap);
	va_end(ap);
	return (done);
}
