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

static inline int buffer_space_left(int pos) {
    return 1023 - pos;
}

static inline int can_append(int pos, int len) {
    return pos + len <= 1023;
}