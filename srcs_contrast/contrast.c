/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contrast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 11:58:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

void	ft_putnbr_str(char *str, int nb, int *idx)
{
	if (nb >= 10)
	{
		ft_putnbr_str(str, nb / 10, idx);
		ft_putnbr_str(str, nb % 10, idx);
	}
	if (nb < 10 && nb >= 0)
	{
		*idx += 1;
		str[*idx] = nb + '0';
	}
}

void	contrast_chunk(char **chunk)
{
	char	*new;
	int		nb;
	int		i;
	int		y;

	i = -1;
	y = -1;
	if (!(new = (char*)ft_memalloc((ft_strlen(*chunk) + 1) * sizeof(char))))
		ft_err_exit("read_chunk : malloc error");
	while ((*chunk)[++y])
	{
		nb = 0;
		if (ft_isdigit((*chunk)[y]))
		{
			while (ft_isdigit((*chunk)[y]))
				nb = nb * 10 + ((*chunk)[y++] - '0');
			y -= 1;
			ft_putnbr_str(new, (nb * (g_env.contrast / 100.0)), &i);
		}
		else
			new[++i] = (*chunk)[y];
	}
	ft_strdel(chunk);
	*chunk = new;
}
