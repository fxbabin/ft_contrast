/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast_tp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:36:16 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/06 15:22:12 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_tpool.h"

void	*pthread_contrast(void *chunk)
{
	contrast_chunk((char**)chunk);
	return (NULL);
}

void	process_chunks_th(void)
{
	t_list		*chunks_tmp;
	int			i;
	int			y;

	i = -1;
	chunks_tmp = g_env.chunks;
	while (chunks_tmp)
	{
		pthread_create(&(g_env.callThd[++i]), &(g_env.attr), pthread_contrast,
			(void*)&(chunks_tmp->content));
		if (i == NB_THREADS - 1)
		{
			y = -1;
			while (++y < NB_THREADS)
				pthread_join(g_env.callThd[y], &(g_env.status));
			i = -1;
		}
		chunks_tmp = chunks_tmp->next;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv))
		ft_usage();
	pthread_attr_init(&(g_env.attr));
	get_file_chunks();
	process_chunks_th();
	write_chunks();
	pthread_attr_destroy(&(g_env.attr));
	pthread_exit(NULL);
	return (0);
}
