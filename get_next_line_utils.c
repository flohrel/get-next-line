/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:57 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/07 14:51:38 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy(char *dst, char *src, size_t size)
{
	char *d;

	d = dst;
	while (size--)
		*d++ = *src++;
	return (dst);
}

char	*ft_strchr(char *str, int c, size_t size)
{
	while (size--)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

t_queue	*init_file_q(int fd)
{
	t_queue *new_q;

	if (!(new_q = malloc(sizeof(t_queue))))
		return (NULL);
	new_q->fd = fd;
	new_q->len = 0;
	new_q->first = NULL;
	new_q->last = NULL;
	new_q->next = NULL;
	return (new_q);
}

t_queue	*set_file_q(t_queue *qlist, int fd)
{
	t_queue	*qptr;
	t_queue	*file_q;

	file_q = init_file_q(fd);
	if (!(qptr = qlist->next))
		return ((qlist->next = file_q));
	while (qptr->next && (fd > qptr->next->fd))
		qptr = qptr->next;
	file_q->next = qptr->next;
	qptr->next = file_q;
	return (file_q);
}

t_queue	*get_file_q(t_queue *qlist, int fd)
{
	t_queue	*file_q;

	file_q = qlist;
	while (file_q->next && (file_q->fd < fd))
		file_q = file_q->next;
	if (file_q->fd == fd)
		return (file_q);
	return (NULL);
}
