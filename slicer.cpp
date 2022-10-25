/*
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
 

*/

int main(int argc, char **argv)	{
	int i;
	mpz_t start_range,end_range,number_of_ranges,slice_value,current_range,diff;
	if(argc == 4)	{ 
		
		mpz_init(start_range);
		mpz_init(end_range);
		mpz_init(number_of_ranges);
		mpz_init(slice_value);
		mpz_init(current_range);
		mpz_init(diff);
		
		mpz_set_str(start_range,argv[1],0);
		mpz_set_str(end_range,argv[2],0);
		mpz_set_str(number_of_ranges,argv[3],0);
	
		mpz_sub(diff,end_range,start_range);
	
		mpz_fdiv_q(slice_value,diff,number_of_ranges);
		
		gmp_printf("Range start: %Zx\n",start_range);
		gmp_printf("Range end: %Zx\n",end_range);
		gmp_printf("number: %Zx\n",number_of_ranges);
		gmp_printf("slice value: %Zx\n",slice_value);

		mpz_set (current_range,start_range);

		while(mpz_cmp (current_range,end_range) <= 0	)	{	//to compare two mpz_t values
			gmp_printf("%Zx:",current_range);
			mpz_add(current_range,current_range,slice_value);
			gmp_printf("%Zx\n",current_range);
		}
	}
	

}
