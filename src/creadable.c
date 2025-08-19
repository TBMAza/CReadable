#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include "creadable.h"

static void extract_number(char* rn, char** number, size_t* len, char* negative, char* floating) {
	*number = NULL;
	*negative = 0;
	*floating = 0;
	if(len) *len = 0;
	size_t rnlen = strlen(rn);

	if(!rnlen) {
		fprintf(stderr, "[CREADABLE ERROR] No number provided. Defaulting to zero.\n");
		return;
	}

	// remove trailing spaces
	char readable_number[rnlen];
	strcpy(readable_number, rn);
	for(size_t i = rnlen-2; readable_number[i] == ' ' || readable_number[i] == '\t'; --i) {
		readable_number[i] = '\0';
	}
	rnlen = strlen(readable_number);

	// checks
	char leading_spaces = 1;
	char separator = '\0';

	char* ret = malloc(sizeof(char)*rnlen);
	if(!ret) {
		fprintf(stderr, "[CREADABLE ERROR] Internal memory error. Defaulting to zero.\n");
		return;
	}
	size_t j = 0; // cursor for ret

	for(size_t i = 0; i < rnlen; ++i) {
		switch(readable_number[i]) {
		case '-':
			if(!leading_spaces) {
				fprintf(stderr, "[CREADABLE ERROR] Incorrect usage of '-' symbol. Defaulting to zero.\n");
				free(ret);
				return;
			}
			leading_spaces = 0;
			*negative = 1;
		break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			leading_spaces = 0;
			ret[j++] = readable_number[i];
		break;
		case ' ':
		case '\t':
			if(!leading_spaces && separator == '\0') {
			    separator = readable_number[i];
			}
		// intentional fall-through
		case '_':
		case ',':
			if(readable_number[i] != ' ' && readable_number[i] != '\t') leading_spaces = 0;
			if(separator == '\0') {
			    separator = readable_number[i];
			}
			else if(separator != readable_number[i]) {
				fprintf(
					stderr,
					"[CREADABLE ERROR] Incosistent usage of separators: "
					"found '%s' while '%s' already in use. Defaulting to zero.\n",
					readable_number[i] == ' ' ? "<space>" : (readable_number[i] == '\t' ? "<tab>" : (char[]){readable_number[i], '\0'}),
					separator == ' ' ? "<space>" : (separator == '\t' ? "<tab>" : (char[]){separator, '\0'})
				);
				free(ret);
				return;
			}
		break;
		case '.':
			if(leading_spaces || *floating) {
				fprintf(stderr, "[CREADABLE ERROR] Incorrect usage of '.' symbol. Defaulting to zero.\n");
				free(ret);
				return;
			}
			*floating = 1;
			ret[j++] = '.';
		break;
		default:
			fprintf(
				stderr,
				"[CREADABLE ERROR] Invalid symbol found: '%c'. Defaulting to zero.\n",
				readable_number[i]
			);
			free(ret);
			return;
		break;
		}
	}
	ret[j] = '\0';
	if(len) *len = j;
	*number = ret;
}

