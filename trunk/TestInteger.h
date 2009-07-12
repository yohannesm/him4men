#ifndef TestInteger_h
#define TestInteger_h

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------
    void test_constructor_0 () {
        try {
            const My::Integer<int> x("0");
			assert(x == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}


    void test_constructor_1 () {
        try {
            const My::Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "My::Integer()"));}}

    void test_constructor_2 () {
        try {
            const My::Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const My::Integer<int> x = 2;}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_4 () {
        try {
            const My::Integer<int> x("aasdjj31asjdaskdlkk");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "My::Integer()"));}}

    void test_constructor_5 () {
        try {
            const My::Integer<int> x("abskajdkaljwqe,mz,cmwjlkep[c");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "My::Integer()"));}}

    void test_constructor_6 () {
        try {
            const My::Integer<int> x(21612273);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_7 () {
        try {
            const My::Integer<int> x = 6972198;}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_8 () {
        try {
            const My::Integer<int> x("172389172398712983712983719287391827398214681723");
	    }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // test_abs
    // --------

    void test_abs () {
        try {
            const My::Integer<int> x = -98765;
            const My::Integer<int> y = x.abs();
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs1 () {
        try {
            const My::Integer<int> x = -1234;
            const My::Integer<int> y = x.abs();
            CPPUNIT_ASSERT(y == 1234);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs2 () {
        try {
            const My::Integer<int> x = 9876;
            const My::Integer<int> y = x.abs();
            CPPUNIT_ASSERT(y == 9876);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs3 () {
        try {
            const My::Integer<int> x = 0;
            const My::Integer<int> y = x.abs();
            CPPUNIT_ASSERT(y == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -------------------
    // test_divides_digits
    // -------------------

	template <typename T>
    void test_divides_digits () {
        const T a[] = {8, 7, 6, 2, 3, 1};
        const T b[] = {7, 6, 5};
        const T c[] = {4, 3, 2};
              T x[10];
        const T* p = My::divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x), p, c));}


    void test_divides_int () {
        My::Integer<int> a = 45;
        My::Integer<int> b = 5;
        My::Integer<int> c = 9;
		My::Integer<int> r = (a / b);
        CPPUNIT_ASSERT((a / b) == c);
        CPPUNIT_ASSERT(r == c);
	}

    void test_modulo_int () {
        My::Integer<int> a = 123;
        My::Integer<int> b = 10;
        My::Integer<int> c = 3;
		My::Integer<int> r = (a % b);
        CPPUNIT_ASSERT((a % b) == c);
        CPPUNIT_ASSERT(r == c);
	}
    // -------------
    // test_equal_to
    // -------------

    void test_equal_to () {
        try {
            const My::Integer<int> x = 98765;
            const My::Integer<int> y = 98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 98765);
            CPPUNIT_ASSERT(  98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----------------
    // test_minus_digits
    // -----------------

	template <typename T>
    void test_minus_digits () {
        const T a[] = {1, 0, 8};
        const T b[] = {7, 6, 5};
        const T c[] = {4, 3, 2};
              T x[10];
        const T* p = My::minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x), p, c));
	}


    void test_minus_int () {
        My::Integer<int> a = 5;
        My::Integer<int> b = 3;
        My::Integer<int> c = 2;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	
	
    void test_minus_int_1 () {
        My::Integer<int> a = 5;
        My::Integer<int> b = -2;
        My::Integer<int> c = 7;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	

    void test_minus_int_2 () {
        My::Integer<int> a = -5;
        My::Integer<int> b = 2;
        My::Integer<int> c = -7;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	

    void test_minus_int_3 () {
        My::Integer<int> a = -5;
        My::Integer<int> b = -2;
        My::Integer<int> c = -3;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	


    void test_minus_int_4 () {
        My::Integer<int> a = -2;
        My::Integer<int> b = 5;
        My::Integer<int> c = -7;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	

    void test_minus_int_5 () {
        My::Integer<int> a = 2;
        My::Integer<int> b = -5;
        My::Integer<int> c = 7;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	


    void test_minus_int_6 () {
        My::Integer<int> a = -2;
        My::Integer<int> b = -5;
        My::Integer<int> c = 3;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	

    void test_minus_int_7 () {
        My::Integer<int> a = 2;
        My::Integer<int> b = 5;
        My::Integer<int> c = -3;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	
	
    void test_minus_int_8 () {
        My::Integer<int> a = 123;
        My::Integer<int> b = 120;
        My::Integer<int> c = 3;
		My::Integer<int> r = (a - b);
        CPPUNIT_ASSERT((a - b) == c);
	}	
	

    // -----------------
    // test_plus_digits
    // -----------------


    void test_plus_int () {
        My::Integer<int> a = 2;
        My::Integer<int> b = 3;
        My::Integer<int> c = 5;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	
	
    void test_plus_int_1 () {
        My::Integer<int> a = 5;
        My::Integer<int> b = -2;
        My::Integer<int> c = 3;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	

    void test_plus_int_2 () {
        My::Integer<int> a = -5;
        My::Integer<int> b = 2;
        My::Integer<int> c = -3;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	

    void test_plus_int_3 () {
        My::Integer<int> a = -5;
        My::Integer<int> b = -2;
        My::Integer<int> c = -7;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	

    void test_plus_int_4 () {
        My::Integer<int> a = -2;
        My::Integer<int> b = 5;
        My::Integer<int> c = 3;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	

    void test_plus_int_5 () {
        My::Integer<int> a = 2;
        My::Integer<int> b = -5;
        My::Integer<int> c = -3;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	


    void test_plus_int_6 () {
        My::Integer<int> a = -2;
        My::Integer<int> b = -5;
        My::Integer<int> c = -7;
		My::Integer<int> r = (a + b);
        CPPUNIT_ASSERT((a + b) == c);
	}	

    // ----------------------
    // test_multiplies_digits
    // ----------------------

	template <typename T>
    void test_multiplies_digits () {
        const T a[] = {4, 3, 2};
        const T b[] = {7, 6, 5};
        const T c[] = {8, 7, 6, 2, 3, 1};
              T x[10];
        const T* p = My::multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x), p, c));}

    // -------------
    // test_negation
    // -------------

    void test_negation () {
        try {
            const My::Integer<int> x = 98765;
            const My::Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----------
    // test_output
    // -----------

    void test_output () {
        try {
            const My::Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output1 () {
        try {
            const My::Integer<int> x = 12345;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "12345");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output2 () {
        try {
            const My::Integer<int> x = -36457;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-36457");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ----------------
    // test_plus_digits
    // ----------------

	template <typename T>
    void test_plus_digits () {
        const T a[] = {4, 3, 2};
        const T b[] = {7, 6, 5};
        const T c[] = {1, 0, 8};
              T x[10];
        const T* p = My::plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x), p, c));

        const T a1[] = {4, 3, 2};
        const T b1[] = {9};
        const T c1[] = {3, 4, 2};
              T x1[10];
        const T* p1 = My::plus_digits(a1, a1 + 3, b1, b1 + 1, x1);
        CPPUNIT_ASSERT(p1 - x1 == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x1), p1, c1));

        const T a2[] = {9, 9, 9};
        const T b2[] = {1};
        const T c2[] = {0, 0, 0, 1};
              T x2[10];
        const T* p2 = My::plus_digits(a2, a2 + 3, b2, b2 + 1, x2);
        CPPUNIT_ASSERT(p2 - x2 == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const T*>(x2), p2, c2));
	}

    // --------
    // test_pow
    // --------

    void test_pow1() {
        try {
            const My::Integer<int> x = 98765;
            const int              e =     1;
            const My::Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e ==     1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow0 () {
        try {
            const My::Integer<int> x = 98765;
            const int              e =     0;
            const My::Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e ==     0);
			CPPUNIT_ASSERT(y ==     1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow2 () {
        try {
            const My::Integer<int> x = 	   8;
            const int              e =     2;
            const My::Integer<int> y = x.pow(e);
			CPPUNIT_ASSERT(y ==    64);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_neg_3 () {
        try {
            const My::Integer<int> x = 	  -8;
            const int              e =     3;
            const My::Integer<int> y = x.pow(e);
			CPPUNIT_ASSERT(y == -512);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_neg_2 () {
        try {
            const My::Integer<int> x = 	  -8;
            const int              e =     2;
            const My::Integer<int> y = x.pow(e);
			CPPUNIT_ASSERT(y ==    64);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow00() {
        try {
            const My::Integer<int> x = 0;
            const int              e = 0;
            const My::Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);
		}
	}

    void test_pow_neg() {
        try {
            const My::Integer<int> x = 2;
            const int              e = -1;
            const My::Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);
		}
	}
    // ----------------------
    // test_shift_left_digits
    // ----------------------

    void test_shift_left_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {0, 0, 2, 3, 4};
        int x[10];
        const int* p = My::shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));

        int x1[10];
        const int* p1 = My::shift_left_digits(a, a + 3, 0, x1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x1), p1, a));
	}
		

    // -----------------------
    // test_shift_right_digits
    // -----------------------

    void test_shift_right_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {4};
              int x[10];
        const int *p = My::shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	
		memset(x, 0, 10 * sizeof(int));
		const int b1[] = {0};
		const int *p1 = My::shift_right_digits(a, a + 3, 3, x);
		CPPUNIT_ASSERT(std::equal(const_cast<const int *>(x), p1, b1));

		memset(x, 0, 10 * sizeof(int));
		const int b2[] = {0};
		const int *p2 = My::shift_right_digits(a, a + 3, 30, x);
		CPPUNIT_ASSERT(std::equal(const_cast<const int *>(x), p2, b2));

		memset(x, 0, 10 * sizeof(int));
		const int *p3 = My::shift_right_digits(a, a + 3, 0, x);
		CPPUNIT_ASSERT(std::equal(const_cast<const int *>(x), p3, a));
	}

	
    // ------------------------------
    // operator == (Integer, Integer)
    // ------------------------------
    void test_equal_equal () {
		const My::Integer<int> a = 1;
		const My::Integer<int> b = 1;
		const My::Integer<int> c = 11;
		const My::Integer<int> d = 11;
		CPPUNIT_ASSERT(a == b);
		CPPUNIT_ASSERT(c == d);
	}
    // ------------------------------
    // operator != (Integer, Integer)
    // ------------------------------
    void test_not_equal () {
		const My::Integer<int> a = 1;
		const My::Integer<int> b = -1;
		const My::Integer<int> c = 11;
		const My::Integer<int> d = 110;
		CPPUNIT_ASSERT(a != b);
		CPPUNIT_ASSERT(c != d);
	}
    // ------------------------------
    // operator < (Integer, Integer)
    // ------------------------------
    void test_less_than () {
		const My::Integer<int> a = 9;
		const My::Integer<int> b = 10;
		const My::Integer<int> c = -10;
		const My::Integer<int> d = -9;
		CPPUNIT_ASSERT(a < b);
		CPPUNIT_ASSERT(c < a);
		CPPUNIT_ASSERT(c < d);
	}
    // ------------------------------
    // operator <= (Integer, Integer)
    // ------------------------------
    void test_less_than_equal () {
		const My::Integer<int> a = 9;
		const My::Integer<int> b = 10;
		const My::Integer<int> c = -10;
		const My::Integer<int> d = -10;
		CPPUNIT_ASSERT(a <= b);
		CPPUNIT_ASSERT(c <= b);
		CPPUNIT_ASSERT(c <= d);
	}
    // ------------------------------
    // operator > (Integer, Integer)
    // ------------------------------
    void test_greater_than () {
		const My::Integer<int> a = 9;
		const My::Integer<int> b = 10;
		const My::Integer<int> c = -10;
		CPPUNIT_ASSERT(b > a);
		CPPUNIT_ASSERT(b > c);
	}
    // ------------------------------
    // operator >= (Integer, Integer)
    // ------------------------------
    void test_greater_than_equal () {
		const My::Integer<int> a = 9;
		const My::Integer<int> b = 10;
		const My::Integer<int> c = -10;
		const My::Integer<int> d = -10;
		CPPUNIT_ASSERT(b >= a);
		CPPUNIT_ASSERT(b >= c);
		CPPUNIT_ASSERT(d >= c);
	}
    // ------------------------------
    // operator * (Integer, Integer)
    // ------------------------------
    void test_multiply () {
		const My::Integer<int> a = 1;
		const My::Integer<int> b = 50;
		const My::Integer<int> c = -11;
		const My::Integer<int> d = 40;
		const My::Integer<int> e = 999;
		const My::Integer<int> f = 998001;
		CPPUNIT_ASSERT((a*b) == My::Integer<int>(50));
		CPPUNIT_ASSERT((b*c) == My::Integer<int>(-550));
		CPPUNIT_ASSERT((b*d) == My::Integer<int>(2000));
		CPPUNIT_ASSERT((e*e) == My::Integer<int>(998001));
	}
    // ------------------------------
    // operator << (Integer, int)
    // ------------------------------
    void test_left_shift () {
		const My::Integer<int> a = 101;
		const My::Integer<int> b = 0;
		CPPUNIT_ASSERT((a << 0) == a);
		CPPUNIT_ASSERT((a << 1) == My::Integer<int>(1010));
		CPPUNIT_ASSERT((a << 2) == My::Integer<int>(10100));
		CPPUNIT_ASSERT((b << 3) == My::Integer<int>(0));
	}
    // ------------------------------
    // operator >> (Integer, int)
    // ------------------------------
    void test_right_shift () {
		const My::Integer<int> a = 20101;
		const My::Integer<int> b = 0;
		CPPUNIT_ASSERT((a >> 0) == a);
		CPPUNIT_ASSERT((a >> 1) == My::Integer<int>(2010));
		CPPUNIT_ASSERT((a >> 2) == My::Integer<int>(201));
		CPPUNIT_ASSERT((a >> 4) == My::Integer<int>(2));
		CPPUNIT_ASSERT((a >> 5) == My::Integer<int>(0));
		CPPUNIT_ASSERT((a >> 20) == My::Integer<int>(0));
		CPPUNIT_ASSERT((b >> 3) == My::Integer<int>(0));
		CPPUNIT_ASSERT((b << 3) == My::Integer<int>(0));
		try {
			CPPUNIT_ASSERT((a >> -2) == My::Integer<int>(2010100));
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);
		}
	}
    // ------------------------------
    // Integer::operator - ()
    // ------------------------------
    void test_negation2(){
		const My::Integer<int> a = 201;
		const My::Integer<int> b = 0;
		CPPUNIT_ASSERT((-a) == -201);
		CPPUNIT_ASSERT((-b) == 0);
	}
    // ------------------------------
    // Integer::operator ++ () // pre
    // ------------------------------

   void test_pre_inc(){
		My::Integer<int> a = 3;
		My::Integer<int> b = -1;
		CPPUNIT_ASSERT((++a) == My::Integer<int>(4));
		CPPUNIT_ASSERT((++b) ==  My::Integer<int>(0));
	}
    // ------------------------------
    // Integer::operator ++ (int) // post
    // ------------------------------
    void test_post_inc(){
		My::Integer<int> a = 3;
		My::Integer<int> b = -1;
		CPPUNIT_ASSERT((a++) == My::Integer<int>(3));
		CPPUNIT_ASSERT((b++) ==  My::Integer<int>(-1));
	}
    // ------------------------------
    // Integer::operator -- () // pre
    // ------------------------------

   void test_pre_dec(){
		My::Integer<int> a = 3;
		My::Integer<int> b = 0;
		CPPUNIT_ASSERT((--a) == My::Integer<int>(2));
		CPPUNIT_ASSERT((--b) ==  My::Integer<int>(-1));
	}
    // ------------------------------
    // Integer::operator -- (int) // post
    // ------------------------------
    void test_post_dec(){
		My::Integer<int> a = 3;
		My::Integer<int> b = -1;
		CPPUNIT_ASSERT((a--) == My::Integer<int>(3));
		CPPUNIT_ASSERT((b--) ==  My::Integer<int>(-1));
	}
    // ------------------------------
    // Integer::operator += (const Integer)
    // ------------------------------

    void test_plus_equal(){
		My::Integer<int> a = 12;
		My::Integer<int> b = 0;
		const My::Integer<int> c = 1;
		const My::Integer<int> d = 13;
		My::Integer<int> e = -1;
		CPPUNIT_ASSERT((a += c) == d);
		CPPUNIT_ASSERT((b += b) == b);
		CPPUNIT_ASSERT((e += c) == b);
	}
    // ------------------------------
    // Integer::operator -= (const Integer)
    // ------------------------------
    void test_minus_equal(){
		My::Integer<int> a = 12;
		My::Integer<int> b = 0;
		const My::Integer<int> c = 1;
		const My::Integer<int> d = 11;
		My::Integer<int> e = 1;
		CPPUNIT_ASSERT((a -= c) == d);
		CPPUNIT_ASSERT((b -= b) == b);
		CPPUNIT_ASSERT((e -= c) == b);
	}
    // ------------------------------
    // Integer::operator *= (const Integer)
    // ------------------------------
    void test_multip_equal(){
		My::Integer<int> a = 12;
		My::Integer<int> b = 0;
		const My::Integer<int> c = 1;
		const My::Integer<int> d = 11;
		My::Integer<int> e = -1;
		CPPUNIT_ASSERT((b *= a) == b);
		CPPUNIT_ASSERT((a *= b) == b);
		CPPUNIT_ASSERT((b *= b) == b);
		CPPUNIT_ASSERT((e *= c) == e);
	}
    // ------------------------------
    // Integer::operator /= (const Integer)
    // ------------------------------
    // ------------------------------
    // Integer::operator %= (const Integer)
    // ------------------------------
    // ------------------------------
    // Integer::operator <<= (int)
    // ------------------------------
    // ------------------------------
    // Integer::operator >>= (int)
    // ------------------------------

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits);
    CPPUNIT_TEST(test_shift_right_digits);
    CPPUNIT_TEST(test_plus_digits<int>);
    CPPUNIT_TEST(test_plus_digits<char>);
    CPPUNIT_TEST(test_minus_digits<int>);
    CPPUNIT_TEST(test_minus_digits<char>);
    CPPUNIT_TEST(test_multiplies_digits<int>);
    CPPUNIT_TEST(test_multiplies_digits<char>);
    CPPUNIT_TEST(test_divides_digits<int>);
    CPPUNIT_TEST(test_divides_digits<char>);
    CPPUNIT_TEST(test_constructor_0);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    CPPUNIT_TEST(test_constructor_6);
    CPPUNIT_TEST(test_constructor_7);
    CPPUNIT_TEST(test_constructor_8);
    CPPUNIT_TEST(test_abs);
    CPPUNIT_TEST(test_abs1);
    CPPUNIT_TEST(test_abs2);
    CPPUNIT_TEST(test_abs3);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_output1);
    CPPUNIT_TEST(test_output2);
    CPPUNIT_TEST(test_pow1);
    CPPUNIT_TEST(test_pow0);
    CPPUNIT_TEST(test_pow00);
    CPPUNIT_TEST(test_pow_neg);
    CPPUNIT_TEST(test_pow_neg_2);
    CPPUNIT_TEST(test_pow_neg_3);
    CPPUNIT_TEST(test_pow2);
    CPPUNIT_TEST(test_plus_int);
    CPPUNIT_TEST(test_plus_int_1);
    CPPUNIT_TEST(test_plus_int_2);
    CPPUNIT_TEST(test_plus_int_3);
    CPPUNIT_TEST(test_plus_int_4);
    CPPUNIT_TEST(test_plus_int_5);
    CPPUNIT_TEST(test_plus_int_6);
    CPPUNIT_TEST(test_minus_int);
    CPPUNIT_TEST(test_minus_int_1);
    CPPUNIT_TEST(test_minus_int_2);
    CPPUNIT_TEST(test_minus_int_3);
    CPPUNIT_TEST(test_minus_int_4);
    CPPUNIT_TEST(test_minus_int_5);
    CPPUNIT_TEST(test_minus_int_6);
    CPPUNIT_TEST(test_minus_int_7);
    CPPUNIT_TEST(test_minus_int_8);
	CPPUNIT_TEST(test_multiply);
    CPPUNIT_TEST(test_divides_int);
    CPPUNIT_TEST(test_modulo_int);
    CPPUNIT_TEST(test_equal_equal);
    CPPUNIT_TEST(test_not_equal);
    CPPUNIT_TEST(test_less_than);
    CPPUNIT_TEST(test_less_than_equal);
    CPPUNIT_TEST(test_greater_than);
    CPPUNIT_TEST(test_greater_than_equal);
    CPPUNIT_TEST(test_left_shift);
    CPPUNIT_TEST(test_right_shift);
	CPPUNIT_TEST(test_negation2);
	CPPUNIT_TEST(test_pre_inc);
	CPPUNIT_TEST(test_post_inc);
	CPPUNIT_TEST(test_pre_dec);
	CPPUNIT_TEST(test_post_dec);
	CPPUNIT_TEST(test_plus_equal);
	CPPUNIT_TEST(test_minus_equal);
	CPPUNIT_TEST(test_multip_equal);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestInteger_h


