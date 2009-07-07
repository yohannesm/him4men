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
	x++;

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
     while(b1!=e1 && b2!=e2){
    	*x = *b1 * *b2; // assigning x
    	++b1; ++b2; ++x;
    }
    return x;}

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
     while(b1!=e1 && b2!=e2){
    	*x = *b1 / *b2; // assigning x
    	++b1; ++b2; ++x;
    }
    return x;}

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
 * (s << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    while (b != e) {
    	*x = *b;
    	++b; ++x;
    }
	// Stream in the least significant zeroes produced by the shift
	for (int i = 0; i < n; i++) {
		*x = 0;
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
 * (s >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
	int shift_count;
	II shifted;

	shifted = b;
	shift_count = 0;
	// First, allow the original iterator to proceed along, not copying anything
	// to the destination until we get n elements into the container
	while(b != e && shift_count < n) {
		++b;
		++shift_count;
	}

	// Then, start copying elements into x, starting at the beginning of where
	// b started.  Continue until we run out of input in e.
	// If we are already at the end, we have shifted off the end of the input,
	// so just output 0.
	if (b == e) {
		*x = 0;
		++x;
	} else {
		do {
			*x = *shifted;
			++shifted; ++x; ++b;
		} while (b != e);
	}

    return x;
}

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
         * <your documentation>
         */
        friend bool operator == (const Integer& lhs, const Integer& rhs) {
            // <your code>
            return false;}

        // -----------
        // operator !=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator != (const Integer& lhs, const Integer& rhs) {
            return !(lhs == rhs);}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const Integer& lhs, const Integer& rhs) {
            // <your code>
            return false;}

        // -----------
        // operator <=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator <= (const Integer& lhs, const Integer& rhs) {
            return !(rhs < lhs);}

        // ----------
        // operator >
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator > (const Integer& lhs, const Integer& rhs) {
            return (rhs < lhs);}

        // -----------
        // operator >=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator >= (const Integer& lhs, const Integer& rhs) {
            return !(lhs < rhs);}

        // ----------
        // operator +
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator + (Integer lhs, const Integer& rhs) {
            return lhs += rhs;}

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator - (Integer lhs, const Integer& rhs) {
            return lhs -= rhs;}

        // ----------
        // operator *
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator * (Integer lhs, const Integer& rhs) {
            return lhs *= rhs;}

        // ----------
        // operator /
        // ----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        friend Integer operator / (Integer lhs, const Integer& rhs) {
            return lhs /= rhs;}

        // ----------
        // operator %
        // ----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        friend Integer operator % (Integer lhs, const Integer& rhs) {
            return lhs %= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * <your documentation>
         */
        friend Integer operator << (Integer lhs, int rhs) {
            return lhs <<= rhs;}

        // -----------
        // operator >>
        // -----------

        /**
         * <your documentation>
         */
        friend Integer operator >> (Integer lhs, int rhs) {
            return lhs >>= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * <your documentation>
         */
        friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
            // <your code>
            return lhs << "0";
		}

    private:
        // data
        // ----
        size_t digits; // number of digits
	bool sign; // true = positive & false = negative 
        C container;

        // -----
        // valid
        // -----
	/**
         * checking the validity of the values inside the container
         */
        bool valid () const {
			using namespace std;
	  	        typename  C::const_iterator it = container.begin();
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
			typename C::iterator it;
			// Determine sign, and get absolute value
			if (value < 0) {
				value = -value;
				sign = false;
			} else {
				sign = true;
			}
			//storing the least significant digit at index 0 and then 
			//continue on storing it backward
			digits = 0;
			it = container.begin();
			while (value > 0) {
				*it = value % 10;
				value = value / 10;
				++it; ++digits;
			}
            assert(valid());
		}

        /**
         * Integer constructor for a string
         * we are also going to store the digit backward
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // we are just going to start build the object out of the string value
            // if the input is not valid, the valid() will fails and it will
            // throw the exceptions
            std::string::reverse_iterator str_rit = value.rbegin();
            typename C::iterator it = container.begin();
            while(str_rit != value.rend()){
            	++str_rit;
            	*it = std::atoi(reinterpret_cast<const char*>(*str_rit));
            	++it;
            }
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}
        // Default copy, destructor, and copy assignment.
        // are provided by the compiler
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer abs () const {
            // <your code>
            return Integer(0);}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer pow (int e) const {
            // <your code>
            return Integer(0);}};

} // My

#endif // Integer_h


