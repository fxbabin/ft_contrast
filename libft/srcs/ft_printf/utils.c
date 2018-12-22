/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:15:04 by fbabin            #+#    #+#             */
/*   Updated: 2018/06/19 16:40:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_countt(long long nb)
{
	int		i;

	if (nb == 0)
		return (1);
	i = (nb < 0) ? 1 : 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static int		ft_countllu(unsigned long nb, int len)
{
	int				i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb)
	{
		nb /= len;
		i++;
	}
	return (i);
}

void			ft_lltoa_static(char *str, long long nb)
{
	int		i;
	int		neg;

	neg = (nb < 0) ? -1 : 1;
	i = ft_countt(nb);
	while (i--)
	{
		str[i] = ft_abs(nb % 10) + '0';
		nb /= 10;
	}
	if (neg < 0)
		str[0] = '-';
}

void			ft_llutoa_base_static(char *str,
						unsigned long long nb, const char *base)
{
	int					i;
	int					len;
	unsigned long long	x;

	x = (unsigned long long)nb;
	len = ft_strlen(base);
	i = ft_countllu(x, len);
	while (i--)
	{
		str[i] = base[ft_abs(x % len)];
		x /= len;
	}
}
