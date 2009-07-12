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
void print_digits(II b, II e)
{
	while (b != e) {
		std::cout << *b;
		++b;
	}
}


/**
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the MOST significant byte.
 * @FIXME: No tests
 */
template <typename II1, typename II2>
bool less_than_digits(II1 b1, II1 e1, II2 b2, II2 e2)
{
	unsigned int s1_len, s2_len;

	s1_len = distance(b1, e1);
	s2_len = distance(b2, e2);
	if (s1_len < s2_len) return true;
	if (s1_len > s2_len) return false;

	while (e1 != b1) {
		--e1; --e2;
		if (*e1 > *e2) return false;
		if (*e1 < *e2) return true;
	}

	return true;
}


/**
 * @note This function is AGNOSTIC to digit ordering; either LEAST or MOST may
 * be first.
 * @FIXME: No tests
 */
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

	assert(b2 == e2);
	return true;
}

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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
 * (s >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
	if (n < 0) {
		throw std::invalid_argument("Integer::operator <<=: n < 0");
	}

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

/** Given two sets of iterators, add the next right-most column with the carry,
 * put the result in the output iterator, and return the carry.
 * @param Iterator to beginning (left-most digit) of input 1
 * @param Iterator to one past the end (current right-most digit) of input 1
 * @param Iterator to beginning (left-most digit) of input 2
 * @param Iterator to one past the end (current right-most digit) of input 2
 * @param Iterator to the output
 * @post x is moved one digit to the right.
 * @return The new carry value for this column.
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
 */
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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
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
				 	  typename std::iterator_traits<OI>::value_type borrow_in,
					  unsigned int &pending_zeroes)
{
	typename std::iterator_traits<OI>::value_type minuend, subtrahend;
	typename std::iterator_traits<OI>::value_type result;
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

	result = minuend - subtrahend;
	assert((result) < 10);
	assert((result) >= 0);
	
	if (result == 0) {
		++pending_zeroes;
	} else {
		// Result non-zero; handle pending zeroes
		while (pending_zeroes > 0) {
			*x = 0;
			++x; --pending_zeroes;
		}
		assert(pending_zeroes == 0);
		*x = result;
		++x;
	}
	
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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
 * @note The parameters represented by b1/e1 and b2/e2 are assumed to be 
 * non-negative integers.
 * @note Additionally, it is assumed that integer represented by the sequences
 * s1 and s2 are provided such that s1 >= s2.
 * (s1 - s2) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	typename std::iterator_traits<OI>::value_type borrow = 0;
	unsigned int zeroes = 0;
	bool all_zeroes = true;


	while (b1 != e1) {
		borrow = subtract_next_column(b1, e1, b2, e2, x, borrow, zeroes);
		if (all_zeroes && (zeroes == 0)) all_zeroes = false;
	}

	if (all_zeroes) {
		*x = 0;
		x++;
	}

	assert(b2 == e2);
	assert(borrow == 0);

    return x;
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
 */
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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the LEAST significant byte.
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
 * @note Assumes the iterators are iterating such that bX points at the LEAST
 * significant digit, and eX points just past the MOST significant byte.
 * (s1 / s2) => x
 * s1 is the numerator, s2 is the denominator.
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	typedef std::vector<typename std::iterator_traits<OI>::value_type> d_vector;
	d_vector numer; /* This one is MOST signaificant first...pay attention */
	d_vector denom;
	d_vector mul_result;
	d_vector prev_mul;
	d_vector result;
	d_vector tmp;
	typename d_vector::iterator tmp_end;
	typename d_vector::reverse_iterator out_it;
	typename std::iterator_traits<OI>::value_type div_digit;

	/* Will always hold the denominator */
	denom.assign(b2, e2);

	// Loop until we run out of numerator
	while (e1 != b1) {
		do {
			--e1;
			numer.push_back(*e1);
		} while (less_than_digits(numer.rbegin(), numer.rend(),
								  denom.begin(), denom.end()));

		div_digit = 0;
		prev_mul.clear();
		mul_result.assign(denom.begin(), denom.end());
		do {
			++div_digit;
			prev_mul = mul_result;
			tmp.clear();
			tmp.resize(mul_result.size() + 1, 0);
			tmp_end = plus_digits(mul_result.begin(), mul_result.end(),
	 				    		  denom.begin(), denom.end(), tmp.begin());
			mul_result.assign(tmp.begin(), tmp_end);
		} while (less_than_digits(mul_result.begin(), mul_result.end(),
								  numer.rbegin(), numer.rend()));
		
		result.push_back(div_digit);
		/* Prev_mul now holds the number to be subtracted from numerator */
		tmp.resize(distance(numer.begin(), numer.end()), 0);
		tmp_end = minus_digits(numer.rbegin(), numer.rend(),
				   	 		   prev_mul.begin(), prev_mul.end(), tmp.begin());
		tmp.resize(distance(tmp.begin(), tmp_end));
		numer.assign(tmp.rbegin(), tmp.rend());
	}
	
	out_it = result.rbegin();
	while(out_it != result.rend()) {
		*x = *out_it;
		++x; ++out_it;
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
         * Checking whether 2 integer object: lhs and rhs is equal to each other
         * O(N) if the Integer objects are equal. 
         */
        friend bool operator == (const Integer& lhs, const Integer& rhs) {
			// If called with yourself, this is true
			if (&lhs == &rhs) return true;

            if (lhs.sign != rhs.sign) return false;
            if (lhs.container.size() != rhs.container.size()) return false;
            //check each element of the container
            return (lhs.container == rhs.container);
		}

        // -----------
        // operator !=
        // -----------

        /**
         * Checking whether 2 integer object: lhs and rhs is not equal to each other
         */
        friend bool operator != (const Integer& lhs, const Integer& rhs) {
            return !(lhs == rhs);
		}

        // ----------
        // operator <
        // ----------

        /**
         * Checking whether the lhs object is less than the rhs object
         */
        friend bool operator < (const Integer& lhs, const Integer& rhs) {
			// Check signs - if they are different, handle this first
			if (!lhs.sign && rhs.sign) return true;
			if (lhs.sign && !rhs.sign) return false;
			// We know all signs are the same; handle size differences
            if (lhs.container.size() < rhs.container.size()) return (lhs.sign);
			if (lhs.container.size() > rhs.container.size()) return (!lhs.sign);
			// Same size, same sign - compare all digits until difference
			typename C::const_iterator lhs_it = lhs.container.end();
			typename C::const_iterator rhs_it = rhs.container.end();
			while (lhs_it != lhs.container.begin()) {
				--lhs_it; --rhs_it;
				if (*lhs_it > *rhs_it) return (!lhs.sign);
			}
           	return (lhs.sign);
        }

        // -----------
        // operator <=
        // -----------

        /**
         * Checking whether the lhs object is less than or equal to the rhs object
         */
        friend bool operator <= (const Integer& lhs, const Integer& rhs) {
            return !(rhs < lhs);
		}

        // ----------
        // operator >
        // ----------

        /**
         * Checking whether the lhs object has bigger Integer value than the rhs object
         */
        friend bool operator > (const Integer& lhs, const Integer& rhs) {
            return (rhs < lhs);
		}

        // -----------
        // operator >=
        // -----------

        /**
         * Checking whether the lhs object has bigger or equal Integer value than the rhs object
         */
        friend bool operator >= (const Integer& lhs, const Integer& rhs) {
            return !(lhs < rhs);
		}

        // ----------
        // operator +
        // ----------

        /**
         * adding 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator + (Integer lhs, const Integer& rhs) {
            return lhs += rhs;
		}

        // ----------
        // operator -
        // ----------

        /**
         * subtracting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator - (Integer lhs, const Integer& rhs) {
            return lhs -= rhs;
		}

        // ----------
        // operator *
        // ----------

        /**
         * multiplying 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator * (Integer lhs, const Integer& rhs) {
            return lhs *= rhs;
		}

        // ----------
        // operator /
        // ----------

        /**
         * dividing 2 integer object an outputting a new Integer object for the result
         * rhs can't be equal to zero
         * @throws invalid_argument if (rhs == 0)
         *FIXME: the exception thrown doesn't work somehow
         */
        friend Integer operator / (Integer lhs, const Integer& rhs) {
            /*if((rhs.container.size == 1) && (rhs.container[0] == 0)){
            	throw std::invalid_argument("Integer::operator /");
            	}*/
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
            return lhs %= rhs;
		}

        // -----------
        // operator <<
        // -----------

        /**
         * left shifting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator << (Integer lhs, int rhs) {
            return lhs <<= rhs;
		}

        // -----------
        // operator >>
        // -----------

        /**
         * right shifting 2 integer object an outputting a new Integer object for the result
         */
        friend Integer operator >> (Integer lhs, int rhs) {
            return lhs >>= rhs;
		}

        // -----------
        // operator <<
        // -----------

        /**
         * Outputting the Integer object in order to the console/standard output
         */
        friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
            typename C::const_iterator rit;
			if (!rhs.sign) lhs << "-";
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
			
			// Handle the 0 special case
			if (container.size() == 0) {
				container.push_back(0);
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
			Integer copy = *this;
			if(*this != 0)
			copy.sign = (!copy.sign);
			
            return copy;
		}

        // -----------
        // operator ++
        // -----------

        /**
         * pre-increment operator for Integer object
         * the returning result will be the object itself + 1
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;
		}

        /**
         * post-increment operator for Integer object
         * the returning result will be the old value of the Integer object
         * but after this operation is done the object itself will have +1 to its value
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;
		}

        // -----------
        // operator --
        // -----------

        /**
         * pre-decrement operator for Integer object
         * the returning result will be the object itself - 1
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;
		}

        /**
         * post-decrement operator for Integer object
         * the returning result will be the old value of the Integer object
         * but after this operation is done the object itself will have -1 to its value
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;
		}

        // -----------
        // operator +=
        // -----------

        /**
         * += operator for Integer object, 
         * the operation will return the modified object + value of rhs Integer
         */
        Integer& operator += (const Integer& rhs) {
			if (this->sign != rhs.sign) {
				if (this->abs() == rhs.abs()) {
					container.clear();
					container.push_back(0);
					sign = true;
					return *this;
				}

				// Four cases - first, they need to be submitted to minus with
				// the largest one first; so, if we need to switch their order,
				// we reverse the sign.
				// Ex: 9 - 18 = -(18 - 9)
				// FIXME: Maybe use swap here instead
				C copy = this->container;
				typename C::iterator end;
				if (this->abs() > rhs.abs()) {
						end = minus_digits(copy.begin(),
									 	   copy.end(),
									 	   rhs.container.begin(),
									 	   rhs.container.end(),
									 	   this->container.begin());
				} else {
						end = minus_digits(rhs.container.begin(),
									 	   rhs.container.end(),
									 	   copy.begin(),
									 	   copy.end(),
									 	   this->container.begin());
						this->sign = !this->sign;
				}
				this->container.resize(distance(this->container.begin(), end));
			} else {
				plus_digits(this->container.begin(), this->container.end(),
							rhs.container.begin(), rhs.container.end(),
							this->container.begin());
			}
            return *this;
		}

        // -----------
        // operator -=
        // -----------

        /**
         * -= operator for Integer object, 
         * the operation will return the modified object - value of rhs Integer
         */
        Integer& operator -= (const Integer& rhs) {
			return ((*this) += -(rhs));
		}
		

        // -----------
        // operator *=
        // -----------

        /**
         * *= operator for Integer object, 
         * the operation will return the modified object * value of rhs Integer
         */
        Integer& operator *= (const Integer& rhs) {
			if(*this==0 || rhs==0){
				this->container.clear();
				this->container.push_back(0);
				this->sign = true;
				return *this;
				}
			typename C::iterator copy_end;
			C copy;
			copy.resize(this->container.size() + rhs.container.size() + 1);
			this->sign = (this->sign == rhs.sign);
			copy_end = multiplies_digits(this->container.begin(),
										 this->container.end(),
						      			 rhs.container.begin(),
										 rhs.container.end(), copy.begin());
			this->container.assign(copy.begin(), copy_end);
			return *this;
		}

        // -----------
        // operator /=
        // -----------

        /**
         * /= operator for Integer object, 
         * the operation will return the modified object / value of rhs Integer
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
			typename C::iterator copy_end;
            if(rhs == 0) {
            	throw std::invalid_argument("Integer::operator /: div by 0");
            }

			C copy = this->container;
			this->sign = (this->sign == rhs.sign);
			copy_end = divides_digits(this->container.begin(),
									  this->container.end(),
						    		  rhs.container.begin(),
									  rhs.container.end(),
						    		  copy.begin());
			
			this->container.assign(copy.begin(), copy_end);
            return *this;
		}

        // -----------
        // operator %=
        // -----------

        /**
         * %= operator for Integer object, 
         * the operation will return the modified object % value of rhs Integer
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
			Integer copy = *this;

			copy = *this - ((*this / rhs) * rhs);

			this->container = copy.container;
			this->sign = copy.sign;
			return *this;
		}

        // ------------
        // operator <<=
        // ------------

        /**
         * <<= operator for Integer object, 
         * the operation will return the modified object << n
         */
        Integer& operator <<= (int n) {
            int i, len;

			if (n < 0) {
				throw std::invalid_argument("Integer::operator <<=: n < 0");
			}

			if (*this != 0) {
				len = this->container.size();
				this->container.resize(len + n);
				for (i = (len - 1); i >= 0; i--) {
					this->container[i + n] = this->container[i];
				}

				for (i = 0; i < n; i++) {
					this->container[i] = 0;
				}
			}

            return *this;
		}

        // ------------
        // operator >>=
        // ------------

        /**
         * <<= operator for Integer object, 
         * the operation will return the modified object >> n
         */
        Integer& operator >>= (int n) {
			typename C::iterator it;

			if (n < 0) {
				throw std::invalid_argument("Integer::operator <<=: n < 0");
			}

			if ((unsigned int)n >= this->container.size()) {
				this->container.clear();
				this->container.push_back(0);
			} else {
				it = this->container.begin();
				std::advance(it, n);
				this->container.erase(this->container.begin(), it);
			}

            return *this;
		}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * return the absolute value of an Integer object if it's negative
         * return a copy of the Integer object if it's positive
         */
        Integer abs () const {
			if (this->sign) {
            	Integer copy = *this;
				return copy;
			} else {
				return -(*this);
			}
		}

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
			if (e < 0) {
                	throw std::invalid_argument("Integer::pow(int e): e < 0");
			}
			
			if (e == 0) {
				if (*this == 0) {
                	throw std::invalid_argument("Integer::pow(int e): 0^0");
				}
				return Integer(1);
			}

			Integer copy = *this;
			C tmp;
			typename C::iterator tmp_end;
			for (int i = 1; i < e; i++) {
				tmp.resize(copy.container.size() + 1, 0);
				tmp_end = multiplies_digits(copy.container.begin(),
										    copy.container.end(),
										    this->container.begin(),
										    this->container.end(),
										    tmp.begin());
				copy.container.assign(tmp.begin(), tmp_end);
				tmp.clear();
			}
			if ((copy.sign == false) && ((e % 2) == 0)) {
				copy.sign = true;
			} else {
				copy.sign = this->sign;
			}
	
            return copy;
		}
	};

} // My

#endif // Integer_h


