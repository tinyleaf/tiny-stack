/**
 *  Tiny Stack - Stack implementation in C for storing objects.
 *  Copyright (C) 2016  NETHAJI S
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include "tinyStack.h"


tinyStack_t test_stack; // Test stack object.
uint8_t stack_buffer[4096]; // Stack buffer.

/**
 * Test and illustrative main application for using stack.
 * @return ZERO always.
 */
int main(void){

	int cntr;

	printf("****** Tiny Stack ************\r\n");

	printf ("INFO: Initializing Stack \r\n");
	// Initializing Stack.
	tinyStackSetUp(&test_stack,stack_buffer,sizeof(stack_buffer));

	printf ("INFO: Pushing INT Data to the Stack \r\n");
	// Put data to the stack.
	for(cntr = 0x10452125; cntr <= (0x10452125+512); cntr++){
		// Push INT data to the stack.
		if(tinyStackPush(&test_stack,(uint8_t*)&cntr,sizeof(int)) == 0){
			printf(" FAIL: Pushing INT data %d \r\n",cntr);
		}
	}

	// Validate the number of objects stored in the stack.
	if(tinyStackGetNumberObjects(&test_stack) != 513){
		printf(" FAIL: Incorrect INT data %d \r\n",tinyStackGetNumberObjects(&test_stack));
	}

	printf ("INFO: Popping INT Data from the Stack \r\n");
	// Get INT data from the stack.
	for(cntr = 0x10452125; cntr <=  (0x10452125+512); cntr++){
		int data;
		// Pop data from the stack.
		if(tinyStackPop(&test_stack,(uint8_t*)&data,sizeof(int)) == 0){
			printf(" FAIL: Pop INT data %d \r\n",cntr);
		}

		// Check the Data.
		if(data != ( (0x10452125+512) - (cntr-0x10452125))){
			printf (" FAIL: Invalid Data; Expected %d got %d \r\n", ((0x10452125+512) - cntr),data);
		}
	}

	// Validate the Stack TOP location. It should be zero.
	if(test_stack.top != 0){
		printf(" FAIL: Invalid stack operation \r\n");
	}

	// Validate the number of objects stored in the stack.
	if(tinyStackGetNumberObjects(&test_stack) != 0){
		printf(" FAIL: Incorrect INT data %d \r\n",tinyStackGetNumberObjects(&test_stack));
	}

	// Clear the Stack Buffer for Testing Allocation and Deallocation.
	memset(stack_buffer,0,sizeof(stack_buffer));

	printf ("INFO: Pushing INT Data to the Stack [Take Buffer] \r\n");
	// Put INT data to the stack using Take buffer.
	for(cntr = 0x10452125; cntr <= (0x10452125+512); cntr++){
		uint8_t *data;
		// Get the buffer of size of INT.
		data = tinyStackTakeBuffer(&test_stack,sizeof(int));
		if(data != NULL){
			// Copy the data to the buffer.
			memcpy(data,&cntr,sizeof(int));
		}else{
			printf(" FAIL: Pushing INT data %d [Take Buffer] \r\n",cntr);
		}
	}

	// Validate the number of objects stored in the stack.
	if(tinyStackGetNumberObjects(&test_stack) != 513){
		printf(" FAIL: Incorrect INT data %d \r\n",tinyStackGetNumberObjects(&test_stack));
	}

	printf ("INFO: Popping INT Data from the Stack [Give Buffer]\r\n");
	// Get INT data from the stack.
	for(cntr = 0x10452125; cntr <=  (0x10452125+512); cntr++){
		uint8_t *data_ptr;uint16_t length;
		int data;
		// Get the buffer present at the top of the stack.
		data_ptr = tinyStackGetTopBuffer(&test_stack,&length);
		if(data_ptr != NULL){
			// Verify the size of the buffer.
			if(length != sizeof(int)){
				printf(" FAIL: Data Length Fail [Get Buffer]\r\n");
			}
			// Copy the data.
			memcpy(&data,data_ptr,sizeof(int));

			// Give the buffer to stack.
			tinyStackGiveBuffer(&test_stack);

		}else{
			printf(" FAIL: Pop INT data %d [Give Buffer]\r\n",cntr);
		}


		// Check the Data.
		if(data != ( (0x10452125+512) - (cntr-0x10452125))){
			printf (" FAIL: Invalid Data [Get Buffer]; Expected %d got %d \r\n", ((0x10452125+512) - cntr),data);
		}
	}

	// Check the top of the stack, It should be zero.
	if(test_stack.top != 0){
		printf(" FAIL: Invalid stack operation [Give and Take Buffer]\r\n");
	}

	// Validate the number of objects stored in the stack.
	if(tinyStackGetNumberObjects(&test_stack) != 0){
		printf(" FAIL: Incorrect INT data %d \r\n",tinyStackGetNumberObjects(&test_stack));
	}

	printf("****** End of Application ************\r\n");
	return(0);
}
