/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 22:49:05 by flohrel           #+#    #+#             */
/*   Updated: 2020/12/17 03:03:17 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

typedef struct	s_list
{
	size_t			len;
	char			*buf;
	struct s_list	*next;
}				t_list;

typedef struct	s_queue
{
	size_t	size;
	t_list	*front;
	t_list	*back;
}				t_queue;

int			get_next_line(int fd, char **line);
char		*ft_memchr(char *s, int c, size_t len);
char		*ft_memcpy(char *dest, char *src, size_t n);
t_list		*ft_lstnew(char *buf, size_t len);
t_list		*qpush(t_queue *q, char *buf, size_t len);
void		qpop(t_queue *q);

#endif