char _rchar(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	char ret = 0;
	for(size_t i = 0; i < len; ++i) {
		char digit = number[i] - '0';
		if(negative) digit = -digit;

		if(ret > CHAR_MAX/10 || (ret == CHAR_MAX/10 && digit > CHAR_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows char type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < CHAR_MIN/10 || (ret == CHAR_MIN/10 && digit < CHAR_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows char type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}

	free(number);
	return ret;
}
signed char _rschar(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	signed char ret = 0;
	for(size_t i = 0; i < len; ++i) {
		signed char digit = (signed char)(number[i] - '0');
		if(negative) digit = -digit;

		if(ret > SCHAR_MAX/10 || (ret == SCHAR_MAX/10 && digit > SCHAR_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows signed char type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < SCHAR_MIN/10 || (ret == SCHAR_MIN/10 && digit < SCHAR_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows signed char type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
unsigned char _ruchar(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(negative) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign negative number to unsigned type. Defaulting to zero.\n");
		return 0;
	}
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	unsigned char ret = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned char digit = (unsigned char)(number[i] - '0');
		if(ret > UCHAR_MAX/10 || (ret == UCHAR_MAX/10 && digit > UCHAR_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows unsigned char type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
short _rshort(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	short ret = 0;
	for(size_t i = 0; i < len; ++i) {
		short digit = (short)(number[i] - '0');
		if(negative) digit = -digit;

		if(ret > SHRT_MAX/10 || (ret == SHRT_MAX/10 && digit > SHRT_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows short type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < SHRT_MIN/10 || (ret == SHRT_MIN/10 && digit < SHRT_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows short type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
unsigned short _rushort(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(negative) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign negative number to unsigned type. Defaulting to zero.\n");
		return 0;
	}
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	unsigned short ret = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned short digit = (unsigned short)(number[i] - '0');
		if(ret > USHRT_MAX/10 || (ret == USHRT_MAX/10 && digit > USHRT_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows unsigned short type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
int _rint(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	int ret = 0;
	for(size_t i = 0; i < len; ++i) {
		int digit = (int)(number[i] - '0');
		if(negative) digit = -digit;

		if(ret > INT_MAX/10 || (ret == INT_MAX/10 && digit > INT_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows int type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < INT_MIN/10 || (ret == INT_MIN/10 && digit < INT_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows int type. Defaulting to zero.\n", number);
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
unsigned int _ruint(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(negative) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign negative number to unsigned type. Defaulting to zero.\n");
		return 0;
	}
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	unsigned int ret = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned int digit = (unsigned int)(number[i] - '0');
		if(ret > UINT_MAX/10 || (ret == UINT_MAX/10 && digit > UINT_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows int type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
long _rlong(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	long ret = 0;
	for(size_t i = 0; i < len; ++i) {
		long digit = (long)(number[i] - '0');
		if(negative) digit = -digit;

		if(ret > LONG_MAX/10 || (ret == LONG_MAX/10 && digit > LONG_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows long type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < LONG_MIN/10 || (ret == LONG_MIN/10 && digit < LONG_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows long type. Defaulting to zero.\n", number);
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
long long _rlonglong(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	long long ret = 0;
	for(size_t i = 0; i < len; ++i) {
		long long digit = (long long)(number[i] - '0');
		if(negative) digit = -digit;

		if(ret > LLONG_MAX/10 || (ret == LLONG_MAX/10 && digit > LLONG_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows long long type. Defaulting to zero.\n", number);
			return 0;
		}
		if(ret < LLONG_MIN/10 || (ret == LLONG_MIN/10 && digit < LLONG_MIN%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s underflows long long type. Defaulting to zero.\n", number);
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
unsigned long _rulong(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(negative) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign negative number to unsigned type. Defaulting to zero.\n");
		return 0;
	}
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	unsigned long ret = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned long digit = (unsigned long)(number[i] - '0');
		if(ret > ULONG_MAX/10 || (ret == ULONG_MAX/10 && digit > ULONG_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows unsigned long type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
unsigned long long _rulonglong(char* readable_number) {
	char* number;
	size_t len;
	char negative;
	char floating;
	extract_number(readable_number, &number, &len, &negative, &floating);

	if(!number) return 0;
	if(negative) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign negative number to unsigned type. Defaulting to zero.\n");
		return 0;
	}
	if(floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign floating point number to integer type. Defaulting to zero.\n");
		return 0;
	}

	unsigned long long ret = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned long long digit = (unsigned long long)(number[i] - '0');
		if(ret > ULLONG_MAX/10 || (ret == ULLONG_MAX/10 && digit > ULLONG_MAX%10)) {
			fprintf(stderr, "[CREADABLE ERROR] %s overflows unsigned long long type. Defaulting to zero.\n", number);
			return 0;
		}
		ret = ret*10 + digit;
	}
	
	free(number);
	return ret;
}
float _rfloat(char* readable_number) {
	char* number;
	char negative;
	char floating;
	extract_number(readable_number, &number, NULL, &negative, &floating);

	if(!number) return 0.0;
	if(!floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign integer number to floating point type. Defaulting to zero.\n");
		return 0.0;
	}

	float ret = strtof(number, NULL);
	if(negative) ret = -ret;

	free(number);
	return ret;
}
double _rdouble(char* readable_number) {
	char* number;
	char negative;
	char floating;
	extract_number(readable_number, &number, NULL, &negative, &floating);

	if(!number) return 0.0;
	if(!floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign integer number to floating point type. Defaulting to zero.\n");
		return 0.0;
	}
	
	double ret = strtod(number, NULL);
	if(negative) ret = -ret;

	free(number);
	return ret;
}
long double _rlongdouble(char* readable_number) {
	char* number;
	char negative;
	char floating;
	extract_number(readable_number, &number, NULL, &negative, &floating);

	if(!number) return 0.0;
	if(!floating) {
		fprintf(stderr, "[CREADABLE ERROR] Cannot assign integer number to floating point type. Defaulting to zero.\n");
		return 0.0;
	}

	long double ret = strtold(number, NULL);
	if(negative) ret = -ret;

	free(number);
	return ret;
}
