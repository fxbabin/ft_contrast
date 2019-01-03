/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:51:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 12:51:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

int a = 0 ;
void *funcc(void *arg)
{
	int		i;

	i = 0;
	(void)arg;
	while (++i < 5000000)
		;
	a += i;
	ft_printf("%d\n", a);
	return (NULL);
}

void	process_queue_th(t_queue **queue)
{
	char	*tmp;
	int		i;
	int		y;

	i = -1;
	while ((tmp = ft_dequeue(queue)))
	{
		pthread_create(&(g_env.callThd[++i]), &(g_env.attr), contrast_chunk, (void *)tmp);	 
		if (i == NB_THREADS - 1)
		{
			y = -1;
			while (++y < NB_THREADS)
  				pthread_join(g_env.callThd[y], &(g_env.status));
			i = -1;
		}
	}
}

void	process_file_th(void)
{
	char		buff[BUF_SIZE + 1];
	t_queue		*chunk_queue;
	char		*chunk;
	int			ret;

	ret = 0;
	chunk = NULL;
	chunk_queue = NULL;
	process_header();
	while ((ret = read(g_env.input_fd, buff, BUF_SIZE)) > 0)
	{
		chunk = read_chunk(buff, ret);
		ft_enqueue(&chunk_queue, chunk);
	}
	process_queue_th(&chunk_queue);
	ft_qdel(&chunk_queue);
}




int		main(int argc, char **argv)
{
	//void *status;

    pthread_mutex_init(&(g_env.mutexsum), NULL);
         
    /* Create threads to perform the dotproduct  */
    pthread_attr_init(&(g_env.attr));
    //pthread_attr_setdetachstate(&(g_env.attr), PTHREAD_CREATE_JOINABLE);


	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv))
		ft_usage();
	
	/*int		i;

	i = -1;
	while (++i < NB_THREADS)
		pthread_create(&(g_env.callThd[i]), &(g_env.attr), funcc, (void *)&i); 

	i = -1;
	while (++i < NB_THREADS)
  		pthread_join(g_env.callThd[i], &(g_env.status));*/
    process_file_th();
    
	pthread_attr_destroy(&(g_env.attr));
    pthread_mutex_destroy(&(g_env.mutexsum));
    pthread_exit(NULL);
	
    close(g_env.input_fd);
	ft_qdel(&(g_env.queue));
	return (0);
}