/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:17:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/08 13:17:56 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			set_line(t_queue *file_q, char **line)
{
	char	*lptr;
	t_buf	*cur_buf;

	*line = malloc(sizeof(char) * (file_q->len + 1));
	if (!(*line))
		return (-1);
	lptr = *line;
	while ((cur_buf = file_q->first))
	{
		ft_memcpy(lptr, cur_buf->data, cur_buf->size);
		lptr += cur_buf->size;
		pop(file_q);
	}
	*lptr = '\0';
	file_q = init_file_queue(file_q);
	return (0);
}

int			get_line(t_queue *file_q, char *buf, size_t size, char **line)
{
	char	*c;
	int		is_tmp;
	size_t	tmp_size;

	if ((c = ft_strchr(buf, '\n', size)))
	{
		is_tmp = 0;
		if (file_q->first->data == buf)
			is_tmp = 1;
		tmp_size = c - buf;
		if (push(file_q, buf, tmp_size) == -1)
			return (-1);
		if (is_tmp)
			pop(file_q);
		if ((set_line(file_q, line) == -1) ||
			((tmp_size = size - tmp_size) &&
			(push(file_q, c + 1, tmp_size) == -1)))
			return (-1);
		return (1);
	}
	else if ((!file_q->first || (file_q->first->data != buf)) && size)
		return (push(file_q, buf, size));
	return (0);
}


int			get_next_line(int fd, char **line)
{
	static t_queue	*qlist[MAX_FD] = { NULL };
	t_queue			*file_q;
	t_buf			*tmp;
	char			buf[BUFFER_SIZE];
	int				ret[2];

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	file_q = qlist[fd];
	if (!file_q || !(file_q = init_file_queue(file_q)))
		return (-1);
	tmp = file_q->first;
	if (tmp && (ret[0] = get_line(file_q, tmp->data, tmp->size, line)))
		return (ret[0]);
	while ((ret[1] = read(fd, buf, BUFFER_SIZE)) > 0)
		if ((ret[0] = get_line(file_q, buf, ret[1], line)))
			return (ret[0]);
	if ((ret[1] == -1) ||
		(file_q->first && (set_line(file_q, line) == -1)))
		return (-1);
	free(qlist[fd]);
	qlist[fd] = NULL;
	return (0);
}
