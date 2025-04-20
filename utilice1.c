/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:57:16 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 17:45:41 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	refill_buffer(char *buf, ssize_t *len, ssize_t *pos)
{
	*len = read(0, buf, READ_SIZE);
	*pos = 0;
	return (*len > 0);
}

static int	resize_line(char **line, size_t *alloc, size_t needed)
{
	char	*new;

	if (needed < *alloc)
		return (1);
	new = ft_realloc(*line, *alloc, *alloc * 2);
	if (!new)
		return (0);
	*line = new;
	*alloc *= 2;
	return (1);
}

static int	handle_buffer(t_line *line_data, t_buffer *buffer, int *done)
{
	while (buffer->pos < buffer->len && !(*done))
	{
		if (!resize_line(&line_data->line, &line_data->alloc,
				line_data->line_len + 1))
			return (0);
		line_data->line[line_data->line_len] = buffer->buf[buffer->pos++];
		*done = (line_data->line[line_data->line_len++] == '\n');
	}
	return (1);
}

static char	*finalize_line(t_line *line_data)
{
	char	*tmp;

	if (line_data->line_len == 0)
		return (free(line_data->line), NULL);
	line_data->line[line_data->line_len] = '\0';
	if (line_data->line_len + 1 < (long)(line_data->alloc / 2))
	{
		tmp = ft_realloc(line_data->line, line_data->alloc, line_data->line_len
				+ 1);
		if (tmp)
			line_data->line = tmp;
	}
	return (line_data->line);
}

char	*get_line(void)
{
	static t_buffer	buffer = {{0}, 0, 0};
	t_line			line_data;
	int				done;

	done = 0;
	line_data.line_len = 0;
	line_data.alloc = INITIAL_ALLOC;
	line_data.line = (char *)malloc(line_data.alloc);
	if (!line_data.line)
		return (NULL);
	while (!done)
	{
		if (buffer.pos >= buffer.len && !refill_buffer(buffer.buf, &buffer.len,
				&buffer.pos))
			break ;
		if (!handle_buffer(&line_data, &buffer, &done))
			return (free(line_data.line), NULL);
	}
	return (finalize_line(&line_data));
}
