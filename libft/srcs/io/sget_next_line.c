/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sget_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 22:41:59 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/18 00:38:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include "str.h"

int				sget_next_char(const int fd, char **line, char c)
{
	static char		buff[BUF_SIZE + 1];
	int				ret;
	int				endl;
	int				idx;

	ret = 0;
	if (fd < 0 || !line || !(*line = ft_strnew(BUF_SIZE)) || BUF_SIZE < 1)
		return (-1);
	while (1)
	{
		(!*buff) ? ft_bzero(buff, BUF_SIZE + 1) : 0;
		if (!*buff && (ret = read(fd, buff, BUF_SIZE)) < 0)
			return (-1);
		if (!ret && **line)
			return (1);
		if (!ret && !*buff)
			return (0);
		idx = ft_strchrindex(buff, c);
		if ((endl = ft_charinset(c, buff)) < 0 ||
				!(*line = ft_strnjoinclr(*line, buff, idx, 1)))
			return (-1);
		ft_strcpy((char*)buff, &(buff[(buff[idx] == c) ? (idx + 1) : idx]));
		if (endl)
			return (1);
	}
}

int				sget_next_line(const int fd, char **line)
{
	return (sget_next_char(fd, line, '\n'));
}
