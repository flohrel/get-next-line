/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:14 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/07 15:32:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

typedef struct	s_buf	t_buf;
struct s_buf
{
	size_t	size;
	char	*data;
	t_buf	*next;
};

typedef struct	s_queue	t_queue;
struct s_queue
{
	int		fd;
	size_t	len;
	t_buf	*first;
	t_buf	*last;
	t_queue	*next;
};

int		get_next_line(int fd, char **line);
char	*ft_strchr(char *str, int c, size_t size);
char	*ft_memcpy(char *dst, char *src, size_t size);
t_queue	*get_file_q(t_queue *qlist, int fd);
t_queue	*set_file_q(t_queue *qlist, int fd);
t_queue	*init_file_q(int fd);

#endif
