/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:02:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/28 11:11:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdbool.h>
# include <stdlib.h>
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
}						t_hash_table;

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

typedef struct s_input
{
	char				*key;
	char				*line;
	char				*value;
	bool				no_empty;
}						t_input;

void					*ft_realloc(void *ptr, size_t old_size,
							size_t new_size);
void					ft_putstr_fd(char *str, int fd, int flag);
bool					handle_input(t_hash_table **ht);
t_hash_table			*hash_table_create(unsigned long int size);
unsigned long int		hash_djb2(const unsigned char *str);
unsigned long int		key_index(const unsigned char *key,
							unsigned long int size);
int						hash_table_set(t_hash_table *ht, char *key,
							char *value);
char					*hash_table_get(const t_hash_table *ht,
							const char *key);
void					hash_table_delete(t_hash_table *ht);
char					*get_line(void);
int						ft_strcmp(const char *s1, const char *s2);

#endif