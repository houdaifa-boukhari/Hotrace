/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:53:07 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 13:01:59 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

// real    0m43.707s // murmur
// user    0m13.231s
// sys     0m30.451s

// real    0m48.682s // djb2
// user    0m16.453s
// sys     0m31.936s


unsigned long int murmur_hash3(const unsigned char *key, unsigned long int len) {
    unsigned long int hash = 0;
    unsigned int c1 = 0xCC9E2D51, c2 = 0x1B873593;
    unsigned long int k = 0;
    unsigned int i = 0;

    // Process the key in chunks of 4 bytes
    while (len >= 4) {
        // Get the next 4 bytes
        k = key[i] | key[i + 1] << 8 | key[i + 2] << 16 | key[i + 3] << 24;

        // Mix the bytes using the Murmur hash method
        k *= c1;
        k = (k << 15) | (k >> 17);  // Rotate left by 15
        k *= c2;

        hash ^= k;
        hash = (hash << 13) | (hash >> 19);  // Rotate left by 13
        hash = hash * 5 + 0xE6546B64;

        i += 4;
        len -= 4;
    }

    // Handle the remaining bytes (1-3)
    if (len) {
        k = 0;
        for (int j = len - 1; j >= 0; j--) {
            k |= key[i++] << (8 * j);
        }
        k *= c1;
        k = (k << 15) | (k >> 17);  // Rotate left by 15
        k *= c2;

        hash ^= k;
    }

    // Finalize the hash
    hash ^= len;
    hash = hash ^ (hash >> 16);
    hash = hash * 0x85EBCA6B;
    hash = hash ^ (hash >> 13);
    hash = hash * 0xC2B2AE35;
    hash = hash ^ (hash >> 16);

    return hash;
}


// unsigned long int hash_djb2(const unsigned char *str) {
//     unsigned long hash = 5381;
//     char c;

//     while ((c = *str++)) {
//         __asm__ __volatile__ (
//             "leal (%1, %1, 4), %0\n\t"  // hash * 5
//             "leal (%0, %1, 8), %0"      // hash * 33
//             : "=&r" (hash)
//             : "r" (hash), "0" (hash)
//         );
//         hash += c;
//     }
//     return hash;
// }


unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
		hash = hash * 33 + c;
	return (hash);
}

unsigned long int key_index(const unsigned char *key, unsigned long int size) {
    unsigned long int len = 0;

    // Find the length of the key
    while (key[len] != '\0') {
        len++;
    }

    // Compute the index using MurmurHash3
    return (murmur_hash3(key, len) & (size - 1));
}

// unsigned long int key_index(const unsigned char *key, unsigned long int size)
// {
// 	return (hash_djb2(key) & (size - 1));
// }

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
		if (strcmp(ptr->key, key) == 0) // implement a more comparing function
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
		line = get_line();
		if (!line)
			break;
		// struct timeval start, end;
		// long time_taken;
		
		// get current time
		// gettimeofday(&start, NULL);
		
		tmp = hash_table_get(ht, line);
		
		// // calculate the time
		// gettimeofday(&end, NULL);
		
		// time_taken = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
		// fprintf(stderr, "Time taken for lookup: %ld microseconds\n", time_taken);
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
		char *line = get_line();
		if (!line)
			break;
		if (line[0] == '\n' && no_empty)
			return (search_key(tmp));
		key = line;
		value = get_line();
		if (value)
		{
			hash_table_set(tmp, key, value);
			no_empty = true;
		}
	}
	return (true);
}
