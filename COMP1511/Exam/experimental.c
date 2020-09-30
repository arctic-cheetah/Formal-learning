#include<stdio.h>
 
// For demonstration purpose I used extra variable 'len'
// but you can replace this variable with 1000 
const int len = 1000;
 
void findSum(char str1[], char str2[])
{
 
 
    int carry = 0, i;
 
    // Adding 1 to len of sum array[], to
    // handle the last carry
 
    int sum[len+1];
 
    sum[0] = 0;
 
    for (i=len-1; i >= 0; --i)
    {
 
        sum[i+1] = (str1[i]-'0')+(str2[i]-'0') + carry;
 
        // Calculate carry for next step
        carry = sum[i+1] / 10;
 
        sum[i+1] %= 10;
    }
 
    // If carry still there, Add it to sum[] array
    // and initialize i according to it
	if (carry)
        sum[0] = carry, i = 0;
    else
        i = 1;
 
 
 
	for(; i <= len; ++i)
		printf("%d",sum[i]);
 
   return;
}
 
// Driver code
int main()
{
    char str1[] = "93234";
    char str2[] = "28745";
 
    findSum(str1,str2);
 
    return 0;
}
