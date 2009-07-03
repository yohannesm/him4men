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

    // -------------------
    // test_divides_digits
    // -------------------

    void test_divides_digits () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = My::divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

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

    void test_minus_digits () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = My::minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // ----------------------
    // test_multiplies_digits
    // ----------------------

    void test_multiplies_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = My::multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

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

    // ----------------
    // test_plus_digits
    // ----------------

    void test_plus_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = My::plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));

        const char a1[] = {2, 3, 4};
        const char b1[] = {5, 6, 7};
        const char c1[] = {8, 0, 1};
              char x1[10];
        const char* p1 = My::plus_digits(a1, a1 + 3, b1, b1 + 3, x1);
        CPPUNIT_ASSERT(p1 - x1 == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const char*>(x1), p1, c1));

	}

    // --------
    // test_pow
    // --------

    void test_pow () {
        try {
            const My::Integer<int> x = 98765;
            const int              e =  9867;
            const My::Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e ==  9867);
            CPPUNIT_ASSERT(y ==     0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ----------------------
    // test_shift_left_digits
    // ----------------------

    void test_shift_left_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0};
        int x[10];
        const int* p = My::shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));

		memset(x, 0, 10 * sizeof(int));
        const int* p1 = My::shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p1, a));
	}
		

    // -----------------------
    // test_shift_right_digits
    // -----------------------

    void test_shift_right_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
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
    CPPUNIT_TEST(test_plus_digits);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_abs);
    CPPUNIT_TEST(test_divides_digits);
    CPPUNIT_TEST(test_minus_digits);
    CPPUNIT_TEST(test_multiplies_digits);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_pow);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestInteger_h


