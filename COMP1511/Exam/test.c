  #include <stdio.h>   
  void work(int num, int nums[10], int *pointer);   
  int main(void) {
      int my_number;
      int my_numbers[5];
      int *num_pointer;
      my_number = 10;
      my_numbers[3] = 11;
      num_pointer = &my_number;
     work(my_number, my_numbers, num_pointer);
      printf("%d %d %d", my_number, my_numbers[3], *num_pointer);
  }
  
  void work(int num, int nums[10], int *pointer) {
      num = 3;
      nums[3] = 2;
      *pointer = 1;
      pointer = nums;
      //*pointer = 4;
  }

[[[[[[)]]]]]]


















