#include <stdio.h>
#include <string.h>

int main () {
   char dest[20];
   char src[20];
   int len;

   strcpy(src, "Tutorials Point");
   len = strxfrm(dest, src, 15);

   printf("Length of string |%s| is: |%d|", dest, len);
   
   return(0);
}
