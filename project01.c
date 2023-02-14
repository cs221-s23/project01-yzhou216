#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

#define DICT_LEN sizeof(passwords) / sizeof(passwords[0])

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
	char *dig_str;
	dig_str = (char *) malloc(DIG_STR_LEN);
	sha256(dig_str, str);
	return dig_str;
}

char *leet(char *str)
{
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
	return str;
}

char *add_one(char *str)
{
	strcat(str, "1");
	//printf("%s\n", str); //debug
	return str;
}

int main(int argc, char **argv)
{
	//printf("%s\n", dig("sunshone"));
	//printf("%s\n", add_one(argv[1]));
	//return 0;
	/* password array for debug purpose */

	//char *password_d[] = {"sunshone", "password", "123456789", "niners"};
	
	/* chage DICT_LEN to 1000 at the top of the file when running using the
	   provided password dict */

	char dig_str[DIG_STR_LEN];
	strcpy(dig_str, argv[1]);
	for (int i = 0; i < DICT_LEN; i++) {
		if (!strcmp(dig_str, dig(passwords[i]))) {
			printf("%s\n", passwords[i]);
			exit(0);
		}

		/*
		if(!strcmp(dig_str, dig(add_one(passwords[i])))) {
			printf("%s\n", add_one(passwords[i]));
			//printf("%s\n", "Helloworld");
			exit(0);
		}
		if (!strcmp(dig_str, dig(leet(passwords[i])))) {
			//printf("%s\n", leet(passwords[i]));
			printf("%s\n", "Helloworld0");
			exit(0);
		}
		*/
	}

	printf("%s\n", "not found");
	return 0;
}
