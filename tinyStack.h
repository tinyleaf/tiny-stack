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

#ifndef TINYSTACK_H_
#define TINYSTACK_H_


#include <stdint.h>


/**
 * Stack structure typedef.
 */
typedef struct{

	uint32_t top; /*** Store the top index */
	uint32_t size; /*** Store the size of the stack buffer */
	uint32_t ndata; /** Number of objects stored in the stack */
	uint8_t  *buffer; /*** Points to the stack buffer */

}tinyStack_t;


#define tinyStackGetNumberObjects(stack) ((stack)->ndata) /*** Returns the number of objects present in the stack */


void tinyStackSetUp(tinyStack_t *stack,uint8_t *buffer,uint32_t size);
uint32_t tinyStackPushLength(tinyStack_t *stack);
uint8_t tinyStackPush(tinyStack_t *stack,uint8_t *data,uint16_t length);
uint16_t tinyStackPop(tinyStack_t *stack,uint8_t *data,uint16_t size);
uint16_t tinyStackPopLength(tinyStack_t *stack);

uint8_t *tinyStackTakeBuffer(tinyStack_t *stack,uint16_t length);
uint8_t *tinyStackGetTopBuffer(tinyStack_t* stack,uint16_t *length);
void tinyStackGiveBuffer(tinyStack_t* stack);




#endif /* TINYSTACK_H_ */
