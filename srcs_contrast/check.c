/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 10:46:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

void	ft_usage(void)
{
	ft_printf("usage: ./ft_contrast -f [input.pgm] -c [contrast_level] -o \
		[output.pgm]\n");
	exit(-1);
}

int		ft_isnumber(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		check_arguments(int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-f"))
			g_env.input_fd = open(argv[i + 1], O_RDONLY);
		if (ft_strequ(argv[i], "-c"))
		{
			if (ft_isnumber(argv[i + 1]))
				g_env.contrast = ft_atoi(argv[i + 1]);
			else
				return (0);
		}
		if (ft_strequ(argv[i], "-o"))
			g_env.output_fd = open(argv[i + 1], O_WRONLY | O_CREAT \
					| O_TRUNC, 0755);
	}
	if (g_env.input_fd < 0 || g_env.output_fd < 1)
		return (0);
	if (g_env.contrast < 0 || g_env.contrast > 100)
		return (0);
	return (1);
}
