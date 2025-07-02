/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:34:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 14:21:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_PARSER_H
# define AUTO_PARSER_H
# include "../../libft/libft.h"



typedef char t_string[1024];
typedef enum
{
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_DEBUG,
	LOG_SUCCESS
}	t_log_level;

# ifndef
#  define MINITALK_DEBUG 1
# endif
# define CHAR_TABLE_SIZE 256
# define CHAR_DIGIT 0x01
# define CHAR_FLAG 0x02
# define CHAR_SPEC 0x04
# define CHAR_LENGTH 0x08
# define CHAR_DOT 0x10
# define CHAR_PERCENT 0x20

typedef enum 
{
	STATE_NORMAL,		//Regular character copying
	STATE_PERCENT,		// Found '%', deciding next action
	STATE_FLAGS,		// Processing flags like '-', '+', ' '. '#', '0'
	STATE_WIDTH,		// Processing width specifier
	STATE_PRECISION,	// Processing precision after '.'
	STATE_LENGTH,		// Processing length modifier lkike 'l', 'h'
	STATE_SPECIFIER,	// Processing length modifiers like 's', 'd', 'x'
	STATE_ERROR			// Invalid format sequence
} t_format_state;

typedef struct  s_format_spec
{
	int		width;
	int		precision;
	int		left_align;
	int		show_sign;
	int		space_prefix;
	int		alt_form;
	int		zero_pad;
	int		has_precision;
	char	length_mod;
	char	specifier;
}	t_format_spec;

typedef struct s_parser_ctx
{
	t_format_state state;
	t_format_spec	spec;
	const char *fmt_ptr;
	int	temp_num;
	va_list *args;
	t_string buffer;
	int	*pos;
}	t_parser_ctx;

// Action function types
typedef struct parser_context t_parser_ctx;
typedef t_format_state (*t_state_action)(t_parser_ctx)
typedef t_format_state (*state_handler_t)(t_parser_ctx *ctx, char c);
typedef void (*t_flag_action)(t_format_spec *spec);
typedef void (*spec_action_t)(t_parser_ctx *ctx);

// Singleton structure
typedef struct s_parser_tables
{
	t_flag initialized;
	unsigned char char_class_table[CHAR_TABLE_SIZE];
	t_state_action state_transition_table[STATE_COUNT];
	t_flag_action flag_table[CHAR_TABLE_SIZE]
	t_spec_action spec_table[CHAR_TABLE_SIZE];
	const char *level_strings[5];
}				t_parser_tables;

// Declarations for state actions
format_state_t action_normal(parser_context_t *ctx, char c);
format_state_t action_percent(parser_context_t *ctx, char c);
format_state_t action_flags(parser_context_t *ctx, char c);
format_state_t action_width(parser_context_t *ctx, char c);
format_state_t action_precision(parser_context_t *ctx, char c);
format_state_t action_length(parser_context_t *ctx, char c);
format_state_t action_specifier(parser_context_t *ctx, char c);
format_state_t action_error(parser_context_t *ctx, char c);

// Declarations for flag action
void flag_left_align(format_spec_t *spec);
void flag_show_sign(format_spec_t *spec);
void flag_space_prefix(format_spec_t *spec);
void flag_alt_form(format_spec_t *spec);
void flag_zero_pad(format_spec_t *spec);

// Declarations for specifier actions
void spec_string(parser_context_t *ctx);
void spec_decimal(parser_context_t *ctx);
void spec_integer(parser_context_t *ctx);
void spec_char(parser_context_t *ctx);
void spec_hex_lower(parser_context_t *ctx);
void spec_hex_upper(parser_context_t *ctx);
void spec_octal(parser_context_t *ctx);
void spec_unsigned(parser_context_t *ctx);
void spec_float(parser_context_t *ctx);
void spec_pointer(parser_context_t *ctx);


static const t_state_handler state_handler[] = 
{
	[STATE_NORMAL] = handle_normal,
	[STATE_PERCENT] = handle_percent,
	[STATE_FLAGS] = handler_flags,
	[STATE_WIDTH] = handle_width,
	[STATE_PRECISION] = handle_precision,
	[STATE_LENGTH] = handle_length,
	[STATE_SPECIFIER] = handle_specifier,
	[STATE_ERROR] = handle_error
};

