/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:17:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/07 14:55:43 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			push(t_queue *file_q, char *buf, size_t size)
{
	t_buf	*new_buf;

	if (!(new_buf = malloc(sizeof(t_buf))) ||
		!(new_buf->data = malloc(sizeof(char) * size)))
		return (-1);
	ft_memcpy(new_buf->data, buf, size);
	new_buf->size = size;
	new_buf->next = NULL;
	file_q->len += size;
	if (!(file_q->first))
		file_q->first = new_buf;
	if (file_q->last)
		file_q->last->next = new_buf;
	file_q->last = new_buf;
	return (0);
}

void		pop(t_queue *file_q)
{
	t_queue	*cur_file;
	t_buf	*cur_buf;

	if (file_q->fd != -1)
	{
		cur_buf = file_q->first;
		file_q->first = cur_buf->next;
		file_q->len -= cur_buf->size;
		free(cur_buf->data);
		free(cur_buf);
	}
	else
	{
		while (file_q->next->fd != -1)
			file_q = file_q->next;
		cur_file = file_q->next;
		file_q->next = cur_file->next;
		free(cur_file);
	}
}

int			set_line(t_queue *file_q, char **line)
{
	char	*lptr;
	t_buf	*cur_buf;

	if (*line)
		free(*line);
	if (!(*line = malloc(sizeof(char) * file_q->len + 1)))
		return (-1);
	lptr = *line;
	while ((cur_buf = file_q->first))
	{
		ft_memcpy(lptr, cur_buf->data, cur_buf->size);
		lptr += cur_buf->size;
		pop(file_q);
	}
	*lptr = '\0';
	file_q->first = NULL;
	file_q->last = NULL;
	file_q->len = 0;
	return (0);
}

int			get_line(t_queue *file_q, char *buf, size_t size, char **line)
{
	char	*c;
	t_buf	*tmp;
	int		is_tmp;
	size_t	tmp_size;

	if ((c = ft_strchr(buf, '\n', size)))
	{
		is_tmp = 0;
		if ((tmp = file_q->first) && (tmp->data == buf))
		{
			file_q->len -= tmp->size;
			file_q->first = tmp->next;
			is_tmp = 1;
		}
		if (((tmp_size = c - buf) && (push(file_q, buf, tmp_size) == -1)) ||
			(set_line(file_q, line) == -1) ||
			((tmp_size = size - tmp_size - 1) &&
			(push(file_q, c + 1, tmp_size) == -1)))
			return (-1);
		if (is_tmp)
		{
			free(tmp->data);
			free(tmp);
		}
		return (1);
	}
	else if ((!file_q->first || (file_q->first->data != buf)) && size)
		return (push(file_q, buf, size));
	return (0);
}


int			get_next_line(int fd, char **line)
{
	int				ret[2];
	char			buf[BUFFER_SIZE];
	t_buf			*tmp;
	t_queue			*file_q;
	static t_queue	qlist = { -1, 0, NULL, NULL, NULL };

	if (!line ||
		BUFFER_SIZE <= 0 ||
		(!(file_q = get_file_q(&qlist, fd)) &&
		!(file_q = set_file_q(&qlist, fd))))
		return (-1);
	if ((tmp = file_q->first) &&
		(ret[0] = get_line(file_q, tmp->data, tmp->size, line)))
		return (ret[0]);
	while ((ret[1] = read(fd, buf, BUFFER_SIZE)) > 0)
		if ((ret[0] = get_line(file_q, buf, ret[1], line)))
			return (ret[0]);
	if ((ret[1] == -1) ||
		(file_q->first && (set_line(file_q, line) == -1)))
		return (-1);
	file_q->fd = -1;
	pop(&qlist);
	return (0);
}
