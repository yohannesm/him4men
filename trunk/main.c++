// -----------------------------
// projects/c++/integer/main.c++
// Copyright (C) 2009
// Glenn P. Downing
// -----------------------------

// To run the tests:
//     g++ -ansi -pedantic -lcppunit -ldl -Wall -DTEST main.c++ -o main.app
//     valgrind main.app

// To run the program:
//     g++ -ansi -pedantic -Wall main.c++ -o main.app
//     valgrind main.app > main.out

// To configure Doxygen:
//     doxygen -g
// That creates the file Doxyfile.
// Make the following edits:
//     EXTRACT_ALL            = YES
//     EXTRACT_PRIVATE        = YES
//     EXTRACT_STATIC         = YES
//     GENERATE_LATEX         = NO

// To document the program:
//     doxygen Doxyfile

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl, ios_base, noskipws
#include <deque>    // deque
#include <fstream>  // ifstream
#include <string>   // string

#include "Integer.h"

#ifdef TEST
    #include "cppunit/TestSuite.h"      // TestSuite
    #include "cppunit/TextTestRunner.h" // TestRunner

    #include "TestInteger.h"
#endif // TEST

// ----
// main
// ----

int main (int argc, char* argv[]) {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    #ifdef TEST
        // ----------
        // unit tests
        // ----------

        CppUnit::TextTestRunner tr;
        tr.addTest(TestInteger::suite());
        tr.run();
    #else
        // -------
        // program
        // -------

        cout << "*** 20th Mersenne prime: 1,332 digits ***" << endl << endl;

        {
        const My::Integer<int> n = My::Integer<int>(2).pow(4423) - 1;
        cout << "2^4423 - 1 = " << n << endl << endl;
        }

        {
        const My::Integer< int, std::deque<int> > n = My::Integer< int, std::deque<int> >(2).pow(4423) - 1;
        cout << "2^4423 - 1 = " << n << endl << endl;
        }

        // ---------------------
        // extra credit (10 pts)
        // ---------------------

        cout << "*** 30th Mersenne prime: 39,751 digits ***" << endl << endl;

        {
        const My::Integer<int> n = My::Integer<int>(2).pow(132049) - 1;
        cout << "2^132049 - 1 = " << n << endl << endl;
        }

        {
        //const My::Integer< int, std::deque<int> > n = My::Integer< int, std::deque<int> >(2).pow(132049) - 1;
        //cout << "2^132049 - 1 = " << n << endl << endl;
        }

        cout << "Done." << endl;
    #endif // TEST

    return 0;}