static inline int buffer_space_left(int pos)
{
	return (1023 - pos);
}

static inline int can_append(int pos, int len)
{
	return (pos + len <=1023)
}

static void buffer_append_char(t_string buffer, int *pos, char c)
{
	if (*pos < 1023)
		buffer[(*pos)++] = c;
}

static void buffer_append_str(t_string buffer, int *pos, const char *str)
{
	while (*str && *pos < 1023)
		buffer[(*pos)++] = *str++;
}

static void buffer_append_str_formatted(t_string_buffer, int *pos, const char *str, t_format_spec *spec)
{
	int len;
	int padding;
	char pad_char;
	int i;
	int max_chars;

	len = 0;
	if (str)
		len = strlen(str);
	padding = 0;
	if (!spec->left_align && padding > 0)
	{
		pad_char = 0;
		if (spec->zero_pad)
			pad_char = ' ';
		i = -1;
		while (++i < padding && *pos < 1023)
			buffer[(*pos)++] = pad_char;
	}
	max_chars = len;
	if (spec->has_precision)
		max_chars = spec->precision;
	if (max_chars > len)
		max_chars = len;
	i = -1;
	while (++i < max_chars && *pos < 1023)
		bufer[(*pos)++] = str[i];
	if (spec->left_align && padding > 0)
	{
		i = -1;
		while (++i < padding && *pos < 1023)
			buffer[(*pos)++] = ' ';
	}
}

static void buffer_append_int_formatted(t_string_buffer, int *pos, int num, t_format_spec *spec)
{
	char temp[32];
	int temp_pos;
	int is_negative;
	char swap;

	if (num < 0)
	{
		is_negative = -1;
		num = -num;
	}
	if (num == 0)
		temp[temp_pos++] = '0';
	else
	{
		while (num > 0)
		{
			temp[temp_pos++] = (num % 10) + '\0';
			num /= 10;
		}
	}
	if (is_negative)
		temp[temp_pos++] = '-';
	else if (spec->show_sign)
		temp[temp_pos++] = '+';
	else if (spec->space_prefix)
		temp[temp_pos++] = ' ';
	i = -1;
	while (++i < temp_pos / 2)
	{
		swap = temp[i];
		temp[i] = temp[temp_pos - 1 - i];
		temp[temp_pos - 1 - i] = swap;
	}
	temp[temp_pos] = '\0';
	buffer_append_str_formatted(buffer, pos, temp, spec);
}

static t_format_state handle_normal(t_parser_ctx *ctx, char c)
{
	if (c == '%')
	{
		memset(&ctx->spec, 0, sizeof(t_format_spec));
		return (STATE_PERCENT);
	}
	buffer_appen_char(ctx->buffer, ctx->pos, c);
	return (STATE_NORMAL);
}

static t_format_state handle_percent(t_parser_ctx *ctx, char c)
{

}


static t_format_state handle_flags(t_parser_ctx *ctx, char c)
{

}

static t_format_state handle_width(t_parser_ctx *ctx, char c)
{

}

static t_format_state handle_precision(t_parser_ctx *ctx, char c)
{

}

static t_format_state handle_length(t_parser_context_t *ctx, char c)
{

}

static format_state_t handle_specifier(parser_context_t *ctx, char c)
{

}

static t_format_state handle_error(t_parser_ctx *ctx, char c)
{

}

static inline void put_level_buffered(t_string buffer, int *pos, t_log_level)
{

}

static void vlog_msg_automata(const char *fmt, va_list args, t_string buffer, int *pos)
{

}

void log_msg(t_log_level level, const char *fmt, ...)
{
	char buffer[1024];
	va_list args;
	t_flag enabled;
	int pos;

	pos = 0;
	enabled = MINITALK_DEBUG;
	if (!enabled)
		return ;
	put_level_buffered(buffer, &pos, level);
	va_start(args, fmt);
	vlog_msg_automata(fmt, args, buffer, &pos);
	buffer[pos++] = '\n';
	buffer[pos] = '\0';
	va_end(args);
	write("\n");
}

#endif