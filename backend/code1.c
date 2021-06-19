/* code1.c - USS Code One */

/*
    libzint - the open source barcode library
    Copyright (C) 2009-2021 Robin Stuart <rstuart114@gmail.com>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
 */
/* vim: set ts=4 sw=4 et : */

#include "common.h"
#include "code1.h"
#include "reedsol.h"
#include "large.h"
#include <stdio.h>
#include <math.h>
#ifdef _MSC_VER
#include <malloc.h>
#endif

/* Add solid bar */
static void horiz(struct zint_symbol *symbol, const int row_no, const int full) {
    int i;

    if (full) {
        for (i = 0; i < symbol->width; i++) {
            set_module(symbol, row_no, i);
        }
    } else {
        for (i = 1; i < symbol->width - 1; i++) {
            set_module(symbol, row_no, i);
        }
    }
}

/* Central recognition pattern for Versions A-H */
static void central_finder(struct zint_symbol *symbol, const int start_row, const int row_count,
            const int full_rows) {
    int i;

    for (i = 0; i < row_count; i++) {
        if (i < full_rows) {
            horiz(symbol, start_row + (i * 2), 1);
        } else {
            horiz(symbol, start_row + (i * 2), 0);
            if (i != row_count - 1) {
                set_module(symbol, start_row + (i * 2) + 1, 1);
                set_module(symbol, start_row + (i * 2) + 1, symbol->width - 2);
            }
        }
    }
}

/* Add solid column */
static void vert(struct zint_symbol *symbol, const int column, const int height, const int top) {
    int i;

    if (top) {
        for (i = 0; i < height; i++) {
            set_module(symbol, i, column);
        }
    } else {
        for (i = 0; i < height; i++) {
            set_module(symbol, symbol->rows - i - 1, column);
        }
    }
}

/* Add bump to the right of the vertical recognition pattern column (Versions A-H) */
static void spigot(struct zint_symbol *symbol, const int row_no) {
    int i;

    for (i = symbol->width - 1; i > 0; i--) {
        if (module_is_set(symbol, row_no, i - 1)) {
            set_module(symbol, row_no, i);
        }
    }
}

/* Is basic (non-shifted) C40? */
static int isc40(const unsigned char input) {
    if ((input >= '0' && input <= '9') || (input >= 'A' && input <= 'Z') || input == ' ') {
        return 1;
    }
    return 0;
}

/* Is basic (non-shifted) TEXT? */
static int istext(const unsigned char input) {
    if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'z') || input == ' ') {
        return 1;
    }
    return 0;
}

/* Is basic (non-shifted) C40/TEXT? */
static int isc40text(const int current_mode, const unsigned char input) {
    return current_mode == C1_C40 ? isc40(input) : istext(input);
}

/* EDI characters are uppercase alphanumerics plus space plus EDI terminator (CR) plus 2 EDI separator chars */
static int isedi(const unsigned char input) {

    if (isc40(input)) {
        return 1;
    }
    if (input == 13 || input == '*' || input == '>') {
        return 1;
    }

    return 0;
}

/* Whether Step Q4bi applies, i.e. if one of the 3 EDI terminator/separator chars appears before a non-EDI char */
static int is_step_Q4bi_applicable(const unsigned char source[], const int sourcelen, const int position) {
    int i;

    for (i = position; i < sourcelen && isedi(source[i]); i++) {
        if (source[i] == 13 || source[i] == '*' || source[i] == '>') {
            return 1;
        }
    }

    return 0;
}

/* AIM USS Code One Annex D Steps J-R */
static int c1_look_ahead_test(const unsigned char source[], const int sourcelen, const int position,
            const int current_mode, const int gs1) {
    float ascii_count, c40_count, text_count, edi_count, byte_count;
    int ascii_rnded, c40_rnded, text_rnded, edi_rnded, byte_rnded;
    int sp;

    /* Step J1 */
    if (current_mode == C1_ASCII) {
        ascii_count = 0.0f;
        c40_count = 1.0f;
        text_count = 1.0f;
        edi_count = 1.0f;
        byte_count = 2.0f;
    } else {
        ascii_count = 1.0f;
        c40_count = 2.0f;
        text_count = 2.0f;
        edi_count = 2.0f;
        byte_count = 3.0f;
    }

    switch (current_mode) {
        case C1_C40: c40_count = 0.0f; /* Step J2 */
            break;
        case C1_TEXT: text_count = 0.0f; /* Step J3 */
            break;
        case C1_EDI: edi_count = 0.0f; /* Missing in spec */
            break;
        case C1_BYTE: byte_count = 0.0f; /* Step J4 */
            break;
    }

    for (sp = position; sp < sourcelen; sp++) {

        /* Step L */
        if ((source[sp] >= '0') && (source[sp] <= '9')) {
            ascii_count += 0.5f; /* Step L1 */
        } else {
            if (source[sp] > 127) {
                ascii_count = ceilf(ascii_count) + 2.0f; /* Step L2 */
            } else {
                ascii_count = ceilf(ascii_count) + 1.0f; /* Step L3 */
            }
        }

        /* Step M */
        if (isc40(source[sp])) {
            c40_count += (2.0f / 3.0f); /* Step M1 */
        } else if (source[sp] > 127) {
            c40_count += (8.0f / 3.0f); /* Step M2 */
        } else {
            c40_count += (4.0f / 3.0f); /* Step M3 */
        }

        /* Step N */
        if (istext(source[sp])) {
            text_count += (2.0f / 3.0f); /* Step N1 */
        } else if (source[sp] > 127) {
            text_count += (8.0f / 3.0f); /* Step N2 */
        } else {
            text_count += (4.0f / 3.0f); /* Step N3 */
        }

        /* Step O */
        if (isedi(source[sp])) {
            edi_count += (2.0f / 3.0f); /* Step O1 */
        } else if (source[sp] > 127) {
            edi_count += (13.0f / 3.0f); /* Step O2 */
        } else {
            edi_count += (10.0f / 3.0f); /* Step O3 */
        }

        /* Step P */
        if (gs1 && (source[sp] == '[')) {
            byte_count += 3.0f; /* Step P1 */
        } else {
            byte_count += 1.0f; /* Step P2 */
        }

        /* If at least 4 characters processed */
        /* NOTE: different than spec, where it's at least 3, but that ends up suppressing C40/TEXT/EDI.
           BWIPP also uses 4 (cf very similar Data Matrix ISO/IEC 16022:2006 Annex P algorithm) */
        if (sp >= position + 3) {
            /* Step Q */
            float cnt;
            ascii_rnded = (int) ceilf(stripf(ascii_count));
            c40_rnded = (int) ceilf(stripf(c40_count));
            text_rnded = (int) ceilf(stripf(text_count));
            edi_rnded = (int) ceilf(stripf(edi_count));
            byte_rnded = (int) ceilf(stripf(byte_count));

            cnt = byte_count + 1.0f;
            if (cnt <= ascii_rnded && cnt <= c40_rnded && cnt <= text_rnded && cnt <= edi_rnded) {
                return C1_BYTE; /* Step Q1 */
            }
            cnt = ascii_count + 1.0f;
            if (cnt <= c40_rnded && cnt <= text_rnded && cnt <= edi_rnded && cnt <= byte_rnded) {
                return C1_ASCII; /* Step Q2 */
            }
            cnt = text_rnded + 1.0f;
            if (cnt <= ascii_rnded && cnt <= c40_rnded && cnt <= edi_rnded && cnt <= byte_rnded) {
                return C1_TEXT; /* Step Q3 */
            }
            cnt = c40_rnded + 1.0f;
            if (cnt <= ascii_rnded && cnt <= text_rnded) {
                /* Step Q4 */
                if (c40_rnded < edi_rnded) {
                    return C1_C40; /* Step Q4a */
                }
                if (c40_rnded == edi_rnded) {
                    /* Step Q4b */
                    if (is_step_Q4bi_applicable(source, sourcelen, sp + 1)) {
                        return C1_EDI; /* Step Q4bi */
                    }
                    return C1_C40; /* Step Q4bii */
                }
            }
            cnt = edi_rnded + 1.0f;
            if (cnt <= ascii_rnded && cnt <= c40_rnded && cnt <= text_rnded && cnt <= byte_rnded) {
                return C1_EDI; /* Step Q5 */
            }
        }
    }

    /* Step K */
    ascii_rnded = (int) ceilf(stripf(ascii_count));
    c40_rnded = (int) ceilf(stripf(c40_count));
    text_rnded = (int) ceilf(stripf(text_count));
    edi_rnded = (int) ceilf(stripf(edi_count));
    byte_rnded = (int) ceilf(stripf(byte_count));

    if (byte_count <= ascii_rnded && byte_count <= c40_rnded && byte_count <= text_rnded && byte_count <= edi_rnded) {
        return C1_BYTE; /* Step K1 */
    }
    if (ascii_count <= c40_rnded && ascii_count <= text_rnded && ascii_count <= edi_rnded
            && ascii_count <= byte_rnded) {
        return C1_ASCII; /* Step K2 */
    }
    if (c40_rnded <= text_rnded && c40_rnded <= edi_rnded) {
        return C1_C40; /* Step K3 */
    }
    if (text_rnded <= edi_rnded) {
        return C1_TEXT; /* Step K4 */
    }

    return C1_EDI; /* Step K5 */
}

