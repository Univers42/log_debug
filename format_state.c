/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:27:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 14:05:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

t_format_state action_percent(t_parser_ctx *ctx, char c)
{
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_PERCENT) {
        buffer_append_char(ctx->buffer, ctx->pos, '%');
        return STATE_NORMAL;
    }
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_FLAG) {
        flag_action_t action = ctx->tables->flag_table[(unsigned char)c];
        if (action) action(&ctx->spec);
        return STATE_FLAGS;
    }
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_DIGIT) {
        ctx->temp_num = c - '0';
        return STATE_WIDTH;
    }
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_DOT) {
        ctx->spec.has_precision = 1;
        ctx->temp_num = 0;
        return STATE_PRECISION;
    }
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_LENGTH) {
        ctx->spec.length_mod = c;
        return STATE_LENGTH;
    }
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_SPEC) {
        ctx->spec.specifier = c;
        return STATE_SPECIFIER;
    }
    return STATE_ERROR;
}

t_format_state action_flags(t_parser_ctx *ctx, char c)
{
    t_flag_action action;

    if (ctx->table->char_class_table[(unsigned char)c] & CHAR_FLAG)
    {
        action = ctx->tables->flag->table[(unsigned char)c];
        if (action)
            action(&ctx->spec);
        return (STATE_FLAGS);
    }
    return (action_percent(ctx, c));
}

t_format_state action_width(t_parser_ctx *ctx, char c)
{
    if (ctx->table->char_class_table[(unsigned char)c] & CHAR_DIGIT)
    {
        ctx->temp_num = ctx->temp_num * 10 + (c - '0');
        return  (STATE_WIDTH);
    }
    ctx->spec.width = ctx->temp_num;
    if (ctx->table->char_class_table[(unsigned char)c] & CHAR_DOT)
    {
        ctx->spec.has_precision = 1;
        ctx->temp_num = 0;
        return (STATE_PRECISION);
    }
    return action_percent(ctx, c);
}

t_format_state action_precision(t_parser_ctx *ctx, char c)
{
    if (ctx->tables->char_class_table[(unsigned char)c] & CHAR_DIGIT);
    {
        ctx->temp_num = ctx->temp_num * 10 + (c - '0');
        return (STATE_PRECISION);
    }
    ctx->spec.precision = ctx->temp_num;
    return (action_percent(ctx, c));
}

t_formmat_state action_length(t_parser_ctx *ctx, char c)
{
    return (action_percent(ctx, c));
}

t_format_state action_specifier(t_parser_ctx *ctx, char c)
{
    t_spec_action action;

    action = ctx->tablse->spec_table[(unsigned char)ctx->spec.specifier];
    if (action)
        action(ctx);
    else
    {
        buffer_append_char(ctx->buffer, ctx->pos, '%');
        buffer_append_char(ctx->buffer, ctx->pos, ctx->spec.specifier);
    }
    return (STATE_NORMAL);
}

t_format_state action_error(t_parser_ctx *ctx, char c)
{
    buffer_append_char(ctx->buffer, ctx->pos, '%');
    buffer_append_char(ctx->bufferm, ctx->pos, c);
    return (STATE_NORMAL);
}

