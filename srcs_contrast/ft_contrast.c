/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 10:48:51 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

int		main(int argc, char **argv)
{
	t_env	env;

	env.contrast = -1;
	env.input_fd = -1;
	env.output_fd = -1;
	env.queue = NULL;
	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv, &env))
		ft_usage();
	process_file(&env);
	close(env.input_fd);
	ft_qdel(&(env.queue));
	return (0);
}
