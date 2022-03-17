/*

 * Copyright (C) 2020 Xiaomi Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <zint.h>

#define GENERATE_BMP  1

int main(int argc, char **argv) {
    struct zint_symbol *my_symbol;
    int ret;

    my_symbol = ZBarcode_Create();
    if (my_symbol != NULL) {
        printf("Symbol create success!\n");
    } else {
        printf("Symbol create failed!\n");
        ret = -1;
        return ret;
    }

    my_symbol->symbology = BARCODE_QRCODE;
    my_symbol->option_1 = 4;

#if GENERATE_BMP
    /* Generate bmp */
    memcpy(my_symbol->outfile, "/data/bijian.bmp", 16);
    ret = ZBarcode_Encode_and_Print(my_symbol, "abf48wfg12gdnj3", 15, 0);
    printf("ZBarcode_Encode_and_Print ret = %d\n", ret);
#else
    /* Generate array buff (RGB888, 3 bytes per pixel, row by row) */
    ret = ZBarcode_Encode_and_Buffer(my_symbol, "123", 3, 0);
    printf("ZBarcode_Encode_and_Buffer ret = %d\n", ret);
#endif

    ZBarcode_Delete(my_symbol);

    return ret;
}