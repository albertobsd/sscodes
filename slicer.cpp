/*
	Compile
	gcc -o slicer slicer.cpp -lgmp
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>

/* I want to create one range slicer 
using GMP manual is https://gmplib.org/manual/Simultaneous-Integer-Init-_0026-Assign
example from 800000000000000000000000000000 to 1000000000000000000000000000000
and we want 4 billions of subrange or any other number "N" of ranges
usage:

./slicer 0x800000000000000000000000000000 0x1000000000000000000000000000000 128

*/

int main(int argc, char **argv)	{
	int i;
	mpz_t start_range,end_range,number_of_ranges,slice_value,current_range,diff;
	if(argc == 4)	{ 
		
		//It initializes several mpz_t variables to store the start and end range, the number of ranges, and other intermediate values.
		mpz_init(start_range);
		mpz_init(end_range);
		mpz_init(number_of_ranges);
		mpz_init(slice_value);
		mpz_init(current_range);
		mpz_init(diff);
		
		// It then sets the values of these variables using the command line arguments, and calculates the size of each range (slice_value) by dividing the difference between the start and end range by the number of ranges. The code then prints these values.
		mpz_set_str(start_range,argv[1],0);
		mpz_set_str(end_range,argv[2],0);
		mpz_set_str(number_of_ranges,argv[3],0);
	
		mpz_sub(diff,end_range,start_range);
		mpz_fdiv_q(slice_value,diff,number_of_ranges);
		
		gmp_printf("Range start: 0x%Zx\n",start_range);
		gmp_printf("Range end: 0x%Zx\n",end_range);
		gmp_printf("number: 0x%Zx\n",number_of_ranges);
		gmp_printf("slice value: 0x%Zx\n",slice_value);

		mpz_set (current_range,start_range);

		while(mpz_cmp (current_range,end_range) < 0	)	{//to compare two mpz_t values
			//Next, it sets the current range to the start range and enters a loop that continues until the current range is less than the end range. Inside the loop, it prints the current range, adds the slice value to it, subtracts 1, and prints the new value.
			gmp_printf("%Zx:",current_range);
			mpz_add(current_range,current_range,slice_value);
			mpz_sub_ui(current_range,current_range,1);
			gmp_printf("%Zx\n",current_range);
			mpz_add_ui(current_range,current_range,1);
		}
		//This effectively divides the original range into the specified number of ranges and prints each range
	}
}
