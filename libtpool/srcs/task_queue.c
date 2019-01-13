/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/05 17:43:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

t_task_q      *ft_task_q_create(void *args, void (*func)(void*))
{
    t_task_q        *task_q;
    t_task          *task;

    if (!(task_q = (t_task_q*)malloc(sizeof(t_task_q))))
        return (NULL);
    if (!(task = (t_task*)malloc(sizeof(t_task))))
        return (NULL);
    task->args = args;
    task->func = func;
    task_q->task = task;
    task_q->next = NULL;
    return (task_q);
}

void		ft_task_enqueue(t_task_q **task_queue, void *args, void (*func)(void*))
{
	t_task_q		*tmp;

	if (!task_queue)
		return ;
	if (*task_queue)
	{
		tmp = *task_queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_task_q_create(args, func);
	}
	else
		*task_queue = ft_task_q_create(args, func);
}

t_task      *ft_task_dequeue(t_task_q **task_queue)
{
    t_task_q    *tmp;
    t_task      *ret;

    if (!task_queue || !*task_queue)
        return (NULL);
    tmp = *task_queue;
    ret = (tmp) ? tmp->task : NULL;
    *task_queue = (*task_queue)->next;
    free(tmp);
    return (ret);
}