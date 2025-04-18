/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:51:46 by hel-bouk          #+#    #+#             */
/*   Updated: 2025/04/18 16:50:01 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int main()
{
	hash_table_t	*ht;

	ht = hash_table_create(1024);
	if (!ht)
	{
		write(2, "Error: Could not create hash table\n", 36);
		return (1);
	}
	if (!handle_input(&ht))
	{
		// hash_table_delete(ht);
		write(2, "Error: Could not handle input\n", 31);
		return (1);
	}
}