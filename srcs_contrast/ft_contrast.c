/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:08:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 10:48:51 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

void	process_chunks(void)
{
	t_list		*chunks_tmp;

	chunks_tmp = g_env.chunks;
	while (chunks_tmp)
	{
		contrast_chunk((char**)&(chunks_tmp->content));
		chunks_tmp = chunks_tmp->next;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv))
		ft_usage();
	get_file_chunks();
	process_chunks();
	write_chunks();
	return (0);
}
