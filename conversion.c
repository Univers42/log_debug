/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:58:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 13:58:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

static int	count_digits(unsigned long num, int base)
{
	int	count;

	if (num == 0)
		return (1);
	count = 0;
	while (num > 0)
	{
		num /= base;
		count++;
	}
	return (count);
}

static void	fill_number_string(char *str, unsigned long num, int base, int uppercase)
{
	int		len;
	char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = count_digits(num, base);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	else
	{
		while (num > 0)
		{
			str[--len] = digits[num % base];
			num /= base;
		}
	}
}

int	convert_number_to_string(char *dest, long num, int base, int uppercase)
{
	unsigned long	unum;
	int				offset;

	offset = 0;
	if (num < 0 && base == 10)
	{
		unum = -num;
		dest[0] = '-';
		offset = 1;
	}
	else
		unum = num;
	fill_number_string(dest + offset, unum, base, uppercase);
	return (ft_strlen(dest));
}

int	format_with_precision(char *dest, const char *src, t_format_spec *spec)
{
	int	src_len;
	int	precision;
	int	i;

	src_len = ft_strlen(src);
	precision = spec->precision;
	if (!spec->has_precision)
		precision = src_len;
	if (precision > src_len)
		precision = src_len;
	i = 0;
	while (i < precision)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}