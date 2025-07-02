/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:39:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/02 12:59:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Singleton accessor function

init_table(t_parser_table tables)
{
    int i;

    i = -1;
    while (++i < CHAR_TABLE_SIZE)
        tables.char_class_table[i] = 0;
}

init_specifier_table(t_parser_table tables)
{
    int i;

    i = -1;
    for (++i < CHAR_TABLE_SIZE)
        tables.spec_table[i] = 0;
    tables.spec_table['s'] = spec_string;
    tables.spec_table['d'] = spec_decimal;
    tables.spec_table['i'] = spec_integer;
    tables.spec_table['u'] = spec_unsigned;
    tables.spec_table['x'] = spec_hex_lower;
    tables.spec_table['X'] = spec_hex_upper;
    tables.spec_table['o'] = spec_octal;
    tables.spec_table['c'] = spec_char;
    tables.spec_table['p'] = spec_pointer;
    tables.spec_table['f'] = spec_float;
    tables.spec_table['g'] = spec_float;
    tables.spec_table['G'] = spec_float;
}

init_level(t_parser_table tables)
{
    // Initialize level strings
        tables.level_strings[LOG_INFO] = BLUE "[INFO] " RESET;
        tables.level_strings[LOG_WARNING] = YELLOW "[WARNING] " RESET;
        tables.level_strings[LOG_ERROR] = RED "[ERROR] " RESET;
        tables.level_strings[LOG_DEBUG] = MAGENTA "[DEBUG] " RESET;
        tables.level_strings[LOG_SUCCESS] = GREEN "[SUCCESS] " RESET;
}

init_flag(t_parser_table tables)
{
    int i;

    i = -1;
    while (++i < CHAR_TABLE_SIZE)
        tables.flag_table[i] = 0;
    tables.flag_table['-'] = flag_left_align;
    tables.flag_table['+'] = flag_show_sign;
    tables.flag_table[' '] = flag_space_prefix;
    tables.flag_table['#'] = flag_alt_form;
    tables.flag_table['0'] = flag_zero_pad;
}

init_transitor(t_parser_table tables)
{
    tables.state_transition_table[STATE_NORMAL] = action_normal;
    tables.state_transition_table[STATE_PERCENT] = action_percent;
    tables.state_transition_table[STATE_FLAGS] = action_flags;
    tables.state_transition_table[STATE_WIDTH] = action_width;
    tables.state_transition_table[STATE_PRECISION] = action_precision;
    tables.state_transition_table[STATE_LENGTH] = action_length;
    tables.state_transition_table[STATE_SPECIFIER] = action_specifier;
    tables.state_transition_table[STATE_ERROR] = action_error;
}

void init var_(t_parser_table tables)
{
        tables.char_class_table['-'] |= CHAR_FLAG;
        tables.char_class_table['+'] |= CHAR_FLAG;
        tables.char_class_table[' '] |= CHAR_FLAG;
        tables.char_class_table['#'] |= CHAR_FLAG;
        tables.char_class_table['0'] |= CHAR_FLAG;
        tables.char_class_table['s'] |= CHAR_SPEC;
        tables.char_class_table['d'] |= CHAR_SPEC;
        tables.char_class_table['i'] |= CHAR_SPEC;
        tables.char_class_table['u'] |= CHAR_SPEC;
        tables.char_class_table['x'] |= CHAR_SPEC;
        tables.char_class_table['X'] |= CHAR_SPEC;
        tables.char_class_table['o'] |= CHAR_SPEC;
        tables.char_class_table['c'] |= CHAR_SPEC;
        tables.char_class_table['p'] |= CHAR_SPEC;
        tables.char_class_table['f'] |= CHAR_SPEC;
        tables.char_class_table['g'] |= CHAR_SPEC;
        tables.char_class_table['G'] |= CHAR_SPEC;
        tables.char_class_table['l'] |= CHAR_LENGTH;
        tables.char_class_table['h'] |= CHAR_LENGTH;
        tables.char_class_table['L'] |= CHAR_LENGTH;
        tables.char_class_table['.'] |= CHAR_DOT;
        tables.char_class_table['%'] |= CHAR_PERCENT;
}

static parser_tables_t *get_parser_tables(void) {
    static t_parser_tables tables = {0};
    int i;
    char c;

    if (!tables.initialized)
    {
        i = -1;
        tables.initialized = 1;
        while (++i < CHAR_TABLE_SIZE)
            tables.char_class_table[i] = 0;
        c = '0' - 1;
        while (c <= '9')
        {
            tables.char_class_table[(unsigned char)c] |= CHAR_DIGIT;
            c++;
        }
        init_var(tables);
        init_transitor(tables);
        init_flag(tables);
        init_specifier_table(tables);
        init_level(tables);
    }
    return &tables;
}
