/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:20:52 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/28 11:11:48 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
		return (len);
	}
	return (0);
}

void	ft_putstr_fd(char *str, int fd, int flag)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		if (!flag)
		{
			if (str[len - 1] == '\n')
				write(fd, str, len - 1);
			else
				write(fd, str, len);
		}
		else
			write(fd, str, len);
	}
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = src;
	d = dest;
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = (void *)malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
