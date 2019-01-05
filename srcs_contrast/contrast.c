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

#include "ft_tpool.h"

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

void	*contrast_chunk(t_args *args)//void *chunk)
{
	char	*tmp;
	char	*new;
	int		nb;
	int		i;
	int		y;

	i = -1;
	y = -1;
	tmp = (char*)args->chunk;
	if (!(new = (char*)ft_memalloc((ft_strlen(tmp) + 1) * sizeof(char))))
		ft_err_exit("read_chunk : malloc error");
	while (tmp[++y])
	{
		nb = 0;
		if (ft_isdigit(tmp[y]))
		{
			while (ft_isdigit(tmp[y]))
				nb = nb * 10 + (tmp[y++] - '0');
			y -= 1;
			//pthread_mutex_lock(&g_env.mutexsum);
			ft_putnbr_str(new, (nb * (g_env.contrast / 100.0)), &i);
			//pthread_mutex_unlock(&g_env.mutexsum);
		}
		else
			new[++i] = tmp[y];
	}
	ft_strdel(&tmp);
	//pthread_mutex_lock(&g_env.mutexsum);
	while (g_env.curr_th != args->th_nb)
	;
	ft_dprintf(g_env.output_fd, "%s", new);
	//pthread_mutex_unlock(&g_env.mutexsum);
	ft_strdel(&new);
	return (NULL);
}
