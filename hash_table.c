/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:53:07 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/18 17:49:43 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"


unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
		hash = hash * 33 + c;
	return (hash);
}

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}

hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *hash_table = NULL;
	unsigned long int i = 0;

	hash_table = (hash_table_t *)malloc(sizeof(hash_table_t));
	if (!hash_table)
		return (NULL);
	hash_table->size = size;
	hash_table->array = (hash_node_t **)malloc(sizeof(hash_node_t *) * (size));
	if (!hash_table->array)
	{
		free(hash_table);
		return (NULL);
	}
	while (i < size)
		hash_table->array[i++] = NULL;
	return (hash_table);
}

int hash_table_set(hash_table_t *ht, char *key, char *value)
{
	unsigned long int	idx;
	hash_node_t *hash;

	if (!ht || !ht->array || ht->size == 0 || !key || !value)
		return (0);
	idx = key_index((const unsigned char *)key, ht->size);
	hash = ht->array[idx];
	while (hash)
	{
		if (strcmp(hash->key, key) == 0)
		{
			// free(hash->value);
			// hash->value = value;
			return (1);
		}
		hash = hash->next;
	}
	hash = (hash_node_t *)malloc(sizeof(hash_node_t));
	if (!hash)
		return (0);
	hash->key = key;
	hash->value = value;
	hash->next = ht->array[idx];
	ht->array[idx] = hash;
	return (1);
}

char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int idx;
	hash_node_t		*ptr;

	if (!ht || !ht->array || ht->size == 0 || !key)
		return (NULL);
	idx = key_index((const unsigned char *)key, ht->size);
	ptr = ht->array[idx];
	while (ptr)
	{
		if (strcmp(ptr->key, key) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}



bool search_key(hash_table_t *ht)
{
	char *line;
	char *tmp;

	tmp = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break;
		tmp = hash_table_get(ht, line);
		if (!tmp)
		{
			ft_putstr_fd(line, 2);
			write(2, ": Not found.\n", 13);	
		}
		else
		{
			ft_putstr_fd(tmp, 1);
			write(1, "\n", 1);
		}
		free(line);
	}
	return (true);
}

bool	handle_input(hash_table_t **ht)
{
	bool no_empty = false;
	char *key = NULL, *value = NULL;
	hash_table_t *tmp;

	tmp = *ht;
	while (1)
	{
		key = NULL;
		value = NULL;
		char *line = get_next_line(0);
		if (!line)
			break;
		if (line[0] == '\n' && no_empty)
			return (search_key(tmp));
		key = line;
		value = get_next_line(0);
		if (value)
		{
			hash_table_set(tmp, key, value);
			no_empty = true;
		}
	}
	return (true);
}
