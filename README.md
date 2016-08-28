# tiny-stack
Stack implementation in C for storing objects

# Introduction

Tiny stack is the C code for storing and retreiving objects by **first in last 
out** oder. The stack stores varying objects size. Tiny stack stores both 
object data and length. The objects are copied to the stack byte by byte.

Tiny stack provides two API's

1. API to Push and Pop object by passing pointer of the data object
2. API to Push and Pop object by getting pointer to the data object.

# Example

## Initialize Stack.

```
	tinyStack_t test_stack; // Test stack object.
	uint8_t stack_buffer[4096]; // Stack buffer. 
	
	// Initialize the Stack.
	tinyStackSetUp(&test_stack,stack_buffer,sizeof(stack_buffer));
```

## Pushing Object to Stack.


```
	/* METHOD 1: By passing data pointer */

	int data = 234324;
	tinyStackPush(&test_stack,(uint8_t*)&data,sizeof(int));
```


```
	/* METHOD 2: By getting data pointer */

	uint8_t *data_ptr;int data;
	// Get the buffer of size of INT.
	data_ptr = tinyStackTakeBuffer(&test_stack,sizeof(int));
	// Copy the data to the buffer.
	data = 234324;
	memcpy(data_ptr,&data,sizeof(int));

```

## Retreiving object from Stack.


```
	/* METHOD 1: By passing data pointer */
	
	int data;
	tinyStackPop(&test_stack,(uint8_t*)&data,sizeof(int));

```


```
	/* METHOD 2: By getting data pointer */

	uint8_t *data_ptr;uint16_t length;
	int data;
	// Get the buffer present at the top of the stack.
	data_ptr = tinyStackGetTopBuffer(&test_stack,&length);
	// Copy the data.
	memcpy(&data,data_ptr,sizeof(int));
	// Give the buffer to stack.
	tinyStackGiveBuffer(&test_stack);

```
