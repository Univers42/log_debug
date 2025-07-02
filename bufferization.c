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
# include "auto_parser.h"

void	buffer_append_char(t_buffer buffer, int *pos, char c)
{
	if (*pos < 1023)
		buffer[(*pos)++] = c;
}

void	buffer_append_str(t_buffer buffer, int *pos, const char *str)
{
	while (*str && *pos < 1023)
		buffer[(*pos)++] = *str++;
}

void	buffer_append_str_formatted(t_buffer buffer, int *pos,
	const char *str, t_format_spec *spec)
{
	int	len;
	int	padding;
	int	i;
	int	max_chars;

	len = 0;
	if (str)
		len = strlen(str);
	max_chars = len;
	if (spec->has_precision && spec->precision < len)
		max_chars = spec->precision;
	padding = 0;
	if (spec->width > max_chars)
		padding = spec->width - max_chars;
	if (!spec->left_align && padding > 0)
	{
		i = -1;
		while (++i < padding && *pos < 1023)
			buffer[(*pos)++] = ' ';
	}
	i = -1;
	while (++i < max_chars && *pos < 1023)
		buffer[(*pos)++] = str[i];
	if (spec->left_align && padding > 0)
	{
		i = -1;
		while (++i < padding && *pos < 1023)
			buffer[(*pos)++] = ' ';
	}
}

static void	reverse_string(char *str, int len)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static int	convert_to_string(long num, char *temp, int base, int uppercase)
{
	int		temp_pos;
	char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	temp_pos = 0;
	if (num == 0)
		temp[temp_pos++] = '0';
	else
	{
		while (num > 0)
		{
			temp[temp_pos++] = digits[num % base];
			num /= base;
		}
	}
	return (temp_pos);
}

void	buffer_append_int_formatted(t_buffer buffer, int *pos,
	long num, t_format_spec *spec, int base)
{
	char	temp[64];
	int		temp_pos;
	int		is_negative;
	int		uppercase;

	is_negative = 0;
	uppercase = (spec->specifier == 'X');
	if (num < 0 && base == 10)
	{
		is_negative = 1;
		num = -num;
	}
	temp_pos = convert_to_string(num, temp, base, uppercase);
	if (is_negative)
		temp[temp_pos++] = '-';
	else if (spec->show_sign && base == 10)
		temp[temp_pos++] = '+';
	else if (spec->space_prefix && base == 10)
		temp[temp_pos++] = ' ';
	reverse_string(temp, temp_pos);
	temp[temp_pos] = '\0';
	buffer_append_str(buffer, pos, temp);
}

void	put_level_buffered(t_buffer buffer, int *pos, t_log_level level)
{
	t_parser_tables	*tables;

	tables = get_parser_tables();
	if (level >= 0 && level < 5 && tables->level_strings[level])
		buffer_append_str(buffer, pos, tables->level_strings[level]);
	else
		buffer_append_str(buffer, pos, "[UNKNOWN] ");
}