/* Whether can fit last character or characters in a single ASCII codeword */
static int is_last_single_ascii(const unsigned char string[], const int length, const int sp) {
    if (length - sp == 1 && string[sp + 1] <= 127) {
        return 1;
    }
    if (length - sp == 2 && istwodigits(string, length, sp)) {
        return 1;
    }
    return 0;
}

/* Initialize number of digits array (taken from BWIPP) */
static void set_num_digits(const unsigned char source[], const int length, int *num_digits) {
    int i;
    for (i = length - 1; i >= 0; i--) {
        if (source[i] >= '0' && source[i] <= '9') {
            num_digits[i] = num_digits[i + 1] + 1;
        }
    }
}

/* Copy C40/TEXT/EDI triplets from buffer to target. Returns elements left in buffer (< 3) */
static int cte_buffer_transfer(int cte_buffer[6], int cte_p, unsigned target[], int *p_tp) {
    int cte_i, cte_e;
    int tp = *p_tp;

    cte_e = (cte_p / 3) * 3;

    for (cte_i = 0; cte_i < cte_e; cte_i += 3) {
        int iv = (1600 * cte_buffer[cte_i]) + (40 * cte_buffer[cte_i + 1]) + (cte_buffer[cte_i + 2]) + 1;
        target[tp++] = iv >> 8;
        target[tp++] = iv & 0xFF;
    }

    cte_p -= cte_e;

    if (cte_p) {
        memmove(cte_buffer, cte_buffer + cte_e, sizeof(int) * cte_p);
    }

    *p_tp = tp;

    return cte_p;
}

/* Copy DECIMAL bytes to target. Returns bits left in buffer (< 8) */
static int decimal_binary_transfer(char decimal_binary[24], int db_p, unsigned int target[], int *p_tp) {
    int b_i, b_e, p;
    int tp = *p_tp;

    /* Transfer full bytes to target */
    b_e = db_p & 0xF8;

    for (b_i = 0; b_i < b_e; b_i += 8) {
        int value = 0;
        for (p = 0; p < 8; p++) {
            value <<= 1;
            value += decimal_binary[b_i + p] == '1';
        }
        target[tp++] = value;
    }

    db_p &= 0x07; /* Bits remaining */

    if (db_p) {
        memmove(decimal_binary, decimal_binary + b_e, db_p);
    }

    *p_tp = tp;

    return db_p;
}

/* Unlatch to ASCII from DECIMAL mode using 6 ones flag. DECIMAL binary buffer will be empty */
static int decimal_unlatch(char decimal_binary[24], int db_p, unsigned int target[], int *p_tp,
            const int decimal_count, const unsigned char *source, int *p_sp) {
    int sp = *p_sp;
    int bits_left;

    db_p = bin_append_posn(63, 6, decimal_binary, db_p); /* Unlatch */
    if (db_p >= 8) {
        db_p = decimal_binary_transfer(decimal_binary, db_p, target, p_tp);
    }
    bits_left = (8 - db_p) & 0x07;
    if (decimal_count >= 1 && bits_left >= 4) {
        db_p = bin_append_posn(ctoi(source[sp]) + 1, 4, decimal_binary, db_p);
        sp++;
        if (bits_left == 6) {
            db_p = bin_append_posn(1, 2, decimal_binary, db_p);
        }
        (void) decimal_binary_transfer(decimal_binary, db_p, target, p_tp);

    } else if (bits_left) {
        if (bits_left >= 4) {
            db_p = bin_append_posn(15, 4, decimal_binary, db_p);
        }
        if (bits_left == 2 || bits_left == 6) {
            db_p = bin_append_posn(1, 2, decimal_binary, db_p);
        }
        (void) decimal_binary_transfer(decimal_binary, db_p, target, p_tp);
    }

    *p_sp = sp;

    return 0;
}

/* Number of codewords remaining in a particular version (may be negative) */
static int codewords_remaining(struct zint_symbol *symbol, const int tp) {
    int i;

    if (symbol->option_2 == 10) { /* Version T */
        if (tp > 24) {
            return 38 - tp;
        }
        if (tp > 10) {
            return 24 - tp;
        }
        return 10 - tp;
    }
    /* Versions A to H */
    for (i = 6; i >= 0; i--) {
        if (tp > c1_data_length[i]) {
            return c1_data_length[i + 1] - tp;
        }
    }
    return c1_data_length[0] - tp;
}

