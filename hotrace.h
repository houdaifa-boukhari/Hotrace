/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:02:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 15:03:20 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TABLE_SIZE 1048576
# define READ_SIZE 8192
# define INITIAL_ALLOC 128

typedef struct hash_node_s
{
	char				*key;
	char				*value;
	struct hash_node_s	*next;
}						t_hash_node;

typedef struct hash_table_s
{
	unsigned long int	size;
	t_hash_node			**array;
}						hash_table_t;

typedef struct s_buffer
{
	char				buf[READ_SIZE];
	ssize_t				len;
	ssize_t				pos;
}						t_buffer;

typedef struct s_line
{
	char				*line;
	size_t				alloc;
	ssize_t				line_len;
}						t_line;

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void					ft_putstr_fd(char *str, int fd);
bool					handle_input(hash_table_t **ht);
hash_table_t			*hash_table_create(unsigned long int size);
unsigned long int		hash_djb2(const unsigned char *str);
unsigned long int		key_index(const unsigned char *key,
							unsigned long int size);
int						hash_table_set(hash_table_t *ht, char *key,
							char *value);
char					*hash_table_get(const hash_table_t *ht,
							const char *key);
// void	hash_table_delete(hash_table_t *ht);
char					*get_line(void);

#endif