#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

void sha256(char *dest, char *src) {
    // zero out the sha256 context
    struct sha256_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));

    // zero out the binary version of the hash digest
    unsigned char dig_bin[DIG_BIN_LEN];
    memset(dig_bin, 0, DIG_BIN_LEN);

    // zero out the string version of the hash digest
    memset(dest, 0, DIG_STR_LEN);

    // compute the binary hash digest
    __sha256_init_ctx(&ctx);
    __sha256_process_bytes(src, strlen(src), &ctx);
    __sha256_finish_ctx(&ctx, dig_bin);

    // convert it into a string of hexadecimal digits
    for (int i = 0; i < DIG_BIN_LEN; i++) {
        snprintf(dest, 3, "%02x", dig_bin[i]);
        dest += 2;
    }
}

char *leet(char *str)
{
	char *leeted_str;
	leeted_str = (char *) malloc(strlen(str));
	for (int i = 0; i < strlen(str); i++) {
		switch (str[i]) {
			case 'o':
				str[i] = '0';
				break;
			case 'e':
				str[i] = '3';
				break;
			case 'i':
				str[i] = '!';
				break;
			case 'a':
				str[i] = '@';
				break;
			case 'h':
				str[i] = '#';
				break;
			case 's':
				str[i] = '$';
				break;
			case 't':
				str[i] = '+';
				break;
		}
	}
	strcpy(leeted_str, str);
	return leeted_str;
}

int main(int argc, char **argv)
{
	printf("Leeted string: %s\n", leet(argv[1]));
	return 0;
}
