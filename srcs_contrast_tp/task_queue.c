/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:46:59 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/06 14:47:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

static t_task_q		*ft_task_q_create(void (*func)(void*), void *args)
{
	t_task_q	*task_q;
    t_task      *task;

	if (!(task_q = (t_task_q*)ft_memalloc(sizeof(t_task_q))))
		ft_err_exit("ft_task_q_create : malloc failed");
    if (!(task = (t_task*)ft_memalloc(sizeof(t_task))))
		ft_err_exit("ft_task_q_create : malloc failed");
    task->function = func;
    task->args = args;
    task_q->task = task;
	task_q->next = NULL;
	return (task_q);
}

void				ft_task_enqueue(t_task_q **queue, void (*func)(void*), void *args)
{
	t_task_q		*tmp;

	tmp = NULL;
	if (!func)
		ft_err_exit("ft_task_enqueue : NULL parameter");
	if (*queue)
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_task_q_create(func, args);
	}
	else
		*queue = ft_task_q_create(func, args);
}

t_task		        *ft_task_dequeue(t_task_q **queue)
{
	t_task		    *ret;
	t_task_q		*tmp;

	ret = NULL;
	tmp = NULL;
	if (!queue || !*queue)
		return (NULL);
	ret = (*queue)->task;
	tmp = *queue;
	(*queue) = (*queue)->next;
	ft_memdel((void**)&tmp);
	return (ret);
}

/*void				ft_qdel(t_task_queue **queue)
{
	t_task_queue		*tmp;

	if (!queue)
		ft_err_exit("ft_qdel : NULL parameter");
	while (*queue)
	{
		tmp = (*queue)->next;
		if ((*queue)->chunk)
			ft_memdel((void**)&((*queue)->chunk));
		ft_memdel((void**)queue);
		*queue = NULL;
		*queue = tmp;
	}
}*/