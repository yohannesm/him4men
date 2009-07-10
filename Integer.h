#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <iterator>  // iterator_traits
#include <cstdlib> //atoi
// ----------
// namespaces
// ----------

namespace My {


template <typename II>
void print_digits(II b, II &e)
{
	while (b != e) {
		std::cout << *b;
		++b;
	}
}


#if 0
/**
 *
 */
template <typename II1, typename II2>
bool less_than_digits(II1 b1, II1 e1, II2 b2, II2 e2)
{
	unsigned int s1_len, s2_len;

	s1_len = distance(b1, e1);
	s2_len = distance(b2, e2);
	if (s1_len < s2_len) return true;

	while (b1 != e1) {
		if (*b1 == *b2) continue;
		is_less = (*b1 < *b2) ? true : false;
		++b1; ++b2;
	}
}




template <typename II1, typename II2>
bool equal_digits(II1 b1, II1 e1, II2 b2, II2 e2)
{
	unsigned int s1_len, s2_len;

	s1_len = distance(b1, e1);
	s2_len = distance(b2, e2);
	if (s1_len != s2_len) return false;
	while (b1 != e1) {
		if (*b1 != *b2) return false;
		++b1; ++b2;
	}
	return (b2 == e2);
}
#endif

// -----------------
// shift_left_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * @note Assumes the digits are least significant first.
 * (s << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
	// Stream in the least significant zeroes produced by the shift
	for (int i = 0; i < n; i++) {
		*x = 0;
		++x;
	}

    while (b != e) {
    	*x = *b;
    	++x; ++b;
    }

    return x;
}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * @note Assumes the digits are least significant first.
 * (s >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
	// First, allow the original iterator to proceed along, not copying anything
	// to the destination until we get n elements into the container
	if (std::distance(b, e) <= n) {
		*x = 0;
		++x;
		return x;
	}

	std::advance(b, n);
	// Then, start copying elements into x, starting at the beginning of where
	// b started.  Continue until we run out of input in e.
	// If we are already at the end, we have shifted off the end of the input,
	// so just output 0.
	while (b != e) {
		*x = *b;
		++x; ++b;
	}

    return x;
}

// -----------
// plus_digits
// -----------

// Given two sets of iterators, add the next right-most column with the carry,
// put the result in the output iterator, and return the carry.
// @param Iterator to beginning (left-most digit) of input 1
// @param Iterator to one past the end (current right-most digit) of input 1
// @param Iterator to beginning (left-most digit) of input 2
// @param Iterator to one past the end (current right-most digit) of input 2
// @param Iterator to the output
// @post x is moved one digit to the right.
// @return The new carry value for this column.
template <typename II1, typename II2, typename OI>
typename std::iterator_traits<OI>::value_type 
add_next_column (II1 &b1, II1 &e1, II2 &b2, II2 &e2, OI &x, 
				 typename std::iterator_traits<OI>::value_type carry)
{
	typename std::iterator_traits<OI>::value_type result = carry;
	
	result = carry;
	// If there is more of the first input, add it
	if (b1 != e1) {
		result += *b1;
		b1++;
	}

	// If there is more of the second input, add it
	if (b2 != e2) {
		result += *b2;
		b2++;
	}

	// Compute the new carry
	carry = 0;
	while (result >= 10) {
		result -= 10;
		carry += 1;
	}

	// Write the result
	*x = result;
	++x;

	return carry;
}


/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * @note assumes the beginning of the sequence is the least significant digit,
 * and that the end of the sequence is one beyond the most sigificant digit.
 * @note The parameters represented by b1/e1 and b2/e2 are assumed to be 
 * non-negative integers.
 * (s1 + s2) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits(II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	typename std::iterator_traits<OI>::value_type carry = 0;

    while((b1 != e1) || (b2 != e2) || (carry != 0)) {
	 	// add the next column of digits; include carry
		carry = add_next_column(b1, e1, b2, e2, x, carry);
    }

	return x;
	
}


// ------------
// minus_digits
// ------------
template <typename II1, typename II2, typename OI>
typename std::iterator_traits<OI>::value_type 
subtract_next_column (II1 &b1, II1 &e1, II2 &b2, II2 &e2, OI &x, 
				 typename std::iterator_traits<OI>::value_type borrow_in)
{
	typename std::iterator_traits<OI>::value_type minuend, subtrahend;
	typename std::iterator_traits<OI>::value_type borrow_out = 0;

	// Start with the minuend's next digit
	assert(b1 != e1);
	minuend = *b1;
	++b1;
	
	// Subtrahend is the sum of the borrow and the next digit of sequence 2,
	// if any
	subtrahend = borrow_in;
	if (b2 != e2) {
		subtrahend += *b2;
		b2++;
	}

	// Calculate any needed borrow
	borrow_out = 0;
	while (minuend < subtrahend) {
		++borrow_out;
		minuend += 10;
	}

	assert((minuend - subtrahend) < 10);
	assert((minuend - subtrahend) >= 0);
	*x = (minuend - subtrahend);
	++x;
	
	return borrow_out;
}



/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * @note The parameters represented by b1/e1 and b2/e2 are assumed to be 
 * non-negative integers.
 * @note Additionally, it is assumed that integer represented by the sequences
 * s1 and s2 are provided such that s1 >= s2.
 * (s1 - s2) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	typename std::iterator_traits<OI>::value_type borrow = 0;

