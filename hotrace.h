#ifndef HOTRACE_H
# define HOTRACE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// # include "./get_next_line/get_next_line.h"
// #include <sys/time.h> // for gettimeofday

#define TABLE_SIZE 1048576

typedef struct hash_node_s
{
	 char *key;
	 char *value;
	 struct hash_node_s *next;
} hash_node_t;


typedef struct hash_table_s
{
	 unsigned long int size;
	 hash_node_t **array;
} hash_table_t;

void ft_putstr_fd(char *str, int fd);
bool	handle_input(hash_table_t **ht);
hash_table_t    *hash_table_create(unsigned long int size);
// unsigned long int hash_djb2(const  char *str);
unsigned long int hash_djb2(const unsigned char *str);
unsigned long int key_index(const unsigned char *key, unsigned long int size);
int		hash_table_set(hash_table_t *ht, char *key, char *value);
char	*hash_table_get(const hash_table_t *ht, const char *key);
void	hash_table_print(const hash_table_t *ht);
void	hash_table_delete(hash_table_t *ht);
char *get_line(void);


#endif