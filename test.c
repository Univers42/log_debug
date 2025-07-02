/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 15:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

int	main(void)
{
	log_msg(LOG_INFO, "Starting test program");
	log_msg(LOG_DEBUG, "Debug message with number: %d", 42);
	log_msg(LOG_WARNING, "Warning with string: %s", "test");
	log_msg(LOG_ERROR, "Error with hex: %x", 255);
	log_msg(LOG_SUCCESS, "Success with char: %c", 'A');
	log_msg(LOG_INFO, "Complex format: %s has %d items", "List", 5);
	log_msg(LOG_DEBUG, "Pointer test: %p", (void *)0x12345678);
	log_msg(LOG_INFO, "Unsigned: %u, Octal: %o", 100, 64);
	log_msg(LOG_ERROR, "Hex upper: %X, lower: %x", 255, 255);
	log_msg(LOG_SUCCESS, "Test completed successfully!");
	return (0);
}
