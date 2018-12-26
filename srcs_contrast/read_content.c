/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 11:58:36 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"

void	process_header(t_env *env)
{
	char	buff[100 + 1];
	int		ret;
	int		nb_lines;
	int		i;

	i = -1;
	nb_lines = 0;
	ft_bzero((char*)&buff, 100);
	ret = read(env->input_fd, buff, 100);
	buff[ret] = 0;
	while (buff[++i])
	{
		if (buff[i] == '\n')
			nb_lines += 1;
		ft_dprintf(env->output_fd, "%c", buff[i]);
		if (nb_lines == 3)
			break ;
	}
	lseek(env->input_fd, i - 100 + 1, SEEK_CUR);
}

char	*read_chunk(t_env *env, char *buff, int ret)
{
	char	*chunk;
	int		i;

	i = 0;
	chunk = NULL;
	while (ft_isdigit(buff[ret - i - 1]))
		i++;
	lseek(env->input_fd, -i, SEEK_CUR);
	buff[ret - i] = 0;
	if (!(chunk = (char*)ft_memalloc((ret + 1) * sizeof(char))))
		ft_err_exit("read_chunk : malloc error");
	ft_memcpy(chunk, buff, ret - i);
	return (chunk);
}

void	process_queue(t_env *env, t_queue **queue)
{
	char	*tmp;

	while ((tmp = ft_dequeue(queue)))
	{
		contrast_chunk(env, tmp);
	}
}

void	process_file(t_env *env)
{
	char		buff[BUF_SIZE + 1];
	t_queue		*chunk_queue;
	char		*chunk;
	int			ret;

	ret = 0;
	chunk = NULL;
	chunk_queue = NULL;
	process_header(env);
	while ((ret = read(env->input_fd, buff, BUF_SIZE)) > 0)
	{
		chunk = read_chunk(env, buff, ret);
		ft_enqueue(&chunk_queue, chunk);
	}
	process_queue(env, &chunk_queue);
	ft_qdel(&chunk_queue);
}
