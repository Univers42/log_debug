/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:32:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 14:02:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
	Instead of calling spagetti code ft ft_printf, let's recode logs function
	that give more send to a debug maintainability in both client and server.
 */
# include "minitalk.h"

static void	buffer_append(t_string buffer, int *pos, const char *str)
{
	while (*str && *pos < 1023)
		buffer[(*pos)++] = *str++;
}

static inline void buffer_append_number(t_string buffer, int *pos, int num) {
    if (num < 0) {
        buffer[(*pos)++] = '-';
        num = -num;
    }
    
    // Convert directly without reversal
    char *start = buffer + *pos;
    char *p = start;
    
    do {
        *p++ = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    
    *pos = p - buffer;
    
    // Reverse in place
    char *end = p - 1;
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

static inline put_level_buffered(t_string buffer, int *pos, t_log_level level)
{
	t_parser_tables *tables;

	tables = get_parser_tables();
	if (level >= 0 && level < 5 && tables->level_strings[level])
		buffer_append_str(buffer, pos, tables->level_strings[level]);
	else
		buffer_append_str(buffer, pos, "[UNKNOWN]");
}

