#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void oct_to_bin(const char*, char*);
void oct_to_hex(const char*, char*);
void hex_to_bin(const char*, char*);

void to_sign_magnitude(int32_t, char*);
void to_ones_complement(int32_t, char*);
void to_twos_complement(int32_t, char*);

static int is_blank_or_comment(const char *s) {
    while (*s == ' ' || *s == '\t' || *s == '\r') ++s;
    return (*s == '\0' || *s == '\n' || *s == '#');
}

int main(int argc, char **argv) {
    const char *path = (argc >= 2) ? argv[1] : "a2_tests.txt";
    FILE *f = fopen(path, "r");
    if (!f) { fprintf(stderr, "could not open %s\n", path); return 1; }

    char line[512];
    int t = 0, pass = 0;

    while (fgets(line, sizeof(line), f)) {
        if (is_blank_or_comment(line)) continue;

        char func[64], in[128], expect[256];
        func[0]=in[0]=expect[0]='\0';

        if (sscanf(line, "%63s %127s %255s", func, in, expect) != 3) continue;

        char got[512]; got[0]='\0';

        if (strcmp(func, "oct_to_bin") == 0)       oct_to_bin(in, got);
        else if (strcmp(func, "oct_to_hex") == 0)  oct_to_hex(in, got);
        else if (strcmp(func, "hex_to_bin") == 0)  hex_to_bin(in, got);
        else if (strcmp(func, "to_sign_magnitude") == 0) {
            to_sign_magnitude((int32_t)strtol(in, NULL, 10), got);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            to_ones_complement((int32_t)strtol(in, NULL, 10), got);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            to_twos_complement((int32_t)strtol(in, NULL, 10), got);
        } else continue;

        ++t;
        int ok = (strcmp(got, expect) == 0);
        if (ok) ++pass;

        
        printf("Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
               t, func, in, expect, got, ok ? "PASS" : "FAIL");
    }

    printf("Summary: %d/%d tests passed\n", pass, t);
    fclose(f);
    return (pass == t) ? 0 : 2;
}