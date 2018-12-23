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

typedef struct		s_queue
{
	char			*chunk;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_env
{
	int				contrast;
	int				input_fd;
	int				output_fd;
	int				max_contrast;
	int				line_len;
	pthread_t 		callThd[NB_THREADS];
    pthread_mutex_t mutexsum;
    pthread_attr_t 	attr;
	t_queue			*queue;
}					t_env;

void				ft_usage(void);
int					check_arguments(int argc, char **argv, t_env *env);
void				contrast_chunk(t_env *env, char *chunk);
void				process_file(t_env *env);
void				ft_err_exit(char *str);
void				ft_enqueue(t_queue **queue, char *chunk);
char				*ft_dequeue(t_queue **queue);
void				ft_qdel(t_queue **queue);

#endif
