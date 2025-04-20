/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:43:45 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 13:00:25 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void ft_putstr_fd(char *str, int fd)
{
	int len;
	if (!str)
		return ;
	len = strlen(str);
	if (len == 0)
		return ;
	str[len - 1] = '\0';
	write(fd, str, len - 1);		
}

// Custom memchr (finds first occurrence of 'c' in 's' within 'n' bytes)
void *my_memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == (unsigned char)c)
            return (void *)(p + i);
    }
    return NULL;
}

void *my_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

#define READ_SIZE 8192
#define LINE_MAX 1048576  // 1MB max line length

char *get_line(void)
{
    static char buffer[READ_SIZE];
    static ssize_t buf_len = 0;
    static ssize_t buf_pos = 0;
    
    // Allocate memory only when needed
    char *line = malloc(LINE_MAX);
    if (!line)
        return NULL;
    
    ssize_t line_len = 0;
    
    // Copy chunks of data instead of byte-by-byte when possible
    while (1)
    {
        // If buffer is empty, refill it
        if (buf_pos >= buf_len)
        {
            buf_len = read(0, buffer, READ_SIZE);
            if (buf_len <= 0)
                break;
            buf_pos = 0;
        }
        
        // Calculate how many bytes we can copy at once
        ssize_t remaining_in_buffer = buf_len - buf_pos;
        ssize_t space_in_line = LINE_MAX - line_len - 1;
        ssize_t chunk_size = remaining_in_buffer;
        
        // Look for newline in current buffer chunk
        char *newline_pos = my_memchr(buffer + buf_pos, '\n', remaining_in_buffer);
        if (newline_pos)
            chunk_size = newline_pos - (buffer + buf_pos) + 1;
        
        // Don't copy more than we have space for
        if (chunk_size > space_in_line)
            chunk_size = space_in_line;
        
        // Copy the chunk
        my_memcpy(line + line_len, buffer + buf_pos, chunk_size);
        line_len += chunk_size;
        buf_pos += chunk_size;
        
        // Check if we hit a newline or filled the buffer
        if (newline_pos || line_len >= LINE_MAX - 1)
            break;
    }
    
    // Return NULL if no data was read
    if (line_len == 0)
    {
        free(line);
        return NULL;
    }
    
    // Resize allocation to actual length (optional optimization)
    char *resized = realloc(line, line_len + 1);
    if (resized)
        line = resized;
    
    line[line_len] = '\0';
    return line;
}