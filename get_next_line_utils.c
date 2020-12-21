/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 22:49:04 by flohrel           #+#    #+#             */
/*   Updated: 2020/12/17 03:30:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy(char *dest, char *src, size_t n)
{
	char *d;

	if (!dest || !src)
		return (dest);
	d = dest;
	while (n--)
		*d++ = *src++;
	return (dest);
}

char	*ft_memchr(char *s, int c, size_t len)
{
	if (!s || !len)
		return (NULL);
	while (len--)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

t_list	*ft_lstnew(char *buf, size_t len)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (new);
	new->buf = buf;
	new->len = len;
	new->next = NULL;
	return (new);
}

t_list	*qpush(t_queue *q, char *buf, size_t len)
{
	t_list	*new;

	new = ft_lstnew(buf, len);
	if (!new)
		return (new);
	if (!(q->front))
		q->front = new;
	if (q->back)
		q->back->next = new;
	q->back = new;
	q->size += len;
	return (new);
}

void	qpop(t_queue *q)
{
	t_list	*lst;

	lst = q->front;
	q->front = lst->next;
	free(lst->buf);
	free(lst);
}
