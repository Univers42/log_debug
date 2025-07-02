/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:59:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 13:59:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

static inline int	buffer_space_left(int pos)
{
	return (1023 - pos);
}

static inline int	can_append(int pos, int len)
{
	return (pos + len <= 1023);
}

int	verify_buffer_integrity(t_buffer buffer, int pos)
{
	(void)buffer;
	if (pos < 0 || pos >= 1024)
		return (0);
	if (buffer_space_left(pos) < 0)
		return (0);
	return (1);
}

int	safe_buffer_append(t_buffer buffer, int *pos, const char *str, int len)
{
	if (!verify_buffer_integrity(buffer, *pos))
		return (0);
	if (!can_append(*pos, len))
		return (0);
	while (len-- > 0 && *str && *pos < 1023)
		buffer[(*pos)++] = *str++;
	return (1);
}