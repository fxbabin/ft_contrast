/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:04:58 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/21 21:05:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CONTRAST_H
# define FT_CONTRAST_H

#include <stdio.h>
#include "../libft/includes/libft.h"

typedef struct  s_env 
{
    int         contrast;
    int         input_fd;
    int         output_fd;
}               t_env;

#endif