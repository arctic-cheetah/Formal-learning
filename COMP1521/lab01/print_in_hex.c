#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_hex(uint32_t n);
char *print_hex_array(uint32_t n);

int main(void) {

    uint32_t a = 0;
    printf("Enter a positive int: ");
    scanf("%u", &a);

    printf("%u = 0x", a);
    print_hex(a);
    printf("\n");
    
    char *Hex = print_hex_array(a);
    
    printf("0x%s\n", Hex);
	
	free(Hex);
	
    return 0;
}

// print n in hexadecimal

void print_hex(uint32_t n) {

    int hex_digits = 2 * sizeof(n);
    //Hexadecimals digits are between 0, 1, 2 ... F
	int count = hex_digits - 1;

	
	while (count >= 0) {
		//Use a mask, that takes 4 bits
		uint32_t mask = 4 * count; 
		//Bitshift the number by 4 to the left.
		//From most significant digit to least significant
		uint32_t shiftedValue = n >> mask;
		//Extract the 4 bits
		uint32_t hexNum = shiftedValue & 0xF;
		//Convert into a decimal and print them out;
		uint32_t hexNumascii = "0123456789ABCDEF"[hexNum];
		//print the number out;
		putchar(hexNumascii);
		count -=1;
	} 

}



//A function that returns a string of hexadecimal digits
char *print_hex_array(uint32_t n) {
	
	//Obtain the number of digits;
	int digits = 2 * sizeof(n);
   	//loop through the bits. Starting from the most significant to the
   	//least
   	
   	char *hexArray = malloc(digits + 1);

   	int count = 0;
   	int i = digits - 1;
   	while (count < digits) {
   		//Obtain a mask
   		uint32_t mask = 4 * count;
   		//Mask off the significant digits first
   		uint32_t value = n >> mask;
   		//Extract the 4 bits
   		value = value & 0xF;
   		//Convert the bits into hexadecimal
   		char hex = "0123456789ABCDEF"[value];
   		
   		hexArray[i] = hex;
   		i -=1;
   		count +=1;
   	}
	hexArray[digits] = '\0';	
	return hexArray;

}

