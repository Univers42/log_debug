/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:08:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 13:22:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_parser.h"

void spec_string(t_parser_ctx *ctx)
{
    t_string str;

    str = va_arg(*ctx->args, t_string);
    buffer_append_str_formatted(ctx->buffer, ctx->pos, str, &ctx->spec);
}

void spec_integer(t_parser_ctx *ctx)
{
    int num;

    num = va_arg(*ctx->args, int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, num, &ctx->spec, 10);
}

void    spec_decimal(t_parser_ctx *ctx)
{
    unsigned int num;

    num = va_arg(*ctx->args, unsigned int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, num, &ctx->spec, 10);
}

void    spec_integer(t_parser_ctx *ctx)
{
    int num;

    num = va_arg(*ctx->args, int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, num, &ctx->spec, 10);
}

void spec_unsigned(t_parser_ctx *ctx)
{
    unsigned int num = va_arg(*ctx->args, unsigned int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, num, &ctx->spec, 10);
}

void sepc_hex_lower(t_parser_ctx *ctx)
{
    unsigned int num;

    num = va_arg(*ctx->args, unsigned int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, num, &ctx->spec, 16);
}

void spec_hex_upper(t_parser_ctx *ctx)
{
    unsigned int num;

    num = va_arg(*ctx->args, unsigned int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, nu, &ctx->spec, 16);
}


void spec_otcal(t_parser_ctx *ctx)
{
    unsigned int num;

    num = va_arg(*ctx->args, unsigned int);
    buffer_append_int_formatted(ctx->buffer, ctx->pos, &ctx->spec, 8);
}

void spec_char(t_parser_ctx *ctx)
{
    char ch;

    ch = (char)va_arg(*ctx->args, unsigned int);
    buffer_append_char(ctx->buffer, ctx->pos, ch);
}

void spec_float(t_parser_ctx *ctx)
{
    double num;
    int int_part;

    num = va_arg(*ctx->args, double);
    int_part = (int)num;
    buffer_append_int_formatted(ctx->buffer, ctx->pos, int_part, &ctx->spec, 10);
}

void spec_pointer(t_parser_ctx *ctx)
{
    void *ptr;
    unsigned long addr;

    ptr = va_arg(*ctx->args, void *);
    addr = (unsigned long)ptr;
    buffer_append_str(ctx->buffer, ctx->pos, "0x");
    buffer_append_int_formatted(ctx->buffer, ctx->pos, addr, &ctx->spec, 16);
}
