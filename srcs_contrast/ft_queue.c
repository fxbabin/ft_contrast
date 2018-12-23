/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 10:51:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

void				ft_err_exit(char *str)
{
	ft_dprintf(2, "%kErrror :: %k%s\n", LRED, RESET, str);
	exit(-1);
}

static t_queue		*ft_qcreate(char *chunk)
{
	t_queue	*t;

	if (!chunk)
		ft_err_exit("ft_qcreate : NULL parameter");
	if (!(t = (t_queue*)ft_memalloc(sizeof(t_queue))))
		ft_err_exit("ft_qcreate : malloc failed");
	t->chunk = chunk;
	t->next = NULL;
	return (t);
}

void				ft_enqueue(t_queue **queue, char *chunk)
{
	t_queue		*tmp;

	tmp = NULL;
	if (!queue || !chunk)
		ft_err_exit("ft_enqueue : NULL parameter");
	if (*queue)
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_qcreate(chunk);
	}
	else
		*queue = ft_qcreate(chunk);
}

char				*ft_dequeue(t_queue **queue)
{
	char		*ret;
	t_queue		*tmp;

	ret = NULL;
	tmp = NULL;
	if (!queue || !*queue)
		return (NULL);
	ret = (*queue)->chunk;
	tmp = *queue;
	(*queue) = (*queue)->next;
	ft_memdel((void**)&tmp);
	return (ret);
}

void				ft_qdel(t_queue **queue)
{
	t_queue		*tmp;

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
}
