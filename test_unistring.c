#include <stdio.h>
#include "unistr.h"
#include "unicase.h"

int main() {
    uint8_t input[] = "TEST";
    uint8_t output[5] = {0}; // Inicializace pole na nuly
    size_t length;
    u8_tolower(input, 4, "en", UNINORM_NFC, output, &length);
    printf("Output: %s\n", output);
    return 0;
}