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

// ----------
// namespaces
// ----------

namespace My {

// -----------
// plus_digits
// -----------

template <typename II1, typename II2, typename OI>
int add_column (II1 a, II2 b, OI x, int carry) {
	*x = *a + *b + carry;
	if (*x >= 10) {
		*x -= 10;
		carry = 1;
	} else {
		carry = 0;
	}

	return carry;
}


template <typename II, typename OI>
int add_digit (II a, OI x, int carry) {
	*x = *a + carry;
	if (*x >= 10) {
		*x -= 10;
		carry = 1;
	} else {
		carry = 0;
	}

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
 * Algorithm:  First, pass through both input sequences, and compute their
 * relative lengths
 * (s1 + s2) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    OI backwards, end;
	int num_digits = 0;

	backwards = x;
    int carry = 0;
    while((e1 != b1) && (e2 != b2)) {
		--e1; --e2;
	 	// add the next column of digits; include carry
		carry = add_column(e1, e2, backwards, carry);
		++num_digits;
        ++backwards;
    }
	// Handle unequal sized inputs, if first input longer
	while (e1 != b1) {
		--e1;
		carry = add_digit(e1, backwards, carry);
		++num_digits;
        ++backwards;
	}

	// Handle unequal sized inputs, if second input longer
	while (e2 != b2) {
		--e2;
		carry = add_digit(e2, backwards, carry);
		++num_digits;
        ++backwards;
	}

	// Handle the case where there was a carry out of the most significant digit
    if (carry != 0) {
        *backwards = carry;
		++num_digits;
        carry = 0;
		++backwards;
    }

	end = backwards;
	//int tmp;
	int i;
	// reverse backwards, and write into x
	for (i = 0; i < (num_digits / 2); i++) {
		--backwards;
#if 0
		tmp = *backwards;
		*x = *backwards;
		*backwards = tmp;
#endif
		*x ^= *backwards;
		*backwards ^= *x;
		*x ^= *backwards;
		++x;
	}

    return end;
}



// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * (s1 - s2) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    while(b1!=e1 && b2!=e2){
    	*x = *b1 - *b2; // assigning x
    	++b1; ++b2; ++x;
    }
    return x;}

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
            return lhs << "0";}

    private:
        // ----template < typename T, typename C = std::vector<T> >
        // data
        // ----
        size_t digits; // number of digits
		// Does not compile - please re-add when it compiles
		//bool sign = true; // true = positive & false = negative 
        //C<T> container;

        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
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


