/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:53:07 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 15:11:21 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

unsigned long int	hash_djb2(const unsigned char *str)
{
	int					c;
	unsigned long int	hash;

	hash = 5381;
	c = *str;
	while (c != '\0')
	{
		hash = hash * 33 + c;
		str++;
		c = *str;
	}
	return (hash);
}

unsigned long int	key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) & (size - 1));
}

t_hash_table	*hash_table_create(unsigned long int size)
{
	t_hash_table		*hash_table;
	unsigned long int	i;

	hash_table = NULL;
	i = 0;
	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	if (!hash_table)
		return (NULL);
	hash_table->size = size;
	hash_table->array = (t_hash_node **)malloc(sizeof(t_hash_node *) * (size));
	if (!hash_table->array)
	{
		free(hash_table);
		return (NULL);
	}
	while (i < size)
		hash_table->array[i++] = NULL;
	return (hash_table);
}

bool	search_key(t_hash_table *ht)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		line = get_line();
		if (!line)
			break ;
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

bool	handle_input(t_hash_table **ht)
{
	char			*key;
	char			*line;
	char			*value;
	bool			no_empty;
	t_hash_table	*tmp;

	tmp = *ht;
	no_empty = false;
	while (1)
	{
		key = NULL;
		value = NULL;
		line = get_line();
		if (!line)
			break ;
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
