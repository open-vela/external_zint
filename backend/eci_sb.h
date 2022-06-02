/*  eci_sb.h - Extended Channel Interpretations single-byte,
    generated by "backend/tools/gen_eci_sb_h.php" from
    "https://unicode.org/Public/MAPPINGS/ISO8859/8859-*.TXT" and
    "https://unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP125*.TXT" */
/* libzint - the open source barcode library
    Copyright (C) 2021-2022 Robin Stuart <rstuart114@gmail.com>

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

#ifndef Z_ECI_SB_H
#define Z_ECI_SB_H

/* Forward reference to base ISO/IEC 8859 routine - see "eci.c" */
static int u_iso8859(const unsigned int u, const unsigned short *tab_s, const unsigned short *tab_u,
            const unsigned char *tab_sb, int e, unsigned char *dest);

/* Tables for ISO/IEC 8859-2 */
static const unsigned short iso8859_2_s[6] = { /* Straight-thru bit-flags */
    0x2191, 0x0111, 0x6A96, 0xB4D8, 0x6A96, 0x34D8,
};
static const unsigned short iso8859_2_u[57] = { /* Unicode codepoints sorted */
    0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D,
    0x010E, 0x010F, 0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B,
    0x0139, 0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143, 0x0144,
    0x0147, 0x0148, 0x0150, 0x0151, 0x0154, 0x0155, 0x0158, 0x0159,
    0x015A, 0x015B, 0x015E, 0x015F, 0x0160, 0x0161, 0x0162, 0x0163,
    0x0164, 0x0165, 0x016E, 0x016F, 0x0170, 0x0171, 0x0179, 0x017A,
    0x017B, 0x017C, 0x017D, 0x017E, 0x02C7, 0x02D8, 0x02D9, 0x02DB,
    0x02DD,
};
static const unsigned char iso8859_2_sb[57] = { /* Single-byte in Unicode order */
    0xC3,   0xE3,   0xA1,   0xB1,   0xC6,   0xE6,   0xC8,   0xE8,
    0xCF,   0xEF,   0xD0,   0xF0,   0xCA,   0xEA,   0xCC,   0xEC,
    0xC5,   0xE5,   0xA5,   0xB5,   0xA3,   0xB3,   0xD1,   0xF1,
    0xD2,   0xF2,   0xD5,   0xF5,   0xC0,   0xE0,   0xD8,   0xF8,
    0xA6,   0xB6,   0xAA,   0xBA,   0xA9,   0xB9,   0xDE,   0xFE,
    0xAB,   0xBB,   0xD9,   0xF9,   0xDB,   0xFB,   0xAC,   0xBC,
    0xAF,   0xBF,   0xAE,   0xBE,   0xB7,   0xA2,   0xFF,   0xB2,
    0xBD,
};

