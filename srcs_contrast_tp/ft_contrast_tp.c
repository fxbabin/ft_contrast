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
		tp_exec_queue_add((void*)&(tmp->content), (void*)(void*)pthread_contrast);
		tmp = tmp->next;
	}
	tp_wait_for_queue();
	write_chunks();
	ft_lstdel(&(g_env.chunks), ft_elemdel);
	close(g_env.input_fd);
	close(g_env.output_fd);
	return (0);
}
