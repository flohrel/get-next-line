/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 22:49:06 by flohrel           #+#    #+#             */
/*   Updated: 2020/12/17 03:33:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_queue	*qset(t_queue *q)
{
	if (!q)
		q = malloc(sizeof(*q));
	if (!q)
		return (q);
	q->front = NULL;
	q->back = NULL;
	q->size = 0;
	return (q);
}

int		enqueue(t_queue *q, char *buf, size_t len)
{
	char	*new_buf;

	new_buf = malloc(sizeof(*new_buf) * len);
	if (!new_buf)
		return (-1);
	new_buf = ft_memcpy(new_buf, buf, len);
	if (!qpush(q, new_buf, len))
		return (-1);
	return (0);
}

int		set_newline(t_queue *q, char **line)
{
	int		i;
	t_list	*lst;

	if (*line)
		free(*line);
	*line = malloc(sizeof(char) * (q->size + 1));
	if (!(*line))
		return (-1);
	i = 0;
	while (i != q->size)
	{
		lst = q->front;
		ft_memcpy(&(*line)[i], lst->buf, lst->len);
		i += lst->len;
		qpop(q);
	}
	(*line)[q->size] = '\0';
	q->size = 0;
	q->front = NULL;
	q->back = NULL;
	return (0);
}

int		get_newline(t_queue *q, char *buf, size_t len, char **line)
{
	char	*next_line;
	size_t	n;

	next_line = ft_memchr(buf, '\n', len);
	if (next_line)
	{
		n = next_line - buf;
		if (n && enqueue(q, buf, n) == -1)
			return (-1);
		if (set_newline(q, line))
			return (-1);
		n = len - n - 1;
		if (n && enqueue(q, next_line + 1, n))
			return (-1);
		return (1);
	}
	else if (!(q->front && (buf == q->front->buf)))
		return (enqueue(q, buf, len));
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				ret[2];
	char			buf[BUFFER_SIZE];
	static t_queue	*q = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!q && !(q = qset(q)))
		return (-1);
	if (q && q->front &&
		(ret[1] = get_newline(q, q->front->buf, q->front->len, line)))
		return (ret[1]);
	while ((ret[0] = read(fd, buf, BUFFER_SIZE)) > 0)
		if ((ret[1] = get_newline(q, buf, ret[0], line)))
			return (ret[1]);
	if (set_newline(q, line))
		return (-1);
	free(q);
	return (ret[0]);
}
