Ariel Ahdoot
Emily Ng

CS214 PA3: Read Me

DESIGN

Our enhanced malloc() and free() detects errors that are commonly made when using dynamic memory.

Our design uses a memory resource of size 10,000. To deal with fragmentation, we create an algorithm that places blocks based on their size. We reserved one part of our memory resource for small blocks, and left the rest available for larger blocks to make our implementation more space efficient. Both parts of the memory resource are of equal size. If the requested size + the size of a MemEntry is <=200, then we consider it to be a “small” request and malloc() places the block in left side in our memory resource. However if the requested size + the size of a MemEntry is >200, then we consider it to be a “large request” and it goes to the right side in our memory resource. By separating blocks by size, we mitigate fragmentation because it reduces the likelihood that we create unusable spaces.

Our malloc() takes an unsigned integer size request provided by the caller.

ERROR HANDLING

Our design handles errors such as free()ing pointers that were never allocated, free()ing pointers to dynamic memory that were not returned from malloc(), and redundant free()ing of the same pointer.

In addition, if the caller requests a size that is 0, a negative number, or a number greater than the block If a call to malloc() or free() fails because of an error, our desgin prints out an error message to notify the caller.

TESTCASES

All of our test cases are run as executables using our makefile and are also documented in hwextra-­‐testcases.txt. We wrote our test cases with chars but our design also works for ints.

EXTRA CREDIT

We created a function called memleak_check() that checks for memory leaks after main() returns and prints out a summary. Also, we created a function for calloc() .
