#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

static void to_32bit_binary(uint32_t v, char *out) {
    for (int i = 31; i >= 0; --i) out[31 - i] = ((v >> i) & 1) ? '1' : '0';
    out[32] = '\0';
}

void oct_to_bin(const char *oct, char *out) {
    static const char *map[8] = {"000","001","010","011","100","101","110","111"};
    size_t n = strlen(oct), p = 0;
    for (size_t i = 0; i < n; ++i) {
        char c = oct[i];
        if (c < '0' || c > '7') continue;
        const char *m = map[c - '0'];
        out[p++] = m[0]; out[p++] = m[1]; out[p++] = m[2];
    }
    out[p] = '\0';
}

void hex_to_bin(const char *hex, char *out) {
    static const char *map[16] = {
        "0000","0001","0010","0011","0100","0101","0110","0111",
        "1000","1001","1010","1011","1100","1101","1110","1111"
    };

    size_t n = strlen(hex), p = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)hex[i];
        int v;
        if      (c >= '0' && c <= '9') v = c - '0';
        else if (c >= 'A' && c <= 'F') v = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f') v = 10 + (c - 'a');
        else continue;
        const char *m = map[v];
        out[p++] = m[0]; out[p++] = m[1]; out[p++] = m[2]; out[p++] = m[3];
    }
    out[p] = '\0';
}

void oct_to_hex(const char *oct, char *out) {
    char bin[256]; bin[0] = '\0';
    oct_to_bin(oct, bin);

    size_t len = strlen(bin);
    size_t pad = (4 - (len % 4)) % 4;
    char padded[260];
    for (size_t i = 0; i < pad; ++i) padded[i] = '0';
    memcpy(padded + pad, bin, len + 1);

    static const char HEX[] = "0123456789ABCDEF";
    size_t L = pad + len, p = 0;

    for (size_t i = 0; i < L; i += 4) {
        int v = (padded[i]-'0')*8 + (padded[i+1]-'0')*4 + (padded[i+2]-'0')*2 + (padded[i+3]-'0');
        out[p++] = HEX[v];
    }
    out[p] = '\0';

    size_t k = 0; while (out[k] == '0' && out[k+1] != '\0') ++k;
    if (k) memmove(out, out + k, p - k + 1);
}

void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
        out[0] = '0';
    } else {
        uint32_t mag;
        if (n == INT32_MIN) mag = 2147483648u;     
        else mag = (uint32_t)(-(int64_t)n);
        char tmp[33];
        to_32bit_binary(mag, tmp);
        out[0] = '1';
        memcpy(out + 1, tmp + 1, 31);
        out[32] = '\0';
    }
}

void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t pos = (n == INT32_MIN) ? 2147483648u : (uint32_t)(-(int64_t)n);
        to_32bit_binary(~pos, out);
    }
}

void to_twos_complement(int32_t n, char *out) {
    to_32bit_binary((uint32_t)n, out);
}
