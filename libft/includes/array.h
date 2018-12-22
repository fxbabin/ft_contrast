/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 00:50:15 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 00:56:14 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

/*
** --------------------------- ARRAY FUNCTIONS ----------------------------
*/

char				*ft_join(char **tab, char *sep);
void				ft_quicksort(int **array, int left, int right);
void				ft_quicksort2(int **array, int left, int right);
void				ft_strquicksort(char **array, int left, int right);
void				ft_mergesort(int **array, int left, int right);
void				ft_strmergesort(char **array, int left, int right);
void				ft_char2dump(char **array);
void				ft_int2dump(int **array);

#endif
