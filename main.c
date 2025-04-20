/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:51:46 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/20 15:00:52 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	main(void)
{
	hash_table_t	*ht;

	ht = hash_table_create(TABLE_SIZE);
	if (!ht)
	{
		write(2, "Error: Could not create hash table\n", 36);
		return (1);
	}
	handle_input(&ht);
	// hash_table_delete(ht);
	return (0);
}
