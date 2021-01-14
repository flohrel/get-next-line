/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:14 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/14 16:10:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

# define MAX_FD			2048

# define TRUE			1
# define FALSE			0

typedef char	t_bool;

typedef struct	s_buf
{
	size_t			size;
	char			*data;
	struct s_buf	*next;
}				t_buf;

typedef struct	s_queue
{
	size_t	len;
	t_buf	*tmp;
	t_buf	*first;
	t_buf	*last;
}				t_queue;

int				get_next_line(int fd, char **line);
char			*ft_strchr(char *str, int c, size_t size);
char			*ft_memcpy(char *dst, char *src, size_t size);
t_queue			*init_file_queue(t_queue *file_q);
int				push(t_queue *file_q, char *buf, size_t size, t_bool is_tmp);
void			pop(t_queue *file_q, t_bool is_tmp);

#endif
