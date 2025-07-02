/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:00:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 14:00:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

void	vlog_msg_automata(const char *fmt, va_list args, t_buffer buffer, int *pos)
{
	char			c;
	t_format_state	next_state;
	t_state_action	action;
	t_parser_ctx	ctx;
	va_list			args_copy;

	va_copy(args_copy, args);
	ctx.state = STATE_NORMAL;
	ctx.fmt_ptr = fmt;
	ctx.args = &args_copy;
	ctx.pos = pos;
	ctx.tables = get_parser_tables();
	memset(&ctx.spec, 0, sizeof(t_format_spec));
	memcpy(ctx.buffer, buffer, sizeof(t_buffer));
	while (*ctx.fmt_ptr && *pos < 1023)
	{
		c = *ctx.fmt_ptr++;
		action = ctx.tables->state_transition_table[ctx.state];
		if (action)
		{
			next_state = action(&ctx, c);
			ctx.state = next_state;
		}
		else
			ctx.state = STATE_ERROR;
		if (ctx.state == STATE_ERROR)
			ctx.state = STATE_NORMAL;
	}
	memcpy(buffer, ctx.buffer, sizeof(t_buffer));
	va_end(args_copy);
}

void	log_msg(t_log_level level, const char *fmt, ...)
{
	char		buffer[1024];
	va_list		args;
	t_flag		enabled;
	int			pos;

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
	write(1, buffer, pos);
}