# tiny-stack
Stack implementation in C for storing objects

# Introduction

Tiny stack is the C code for storing and retreiving objects by **first in last 
out** oder. The stack stores varying objects size. Tiny stack stores both 
object data and length. The objects are copied to the stack byte by byte.

Tiny stack provides two API's

1. API to Push and Pop object by passing pointer to data object
2. API to Push and Pop object by getting pointer to store the data on stack.

# Example

1. Initialize Stack.

```
	tinyStack_t test_stack; // Test stack object.
	uint8_t stack_buffer[4096]; // Stack buffer. 
	
	// Initialize the Stack.
	tinyStackSetUp(&test_stack,stack_buffer,sizeof(stack_buffer));
```

2. Pushing Object to Stack.

  **Method 1**

```
	int data = 234324;
	tinyStackPush(&test_stack,(uint8_t*)&data,sizeof(int));
```

  **Method 2**

```
	uint8_t *data_ptr;int data;
	// Get the buffer of size of INT.
	data_ptr = tinyStackTakeBuffer(&test_stack,sizeof(int));
	// Copy the data to the buffer.
	data = 234324;
	memcpy(data_ptr,&data,sizeof(int));

```

3. Retreiving object from Stack.

  **Method 1**

```
	int data;
	tinyStackPop(&test_stack,(uint8_t*)&data,sizeof(int));

```

  **Method 2**

```
	uint8_t *data_ptr;uint16_t length;
	int data;
	// Get the buffer present at the top of the stack.
	data_ptr = tinyStackGetTopBuffer(&test_stack,&length);
	// Copy the data.
	memcpy(&data,data_ptr,sizeof(int));
	// Give the buffer to stack.
	tinyStackGiveBuffer(&test_stack);

```
