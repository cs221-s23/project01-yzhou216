#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

/* define the length of passwords dictionary */
#define DICT_LEN (sizeof(passwords) / sizeof(passwords[0]))

void sha256(char *dest, char *src)
{
	/* zero out the sha256 context */
	struct sha256_ctx ctx;
	memset(&ctx, 0, sizeof(ctx));

	/* zero out the binary version of the hash digest */
	unsigned char dig_bin[DIG_BIN_LEN];
	memset(dig_bin, 0, DIG_BIN_LEN);

	/* zero out the string version of the hash digest */
	memset(dest, 0, DIG_STR_LEN);

	/* compute the binary hash digest */
	__sha256_init_ctx(&ctx);
	__sha256_process_bytes(src, strlen(src), &ctx);
	__sha256_finish_ctx(&ctx, dig_bin);

	/* convert it into a string of hexadecimal digits */
	for (int i = 0; i < DIG_BIN_LEN; i++) {
		snprintf(dest, 3, "%02x", dig_bin[i]);
		dest += 2;
	}
}

char *dig(char *str)
{
	char *dig_str  = (char *) malloc((DIG_STR_LEN + 1) * sizeof(char));
	sha256(dig_str, str);
	return dig_str;
}

char *leet(char *str)
{
	char *res = (char *) malloc((strlen(str) + 1) * sizeof(char));
	for (int i = 0; i < strlen(str); i++) {
		switch (str[i]) {
			case 'o':
				res[i] = '0';
				break;
			case 'e':
				res[i] = '3';
				break;
			case 'i':
				res[i] = '!';
				break;
			case 'a':
				res[i] = '@';
				break;
			case 'h':
				res[i] = '#';
				break;
			case 's':
				res[i] = '$';
				break;
			case 't':
				res[i] = '+';
				break;
			default:
				res[i] = str[i];
		}
	}
	return res;
}

char *add_one(char *str)
{
	/*
	 * Allocate memory for the result to be one byte more than the source
	 * string.
	 */
	char *res = (char *) malloc((strlen(str) + 2) * sizeof(char));
	strcpy(res, str);
	strcat(res, "1");
	return res;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("%s\n", "invalid arguments");
		exit(0);
	}

	char dig_str[DIG_STR_LEN];
	strcpy(dig_str, argv[1]);

	for (int i = 0; i < DICT_LEN; i++) {
		if (!strcmp(dig_str, dig(passwords[i]))) {
			printf("%s\n", passwords[i]);
			return 0;
		}

		if (!strcmp(dig_str, dig(add_one(passwords[i])))) {
			printf("%s\n", add_one(passwords[i]));
			return 0;
		}

		if (!strcmp(dig_str, dig(leet(passwords[i])))) {
			printf("%s\n", leet(passwords[i]));
			return 0;
		}
	}

	printf("%s\n", "not found");
	return 0;
}
