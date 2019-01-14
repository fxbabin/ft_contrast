/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 10:34:09 by fbabin            #+#    #+#             */
/*   Updated: 2019/01/14 18:45:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTRAST_H
# define FT_CONTRAST_H

# include <pthread.h>
# include "../libft/includes/libft.h"
# include "../libtpool/includes/ft_tpool.h"

typedef struct			s_env
{
	int					contrast;
	int					input_fd;
	int					output_fd;
	t_list				*chunks;
}						t_env;

typedef struct			s_th_env
{
	pthread_t			*threads;
	pthread_mutex_t		mutexsum;
	pthread_attr_t		attr;
	void				*status;
}						t_th_env;

t_env					g_env;
t_th_env				g_th_env;

void					ft_usage(void);
void					ft_err_exit(char *str);
int						check_arguments(int argc, char **argv);

void					get_file_chunks(void);
void					write_chunks(void);

void					contrast_chunk(char **chunk);

#endif
