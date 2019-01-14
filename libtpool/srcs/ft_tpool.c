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

void		*task_handler(void *args)
{
	t_task		*task;

	(void)args;
	while (42)
	{
		pthread_mutex_lock(&(g_tpool->mutexsum));
		pthread_cond_wait(&(g_tpool->cond_signal), &(g_tpool->mutexsum));
		if (!g_tpool->task_q)
			break ;
		task = ft_task_dequeue(&(g_tpool->task_q));
		pthread_mutex_unlock(&(g_tpool->mutexsum));
		task->func(task->args);
	}
	g_tpool->closed++;
	pthread_mutex_unlock(&(g_tpool->mutexsum));
	return (NULL);
}

t_tpool		*tp_create(int nb_threads)
{
	int		i;

	i = -1;
	if(!(g_tpool = (t_tpool*)malloc(sizeof(t_tpool))))
		exit(-1);
	g_tpool->task_q = NULL;
	if (!(g_tpool->callThd =
		(pthread_t*)malloc(nb_threads * sizeof(pthread_t))))
		exit(-1);
	g_tpool->nb_threads = nb_threads;
    g_tpool->closed = 0;
	g_tpool->task_q_size = 0;
	pthread_mutex_init(&(g_tpool->mutexsum), NULL);
	pthread_cond_init(&(g_tpool->cond_signal), NULL);
	while (++i < g_tpool->nb_threads)
		pthread_create(&(g_tpool->callThd[i]), NULL, task_handler, NULL);
	return (g_tpool);
}

void		tp_exec_queue_add(void *args, void (*func)(void*))
{
	ft_task_enqueue(&(g_tpool->task_q), args, func);
	g_tpool->task_q_size += 1;
}

void		tp_wait_for_queue(void)
{
	int		i;

	i = -1;
	while (g_tpool->closed < g_tpool->nb_threads)
		pthread_cond_signal(&(g_tpool->cond_signal));
	while (++i < g_tpool->nb_threads)
		pthread_join(g_tpool->callThd[i], NULL);
}
