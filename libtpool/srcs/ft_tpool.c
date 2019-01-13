/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/05 17:43:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_tpool.h"

void        *task_handler(void *args)
{
    t_task      *task;
    char        **ss;

    (void)args;
    while (42)
    {
        //ft_putstr("rr\n");
        pthread_mutex_lock(&(g_tpool.mutexsum));
        pthread_cond_wait(&(g_tpool.cond_signal), &(g_tpool.mutexsum));
        ft_putstr_fd("rsr\n", 2);
        if (g_task_q->task == NULL)
		{
			pthread_mutex_unlock(&(g_tpool.mutexsum));
			g_tpool.closed++;
			return (NULL);
		}
        
        task = ft_task_dequeue(&g_task_q);
        ss = (char**)task->args;
        pthread_mutex_unlock(&(g_tpool.mutexsum));
        ft_printf("%s\n", *ss);
        //task->func(ss);
    }
    g_tpool.closed++;
    //pthread_mutex_unlock(&(g_tpool.mutexsum));
    return (NULL);
}

void        tp_create(int nb_threads)
{
    int         i;

    i = -1;
    if (!(g_tpool.callThd = (pthread_t*)malloc(nb_threads * sizeof(pthread_t))))
        return ;
    g_tpool.closed = 0;
    g_tpool.nb_threads = nb_threads;
    while (++i < g_tpool.nb_threads)
        pthread_create(&(g_tpool.callThd[i]), &(g_tpool.attr), task_handler, NULL);
    pthread_attr_init(&(g_tpool.attr));
    pthread_mutex_init(&(g_tpool.mutexsum), NULL);
	pthread_cond_init(&(g_tpool.cond_signal), NULL);
}

void        tp_exec_queue_add(void *args, void (*func)(void*))
{
    char    **d;

    d = (char**)args;
    //ft_printf(">%d\n", ft_strlen(((char*)(*d))));
    ft_task_enqueue(&g_task_q, (void*)(d), func);
    //pthread_cond_signal(&(g_tpool.cond_signal));
}

void		tp_wait_for_queue(void)
{
	int		i;

	i = -1;
    while (g_tpool.closed < g_tpool.nb_threads)
	{
        pthread_cond_signal(&(g_tpool.cond_signal));
        ft_putstr_fd("rsr\n", 2);
        g_tpool.closed++;
    }	
	while (++i < g_tpool.nb_threads)
		pthread_join(g_tpool.callThd[i], NULL);
    pthread_attr_destroy(&(g_tpool.attr));
}