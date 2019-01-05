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

void	process_header(void)
{
	char	buff[100 + 1];
	int		ret;
	int		nb_lines;
	int		i;

	i = -1;
	nb_lines = 0;
	ft_bzero((char*)&buff, 100);
	ret = read(g_env.input_fd, buff, 100);
	buff[ret] = 0;
	while (buff[++i])
	{
		if (buff[i] == '\n')
			nb_lines += 1;
		ft_dprintf(g_env.output_fd, "%c", buff[i]);
		if (nb_lines == 3)
			break ;
	}
	lseek(g_env.input_fd, i - 100 + 1, SEEK_CUR);
}

char	*read_chunk(char *buff, int ret)
{
	char	*chunk;
	int		i;

	i = 0;
	chunk = NULL;
	while (ft_isdigit(buff[ret - i - 1]))
		i++;
	lseek(g_env.input_fd, -i, SEEK_CUR);
	buff[ret - i] = 0;
	if (!(chunk = (char*)ft_memalloc((ret + 1) * sizeof(char))))
		ft_err_exit("read_chunk : malloc error");
	ft_memcpy(chunk, buff, ret - i);
	return (chunk);
}

void	get_file_chunks(void)
{
	char		buff[BUF_SIZE + 1];
	char		*chunk;
	int			ret;

	ret = 0;
	chunk = NULL;
	process_header();
	while ((ret = read(g_env.input_fd, buff, BUF_SIZE)) > 0)
	{
		chunk = read_chunk(buff, ret);
		ft_lstpushback(&(g_env.chunks), chunk, 0);
	}
	close(g_env.input_fd);
}
void	write_chunks(void)
{
	t_list		*chunks_tmp;
	
	chunks_tmp = g_env.chunks;
	while (chunks_tmp)
	{
		ft_dprintf(g_env.output_fd, "%s", chunks_tmp->content);
		chunks_tmp = chunks_tmp->next;
	}
	ft_lstdel(&(g_env.chunks) , ft_elemdel);
}