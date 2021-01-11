/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:57 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/11 20:07:41 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy(char *dst, char *src, size_t size)
{
	char	*d;

	if (!dst || !src)
		return (dst);
	d = dst;
	while (size--)
		*d++ = *src++;
	return (dst);
}

char	*ft_strchr(char *str, int c, size_t size)
{
	if (str)
	{
		while (size--)
		{
			if (*str == c)
				return (str);
			str++;
		}
	}
	return (NULL);
}

t_queue	*init_file_queue(t_queue *file_q)
{
	if (!file_q)
		file_q = malloc(sizeof(t_queue));
	if (!file_q)
		return (NULL);
	file_q->len = 0;
	file_q->first = NULL;
	file_q->last = NULL;
	file_q->tmp = NULL;
	return (file_q);
}

int		push(t_queue *file_q, char *buf, size_t size, t_bool is_tmp)
{
	t_buf	*new_buf;

	new_buf = malloc(sizeof(t_buf));
	if (!new_buf)
		return (-1);
	new_buf->data = malloc(sizeof(char) * size);
	if (!(new_buf->data))
		return (-1);
	ft_memcpy(new_buf->data, buf, size);
	new_buf->size = size;
	new_buf->next = NULL;
	if (is_tmp == FALSE)
	{
		file_q->len += size;
		if (!(file_q->first))
			file_q->first = new_buf;
		if (file_q->last)
			file_q->last->next = new_buf;
		file_q->last = new_buf;
	}
	else
		file_q->tmp = new_buf;
	return (0);
}

void	pop(t_queue *file_q, t_bool is_tmp)
{
	t_buf	*cur_buf;

	if (is_tmp == TRUE)
	{
		cur_buf = file_q->tmp;
		file_q->tmp = cur_buf->next;
	}
	else
	{
		cur_buf = file_q->first;
		file_q->len -= cur_buf->size;
		file_q->first = cur_buf->next;
		if (file_q->last == cur_buf)
			file_q->last = NULL;
	}
	free(cur_buf->data);
	free(cur_buf);
}
