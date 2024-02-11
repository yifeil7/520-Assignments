#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

    TEST(TypedArray, Push) {
        TypedArray<Point> a;
        a.push(Point(1,2,3));
        a.push(Point(4,5,6));
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a.get(0).x, 1);
        EXPECT_EQ(a.get(1).y, 5);
    }

    TEST(TypedArray, Pop) {
        TypedArray<Point> a;
        a.push(Point(1,2,3));
        a.push(Point(4,5,6));
        Point p = a.pop();
        EXPECT_EQ(a.size(), 1);
        EXPECT_DOUBLE_EQ(p.z, 6.0);
        EXPECT_THROW(a.pop(); a.pop(), std::range_error);
    }

    TEST(TypedArray, PushFront) {
        TypedArray<Point> a;
        a.push_front(Point(1,2,3));
        a.push_front(Point(4,5,6));
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a.get(0).x, 4);
        EXPECT_EQ(a.get(1).y, 2);
    }

    TEST(TypedArray, PopFront) {
        TypedArray<Point> a;
        a.push(Point(1,2,3));
        a.push(Point(4,5,6));
        Point p = a.pop_front();
        EXPECT_EQ(a.size(), 1);
        EXPECT_DOUBLE_EQ(p.z, 3.0);
        EXPECT_THROW(a.pop_front(); a.pop_front(), std::range_error);
    }

    TEST(TypedArray, Concat) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        // Perform concatenation
        TypedArray<int> b = a.concat(a).concat(a); // Expected to yield [0,1,0,1,0,1]

        // Verify the size and content of the resulting array
        EXPECT_EQ(b.size(), 6);
        for (int i = 0; i < b.size(); ++i) {
            EXPECT_EQ(b.get(i), i % 2);
        }

        // Verify that 'a' remains unchanged
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a.get(0), 0);
        EXPECT_EQ(a.get(1), 1);
    }

    TEST(TypedArray, Reverse) {
        TypedArray<int> a;
        for (int i = 0; i < 5; ++i) {
            a.push(i); // Fill array with values 0, 1, 2, 3, 4
        }

        // Reverse the array and test chaining by calling size() on the result
        EXPECT_EQ(a.reverse().size(), 5); // Ensure the array is reversed and the size is correct

        
        // Verify the array is correctly reversed
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(a.get(i), 4 - i);
        }

        
        // Further verify chaining by reversing back in the same statement
        a.reverse(); // Should revert to the original order

        // Check if it's reverted to original
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(a.get(i), i);
        }
    }

// Test case for the '+' operator overload
TEST(TypedArrayTest, PlusOperator) {
    TypedArray<int> a;
    a.set(0, 1); // Assuming set method to add elements
    TypedArray<int> b;
    b.set(0, 2);

    TypedArray<int> result = a + b;

    // Assuming size and get methods to check results
    ASSERT_EQ(result.size(), 2); // Check size of the result
    EXPECT_EQ(result.get(0), 1); // Check first element
    EXPECT_EQ(result.get(1), 2); // Check second element
}

TEST(ComplexClass, RealAndImaginaryParts) {
        Complex z(3.0, 4.0);
        EXPECT_DOUBLE_EQ(z.real(), 3.0);
        EXPECT_DOUBLE_EQ(z.imaginary(), 4.0);
    }

    TEST(ComplexClass, Conjugate) {
        Complex z(3.0, 4.0);
        Complex zConj = z.conjugate();
        EXPECT_DOUBLE_EQ(zConj.real(), 3.0);
        EXPECT_DOUBLE_EQ(zConj.imaginary(), -4.0);
    }

    TEST(ComplexClass, Addition) {
        Complex a(1.0, 2.0);
        Complex b(3.0, 4.0);
        Complex result = a + b;
        EXPECT_DOUBLE_EQ(result.real(), 4.0);
        EXPECT_DOUBLE_EQ(result.imaginary(), 6.0);
    }

    TEST(ComplexClass, Multiplication) {
        Complex a(1.0, 2.0);
        Complex b(3.0, 4.0);
        Complex result = a * b;
        EXPECT_DOUBLE_EQ(result.real(), -5.0); // 1*3 - 2*4
        EXPECT_DOUBLE_EQ(result.imaginary(), 10.0); // 1*4 + 2*3
    }

    TEST(ComplexClass, Equality) {
        Complex a(1.0, 2.0);
        Complex b(1.0, 2.0);
        Complex c(2.0, 3.0);
        EXPECT_TRUE(a == b);
        EXPECT_FALSE(a == c);
    }



}