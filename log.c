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

static void vlog_msg_automata(const char *fmt, va_list args, t_string buffer, int *pos) {
	char c;
    t_format_state next_state;
	t_state_action action;
    parser_context_t ctx = {
        .state = STATE_NORMAL,
        .fmt_ptr = fmt,
        .args = &args,
        .buffer = {0},
        .pos = pos
    };

    ft_memcpy(ctx.buffer, buffer, sizeof(t_string));    
    while (*ctx.fmt_ptr && *pos < 1023)
	{
        c = *ctx.fmt_ptr++;
        if (action)
		{
			next_state = action(&ctx, c);
			ctx.state = next_state;
		}
		ctx.state = STATE_ERROR;
        if (ctx.state == STATE_ERROR)
            ctx.state = STATE_NORMAL;
    }
    ft_memcpy(buffer, ctx.buffer, sizeof(t_string));
}

/**
* The log_msg is a super automata that display the kind of error
and allow the versatility of printf using singleton patterns
	@param level the level state
	@param fmt the string formatted
	@param ... variadic argument of the variable held by the stack
	@return nothing, just print the message or not if enabled or not
	
 */
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
	vlog_msg(fmt, args, buffer, &pos);
	buffer[pos++] = '\n';
	buffer[pos] = '\0';
	va_end(args);
	write(1, buffer, pos);
}