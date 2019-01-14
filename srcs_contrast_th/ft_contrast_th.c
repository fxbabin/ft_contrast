/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:51:23 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/05 19:08:46 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

void	*pthread_contrast(void *chunk)
{
	contrast_chunk((char**)chunk);
	return (NULL);
}

void	process_chunks_th(int nb_threads)
{
	t_list		*chunks_tmp;
	int			i;
	int			y;

	i = -1;
	if (!(g_th_env.threads = \
		(pthread_t*)malloc(nb_threads * sizeof(pthread_t))))
		return ;
	chunks_tmp = g_env.chunks;
	while (chunks_tmp)
	{
		pthread_create(&(g_th_env.threads[++i]), &(g_th_env.attr), \
			pthread_contrast, (void*)&(chunks_tmp->content));
		if (i == nb_threads - 1)
		{
			y = -1;
			while (++y < nb_threads)
				pthread_join(g_th_env.threads[y], &(g_th_env.status));
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
	pthread_attr_init(&(g_th_env.attr));
	get_file_chunks();
	process_chunks_th(4);
	write_chunks();
	pthread_attr_destroy(&(g_th_env.attr));
	pthread_exit(NULL);
	return (0);
}
