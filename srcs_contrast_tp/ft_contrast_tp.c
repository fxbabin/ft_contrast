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
	if (!(g_th_env.callThd = (pthread_t*)malloc(nb_threads * sizeof(pthread_t))))
		return ;
	chunks_tmp = g_env.chunks;
	while (chunks_tmp)
	{
		pthread_create(&(g_th_env.callThd[++i]), &(g_th_env.attr),
			pthread_contrast, (void*)&(chunks_tmp->content));
		if (i == nb_threads - 1)
		{
			y = -1;
			while (++y < nb_threads)
				pthread_join(g_th_env.callThd[y], &(g_th_env.status));
			i = -1;
		}
		chunks_tmp = chunks_tmp->next;
	}
}

int		main(int argc, char **argv)
{
	t_tpool		*g_tpool;
	t_list		*tmp;

	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv))
		ft_usage();
	g_tpool = tp_create(4);
	get_file_chunks();
	tmp = g_env.chunks;
	while(tmp)
	{
		tp_exec_queue_add((void*)&(tmp->content), (void*)(void*)contrast_chunk);
		tmp = tmp->next;
	}
	tp_wait_for_queue();
	write_chunks();
	pthread_attr_destroy(&(g_tpool->attr));
	pthread_exit(NULL);
	ft_lstdel(&(g_env.chunks), ft_elemdel);
	close(g_env.input_fd);
	close(g_env.output_fd);
	return (0);
}
