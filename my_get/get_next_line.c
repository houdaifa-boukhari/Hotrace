/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tale <aet-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:55:51 by aet-tale          #+#    #+#             */
/*   Updated: 2024/01/30 16:02:36 by aet-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	sl;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	sl = ft_strlen(s);
	if (start >= sl)
		len = 0;
	else if (start + len >= sl)
		len = sl - start;
	if (len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i + 1);
	return (line);
}

char	*ft_new_str(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !str[i + 1])
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	i++;
	new_str = ft_substr(str, i, ft_strlen(str + i));
	free(str);
	return (new_str);
}

char	*ft_get_buff(int fd, char *str)
{
	char	*buff;
	char	*tmp;
	int		char_read;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	tmp = str;
	char_read = 1;
	while (char_read)
	{
		char_read = read(fd, buff, BUFFER_SIZE);
		if (char_read == 0)
			break ;
		buff[char_read] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd > OPEN_MAX)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_get_buff(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_new_str(str);
	return (line);
}