	while (b1 != e1) {
		borrow = subtract_next_column(b1, e1, b2, e2, x, borrow);
	}

	assert(b2 == e2);
	assert(borrow == 0);

    return x;
}

// -----------------
// multiplies_digits
// -----------------

template <typename II, typename T, typename OI>
OI multiply_digit(II b, II e, T digit, OI x)
{
	T carry = 0;
	T mul_result = 0;

	while (b != e) {
		mul_result = ((*b) * digit) + carry;
		*x		= mul_result % 10;
		carry	= mul_result / 10;
		++b; ++x;
	}

	// Handle final carry out
	if (carry) {
		*x = carry;
		++x;
	}
	
	return x;
}

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * (s1 * s2) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	typedef std::vector<typename std::iterator_traits<OI>::value_type> m_vector;
	m_vector sum;
	m_vector shifted;
	m_vector mul;
	typename m_vector::iterator sum_end;
	typename m_vector::iterator shifted_end;
	typename m_vector::iterator mul_end;

	unsigned int shift = 0;
	unsigned int s1_size = std::distance(b1, e1);
	unsigned int s2_size = std::distance(b2, e2);

	/* Reserve enough space in mul for s1 * 9 */
	mul.resize(s1_size + 2, 0);
	/* We shift by the number of digits in s2, plus the largest value in s1 */
	shifted.resize(s2_size + s1_size + 2, 0);
	/* The sum could be the size of the largest shifted number, plus a carry */
	sum.resize(s2_size + s1_size + 2 + 1, 0);
	sum_end = sum.begin();
	
	while (b2 != e2) {
		mul_end = multiply_digit(b1, e1, *b2, mul.begin());
		shifted_end = shift_left_digits(mul.begin(), mul_end,
										shift, shifted.begin());
		sum_end = plus_digits(sum.begin(), sum_end, shifted.begin(),
							  shifted_end, sum.begin());
		++shift; ++b2;
	}

	for(typename m_vector::iterator it = sum.begin(); it != sum_end; ++it) {
			*x = *it;
			++x;
	}

    return x;
}

#if 0
// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * (s1 / s2) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	II2 numerator_end = b1;
	II2 last_end = b1;
	while (b1 != e1) {
		numerator_end++;
		while (less_than_digits(b2, e2, b1, numerator_end)) {
			++numerator_end;
			++b1;
		}
	}
}
#endif


// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    public:
        // -----------
        // operator ==
        // -----------

        /**
         * Checking whether 2 integer object: lhs and rhs is equal to each other
         * O(N) if the Integer objects are equal. 
         */
        friend bool operator == (const Integer& lhs, const Integer& rhs) {
            //how do we check whether the object is just calling itself?
            bool result = false;
            //result = &lhs == &rhs; maybe by checking the address?
            result = lhs.sign == rhs.sign;
            result = lhs.container.size() == rhs.container.size();
            if(!result) return result;
            //check each element of the container
            result = lhs.container == rhs.container;
            return result;}

        // -----------
        // operator !=
        // -----------

        /**
         * Checking whether 2 integer object: lhs and rhs is not equal to each other
         */
        friend bool operator != (const Integer& lhs, const Integer& rhs) {
            return !(lhs == rhs);}

        // ----------
        // operator <
        // ----------

        /**
         * Checking whether the lhs object is less than the rhs object
         */
        friend bool operator < (const Integer& lhs, const Integer& rhs) {
            if(lhs.container.size()<rhs.container.size()) return true;
            else if(lhs == rhs) return false; 
            else if(lhs.container.size()==rhs.container.size()) {
            	//must check the least significant bit and if that's equal then
            	// we move on till we can find something that is less or more than each other
            	return true;
            	}
            else{
           	 return false;
            	}
            }

        // -----------
        // operator <=
        // -----------

        /**
         * Checking whether the lhs object is less than or equal to the rhs object
         */
        friend bool operator <= (const Integer& lhs, const Integer& rhs) {
            return !(rhs < lhs);}

        // ----------
        // operator >
        // ----------

        /**
         * Checking whether the lhs object has bigger Integer value than the rhs object
         */
        friend bool operator > (const Integer& lhs, const Integer& rhs) {
            return (rhs < lhs);}

        // -----------
        // operator >=
        // -----------

        /**
         * Checking whether the lhs object has bigger or equal Integer value than the rhs object
         */
        friend bool operator >= (const Integer& lhs, const Integer& rhs) {
            return !(lhs < rhs);}

        // ----------
        // operator +
        // ----------

        /**
         * adding 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator + (Integer lhs, const Integer& rhs) {
            return lhs += rhs;}

        // ----------
        // operator -
        // ----------

        /**
         * subtracting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator - (Integer lhs, const Integer& rhs) {
            return lhs -= rhs;}

        // ----------
        // operator *
        // ----------

        /**
         * multiplying 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator * (Integer lhs, const Integer& rhs) {
            return lhs *= rhs;}

        // ----------
        // operator /
        // ----------

        /**
         * dividing 2 integer object an outputting a new Integer object for the result
         * rhs can't be equal to zero
         * @throws invalid_argument if (rhs == 0)
         */
        friend Integer operator / (Integer lhs, const Integer& rhs) {
            if((rhs.container.size == 1) && (rhs.container[0] == 0))
            	throw std::invalid_argument("Integer::operator /");
            return lhs /= rhs;
            }

        // ----------
        // operator %
        // ----------

        /**
         * modding 2 integer object an outputting a new Integer object for the result
         * @throws invalid_argument if (rhs <= 0)
         */
        friend Integer operator % (Integer lhs, const Integer& rhs) {
            return lhs %= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * left shifting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator << (Integer lhs, int rhs) {
            return lhs <<= rhs;}

        // -----------
        // operator >>
        // -----------

        /**
         * right shifting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator >> (Integer lhs, int rhs) {
            return lhs >>= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * Outputting the Integer object in order to the console/standard output
         */
        friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
            typename C::const_iterator rit;
            rit = rhs.container.end();
            while(rit != rhs.container.begin()){
            --rit;
            lhs << *rit;
            }
            return lhs;
		}

    private:
        // data
        // ----
        // I don't think we need digits, we can just do container.size()
        //size_t digits; // number of digits
		bool sign; // true = positive & false = negative 
		C container;

        // -----
        // valid
        // -----
		/**
         * checking the validity of the values inside the container
         */
        bool valid () const {
	  	    typename C::const_iterator it = container.begin();
			// All numbers are 0-9
			// Leading numbers non-zero
			while (it != container.end()) {
				if (*it < 0 || *it > 9) return false;
				++it;
			}
            	return true;
		}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Integer constructor for int value
         * we are going to store the digit backward inside the vector container
         * @param the int value that will be converted to an Integer object
         * 
         */
        Integer (int value) {
			// Determine sign, and get absolute value
			if (value < 0) {
				value = -value;
				sign = false;
			} else {
				sign = true;
			}
			//storing the least significant digit at index 0 and then 
			//continue on storing it backward
			while (value > 0) {
				container.push_back(value % 10);
				value = value / 10;
			}
            assert(valid());
		}

        /**
         * Integer constructor for a string
         * we are also going to store the digit backward
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // we are just going to start build the object out of the string
			// value if the input is not valid, the valid() will fails and it
			// will throw the exceptions
	    	using namespace std;
			unsigned int len = value.length();
			unsigned int count = 0;
	    	// if it's a negative number
	    	if(value.at(0)=='-'){
	    		sign = false;
	    		len -= 1;
	    		}
	    	else{ sign = true;}
			
			container.resize(len, 0);
            std::string::const_iterator str_rit = value.end();
            typename C::iterator it = container.begin();
			
            while(count < len && it != container.end()) {
            	--str_rit;
            	//*it = std::atoi(reinterpret_cast<const char*>(*str_rit));
            	*it = static_cast<T>((*str_rit) - '0');
            	++it; ++count;
            }
            if (!valid())
                throw std::invalid_argument("Integer::Integer(const std::string& value)");
               }
        // Default copy, destructor, and copy assignment.
        // are provided by the compiler
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * Unary minus operator for the Integer object, returning a new Integer
		 * object as a result
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * pre-increment operator for Integer object
         * the returning result will be the object itself + 1
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * post-increment operator for Integer object
         * the returning result will be the old value of the Integer object
         * but after this operation is done the object itself will have +1 to its value
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * pre-decrement operator for Integer object
         * the returning result will be the object itself - 1
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * post-decrement operator for Integer object
         * the returning result will be the old value of the Integer object
         * but after this operation is done the object itself will have -1 to its value
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * += operator for Integer object, 
         * the operation will return the modified object + value of rhs Integer
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * -= operator for Integer object, 
         * the operation will return the modified object - value of rhs Integer
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * *= operator for Integer object, 
         * the operation will return the modified object * value of rhs Integer
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * /= operator for Integer object, 
         * the operation will return the modified object / value of rhs Integer
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
          //  if((rhs.container.size == 1) && (rhs.container[0] == 0))
            //	throw std::invalid_argument("Integer::operator/=");
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * %= operator for Integer object, 
         * the operation will return the modified object % value of rhs Integer
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <<= operator for Integer object, 
         * the operation will return the modified object << n
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <<= operator for Integer object, 
         * the operation will return the modified object >> n
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * return the absolute value of an Integer object if it's negative
         * return a copy of the Integer object if it's positive
         */
        Integer abs () const {
            //need to return the absolute value if it's negative by sending
            // -this to copy constructor?
            //if(this->sign) return Integer(this);
            //else
            return Integer(0);}

        // ---
        // pow
        // ---

        /**
         * power
         * returns a new Integer object raised to the 'e' power 
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer pow (int e) const {
            // <your code>
            return Integer(0);}};

} // My

#endif // Integer_h


