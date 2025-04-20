/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tale <aet-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:10:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 15:12:29 by aet-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int ft_strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 && *p1 == *p2) {
        p1++;
        p2++;
    }
    return (*p1 - *p2);
}

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
		if (ft_strcmp(ptr->key, key) == 0)
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
		if (ft_strcmp(hash->key, key) == 0)
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