/* Number of C40/TEXT elements needed to encode `input` */
static int c40text_cnt(const int current_mode, const int gs1, unsigned char input) {
    int cnt;

    if (gs1 && input == '[') {
        return 2;
    }
    cnt = 1;
    if (input > 127) {
        cnt += 2;
        input = input - 128;
    }
    if ((current_mode == C1_C40 && c40_shift[input]) || (current_mode == C1_TEXT && text_shift[input])) {
        cnt += 1;
    }

    return cnt;
}

/* Copy `source` to `eci_buf` with "\NNNNNN" ECI indicator at start and backslashes escaped */
static void eci_escape(const int eci, unsigned char *source, const int length, unsigned char *eci_buf,
            const int eci_length) {
    int i, j;

    j = sprintf((char *) eci_buf, "\\%06d", eci);

    for (i = 0; i < length && j < eci_length; i++) {
        if (source[i] == '\\') {
            eci_buf[j++] = '\\';
        }
        eci_buf[j++] = source[i];
    }
    eci_buf[j] = '\0';
}

/* Convert to codewords */
static int c1_encode(struct zint_symbol *symbol, unsigned char source[], unsigned int target[], int length,
            int *p_last_mode) {
    int current_mode, next_mode;
    int sp, tp, gs1, i;
    int cte_buffer[6], cte_p = 0; /* C1_C40/TEXT/EDI buffer and index */
    char decimal_binary[24]; /* C1_DECIMAL buffer */
    int db_p = 0;
    int byte_start = 0;
    int debug_print = symbol->debug & ZINT_DEBUG_PRINT;
    int eci_length = length + 7 + chr_cnt(source, length, '\\');
#ifndef _MSC_VER
    unsigned char eci_buf[eci_length + 1];
    int num_digits[eci_length + 1];
#else
    unsigned char *eci_buf = (unsigned char *) _alloca(eci_length + 1);
    int *num_digits = (int *) _alloca(sizeof(int) * (eci_length + 1));
#endif

    sp = 0;
    tp = 0;
    memset(num_digits, 0, sizeof(int) * (eci_length + 1));

    /* Step A */
    current_mode = C1_ASCII;
    next_mode = C1_ASCII;

    if ((symbol->input_mode & 0x07) == GS1_MODE) {
        gs1 = 1;
    } else {
        gs1 = 0;
    }
    if (gs1) {
        set_num_digits(source, length, num_digits);
        if (length >= 15 && num_digits[0] >= 15) {
            target[tp++] = 236; /* FNC1 and change to Decimal */
            next_mode = C1_DECIMAL;
        } else if (length >= 7 && num_digits[0] == length) {
            target[tp++] = 236; /* FNC1 and change to Decimal */
            next_mode = C1_DECIMAL;
        } else {
            target[tp++] = 232; /* FNC1 */
        }
        /* Note ignoring ECI if GS1 mode (up to caller to warn) */
    } else {
        if (symbol->eci) {
            target[tp++] = 129; /* Pad */
            target[tp++] = '\\' + 1; /* Escape char */
            eci_escape(symbol->eci, source, length, eci_buf, eci_length);
            source = eci_buf;
            length = eci_length;
        }
        set_num_digits(source, length, num_digits);
    }

    do {
        if (current_mode != next_mode) {
            /* Change mode */
            switch (next_mode) {
                case C1_C40: target[tp++] = 230;
                    break;
                case C1_TEXT: target[tp++] = 239;
                    break;
                case C1_EDI: target[tp++] = 238;
                    break;
                case C1_BYTE: target[tp++] = 231;
                    byte_start = tp;
                    target[tp++] = 0; /* Byte count holder (may be expanded to 2 codewords) */
                    break;
            }
            current_mode = next_mode;
        }

        if (current_mode == C1_ASCII) {
            /* Step B - ASCII encodation */
            next_mode = C1_ASCII;

            if ((length - sp) >= 21 && num_digits[sp] >= 21) {
                /* Step B1 */
                next_mode = C1_DECIMAL;
                db_p = bin_append_posn(15, 4, decimal_binary, db_p);
            } else if ((length - sp) >= 13 && num_digits[sp] == (length - sp)) {
                /* Step B2 */
                next_mode = C1_DECIMAL;
                db_p = bin_append_posn(15, 4, decimal_binary, db_p);
            }

            if (next_mode == C1_ASCII) {
                if (istwodigits(source, length, sp)) {
                    if (debug_print) printf("ASCII double-digits ");

                    /* Step B3 */
                    target[tp++] = (10 * ctoi(source[sp])) + ctoi(source[sp + 1]) + 130;
                    sp += 2;
                } else {
                    if ((gs1) && (source[sp] == '[')) {
                        if (length - (sp + 1) >= 15 && num_digits[sp + 1] >= 15) {
                            /* Step B4 */
                            target[tp++] = 236; /* FNC1 and change to Decimal */
                            sp++;
                            next_mode = C1_DECIMAL;
                        } else if (length - (sp + 1) >= 7 && num_digits[sp + 1] == length - (sp + 1)) {
                            /* Step B5 */
                            target[tp++] = 236; /* FNC1 and change to Decimal */
                            sp++;
                            next_mode = C1_DECIMAL;
                        }
                    }

                    if (next_mode == C1_ASCII) {

                        /* Step B6 */
                        next_mode = c1_look_ahead_test(source, length, sp, current_mode, gs1);

                        if (next_mode == C1_ASCII) {
                            if (debug_print) printf("ASCII ");

                            if (source[sp] > 127) {
                                /* Step B7 */
                                target[tp++] = 235; /* FNC4 (Upper Shift) */
                                target[tp++] = (source[sp] - 128) + 1;
                            } else if ((gs1) && (source[sp] == '[')) {
                                /* Step B8 */
                                target[tp++] = 232; /* FNC1 */
                            } else {
                                /* Step B8 */
                                target[tp++] = source[sp] + 1;
                            }
                            sp++;
                        }
                    }
                }
            }

        } else if (current_mode == C1_C40 || current_mode == C1_TEXT) {
            /* Step C/D - C40/TEXT encodation */

            next_mode = current_mode;
            if (cte_p == 0) {
                /* Step C/D1 */
                if ((length - sp) >= 12 && num_digits[sp] >= 12) {
                    /* Step C/D1a */
                    next_mode = C1_ASCII;
                } else if ((length - sp) >= 8 && num_digits[sp] == (length - sp)) {
                    /* Step C/D1b */
                    next_mode = C1_ASCII;
                } else {
                    next_mode = c1_look_ahead_test(source, length, sp, current_mode, gs1);
                }
            }

            if (next_mode != current_mode) {
                /* Step C/D1c */
                target[tp++] = 255; /* Unlatch */
            } else {
                /* Step C/D2 */
                const char *ct_shift, *ct_value;

                if (current_mode == C1_C40) {
                    ct_shift = c40_shift;
                    ct_value = c40_value;
                } else {
                    ct_shift = text_shift;
                    ct_value = text_value;
                }
                if (debug_print) printf(current_mode == C1_C40 ? "C40 " : "TEXT ");

                if (source[sp] > 127) {
                    cte_buffer[cte_p++] = 1; /* Shift 2 */
                    cte_buffer[cte_p++] = 30; /* FNC4 (Upper Shift) */
                    if (ct_shift[source[sp] - 128]) {
                        cte_buffer[cte_p++] = ct_shift[source[sp] - 128] - 1;
                    }
                    cte_buffer[cte_p++] = ct_value[source[sp] - 128];
                } else if (gs1 && (source[sp] == '[')) {
                    cte_buffer[cte_p++] = 1; /* Shift 2 */
                    cte_buffer[cte_p++] = 27; /* FNC1 */
                } else {
                    if (ct_shift[source[sp]]) {
                        cte_buffer[cte_p++] = ct_shift[source[sp]] - 1;
                    }
                    cte_buffer[cte_p++] = ct_value[source[sp]];
                }

                if (cte_p >= 3) {
                    cte_p = cte_buffer_transfer(cte_buffer, cte_p, target, &tp);
                }
                sp++;
            }

        } else if (current_mode == C1_EDI) {
            /* Step E - EDI Encodation */

            next_mode = C1_EDI;
            if (cte_p == 0) {
                /* Step E1 */
                if ((length - sp) >= 12 && num_digits[sp] >= 12) {
                    /* Step E1a */
                    next_mode = C1_ASCII;
                } else if ((length - sp) >= 8 && num_digits[sp] == (length - sp)) {
                    /* Step E1b */
                    next_mode = C1_ASCII;
                } else if ((length - sp) < 3 || !isedi(source[sp]) || !isedi(source[sp + 1])
                        || !isedi(source[sp + 2])) {
                    /* Step E1c */
                    /* This ensures ASCII switch if don't have EDI triplet, so cte_p will be zero on loop exit */
                    next_mode = C1_ASCII;
                }
            }

            if (next_mode != C1_EDI) {
                if (is_last_single_ascii(source, length, sp) && codewords_remaining(symbol, tp) == 1) {
                    /* No unlatch needed if data fits as ASCII in last data codeword */
                } else {
                    target[tp++] = 255; /* Unlatch */
                }
            } else {
                /* Step E2 */
                static const char edi_nonalphanum_chars[] = "\015*> ";

                if (debug_print) printf("EDI ");

                if ((source[sp] >= '0') && (source[sp] <= '9')) {
                    cte_buffer[cte_p++] = source[sp] - '0' + 4;
                } else if ((source[sp] >= 'A') && (source[sp] <= 'Z')) {
                    cte_buffer[cte_p++] = source[sp] - 'A' + 14;
                } else {
                    cte_buffer[cte_p++] = posn(edi_nonalphanum_chars, source[sp]);
                }

                if (cte_p >= 3) {
                    cte_p = cte_buffer_transfer(cte_buffer, cte_p, target, &tp);
                }
                sp++;
            }

        } else if (current_mode == C1_DECIMAL) {
            /* Step F - Decimal encodation */

            if (debug_print) printf("DECIMAL ");

            next_mode = C1_DECIMAL;

            if (length - sp < 3) {
                /* Step F1 */
                int bits_left = 8 - db_p;
                int can_ascii = bits_left == 8 && is_last_single_ascii(source, length, sp);
                if (codewords_remaining(symbol, tp) == 1 && (can_ascii || (num_digits[sp] == 1 && bits_left >= 4))) {
                    if (can_ascii) {
                        /* Encode last character or last 2 digits as ASCII */
                        if (istwodigits(source, length, sp)) {
                            target[tp++] = (10 * ctoi(source[sp])) + ctoi(source[sp + 1]) + 130;
                            sp += 2;
                        } else {
                            target[tp++] = source[sp] + 1;
                            sp++;
                        }
                    } else {
                        /* Encode last digit in 4 bits */
                        db_p = bin_append_posn(ctoi(source[sp]) + 1, 4, decimal_binary, db_p);
                        sp++;
                        if (bits_left == 6) {
                            db_p = bin_append_posn(1, 2, decimal_binary, db_p);
                        }
                        db_p = decimal_binary_transfer(decimal_binary, db_p, target, &tp);
                    }
                } else {
                    db_p = decimal_unlatch(decimal_binary, db_p, target, &tp, num_digits[sp], source, &sp);
                    current_mode = C1_ASCII; /* Note need to set current_mode also in case exit loop */
                }
                next_mode = C1_ASCII;

            } else {
                if (num_digits[sp] < 3) {
                    /* Step F2 */
                    db_p = decimal_unlatch(decimal_binary, db_p, target, &tp, num_digits[sp], source, &sp);
                    current_mode = next_mode = C1_ASCII; /* Note need to set current_mode also in case exit loop */
                } else {
                    /* Step F3 */
                    /* There are three digits - convert the value to binary */
                    int value = (100 * ctoi(source[sp])) + (10 * ctoi(source[sp + 1])) + ctoi(source[sp + 2]) + 1;
                    db_p = bin_append_posn(value, 10, decimal_binary, db_p);
                    if (db_p >= 8) {
                        db_p = decimal_binary_transfer(decimal_binary, db_p, target, &tp);
                    }
                    sp += 3;
                }
            }

        } else if (current_mode == C1_BYTE) {
            next_mode = C1_BYTE;

            if (gs1 && (source[sp] == '[')) {
                next_mode = C1_ASCII;
            } else {
                if (source[sp] <= 127) {
                    next_mode = c1_look_ahead_test(source, length, sp, current_mode, gs1);
                }
            }

            if (next_mode != C1_BYTE) {
                /* Update byte field length */
                int byte_count = tp - (byte_start + 1);
                if (byte_count <= 249) {
                    target[byte_start] = byte_count;
                } else {
                    /* Insert extra codeword */
                    memmove(target + byte_start + 2, target + byte_start + 1, sizeof(unsigned int) * byte_count);
                    target[byte_start] = 249 + (byte_count / 250);
                    target[byte_start + 1] = (byte_count % 250);
                    tp++;
                }
            } else {
                if (debug_print) printf("BYTE ");

                target[tp++] = source[sp];
                sp++;
            }
        }

        if (tp > 1480) {
            if (debug_print) printf("\n");
            /* Data is too large for symbol */
            return 0;
        }
    } while (sp < length);

    if (debug_print) {
        printf("\nEnd Current Mode: %d, tp %d, cte_p %d, db_p %d\n", current_mode, tp, cte_p, db_p);
    }

    /* Empty buffers (note cte_buffer will be empty if current_mode C1_EDI) */
    if (current_mode == C1_C40 || current_mode == C1_TEXT) {
        if (cte_p >= 1) {
            int cws_remaining = codewords_remaining(symbol, tp);

            /* Note doing strict interpretation of spec here (same as BWIPP), unlike in Data Matrix case */
            if (cws_remaining == 1 && cte_p == 1 && isc40text(current_mode, source[sp - 1])) {
                /* 2.2.2.2 "...except when a single symbol character is left at the end before the first
                   error correction character. This single character is encoded in the ASCII code set." */
                target[tp++] = source[sp - 1] + 1; /* As ASCII */
                cte_p = 0;
            } else if (cws_remaining == 2 && cte_p == 2) {
                /* 2.2.2.2 "Two characters may be encoded in C40 mode in the last two data symbol characters of the
                   symbol as two C40 values followed by one of the C40 shift characters." */
                cte_buffer[cte_p++] = 0; /* Shift 0 */
                cte_p = cte_buffer_transfer(cte_buffer, cte_p, target, &tp);
            }
            if (cte_p >= 1) {
                int cnt, total_cnt = 0;
                /* Backtrack to last complete triplet (same technique as BWIPP) */
                while (sp > 0 && cte_p % 3) {
                    sp--;
                    cnt = c40text_cnt(current_mode, gs1, source[sp]);
                    total_cnt += cnt;
                    cte_p -= cnt;
                }
                tp -= (total_cnt / 3) * 2;

                target[tp++] = 255; /* Unlatch */
                for (; sp < length; sp++) {
                    if (istwodigits(source, length, sp)) {
                        target[tp++] = (10 * ctoi(source[sp])) + ctoi(source[sp + 1]) + 130;
                        sp++;
                    } else if (source[sp] > 127) {
                        target[tp++] = 235; /* FNC4 (Upper Shift) */
                        target[tp++] = (source[sp] - 128) + 1;
                    } else if ((gs1) && (source[sp] == '[')) {
                        target[tp++] = 232; /* FNC1 */
                    } else {
                        target[tp++] = source[sp] + 1;
                    }
                }
                current_mode = C1_ASCII;
            }
        }

    } else if (current_mode == C1_DECIMAL) {
        int bits_left;

        /* Finish Decimal mode and go back to ASCII unless only one codeword remaining */
        if (codewords_remaining(symbol, tp) > 1) {
            db_p = bin_append_posn(63, 6, decimal_binary, db_p); /* Unlatch */
        }

        if (db_p >= 8) {
            db_p = decimal_binary_transfer(decimal_binary, db_p, target, &tp);
        }

        bits_left = (8 - db_p) & 0x07;

        if (bits_left) {

            if ((bits_left == 4) || (bits_left == 6)) {
                db_p = bin_append_posn(15, 4, decimal_binary, db_p);
            }

            if (bits_left == 2 || bits_left == 6) {
                db_p = bin_append_posn(1, 2, decimal_binary, db_p);
            }

            (void) decimal_binary_transfer(decimal_binary, db_p, target, &tp);
        }
        current_mode = C1_ASCII;

    } else if (current_mode == C1_BYTE) {
        /* Update byte field length unless no codewords remaining */
        if (codewords_remaining(symbol, tp) > 0) {
            int byte_count = tp - (byte_start + 1);
            if (byte_count <= 249) {
                target[byte_start] = byte_count;
            } else {
                /* Insert extra byte field byte */
                memmove(target + byte_start + 2, target + byte_start + 1, sizeof(unsigned int) * byte_count);
                target[byte_start] = 249 + (byte_count / 250);
                target[byte_start + 1] = (byte_count % 250);
                tp++;
            }
        }
    }

    /* Re-check length of data */
    if (tp > 1480) {
        /* Data is too large for symbol */
        return 0;
    }

    *p_last_mode = current_mode;

    if (debug_print) {
        printf("Target (%d):", tp);
        for (i = 0; i < tp; i++) {
            printf(" [%d]", target[i]);
        }
        printf("\nLast Mode: %d\n", *p_last_mode);
    }

    return tp;
}

