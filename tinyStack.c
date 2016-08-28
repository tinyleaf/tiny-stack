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

#include "tinyStack.h"

/**
 * Set up the stack.
 * @param stack Pointer to stack structure.
 * @param buffer Pointer to stack buffer.
 * @param size Size of the stack buffer.
 */
void tinyStackSetUp(tinyStack_t *stack,uint8_t *buffer,uint32_t size){
	stack->ndata = 0; // Initialize Number of the objects stored in stack to zero.
	stack->top = 0; // Initialize TOP of the stack position to zero.
	stack->size = size; // Initialize the stack buffer size.
	stack->buffer = buffer; // Initialize the stack buffer pointer.
}

/**
 * Returns the size of the data that can be pushed to stack.
 * @param stack Pointer to stack structure.
 * @return Number of bytes that can be pushed.
 */
uint32_t tinyStackPushLength(tinyStack_t *stack){
	uint32_t free = 0;

	// Compute the total memory bytes available in the stack.
	if(stack->buffer != (void*)0)
		free = stack->size - stack->top;

	// Reduce the final length by 2 to account for storing the length.
	if(free > 2)
		free -=2;
	else
		free = 0;

	// Return the free bytes available in the stack.
	return(free);
}

/**
 * Push the data to the stack.
 * @param stack Pointer to the stack structure.
 * @param data Pointer of the data to be pushed.
 * @param length Length of the data being pushed.
 * @return 1 on success or 0 if stack is full.
 */
uint8_t tinyStackPush(tinyStack_t *stack,uint8_t *data,uint16_t length){

	uint8_t status = 0;uint32_t cntr;
	if(stack->buffer != (void*)0){
		if((stack->top + 2 + length) < stack->size){ // Is object can be added to the stack
			for(cntr=0;cntr<length;cntr++)
				stack->buffer[stack->top++] = data[cntr]; // Copy the object to the stack.
			stack->buffer[stack->top++] = length & 0x00FF; // Copy the object length LSB.
			stack->buffer[stack->top++] = (length >> 8) & 0x00FF; // Copy the object length MSB.
			stack->ndata++; // Increment the number of objects stored in the stack.
			status = 1; // Mark the status to success.
		}
	}

	// Return the stack operation status.
	return(status);
}

/**
 * Pop the data from the stack.
 * @param stack Pointer to the stack structure.
 * @param data Pointer to the buffer to store the popped data.
 * @param size Size of the buffer
 * @return Amount of bytes copied to the buffer.
 */
uint16_t tinyStackPop(tinyStack_t *stack,uint8_t *data,uint16_t size){

	uint16_t length = 0;uint16_t nread = 0;
	if(stack->buffer != (void*)0){
		if(stack->top >= 2){
			length = (stack->buffer[stack->top-1] << 8); // Copy Object length MSB.
			length |= (stack->buffer[stack->top-2] & 0x00FF); // Copy object length LSB.
			if(stack->top >= (length + 2)){
				stack->top-=2; // Remove the length data.
				// Copy and remove the object data.
				for(nread = 1; nread <= length; nread++){
					if((length - nread) < size){
						data[length - nread] = stack->buffer[--stack->top];
					}

				}
				stack->ndata--; // Decrement the number of objects.
				// Truncate the read length.
				if(nread > size)
					nread = size;
			}
		}
	}

	return(nread);
}

/**
 * Returns the length of the data stored at stack TOP.
 * @param stack Pointer to the stack structure.
 * @return Length of the data in bytes stored at the stack TOP.
 */
uint16_t tinyStackPopLength(tinyStack_t *stack){

	uint16_t length=0;
	if(stack->buffer != (void*)0){
		if(stack->top >= 2){
			length = (stack->buffer[stack->top-1] << 8); // Copy Object length MSB.
			length |= (stack->buffer[stack->top-2] & 0x00FF); // Copy object length LSB.
		}
	}

	// Return the length of the object data.
	return(length);
}

/**
 * Return the pointer to allocated data on the stack
 * @param stack Pointer to the stack structure.
 * @param length Length of the data to be allocated.
 * @return Returns the pointer on successful allocation or NULL on failure.
 * @note: Take buffer gives pointer by allocated at the TOP of stack.
 * @note: The pointer is valid until it is popped up.
 * @note: This API is provided to avoid the use of additional buffer to pass it the stack.
 */
uint8_t *tinyStackTakeBuffer(tinyStack_t *stack,uint16_t length){

	uint8_t *data = (void*)0;
	if(stack->buffer != (void*)0){ // NULL validation.
		if((stack->top + 2 + length) < stack->size){
			data = &stack->buffer[stack->top]; // Assign the pointer to the store the data.
			stack->top+=length; // Increment stack top to data length.
			stack->buffer[stack->top++] = length & 0x00FF; // Store Length LSB
			stack->buffer[stack->top++] = (length >> 8) & 0x00FF; // Store Length MSB
			stack->ndata++; // Increment the number of objects stored in the stack.
		}
	}

	// Return the pointer.
	return(data);
}

/**
 * Return the pointer to allocated data on TOP of the stack.
 * @param stack Pointer to the stack structure.
 * @param length Length of allocated data.
 * @return Pointer to TOP buffer or NULL if stack is empty.
 * @note This API do not decrement the stack, Applications should call
 * 		 @ref tinyStackGiveBuffer to decrement the stack.
 */
uint8_t *tinyStackGetTopBuffer(tinyStack_t* stack,uint16_t *length){

	uint8_t *data = (void*)0;
	*length = 0;
	if(stack->buffer != (void*)0){ // Null validation.
		if(stack->top >= 2){
			*length = (stack->buffer[stack->top-1] << 8); // Copy Length MSB
			*length |= (stack->buffer[stack->top-2] & 0x00FF);  // Copy Length LSB
			if(stack->top >= (*length + 2)) // Validate the Length.
				data = &(stack->buffer[stack->top - (*length+2)]); // Return the Pointer to data present at TOP of the stack.
		}
	}

	// Return the data pointer.
	return(data);
}

/**
 * Release (Decrement the stack) the buffer allocated on TOP of the stack.
 * @param stack Pointer to the stack structure.
 */
void tinyStackGiveBuffer(tinyStack_t* stack){
	uint16_t length=0;
	if(stack->buffer != (void*)0){
		if(stack->top >= 2){
			length = (stack->buffer[stack->top-1] << 8); // Copy length MSB
			length |= (stack->buffer[stack->top-2] & 0x00FF); // Copy length LSB
			if(stack->top >= (length + 2)){
				stack->top = stack->top-(length+2); // Remove the data present in the TOP of stack.
				stack->ndata--; // Decrement the number of objects present in the stack.
			}
		}
	}
}
