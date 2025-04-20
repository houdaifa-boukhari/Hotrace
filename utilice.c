/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:43:45 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 13:08:30 by hel-bouk         ###   ########.fr       */
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
#define INITIAL_ALLOC 128  // Start with smaller allocation

// Custom realloc implementation
void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    // If new size is 0, act like free
    if (new_size == 0)
    {
        if (ptr)
            free(ptr);
        return NULL;
    }
    
    // Allocate new buffer
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    
    // If original pointer exists, copy data and free old buffer
    if (ptr)
    {
        size_t copy_size = (old_size < new_size) ? old_size : new_size;
        char *src = (char *)ptr;
        char *dst = (char *)new_ptr;
        
        // Manual memory copy
        for (size_t i = 0; i < copy_size; i++)
            dst[i] = src[i];
            
        free(ptr);
    }
    
    return new_ptr;
}

// Get a line from standard input
char *get_line(void)
{
    static char buffer[READ_SIZE];
    static ssize_t buf_len = 0;
    static ssize_t buf_pos = 0;
    
    // Initial allocation - start small and grow as needed
    size_t alloc_size = INITIAL_ALLOC;
    char *line = malloc(alloc_size);
    if (!line)
        return NULL;
    
    ssize_t line_len = 0;
    int line_complete = 0;
    
    while (!line_complete)
    {
        // If buffer is empty, refill it
        if (buf_pos >= buf_len)
        {
            buf_len = read(0, buffer, READ_SIZE);
            if (buf_len <= 0)
                break;  // End of file or error
            buf_pos = 0;
        }
        
        // Process current buffer
        while (buf_pos < buf_len && !line_complete)
        {
            // Check if we need to expand the line buffer
            if (line_len + 1 >= alloc_size)
            {
                size_t new_size = alloc_size * 2;
                char *new_line = my_realloc(line, alloc_size, new_size);
                if (!new_line)
                {
                    free(line);
                    return NULL;
                }
                line = new_line;
                alloc_size = new_size;
            }
            
            // Get current character
            char c = buffer[buf_pos++];
            line[line_len++] = c;
            
            // If newline, we're done with this line
            if (c == '\n')
            {
                line_complete = 1;
                break;
            }
        }
    }
    
    // Return NULL if no data was read
    if (line_len == 0)
    {
        free(line);
        return NULL;
    }
    
    // Resize allocation to actual length (only if significantly smaller)
    if (line_len + 1 < alloc_size / 2)
    {
        char *resized = my_realloc(line, alloc_size, line_len + 1);
        if (resized)
            line = resized;
    }
    
    // Null-terminate the string
    line[line_len] = '\0';
    return line;
}