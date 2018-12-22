/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char2dump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:28:30 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 00:34:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "io.h"

void	ft_char2dump(char **array)
{
	int		i;

	i = -1;
	if (!array || !*array)
		return ;
	while (array[++i])
	{
		ft_putstr("[");
		ft_putstr(array[i]);
		ft_putstr("] ");
	}
	ft_putstr("\n");
}
