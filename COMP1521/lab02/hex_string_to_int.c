#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t hex_string_to_int(char *hex_string);
int hex_digit_to_int(int ascii_digit);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hexadecimal-number>\n", argv[0]);
        return 1;
    }

    char *hex_string = argv[1];

    uint32_t u = hex_string_to_int(hex_string);

    printf("%s hexadecimal is %u base 10\n", hex_string, u);

    return 0;
}

// print n in hexadecimal

uint32_t hex_string_to_int(char *hex_string) {
    uint32_t value = 0;
    int digit = 0;
    while (hex_string[digit] != '\0') {
    	uint32_t ascii = hex_string[digit];
    	uint32_t digit_as_int = hex_digit_to_int(ascii);
    	
    	//Bit shift to obtain the required number in decimal
    	value = value << 4;
    	value = value | digit_as_int;
		
    	digit++;
    }
    


    return value;
}

// given the ascii value of a hexadecimal digit
// return the corresponding integer

int hex_digit_to_int(int ascii_digit) {
	if ( '0' <= ascii_digit && ascii_digit <= '9') {
		return ascii_digit - '0';
	}
	else if ('A' <= ascii_digit && ascii_digit <= 'F') {
		return 10 + ascii_digit - 'A';
	}
    
    fprintf(stderr, "Bad digit '%c'\n", ascii_digit);
    exit(1);
}














