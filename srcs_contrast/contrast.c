/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contrast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/21 21:08:04 by fbabin           ###   ########.fr       */
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

void    contrast_chunk(t_env *env, char **chunk)
{
    char    *tmp;
    char    *new;
    int     nb;
    int     i;

    i = -1;
    tmp = *chunk;
    if (!(new = (char*)ft_memalloc(ft_strlen(tmp))))
        ft_err_exit("read_chunk : malloc error");
    while(*tmp)
    {
        nb = 0;
        if (ft_isdigit(*tmp))
        {
            while(ft_isdigit(*tmp))
                nb = nb * 10 + (*(tmp++) - '0');
            //if (*(tmp - 1) == '0' || nb > 0)
            ft_putnbr_str(new, (nb * (env->contrast / 100.0)), &i);
        }
        else
            new[++i] = *(tmp++);
    }
    ft_strdel(chunk);
    *chunk = new;
}