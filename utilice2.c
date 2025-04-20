/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:10:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 15:10:18 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*hash_table_get(const t_hash_table *ht, const char *key)
{
	unsigned long int	idx;
	t_hash_node			*ptr;

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

int	hash_table_set(t_hash_table *ht, char *key, char *value)
{
	unsigned long int	idx;
	t_hash_node			*hash;

	if (!ht || !ht->array || ht->size == 0 || !key || !value)
		return (0);
	idx = key_index((const unsigned char *)key, ht->size);
	hash = ht->array[idx];
	while (hash)
	{
		if (strcmp(hash->key, key) == 0)
			return (1);
		hash = hash->next;
	}
	hash = (t_hash_node *)malloc(sizeof(t_hash_node));
	if (!hash)
		return (0);
	hash->key = key;
	hash->value = value;
	hash->next = ht->array[idx];
	ht->array[idx] = hash;
	return (1);
}