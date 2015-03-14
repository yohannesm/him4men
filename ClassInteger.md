#Arbitrary precision Integer for calculating big prime number
# Integer #

We are implementing a generic integer class to be able to calculate a big integer number and we will not be limited with just a size of 32 bit.


# Details #

The arbitrary precision integer uses a generic container, but we prefer the container to be either a vector or a deque.
The data stored inside the vector will be a binary value, so the generic type that the user use must be something that supports that kind of thing.e.g. (int,char,short,long). We can't use the format of double or float as the internal container.

for the constructor if you want to initialize a very big number you have to use the String constructor because the compiler need to make a temporary copy for constructing something with an int and if you put something that is bigger than 2^31-1 it will fails.

Most of the operator is overloaded for this class so you can perform all of the operation that you can do with an int with this Integer class.

This class is useful for calculating a big number like the Mersenne prime.