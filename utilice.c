#include "hotrace.h"
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 8192
#define INITIAL_ALLOC 128

/* Helper for ft_putstr_fd */
static int strlength(char *str) {
    int len = 0;
    if (str) while (str[len]) len++;
    return len;
}

void ft_putstr_fd(char *str, int fd) {
    int len = strlength(str);
    if (len > 0) {
        str[len - 1] = '\0';
        write(fd, str, len - 1);
    }
}

void *my_memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    while (n-- > 0) {
        if (*p == (unsigned char)c)
            return (void *)p;
        p++;
    }
    return NULL;
}

void *my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n-- > 0)
        *d++ = *s++;
    return dest;
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    void *new_ptr = malloc(new_size);
    if (!new_ptr) return NULL;
    if (ptr) {
        size_t copy_size = old_size < new_size ? old_size : new_size;
        my_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return new_ptr;
}

/* Helpers for get_line */
static int refill_buffer(char *buf, ssize_t *len, ssize_t *pos) {
    *len = read(0, buf, READ_SIZE);
    *pos = 0;
    return *len > 0;
}

static int resize_line(char **line, size_t *alloc, size_t needed) {
    if (needed < *alloc) return 1;
    char *new = my_realloc(*line, *alloc, *alloc * 2);
    if (!new) return 0;
    *line = new;
    *alloc *= 2;
    return 1;
}

char *get_line(void) {
    static char buf[READ_SIZE];
    static ssize_t len = 0, pos = 0;
    size_t alloc = INITIAL_ALLOC;
    char *line = malloc(alloc);
    ssize_t line_len = 0;
    int done = 0;

    if (!line) return NULL;
    while (!done) {
        if (pos >= len && !refill_buffer(buf, &len, &pos)) break;
        while (pos < len && !done) {
            if (!resize_line(&line, &alloc, line_len + 1)) {
                free(line);
                return NULL;
            }
            line[line_len] = buf[pos++];
            done = (line[line_len++] == '\n');
        }
    }
    if (line_len == 0) {
        free(line);
        return NULL;
    }
    line[line_len] = '\0';
    if (line_len + 1 < alloc / 2) {
        char *tmp = my_realloc(line, alloc, line_len + 1);
        if (tmp) line = tmp;
    }
    return line;
}
