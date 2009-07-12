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
    CPPUNIT_TEST_SUITE_END();};

#endif // TestInteger_h