/* Set symbol from datagrid */
static void block_copy(struct zint_symbol *symbol, char datagrid[136][120], const int start_row, const int start_col,
            const int height, const int width, const int row_offset, const int col_offset) {
    int i, j;

    for (i = start_row; i < (start_row + height); i++) {
        for (j = start_col; j < (start_col + width); j++) {
            if (datagrid[i][j]) {
                set_module(symbol, i + row_offset, j + col_offset);
            }
        }
    }
}

INTERNAL int code_one(struct zint_symbol *symbol, unsigned char source[], int length) {
    int size = 1, i, j;

    char datagrid[136][120];
    int row, col;
    int sub_version = 0;
    rs_t rs;
    int error_number = 0;

    if ((symbol->option_2 < 0) || (symbol->option_2 > 10)) {
        strcpy(symbol->errtxt, "513: Invalid symbol size");
        return ZINT_ERROR_INVALID_OPTION;
    }

    if (symbol->option_2 == 9) {
        /* Version S */
        int codewords;
        large_int elreg;
        unsigned int data[30], ecc[15];
        int block_width;

        if (length > 18) {
            strcpy(symbol->errtxt, "514: Input data too long for Version S");
            return ZINT_ERROR_TOO_LONG;
        }
        if (is_sane(NEON, source, length) == ZINT_ERROR_INVALID_DATA) {
            strcpy(symbol->errtxt, "515: Invalid input data (Version S encodes numeric input only)");
            return ZINT_ERROR_INVALID_DATA;
        }

        size = 9;
        if (length <= 6) {
            /* Version S-10 */
            sub_version = 1;
            codewords = 4;
            block_width = 2;
        } else if (length <= 12) {
            /* Version S-20 */
            sub_version = 2;
            codewords = 8;
            block_width = 4;
        } else {
            /* Version S-30 */
            sub_version = 3;
            codewords = 12;
            block_width = 6;
        }

        if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("Subversion: %d\n", sub_version);
        }

        /* Convert value plus one to binary */
        large_load_str_u64(&elreg, source, length);
        large_add_u64(&elreg, 1);
        large_uint_array(&elreg, data, codewords, 5 /*bits*/);

        rs_init_gf(&rs, 0x25);
        rs_init_code(&rs, codewords, 0);
        rs_encode_uint(&rs, codewords, data, ecc);

        for (i = 0; i < codewords; i++) {
            data[i + codewords] = ecc[codewords - i - 1];
        }

        if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("Codewords (%d): ", codewords);
            for (i = 0; i < codewords * 2; i++) printf(" %d", data[i]);
            printf("\n");
        }

        i = 0;
        for (row = 0; row < 2; row++) {
            for (col = 0; col < block_width; col++) {
                datagrid[row * 2][col * 5] = data[i] & 0x10;
                datagrid[row * 2][(col * 5) + 1] = data[i] & 0x08;
                datagrid[row * 2][(col * 5) + 2] = data[i] & 0x04;
                datagrid[(row * 2) + 1][col * 5] = data[i] & 0x02;
                datagrid[(row * 2) + 1][(col * 5) + 1] = data[i] & 0x01;
                datagrid[row * 2][(col * 5) + 3] = data[i + 1] & 0x10;
                datagrid[row * 2][(col * 5) + 4] = data[i + 1] & 0x08;
                datagrid[(row * 2) + 1][(col * 5) + 2] = data[i + 1] & 0x04;
                datagrid[(row * 2) + 1][(col * 5) + 3] = data[i + 1] & 0x02;
                datagrid[(row * 2) + 1][(col * 5) + 4] = data[i + 1] & 0x01;
                i += 2;
            }
        }

        symbol->rows = 8;
        symbol->width = 10 * sub_version + 1;

    } else if (symbol->option_2 == 10) {
        /* Version T */
        unsigned int data[90 + 2]; /* Allow for 90 BYTE mode (+ latch and byte count) */
        unsigned int ecc[22];
        int data_length;
        int data_cw, ecc_cw, block_width;
        int last_mode;

        if (length > 90 || (symbol->eci && length + 7 + chr_cnt(source, length, '\\') > 90)) {
            strcpy(symbol->errtxt, "519: Input data too long for Version T");
            return ZINT_ERROR_TOO_LONG;
        }

        data_length = c1_encode(symbol, source, data, length, &last_mode);

        if (data_length == 0 || data_length > 38) {
            strcpy(symbol->errtxt, "516: Input data too long for Version T");
            return ZINT_ERROR_TOO_LONG;
        }

        size = 10;
        if (data_length <= 10) {
            sub_version = 1;
            data_cw = 10;
            ecc_cw = 10;
            block_width = 4;
        } else if (data_length <= 24) {
            sub_version = 2;
            data_cw = 24;
            ecc_cw = 16;
            block_width = 8;
        } else {
            sub_version = 3;
            data_cw = 38;
            ecc_cw = 22;
            block_width = 12;
        }

        if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("Padding: %d, Subversion: %d\n", data_cw - data_length, sub_version);
        }

        /* If require padding */
        if (data_cw > data_length) {
            /* If did not finish in ASCII or BYTE mode, switch to ASCII */
            if (last_mode != C1_ASCII && last_mode != C1_BYTE) {
                data[data_length++] = 255; /* Unlatch */
            }
            for (i = data_length; i < data_cw; i++) {
                data[i] = 129; /* Pad */
            }
        }

        /* Calculate error correction data */
        rs_init_gf(&rs, 0x12d);
        rs_init_code(&rs, ecc_cw, 0);
        rs_encode_uint(&rs, data_cw, data, ecc);

        for (i = 0; i < ecc_cw; i++) {
            data[data_cw + i] = ecc[ecc_cw - i - 1];
        }

        if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("Codewords (%d):", data_cw + ecc_cw);
            for (i = 0; i < data_cw + ecc_cw; i++) printf(" %d", data[i]);
            printf("\n");
        }

        i = 0;
        for (row = 0; row < 5; row++) {
            for (col = 0; col < block_width; col++) {
                datagrid[row * 2][col * 4] = data[i] & 0x80;
                datagrid[row * 2][(col * 4) + 1] = data[i] & 0x40;
                datagrid[row * 2][(col * 4) + 2] = data[i] & 0x20;
                datagrid[row * 2][(col * 4) + 3] = data[i] & 0x10;
                datagrid[(row * 2) + 1][col * 4] = data[i] & 0x08;
                datagrid[(row * 2) + 1][(col * 4) + 1] = data[i] & 0x04;
                datagrid[(row * 2) + 1][(col * 4) + 2] = data[i] & 0x02;
                datagrid[(row * 2) + 1][(col * 4) + 3] = data[i] & 0x01;
                i++;
            }
        }

        symbol->rows = 16;
        symbol->width = (sub_version * 16) + 1;

    } else {
        /* Versions A to H */
        unsigned int data[1480 + 560];
        unsigned int sub_data[185], sub_ecc[70];
        int data_length;
        int data_cw;
        int blocks, data_blocks, ecc_blocks, ecc_length;
        int last_mode;

        data_length = c1_encode(symbol, source, data, length, &last_mode);

        if (data_length == 0) {
            strcpy(symbol->errtxt, "517: Input data is too long");
            return ZINT_ERROR_TOO_LONG;
        }

        for (i = 7; i >= 0; i--) {
            if (c1_data_length[i] >= data_length) {
                size = i + 1;
            }
        }

        if (symbol->option_2 > size) {
            size = symbol->option_2;
        }

        if ((symbol->option_2 != 0) && (symbol->option_2 < size)) {
            strcpy(symbol->errtxt, "518: Input too long for selected symbol size");
            return ZINT_ERROR_TOO_LONG;
        }
        data_cw = c1_data_length[size - 1];

        /* If require padding */
        if (data_cw > data_length) {
            /* If did not finish in ASCII or BYTE mode, switch to ASCII */
            if (last_mode != C1_ASCII && last_mode != C1_BYTE) {
                data[data_length++] = 255; /* Unlatch */
            }
            if (symbol->debug & ZINT_DEBUG_PRINT) {
                printf("Padding: %d\n", data_cw - data_length);
            }
            for (i = data_length; i < data_cw; i++) {
                data[i] = 129; /* Pad */
            }
        } else if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("No padding\n");
        }

        /* Calculate error correction data */
        blocks = c1_blocks[size - 1];
        data_blocks = c1_data_blocks[size - 1];
        ecc_blocks = c1_ecc_blocks[size - 1];
        ecc_length = c1_ecc_length[size - 1];

        rs_init_gf(&rs, 0x12d);
        rs_init_code(&rs, ecc_blocks, 0);
        for (i = 0; i < blocks; i++) {
            for (j = 0; j < data_blocks; j++) {
                sub_data[j] = data[j * blocks + i];
            }
            rs_encode_uint(&rs, data_blocks, sub_data, sub_ecc);
            for (j = 0; j < ecc_blocks; j++) {
                data[data_cw + j * blocks + i] = sub_ecc[ecc_blocks - 1 - j];
            }
        }

        if (symbol->debug & ZINT_DEBUG_PRINT) {
            printf("Codewords (%d):", data_cw + ecc_length);
            for (i = 0; i < data_cw + ecc_length; i++) printf(" %d", data[i]);
            printf("\n");
        }

        i = 0;
        for (row = 0; row < c1_grid_height[size - 1]; row++) {
            for (col = 0; col < c1_grid_width[size - 1]; col++) {
                datagrid[row * 2][col * 4] = data[i] & 0x80;
                datagrid[row * 2][(col * 4) + 1] = data[i] & 0x40;
                datagrid[row * 2][(col * 4) + 2] = data[i] & 0x20;
                datagrid[row * 2][(col * 4) + 3] = data[i] & 0x10;
                datagrid[(row * 2) + 1][col * 4] = data[i] & 0x08;
                datagrid[(row * 2) + 1][(col * 4) + 1] = data[i] & 0x04;
                datagrid[(row * 2) + 1][(col * 4) + 2] = data[i] & 0x02;
                datagrid[(row * 2) + 1][(col * 4) + 3] = data[i] & 0x01;
                i++;
            }
        }

        symbol->rows = c1_height[size - 1];
        symbol->width = c1_width[size - 1];
    }

    if (symbol->debug & ZINT_DEBUG_PRINT) {
        printf("Version: %d\n", size);
    }

    switch (size) {
        case 1: /* Version A */
            central_finder(symbol, 6, 3, 1);
            vert(symbol, 4, 6, 1);
            vert(symbol, 12, 5, 0);
            set_module(symbol, 5, 12);
            spigot(symbol, 0);
            spigot(symbol, 15);
            block_copy(symbol, datagrid, 0, 0, 5, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 5, 12, 0, 2);
            block_copy(symbol, datagrid, 5, 0, 5, 12, 6, 0);
            block_copy(symbol, datagrid, 5, 12, 5, 4, 6, 2);
            break;
        case 2: /* Version B */
            central_finder(symbol, 8, 4, 1);
            vert(symbol, 4, 8, 1);
            vert(symbol, 16, 7, 0);
            set_module(symbol, 7, 16);
            spigot(symbol, 0);
            spigot(symbol, 21);
            block_copy(symbol, datagrid, 0, 0, 7, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 7, 16, 0, 2);
            block_copy(symbol, datagrid, 7, 0, 7, 16, 8, 0);
            block_copy(symbol, datagrid, 7, 16, 7, 4, 8, 2);
            break;
        case 3: /* Version C */
            central_finder(symbol, 11, 4, 2);
            vert(symbol, 4, 11, 1);
            vert(symbol, 26, 13, 1);
            vert(symbol, 4, 10, 0);
            vert(symbol, 26, 10, 0);
            spigot(symbol, 0);
            spigot(symbol, 27);
            block_copy(symbol, datagrid, 0, 0, 10, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 10, 20, 0, 2);
            block_copy(symbol, datagrid, 0, 24, 10, 4, 0, 4);
            block_copy(symbol, datagrid, 10, 0, 10, 4, 8, 0);
            block_copy(symbol, datagrid, 10, 4, 10, 20, 8, 2);
            block_copy(symbol, datagrid, 10, 24, 10, 4, 8, 4);
            break;
        case 4: /* Version D */
            central_finder(symbol, 16, 5, 1);
            vert(symbol, 4, 16, 1);
            vert(symbol, 20, 16, 1);
            vert(symbol, 36, 16, 1);
            vert(symbol, 4, 15, 0);
            vert(symbol, 20, 15, 0);
            vert(symbol, 36, 15, 0);
            spigot(symbol, 0);
            spigot(symbol, 12);
            spigot(symbol, 27);
            spigot(symbol, 39);
            block_copy(symbol, datagrid, 0, 0, 15, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 15, 14, 0, 2);
            block_copy(symbol, datagrid, 0, 18, 15, 14, 0, 4);
            block_copy(symbol, datagrid, 0, 32, 15, 4, 0, 6);
            block_copy(symbol, datagrid, 15, 0, 15, 4, 10, 0);
            block_copy(symbol, datagrid, 15, 4, 15, 14, 10, 2);
            block_copy(symbol, datagrid, 15, 18, 15, 14, 10, 4);
            block_copy(symbol, datagrid, 15, 32, 15, 4, 10, 6);
            break;
        case 5: /* Version E */
            central_finder(symbol, 22, 5, 2);
            vert(symbol, 4, 22, 1);
            vert(symbol, 26, 24, 1);
            vert(symbol, 48, 22, 1);
            vert(symbol, 4, 21, 0);
            vert(symbol, 26, 21, 0);
            vert(symbol, 48, 21, 0);
            spigot(symbol, 0);
            spigot(symbol, 12);
            spigot(symbol, 39);
            spigot(symbol, 51);
            block_copy(symbol, datagrid, 0, 0, 21, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 21, 20, 0, 2);
            block_copy(symbol, datagrid, 0, 24, 21, 20, 0, 4);
            block_copy(symbol, datagrid, 0, 44, 21, 4, 0, 6);
            block_copy(symbol, datagrid, 21, 0, 21, 4, 10, 0);
            block_copy(symbol, datagrid, 21, 4, 21, 20, 10, 2);
            block_copy(symbol, datagrid, 21, 24, 21, 20, 10, 4);
            block_copy(symbol, datagrid, 21, 44, 21, 4, 10, 6);
            break;
        case 6: /* Version F */
            central_finder(symbol, 31, 5, 3);
            vert(symbol, 4, 31, 1);
            vert(symbol, 26, 35, 1);
            vert(symbol, 48, 31, 1);
            vert(symbol, 70, 35, 1);
            vert(symbol, 4, 30, 0);
            vert(symbol, 26, 30, 0);
            vert(symbol, 48, 30, 0);
            vert(symbol, 70, 30, 0);
            spigot(symbol, 0);
            spigot(symbol, 12);
            spigot(symbol, 24);
            spigot(symbol, 45);
            spigot(symbol, 57);
            spigot(symbol, 69);
            block_copy(symbol, datagrid, 0, 0, 30, 4, 0, 0);
            block_copy(symbol, datagrid, 0, 4, 30, 20, 0, 2);
            block_copy(symbol, datagrid, 0, 24, 30, 20, 0, 4);
            block_copy(symbol, datagrid, 0, 44, 30, 20, 0, 6);
            block_copy(symbol, datagrid, 0, 64, 30, 4, 0, 8);
            block_copy(symbol, datagrid, 30, 0, 30, 4, 10, 0);
            block_copy(symbol, datagrid, 30, 4, 30, 20, 10, 2);
            block_copy(symbol, datagrid, 30, 24, 30, 20, 10, 4);
            block_copy(symbol, datagrid, 30, 44, 30, 20, 10, 6);
            block_copy(symbol, datagrid, 30, 64, 30, 4, 10, 8);
            break;
        case 7: /* Version G */
            central_finder(symbol, 47, 6, 2);
            vert(symbol, 6, 47, 1);
            vert(symbol, 27, 49, 1);
            vert(symbol, 48, 47, 1);
            vert(symbol, 69, 49, 1);
            vert(symbol, 90, 47, 1);
            vert(symbol, 6, 46, 0);
            vert(symbol, 27, 46, 0);
            vert(symbol, 48, 46, 0);
            vert(symbol, 69, 46, 0);
            vert(symbol, 90, 46, 0);
            spigot(symbol, 0);
            spigot(symbol, 12);
            spigot(symbol, 24);
            spigot(symbol, 36);
            spigot(symbol, 67);
            spigot(symbol, 79);
            spigot(symbol, 91);
            spigot(symbol, 103);
            block_copy(symbol, datagrid, 0, 0, 46, 6, 0, 0);
            block_copy(symbol, datagrid, 0, 6, 46, 19, 0, 2);
            block_copy(symbol, datagrid, 0, 25, 46, 19, 0, 4);
            block_copy(symbol, datagrid, 0, 44, 46, 19, 0, 6);
            block_copy(symbol, datagrid, 0, 63, 46, 19, 0, 8);
            block_copy(symbol, datagrid, 0, 82, 46, 6, 0, 10);
            block_copy(symbol, datagrid, 46, 0, 46, 6, 12, 0);
            block_copy(symbol, datagrid, 46, 6, 46, 19, 12, 2);
            block_copy(symbol, datagrid, 46, 25, 46, 19, 12, 4);
            block_copy(symbol, datagrid, 46, 44, 46, 19, 12, 6);
            block_copy(symbol, datagrid, 46, 63, 46, 19, 12, 8);
            block_copy(symbol, datagrid, 46, 82, 46, 6, 12, 10);
            break;
        case 8: /* Version H */
            central_finder(symbol, 69, 6, 3);
            vert(symbol, 6, 69, 1);
            vert(symbol, 26, 73, 1);
            vert(symbol, 46, 69, 1);
            vert(symbol, 66, 73, 1);
            vert(symbol, 86, 69, 1);
            vert(symbol, 106, 73, 1);
            vert(symbol, 126, 69, 1);
            vert(symbol, 6, 68, 0);
            vert(symbol, 26, 68, 0);
            vert(symbol, 46, 68, 0);
            vert(symbol, 66, 68, 0);
            vert(symbol, 86, 68, 0);
            vert(symbol, 106, 68, 0);
            vert(symbol, 126, 68, 0);
            spigot(symbol, 0);
            spigot(symbol, 12);
            spigot(symbol, 24);
            spigot(symbol, 36);
            spigot(symbol, 48);
            spigot(symbol, 60);
            spigot(symbol, 87);
            spigot(symbol, 99);
            spigot(symbol, 111);
            spigot(symbol, 123);
            spigot(symbol, 135);
            spigot(symbol, 147);
            block_copy(symbol, datagrid, 0, 0, 68, 6, 0, 0);
            block_copy(symbol, datagrid, 0, 6, 68, 18, 0, 2);
            block_copy(symbol, datagrid, 0, 24, 68, 18, 0, 4);
            block_copy(symbol, datagrid, 0, 42, 68, 18, 0, 6);
            block_copy(symbol, datagrid, 0, 60, 68, 18, 0, 8);
            block_copy(symbol, datagrid, 0, 78, 68, 18, 0, 10);
            block_copy(symbol, datagrid, 0, 96, 68, 18, 0, 12);
            block_copy(symbol, datagrid, 0, 114, 68, 6, 0, 14);
            block_copy(symbol, datagrid, 68, 0, 68, 6, 12, 0);
            block_copy(symbol, datagrid, 68, 6, 68, 18, 12, 2);
            block_copy(symbol, datagrid, 68, 24, 68, 18, 12, 4);
            block_copy(symbol, datagrid, 68, 42, 68, 18, 12, 6);
            block_copy(symbol, datagrid, 68, 60, 68, 18, 12, 8);
            block_copy(symbol, datagrid, 68, 78, 68, 18, 12, 10);
            block_copy(symbol, datagrid, 68, 96, 68, 18, 12, 12);
            block_copy(symbol, datagrid, 68, 114, 68, 6, 12, 14);
            break;
        case 9: /* Version S */
            horiz(symbol, 5, 1);
            horiz(symbol, 7, 1);
            set_module(symbol, 6, 0);
            set_module(symbol, 6, symbol->width - 1);
            unset_module(symbol, 7, 1);
            unset_module(symbol, 7, symbol->width - 2);
            switch (sub_version) {
                case 1: /* Version S-10 */
                    set_module(symbol, 0, 5);
                    block_copy(symbol, datagrid, 0, 0, 4, 5, 0, 0);
                    block_copy(symbol, datagrid, 0, 5, 4, 5, 0, 1);
                    break;
                case 2: /* Version S-20 */
                    set_module(symbol, 0, 10);
                    set_module(symbol, 4, 10);
                    block_copy(symbol, datagrid, 0, 0, 4, 10, 0, 0);
                    block_copy(symbol, datagrid, 0, 10, 4, 10, 0, 1);
                    break;
                case 3: /* Version S-30 */
                    set_module(symbol, 0, 15);
                    set_module(symbol, 4, 15);
                    set_module(symbol, 6, 15);
                    block_copy(symbol, datagrid, 0, 0, 4, 15, 0, 0);
                    block_copy(symbol, datagrid, 0, 15, 4, 15, 0, 1);
                    break;
            }
            break;
        case 10: /* Version T */
            horiz(symbol, 11, 1);
            horiz(symbol, 13, 1);
            horiz(symbol, 15, 1);
            set_module(symbol, 12, 0);
            set_module(symbol, 12, symbol->width - 1);
            set_module(symbol, 14, 0);
            set_module(symbol, 14, symbol->width - 1);
            unset_module(symbol, 13, 1);
            unset_module(symbol, 13, symbol->width - 2);
            unset_module(symbol, 15, 1);
            unset_module(symbol, 15, symbol->width - 2);
            switch (sub_version) {
                case 1: /* Version T-16 */
                    set_module(symbol, 0, 8);
                    set_module(symbol, 10, 8);
                    block_copy(symbol, datagrid, 0, 0, 10, 8, 0, 0);
                    block_copy(symbol, datagrid, 0, 8, 10, 8, 0, 1);
                    break;
                case 2: /* Version T-32 */
                    set_module(symbol, 0, 16);
                    set_module(symbol, 10, 16);
                    set_module(symbol, 12, 16);
                    block_copy(symbol, datagrid, 0, 0, 10, 16, 0, 0);
                    block_copy(symbol, datagrid, 0, 16, 10, 16, 0, 1);
                    break;
                case 3: /* Verion T-48 */
                    set_module(symbol, 0, 24);
                    set_module(symbol, 10, 24);
                    set_module(symbol, 12, 24);
                    set_module(symbol, 14, 24);
                    block_copy(symbol, datagrid, 0, 0, 10, 24, 0, 0);
                    block_copy(symbol, datagrid, 0, 24, 10, 24, 0, 1);
                    break;
            }
            break;
    }

    for (i = 0; i < symbol->rows; i++) {
        symbol->row_height[i] = 1;
    }
    symbol->height = symbol->rows;

    if (symbol->option_2 == 9) { /* Version S */
        if (symbol->eci || (symbol->input_mode & 0x07) == GS1_MODE) {
            strcpy(symbol->errtxt, "511: ECI and GS1 mode ignored for Version S");
            error_number = ZINT_WARN_INVALID_OPTION;
        }
    } else if (symbol->eci && (symbol->input_mode & 0x07) == GS1_MODE) {
        strcpy(symbol->errtxt, "512: ECI ignored for GS1 mode");
        error_number = ZINT_WARN_INVALID_OPTION;
    }

    return error_number;
}