/* ECI 4 ISO/IEC 8859-2 Latin alphabet No. 2 (Latin-2) */
static int u_iso8859_2(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_2_s, iso8859_2_u, iso8859_2_sb, ARRAY_SIZE(iso8859_2_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-3 */
static const unsigned short iso8859_3_s[6] = { /* Straight-thru bit-flags */
    0x2199, 0x21BD, 0xFF97, 0x9EDE, 0xFF97, 0x1EDE,
};
static const unsigned short iso8859_3_u[28] = { /* Unicode codepoints sorted */
    0x0108, 0x0109, 0x010A, 0x010B, 0x011C, 0x011D, 0x011E, 0x011F,
    0x0120, 0x0121, 0x0124, 0x0125, 0x0126, 0x0127, 0x0130, 0x0131,
    0x0134, 0x0135, 0x015C, 0x015D, 0x015E, 0x015F, 0x016C, 0x016D,
    0x017B, 0x017C, 0x02D8, 0x02D9,
};
static const unsigned char iso8859_3_sb[28] = { /* Single-byte in Unicode order */
    0xC6,   0xE6,   0xC5,   0xE5,   0xD8,   0xF8,   0xAB,   0xBB,
    0xD5,   0xF5,   0xA6,   0xB6,   0xA1,   0xB1,   0xA9,   0xB9,
    0xAC,   0xBC,   0xDE,   0xFE,   0xAA,   0xBA,   0xDD,   0xFD,
    0xAF,   0xBF,   0xA2,   0xFF,
};

/* ECI 5 ISO/IEC 8859-3 Latin alphabet No. 3 (Latin-3) (South European) */
static int u_iso8859_3(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_3_s, iso8859_3_u, iso8859_3_sb, ARRAY_SIZE(iso8859_3_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-4 */
static const unsigned short iso8859_4_s[6] = { /* Straight-thru bit-flags */
    0xA191, 0x0111, 0x6A7E, 0x9DF0, 0x6A7E, 0x1DF0,
};
static const unsigned short iso8859_4_u[50] = { /* Unicode codepoints sorted */
    0x0100, 0x0101, 0x0104, 0x0105, 0x010C, 0x010D, 0x0110, 0x0111,
    0x0112, 0x0113, 0x0116, 0x0117, 0x0118, 0x0119, 0x0122, 0x0123,
    0x0128, 0x0129, 0x012A, 0x012B, 0x012E, 0x012F, 0x0136, 0x0137,
    0x0138, 0x013B, 0x013C, 0x0145, 0x0146, 0x014A, 0x014B, 0x014C,
    0x014D, 0x0156, 0x0157, 0x0160, 0x0161, 0x0166, 0x0167, 0x0168,
    0x0169, 0x016A, 0x016B, 0x0172, 0x0173, 0x017D, 0x017E, 0x02C7,
    0x02D9, 0x02DB,
};
static const unsigned char iso8859_4_sb[50] = { /* Single-byte in Unicode order */
    0xC0,   0xE0,   0xA1,   0xB1,   0xC8,   0xE8,   0xD0,   0xF0,
    0xAA,   0xBA,   0xCC,   0xEC,   0xCA,   0xEA,   0xAB,   0xBB,
    0xA5,   0xB5,   0xCF,   0xEF,   0xC7,   0xE7,   0xD3,   0xF3,
    0xA2,   0xA6,   0xB6,   0xD1,   0xF1,   0xBD,   0xBF,   0xD2,
    0xF2,   0xA3,   0xB3,   0xA9,   0xB9,   0xAC,   0xBC,   0xDD,
    0xFD,   0xDE,   0xFE,   0xD9,   0xF9,   0xAE,   0xBE,   0xB7,
    0xFF,   0xB2,
};

/* ECI 6 ISO/IEC 8859-4 Latin alphabet No. 4 (Latin-4) (North European) */
static int u_iso8859_4(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_4_s, iso8859_4_u, iso8859_4_sb, ARRAY_SIZE(iso8859_4_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-5 */
static const unsigned short iso8859_5_s[6] = { /* Straight-thru bit-flags */
    0x2001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short iso8859_5_u[94] = { /* Unicode codepoints sorted */
    0x00A7, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407,
    0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040E, 0x040F, 0x0410,
    0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418,
    0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 0x0420,
    0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428,
    0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 0x0430,
    0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438,
    0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 0x0440,
    0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448,
    0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 0x0451,
    0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459,
    0x045A, 0x045B, 0x045C, 0x045E, 0x045F, 0x2116,
};
static const unsigned char iso8859_5_sb[94] = { /* Single-byte in Unicode order */
    0xFD,   0xA1,   0xA2,   0xA3,   0xA4,   0xA5,   0xA6,   0xA7,
    0xA8,   0xA9,   0xAA,   0xAB,   0xAC,   0xAE,   0xAF,   0xB0,
    0xB1,   0xB2,   0xB3,   0xB4,   0xB5,   0xB6,   0xB7,   0xB8,
    0xB9,   0xBA,   0xBB,   0xBC,   0xBD,   0xBE,   0xBF,   0xC0,
    0xC1,   0xC2,   0xC3,   0xC4,   0xC5,   0xC6,   0xC7,   0xC8,
    0xC9,   0xCA,   0xCB,   0xCC,   0xCD,   0xCE,   0xCF,   0xD0,
    0xD1,   0xD2,   0xD3,   0xD4,   0xD5,   0xD6,   0xD7,   0xD8,
    0xD9,   0xDA,   0xDB,   0xDC,   0xDD,   0xDE,   0xDF,   0xE0,
    0xE1,   0xE2,   0xE3,   0xE4,   0xE5,   0xE6,   0xE7,   0xE8,
    0xE9,   0xEA,   0xEB,   0xEC,   0xED,   0xEE,   0xEF,   0xF1,
    0xF2,   0xF3,   0xF4,   0xF5,   0xF6,   0xF7,   0xF8,   0xF9,
    0xFA,   0xFB,   0xFC,   0xFE,   0xFF,   0xF0,
};

/* ECI 7 ISO/IEC 8859-5 Latin/Cyrillic */
static int u_iso8859_5(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_5_s, iso8859_5_u, iso8859_5_sb, ARRAY_SIZE(iso8859_5_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-6 */
static const unsigned short iso8859_6_s[6] = { /* Straight-thru bit-flags */
    0x2011, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short iso8859_6_u[48] = { /* Unicode codepoints sorted */
    0x060C, 0x061B, 0x061F, 0x0621, 0x0622, 0x0623, 0x0624, 0x0625,
    0x0626, 0x0627, 0x0628, 0x0629, 0x062A, 0x062B, 0x062C, 0x062D,
    0x062E, 0x062F, 0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635,
    0x0636, 0x0637, 0x0638, 0x0639, 0x063A, 0x0640, 0x0641, 0x0642,
    0x0643, 0x0644, 0x0645, 0x0646, 0x0647, 0x0648, 0x0649, 0x064A,
    0x064B, 0x064C, 0x064D, 0x064E, 0x064F, 0x0650, 0x0651, 0x0652,
};
static const unsigned char iso8859_6_sb[48] = { /* Single-byte in Unicode order */
    0xAC,   0xBB,   0xBF,   0xC1,   0xC2,   0xC3,   0xC4,   0xC5,
    0xC6,   0xC7,   0xC8,   0xC9,   0xCA,   0xCB,   0xCC,   0xCD,
    0xCE,   0xCF,   0xD0,   0xD1,   0xD2,   0xD3,   0xD4,   0xD5,
    0xD6,   0xD7,   0xD8,   0xD9,   0xDA,   0xE0,   0xE1,   0xE2,
    0xE3,   0xE4,   0xE5,   0xE6,   0xE7,   0xE8,   0xE9,   0xEA,
    0xEB,   0xEC,   0xED,   0xEE,   0xEF,   0xF0,   0xF1,   0xF2,
};

/* ECI 8 ISO/IEC 8859-6 Latin/Arabic */
static int u_iso8859_6(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_6_s, iso8859_6_u, iso8859_6_sb, ARRAY_SIZE(iso8859_6_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-7 */
static const unsigned short iso8859_7_s[6] = { /* Straight-thru bit-flags */
    0x3BC9, 0x288F, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short iso8859_7_u[77] = { /* Unicode codepoints sorted */
    0x037A, 0x0384, 0x0385, 0x0386, 0x0388, 0x0389, 0x038A, 0x038C,
    0x038E, 0x038F, 0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395,
    0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D,
    0x039E, 0x039F, 0x03A0, 0x03A1, 0x03A3, 0x03A4, 0x03A5, 0x03A6,
    0x03A7, 0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x03AC, 0x03AD, 0x03AE,
    0x03AF, 0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6,
    0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE,
    0x03BF, 0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6,
    0x03C7, 0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE,
    0x2015, 0x2018, 0x2019, 0x20AC, 0x20AF,
};
static const unsigned char iso8859_7_sb[77] = { /* Single-byte in Unicode order */
    0xAA,   0xB4,   0xB5,   0xB6,   0xB8,   0xB9,   0xBA,   0xBC,
    0xBE,   0xBF,   0xC0,   0xC1,   0xC2,   0xC3,   0xC4,   0xC5,
    0xC6,   0xC7,   0xC8,   0xC9,   0xCA,   0xCB,   0xCC,   0xCD,
    0xCE,   0xCF,   0xD0,   0xD1,   0xD3,   0xD4,   0xD5,   0xD6,
    0xD7,   0xD8,   0xD9,   0xDA,   0xDB,   0xDC,   0xDD,   0xDE,
    0xDF,   0xE0,   0xE1,   0xE2,   0xE3,   0xE4,   0xE5,   0xE6,
    0xE7,   0xE8,   0xE9,   0xEA,   0xEB,   0xEC,   0xED,   0xEE,
    0xEF,   0xF0,   0xF1,   0xF2,   0xF3,   0xF4,   0xF5,   0xF6,
    0xF7,   0xF8,   0xF9,   0xFA,   0xFB,   0xFC,   0xFD,   0xFE,
    0xAF,   0xA1,   0xA2,   0xA4,   0xA5,
};

/* ECI 9 ISO/IEC 8859-7 Latin/Greek */
static int u_iso8859_7(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_7_s, iso8859_7_u, iso8859_7_sb, ARRAY_SIZE(iso8859_7_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-8 */
static const unsigned short iso8859_8_s[6] = { /* Straight-thru bit-flags */
    0xFBFD, 0x7BFF, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short iso8859_8_u[32] = { /* Unicode codepoints sorted */
    0x00D7, 0x00F7, 0x05D0, 0x05D1, 0x05D2, 0x05D3, 0x05D4, 0x05D5,
    0x05D6, 0x05D7, 0x05D8, 0x05D9, 0x05DA, 0x05DB, 0x05DC, 0x05DD,
    0x05DE, 0x05DF, 0x05E0, 0x05E1, 0x05E2, 0x05E3, 0x05E4, 0x05E5,
    0x05E6, 0x05E7, 0x05E8, 0x05E9, 0x05EA, 0x200E, 0x200F, 0x2017,
};
static const unsigned char iso8859_8_sb[32] = { /* Single-byte in Unicode order */
    0xAA,   0xBA,   0xE0,   0xE1,   0xE2,   0xE3,   0xE4,   0xE5,
    0xE6,   0xE7,   0xE8,   0xE9,   0xEA,   0xEB,   0xEC,   0xED,
    0xEE,   0xEF,   0xF0,   0xF1,   0xF2,   0xF3,   0xF4,   0xF5,
    0xF6,   0xF7,   0xF8,   0xF9,   0xFA,   0xFD,   0xFE,   0xDF,
};

/* ECI 10 ISO/IEC 8859-8 Latin/Hebrew */
static int u_iso8859_8(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_8_s, iso8859_8_u, iso8859_8_sb, ARRAY_SIZE(iso8859_8_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-9 */
static const unsigned short iso8859_9_s[6] = { /* Straight-thru bit-flags */
    0xFFFF, 0xFFFF, 0xFFFF, 0x9FFE, 0xFFFF, 0x9FFE,
};
static const unsigned short iso8859_9_u[6] = { /* Unicode codepoints sorted */
    0x011E, 0x011F, 0x0130, 0x0131, 0x015E, 0x015F,
};
static const unsigned char iso8859_9_sb[6] = { /* Single-byte in Unicode order */
    0xD0,   0xF0,   0xDD,   0xFD,   0xDE,   0xFE,
};

/* ECI 11 ISO/IEC 8859-9 Latin alphabet No. 5 (Latin-5) (Latin/Turkish) */
static int u_iso8859_9(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_9_s, iso8859_9_u, iso8859_9_sb, ARRAY_SIZE(iso8859_9_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-10 */
static const unsigned short iso8859_10_s[6] = { /* Straight-thru bit-flags */
    0x2081, 0x0081, 0xEA7E, 0xFD79, 0xEA7E, 0x7D79,
};
static const unsigned short iso8859_10_u[46] = { /* Unicode codepoints sorted */
    0x0100, 0x0101, 0x0104, 0x0105, 0x010C, 0x010D, 0x0110, 0x0111,
    0x0112, 0x0113, 0x0116, 0x0117, 0x0118, 0x0119, 0x0122, 0x0123,
    0x0128, 0x0129, 0x012A, 0x012B, 0x012E, 0x012F, 0x0136, 0x0137,
    0x0138, 0x013B, 0x013C, 0x0145, 0x0146, 0x014A, 0x014B, 0x014C,
    0x014D, 0x0160, 0x0161, 0x0166, 0x0167, 0x0168, 0x0169, 0x016A,
    0x016B, 0x0172, 0x0173, 0x017D, 0x017E, 0x2015,
};
static const unsigned char iso8859_10_sb[46] = { /* Single-byte in Unicode order */
    0xC0,   0xE0,   0xA1,   0xB1,   0xC8,   0xE8,   0xA9,   0xB9,
    0xA2,   0xB2,   0xCC,   0xEC,   0xCA,   0xEA,   0xA3,   0xB3,
    0xA5,   0xB5,   0xA4,   0xB4,   0xC7,   0xE7,   0xA6,   0xB6,
    0xFF,   0xA8,   0xB8,   0xD1,   0xF1,   0xAF,   0xBF,   0xD2,
    0xF2,   0xAA,   0xBA,   0xAB,   0xBB,   0xD7,   0xF7,   0xAE,
    0xBE,   0xD9,   0xF9,   0xAC,   0xBC,   0xBD,
};

/* ECI 12 ISO/IEC 8859-10 Latin alphabet No. 6 (Latin-6) (Nordic) */
static int u_iso8859_10(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_10_s, iso8859_10_u, iso8859_10_sb, ARRAY_SIZE(iso8859_10_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-11 */
static const unsigned short iso8859_11_s[6] = { /* Straight-thru bit-flags */
    0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short iso8859_11_u[87] = { /* Unicode codepoints sorted */
    0x0E01, 0x0E02, 0x0E03, 0x0E04, 0x0E05, 0x0E06, 0x0E07, 0x0E08,
    0x0E09, 0x0E0A, 0x0E0B, 0x0E0C, 0x0E0D, 0x0E0E, 0x0E0F, 0x0E10,
    0x0E11, 0x0E12, 0x0E13, 0x0E14, 0x0E15, 0x0E16, 0x0E17, 0x0E18,
    0x0E19, 0x0E1A, 0x0E1B, 0x0E1C, 0x0E1D, 0x0E1E, 0x0E1F, 0x0E20,
    0x0E21, 0x0E22, 0x0E23, 0x0E24, 0x0E25, 0x0E26, 0x0E27, 0x0E28,
    0x0E29, 0x0E2A, 0x0E2B, 0x0E2C, 0x0E2D, 0x0E2E, 0x0E2F, 0x0E30,
    0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37, 0x0E38,
    0x0E39, 0x0E3A, 0x0E3F, 0x0E40, 0x0E41, 0x0E42, 0x0E43, 0x0E44,
    0x0E45, 0x0E46, 0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C,
    0x0E4D, 0x0E4E, 0x0E4F, 0x0E50, 0x0E51, 0x0E52, 0x0E53, 0x0E54,
    0x0E55, 0x0E56, 0x0E57, 0x0E58, 0x0E59, 0x0E5A, 0x0E5B,
};
static const unsigned char iso8859_11_sb[87] = { /* Single-byte in Unicode order */
    0xA1,   0xA2,   0xA3,   0xA4,   0xA5,   0xA6,   0xA7,   0xA8,
    0xA9,   0xAA,   0xAB,   0xAC,   0xAD,   0xAE,   0xAF,   0xB0,
    0xB1,   0xB2,   0xB3,   0xB4,   0xB5,   0xB6,   0xB7,   0xB8,
    0xB9,   0xBA,   0xBB,   0xBC,   0xBD,   0xBE,   0xBF,   0xC0,
    0xC1,   0xC2,   0xC3,   0xC4,   0xC5,   0xC6,   0xC7,   0xC8,
    0xC9,   0xCA,   0xCB,   0xCC,   0xCD,   0xCE,   0xCF,   0xD0,
    0xD1,   0xD2,   0xD3,   0xD4,   0xD5,   0xD6,   0xD7,   0xD8,
    0xD9,   0xDA,   0xDF,   0xE0,   0xE1,   0xE2,   0xE3,   0xE4,
    0xE5,   0xE6,   0xE7,   0xE8,   0xE9,   0xEA,   0xEB,   0xEC,
    0xED,   0xEE,   0xEF,   0xF0,   0xF1,   0xF2,   0xF3,   0xF4,
    0xF5,   0xF6,   0xF7,   0xF8,   0xF9,   0xFA,   0xFB,
};

/* ECI 13 ISO/IEC 8859-11 Latin/Thai */
static int u_iso8859_11(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_11_s, iso8859_11_u, iso8859_11_sb, ARRAY_SIZE(iso8859_11_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-13 */
static const unsigned short iso8859_13_s[6] = { /* Straight-thru bit-flags */
    0x7ADD, 0x7AEF, 0x0230, 0x90E8, 0x0230, 0x10E8,
};
static const unsigned short iso8859_13_u[56] = { /* Unicode codepoints sorted */
    0x00C6, 0x00D8, 0x00E6, 0x00F8, 0x0100, 0x0101, 0x0104, 0x0105,
    0x0106, 0x0107, 0x010C, 0x010D, 0x0112, 0x0113, 0x0116, 0x0117,
    0x0118, 0x0119, 0x0122, 0x0123, 0x012A, 0x012B, 0x012E, 0x012F,
    0x0136, 0x0137, 0x013B, 0x013C, 0x0141, 0x0142, 0x0143, 0x0144,
    0x0145, 0x0146, 0x014C, 0x014D, 0x0156, 0x0157, 0x015A, 0x015B,
    0x0160, 0x0161, 0x016A, 0x016B, 0x0172, 0x0173, 0x0179, 0x017A,
    0x017B, 0x017C, 0x017D, 0x017E, 0x2019, 0x201C, 0x201D, 0x201E,
};
static const unsigned char iso8859_13_sb[56] = { /* Single-byte in Unicode order */
    0xAF,   0xA8,   0xBF,   0xB8,   0xC2,   0xE2,   0xC0,   0xE0,
    0xC3,   0xE3,   0xC8,   0xE8,   0xC7,   0xE7,   0xCB,   0xEB,
    0xC6,   0xE6,   0xCC,   0xEC,   0xCE,   0xEE,   0xC1,   0xE1,
    0xCD,   0xED,   0xCF,   0xEF,   0xD9,   0xF9,   0xD1,   0xF1,
    0xD2,   0xF2,   0xD4,   0xF4,   0xAA,   0xBA,   0xDA,   0xFA,
    0xD0,   0xF0,   0xDB,   0xFB,   0xD8,   0xF8,   0xCA,   0xEA,
    0xDD,   0xFD,   0xDE,   0xFE,   0xFF,   0xB4,   0xA1,   0xA5,
};

/* ECI 15 ISO/IEC 8859-13 Latin alphabet No. 7 (Latin-7) (Baltic Rim) */
static int u_iso8859_13(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_13_s, iso8859_13_u, iso8859_13_sb, ARRAY_SIZE(iso8859_13_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-14 */
static const unsigned short iso8859_14_s[6] = { /* Straight-thru bit-flags */
    0x6289, 0x0040, 0xFFFF, 0xBF7E, 0xFFFF, 0xBF7E,
};
static const unsigned short iso8859_14_u[31] = { /* Unicode codepoints sorted */
    0x010A, 0x010B, 0x0120, 0x0121, 0x0174, 0x0175, 0x0176, 0x0177,
    0x0178, 0x1E02, 0x1E03, 0x1E0A, 0x1E0B, 0x1E1E, 0x1E1F, 0x1E40,
    0x1E41, 0x1E56, 0x1E57, 0x1E60, 0x1E61, 0x1E6A, 0x1E6B, 0x1E80,
    0x1E81, 0x1E82, 0x1E83, 0x1E84, 0x1E85, 0x1EF2, 0x1EF3,
};
static const unsigned char iso8859_14_sb[31] = { /* Single-byte in Unicode order */
    0xA4,   0xA5,   0xB2,   0xB3,   0xD0,   0xF0,   0xDE,   0xFE,
    0xAF,   0xA1,   0xA2,   0xA6,   0xAB,   0xB0,   0xB1,   0xB4,
    0xB5,   0xB7,   0xB9,   0xBB,   0xBF,   0xD7,   0xF7,   0xA8,
    0xB8,   0xAA,   0xBA,   0xBD,   0xBE,   0xAC,   0xBC,
};

/* ECI 16 ISO/IEC 8859-14 Latin alphabet No. 8 (Latin-8) (Celtic) */
static int u_iso8859_14(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_14_s, iso8859_14_u, iso8859_14_sb, ARRAY_SIZE(iso8859_14_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-15 */
static const unsigned short iso8859_15_s[6] = { /* Straight-thru bit-flags */
    0xFEAF, 0x8EEF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
static const unsigned short iso8859_15_u[8] = { /* Unicode codepoints sorted */
    0x0152, 0x0153, 0x0160, 0x0161, 0x0178, 0x017D, 0x017E, 0x20AC,
};
static const unsigned char iso8859_15_sb[8] = { /* Single-byte in Unicode order */
    0xBC,   0xBD,   0xA6,   0xA8,   0xBE,   0xB4,   0xB8,   0xA4,
};

/* ECI 17 ISO/IEC 8859-15 Latin alphabet No. 9 (Latin-9) */
static int u_iso8859_15(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_15_s, iso8859_15_u, iso8859_15_sb, ARRAY_SIZE(iso8859_15_u) - 1, dest);
}

/* Tables for ISO/IEC 8859-16 */
static const unsigned short iso8859_16_s[6] = { /* Straight-thru bit-flags */
    0x2A81, 0x08C3, 0xFFD7, 0x9E5C, 0xFFD7, 0x9E5C,
};
static const unsigned short iso8859_16_u[40] = { /* Unicode codepoints sorted */
    0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D,
    0x0110, 0x0111, 0x0118, 0x0119, 0x0141, 0x0142, 0x0143, 0x0144,
    0x0150, 0x0151, 0x0152, 0x0153, 0x015A, 0x015B, 0x0160, 0x0161,
    0x0170, 0x0171, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D,
    0x017E, 0x0218, 0x0219, 0x021A, 0x021B, 0x201D, 0x201E, 0x20AC,
};
static const unsigned char iso8859_16_sb[40] = { /* Single-byte in Unicode order */
    0xC3,   0xE3,   0xA1,   0xA2,   0xC5,   0xE5,   0xB2,   0xB9,
    0xD0,   0xF0,   0xDD,   0xFD,   0xA3,   0xB3,   0xD1,   0xF1,
    0xD5,   0xF5,   0xBC,   0xBD,   0xD7,   0xF7,   0xA6,   0xA8,
    0xD8,   0xF8,   0xBE,   0xAC,   0xAE,   0xAF,   0xBF,   0xB4,
    0xB8,   0xAA,   0xBA,   0xDE,   0xFE,   0xB5,   0xA5,   0xA4,
};

/* ECI 18 ISO/IEC 8859-16 Latin alphabet No. 10 (Latin-10) (South-Eastern European) */
static int u_iso8859_16(const unsigned int u, unsigned char *dest) {
    return u_iso8859(u, iso8859_16_s, iso8859_16_u, iso8859_16_sb, ARRAY_SIZE(iso8859_16_u) - 1, dest);
}

/* Forward reference to base Windows-125x routine - see "eci.c" */
static int u_cp125x(const unsigned int u, const unsigned short *tab_s, const unsigned short *tab_u,
            const unsigned char *tab_sb, int e, unsigned char *dest);

/* Tables for Windows 1250 */
static const unsigned short cp1250_s[6] = { /* Straight-thru bit-flags */
    0x7BD1, 0x09F3, 0x6A96, 0xB4D8, 0x6A96, 0x34D8,
};
static const unsigned short cp1250_u[74] = { /* Unicode codepoints sorted */
    0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D,
    0x010E, 0x010F, 0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B,
    0x0139, 0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143, 0x0144,
    0x0147, 0x0148, 0x0150, 0x0151, 0x0154, 0x0155, 0x0158, 0x0159,
    0x015A, 0x015B, 0x015E, 0x015F, 0x0160, 0x0161, 0x0162, 0x0163,
    0x0164, 0x0165, 0x016E, 0x016F, 0x0170, 0x0171, 0x0179, 0x017A,
    0x017B, 0x017C, 0x017D, 0x017E, 0x02C7, 0x02D8, 0x02D9, 0x02DB,
    0x02DD, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A, 0x201C, 0x201D,
    0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A,
    0x20AC, 0x2122,
};
static const unsigned char cp1250_sb[74] = { /* Single-byte in Unicode order */
    0xC3,   0xE3,   0xA5,   0xB9,   0xC6,   0xE6,   0xC8,   0xE8,
    0xCF,   0xEF,   0xD0,   0xF0,   0xCA,   0xEA,   0xCC,   0xEC,
    0xC5,   0xE5,   0xBC,   0xBE,   0xA3,   0xB3,   0xD1,   0xF1,
    0xD2,   0xF2,   0xD5,   0xF5,   0xC0,   0xE0,   0xD8,   0xF8,
    0x8C,   0x9C,   0xAA,   0xBA,   0x8A,   0x9A,   0xDE,   0xFE,
    0x8D,   0x9D,   0xD9,   0xF9,   0xDB,   0xFB,   0x8F,   0x9F,
    0xAF,   0xBF,   0x8E,   0x9E,   0xA1,   0xA2,   0xFF,   0xB2,
    0xBD,   0x96,   0x97,   0x91,   0x92,   0x82,   0x93,   0x94,
    0x84,   0x86,   0x87,   0x95,   0x85,   0x89,   0x8B,   0x9B,
    0x80,   0x99,
};

/* ECI 21 Windows-1250 Latin 2 (Central Europe) */
static int u_cp1250(const unsigned int u, unsigned char *dest) {
    return u_cp125x(u, cp1250_s, cp1250_u, cp1250_sb, ARRAY_SIZE(cp1250_u) - 1, dest);
}

/* Tables for Windows 1251 */
static const unsigned short cp1251_s[6] = { /* Straight-thru bit-flags */
    0x7AD1, 0x08E3, 0x0000, 0x0000, 0x0000, 0x0000,
};
static const unsigned short cp1251_u[112] = { /* Unicode codepoints sorted */
    0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408,
    0x0409, 0x040A, 0x040B, 0x040C, 0x040E, 0x040F, 0x0410, 0x0411,
    0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418, 0x0419,
    0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 0x0420, 0x0421,
    0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429,
    0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 0x0430, 0x0431,
    0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439,
    0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 0x0440, 0x0441,
    0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449,
    0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 0x0451, 0x0452,
    0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A,
    0x045B, 0x045C, 0x045E, 0x045F, 0x0490, 0x0491, 0x2013, 0x2014,
    0x2018, 0x2019, 0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021,
    0x2022, 0x2026, 0x2030, 0x2039, 0x203A, 0x20AC, 0x2116, 0x2122,
};
static const unsigned char cp1251_sb[112] = { /* Single-byte in Unicode order */
    0xA8,   0x80,   0x81,   0xAA,   0xBD,   0xB2,   0xAF,   0xA3,
    0x8A,   0x8C,   0x8E,   0x8D,   0xA1,   0x8F,   0xC0,   0xC1,
    0xC2,   0xC3,   0xC4,   0xC5,   0xC6,   0xC7,   0xC8,   0xC9,
    0xCA,   0xCB,   0xCC,   0xCD,   0xCE,   0xCF,   0xD0,   0xD1,
    0xD2,   0xD3,   0xD4,   0xD5,   0xD6,   0xD7,   0xD8,   0xD9,
    0xDA,   0xDB,   0xDC,   0xDD,   0xDE,   0xDF,   0xE0,   0xE1,
    0xE2,   0xE3,   0xE4,   0xE5,   0xE6,   0xE7,   0xE8,   0xE9,
    0xEA,   0xEB,   0xEC,   0xED,   0xEE,   0xEF,   0xF0,   0xF1,
    0xF2,   0xF3,   0xF4,   0xF5,   0xF6,   0xF7,   0xF8,   0xF9,
    0xFA,   0xFB,   0xFC,   0xFD,   0xFE,   0xFF,   0xB8,   0x90,
    0x83,   0xBA,   0xBE,   0xB3,   0xBF,   0xBC,   0x9A,   0x9C,
    0x9E,   0x9D,   0xA2,   0x9F,   0xA5,   0xB4,   0x96,   0x97,
    0x91,   0x92,   0x82,   0x93,   0x94,   0x84,   0x86,   0x87,
    0x95,   0x85,   0x89,   0x8B,   0x9B,   0x88,   0xB9,   0x99,
};

/* ECI 22 Windows-1251 Cyrillic */
static int u_cp1251(const unsigned int u, unsigned char *dest) {
    return u_cp125x(u, cp1251_s, cp1251_u, cp1251_sb, ARRAY_SIZE(cp1251_u) - 1, dest);
}

/* Tables for Windows 1252 */
static const unsigned short cp1252_s[6] = { /* Straight-thru bit-flags */
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};
static const unsigned short cp1252_u[27] = { /* Unicode codepoints sorted */
    0x0152, 0x0153, 0x0160, 0x0161, 0x0178, 0x017D, 0x017E, 0x0192,
    0x02C6, 0x02DC, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A, 0x201C,
    0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039,
    0x203A, 0x20AC, 0x2122,
};
static const unsigned char cp1252_sb[27] = { /* Single-byte in Unicode order */
    0x8C,   0x9C,   0x8A,   0x9A,   0x9F,   0x8E,   0x9E,   0x83,
    0x88,   0x98,   0x96,   0x97,   0x91,   0x92,   0x82,   0x93,
    0x94,   0x84,   0x86,   0x87,   0x95,   0x85,   0x89,   0x8B,
    0x9B,   0x80,   0x99,
};

/* ECI 23 Windows-1252 Latin 1 */
static int u_cp1252(const unsigned int u, unsigned char *dest) {
    return u_cp125x(u, cp1252_s, cp1252_u, cp1252_sb, ARRAY_SIZE(cp1252_u) - 1, dest);
}

/* Tables for Windows 1256 */
static const unsigned short cp1256_s[6] = { /* Straight-thru bit-flags */
    0xFBFD, 0x7BFF, 0x0000, 0x0080, 0xCF85, 0x1A90,
};
static const unsigned short cp1256_u[85] = { /* Unicode codepoints sorted */
    0x0152, 0x0153, 0x0192, 0x02C6, 0x060C, 0x061B, 0x061F, 0x0621,
    0x0622, 0x0623, 0x0624, 0x0625, 0x0626, 0x0627, 0x0628, 0x0629,
    0x062A, 0x062B, 0x062C, 0x062D, 0x062E, 0x062F, 0x0630, 0x0631,
    0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637, 0x0638, 0x0639,
    0x063A, 0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646,
    0x0647, 0x0648, 0x0649, 0x064A, 0x064B, 0x064C, 0x064D, 0x064E,
    0x064F, 0x0650, 0x0651, 0x0652, 0x0679, 0x067E, 0x0686, 0x0688,
    0x0691, 0x0698, 0x06A9, 0x06AF, 0x06BA, 0x06BE, 0x06C1, 0x06D2,
    0x200C, 0x200D, 0x200E, 0x200F, 0x2013, 0x2014, 0x2018, 0x2019,
    0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026,
    0x2030, 0x2039, 0x203A, 0x20AC, 0x2122,
};
static const unsigned char cp1256_sb[85] = { /* Single-byte in Unicode order */
    0x8C,   0x9C,   0x83,   0x88,   0xA1,   0xBA,   0xBF,   0xC1,
    0xC2,   0xC3,   0xC4,   0xC5,   0xC6,   0xC7,   0xC8,   0xC9,
    0xCA,   0xCB,   0xCC,   0xCD,   0xCE,   0xCF,   0xD0,   0xD1,
    0xD2,   0xD3,   0xD4,   0xD5,   0xD6,   0xD8,   0xD9,   0xDA,
    0xDB,   0xDC,   0xDD,   0xDE,   0xDF,   0xE1,   0xE3,   0xE4,
    0xE5,   0xE6,   0xEC,   0xED,   0xF0,   0xF1,   0xF2,   0xF3,
    0xF5,   0xF6,   0xF8,   0xFA,   0x8A,   0x81,   0x8D,   0x8F,
    0x9A,   0x8E,   0x98,   0x90,   0x9F,   0xAA,   0xC0,   0xFF,
    0x9D,   0x9E,   0xFD,   0xFE,   0x96,   0x97,   0x91,   0x92,
    0x82,   0x93,   0x94,   0x84,   0x86,   0x87,   0x95,   0x85,
    0x89,   0x8B,   0x9B,   0x80,   0x99,
};

/* ECI 24 Windows-1256 Arabic */
static int u_cp1256(const unsigned int u, unsigned char *dest) {
    return u_cp125x(u, cp1256_s, cp1256_u, cp1256_sb, ARRAY_SIZE(cp1256_u) - 1, dest);
}

#endif /* Z_ECI_SB_H */
