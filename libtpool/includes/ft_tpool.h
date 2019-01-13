/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/05 17:43:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TPOOL_H
# define FT_TPOOL_H

# include <pthread.h>
# include "../../libft/includes/libft.h"

typedef struct          s_task 
{
    void                *args;
    void                (*func)(void*);
}                       t_task;

typedef struct          s_task_q 
{
    t_task              *task;
    struct s_task_q     *next;
}                       t_task_q;

typedef struct          s_tpool
{
    int                 closed;
    int                 nb_threads;
    pthread_t 			*callThd;
	pthread_mutex_t 	mutexsum;
	pthread_attr_t 		attr;
    pthread_cond_t      cond_signal; 
	void				*status;
}                       t_tpool;

t_tpool                 g_tpool;
t_task_q                *g_task_q;

void		            ft_task_enqueue(t_task_q **task_queue, void *args,
                            void (*func)(void*));
t_task                  *ft_task_dequeue(t_task_q **task_queue);
void                    tp_create(int nb_threads);
void                    tp_exec_queue_add(void *args, void (*func)(void*));
void		            tp_wait_for_queue(void);

#endif