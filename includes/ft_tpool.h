/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 10:34:09 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 10:35:48 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TPOOL_H
# define FT_TPOOL_H

# include <stdio.h>
# include <pthread.h>
# include "../libft/includes/libft.h"

# define NB_THREADS 4

typedef struct		s_env
{
	int				contrast;
	int				input_fd;
	int				output_fd;
	t_list			*chunks;
	pthread_t 		callThd[NB_THREADS];
    pthread_mutex_t mutexsum;
    pthread_attr_t 	attr;
	void			*status;
}					t_env;

t_env				g_env;

void				ft_usage(void);
void				ft_err_exit(char *str);
int					check_arguments(int argc, char **argv);


void				get_file_chunks(void);
void				write_chunks(void);

void				contrast_chunk(char **chunk);

#endif
