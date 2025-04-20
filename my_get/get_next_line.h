/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tale <aet-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:07:08 by aet-tale          #+#    #+#             */
/*   Updated: 2024/01/30 15:51:25 by aet-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_get_line(char *str);
char	*ft_new_str(char *str);
char	*ft_get_buff(int fd, char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif