#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "gtest/gtest.h"
#include <vector>
#include "utilities.h"
#include <cstdio> // For std::remove
#include <fstream>

class MatrixCSVTest : public ::testing::Test {
protected:
    std::string tempFileName = "temp_test_matrix.csv";

    // Function to create a temporary CSV file
    void SetUp() override {
        std::ofstream tempFile(tempFileName);
        tempFile << "1.0, 2.0, 3.0\n";
        tempFile << "4.0, 5.0, 6.0\n";
        tempFile << "-7.0, 8.0, -9.0\n";
        tempFile.close();
    }

    // Function to clean up the temporary file
    void TearDown() override {
        std::remove(tempFileName.c_str());
    }
};

class MatrixCSVReadWriteTest : public ::testing::Test {
protected:
    std::string tempFileName = "temp_matrix.csv";
};

class OccurrenceMapTest : public ::testing::Test {
protected:
    std::string tempFilePath = "./temp_test_file.txt";

    void SetUp() override {
        // Setup is intentionally left blank
    }

    void TearDown() override {
        std::remove(tempFilePath.c_str());
    }

    void writeTestContent(const std::string& content) {
        std::ofstream tempFile(tempFilePath);
        tempFile << content;
        tempFile.close();
    }
};

namespace {

    
    TEST(SortByMagnitude, CorrectlySortsVector) {
        std::vector<double> vec = {-3, 4, -1, 2, -5, 0};

        // Call the function to sort the vector
        sort_by_magnitude(vec);

        // Expected sorted vector by magnitude
        std::vector<double> expected = {0, -1, 2, -3, 4, -5};

        // Check if the sorted vector matches the expected vector
        ASSERT_EQ(vec.size(), expected.size()) << "Vectors are of unequal length";

        for (size_t i = 0; i < vec.size(); ++i) {
            EXPECT_DOUBLE_EQ(vec[i], expected[i]) << "Vectors differ at index " << i;
        }
    }


    
    TEST_F(MatrixCSVTest, ReadsCorrectly) {
        auto matrix = read_matrix_csv(tempFileName);
        ASSERT_EQ(matrix.size(), 3); // Expect 3 rows

        // Check the first row
        EXPECT_DOUBLE_EQ(matrix.get(0).get(0), 1.0);
        EXPECT_DOUBLE_EQ(matrix.get(0).get(1), 2.0);
        EXPECT_DOUBLE_EQ(matrix.get(0).get(2), 3.0);

        // Check the second row
        EXPECT_DOUBLE_EQ(matrix.get(1).get(0), 4.0);
        EXPECT_DOUBLE_EQ(matrix.get(1).get(1), 5.0);
        EXPECT_DOUBLE_EQ(matrix.get(1).get(2), 6.0);

        // Check the third row
        EXPECT_DOUBLE_EQ(matrix.get(2).get(0), -7.0);
        EXPECT_DOUBLE_EQ(matrix.get(2).get(1), 8.0);
        EXPECT_DOUBLE_EQ(matrix.get(2).get(2), -9.0);
    }

    TEST_F(MatrixCSVTest, ThrowsOnFormatError) {
        // Overwrite the temp file with bad data
        std::ofstream tempFile(tempFileName);
        tempFile << "1.0, 2.0, three\n"; // Invalid number format
        tempFile.close();
        EXPECT_THROW(read_matrix_csv(tempFileName), std::runtime_error);
    }

    TEST_F(MatrixCSVReadWriteTest, WriteAndReadBack) {
        TypedArray<TypedArray<double>> originalMatrix;
        TypedArray<double> row1, row2;
        row1.set(0, 1.0); row1.set(1, 2.0); row1.set(2, 3.0);
        row2.set(0, 4.0); row2.set(1, 5.0); row2.set(2, 6.0);
        originalMatrix.set(0, row1); originalMatrix.set(1, row2);

        // Write the matrix to a temporary file
        write_matrix_csv(originalMatrix, tempFileName);

        // Read the matrix back from the file
        TypedArray<TypedArray<double>> readMatrix = read_matrix_csv(tempFileName);

        // Verify the read matrix matches the original
        ASSERT_EQ(readMatrix.size(), originalMatrix.size());
        for (int i = 0; i < originalMatrix.size(); ++i) {
            for (int j = 0; j < originalMatrix.get(i).size(); ++j) {
                EXPECT_DOUBLE_EQ(readMatrix.get(i).get(j), originalMatrix.get(i).get(j));
            }
        }

        // Clean up the temporary file
        std::remove(tempFileName.c_str());
    }

    TEST_F(OccurrenceMapTest, Examples) {
        // Example 1
        writeTestContent("This is a sentence. Don't think of wier_d strings as words. Really, 123 is a nice number.");
        auto wordMap = occurrence_map(tempFilePath);
        EXPECT_EQ(wordMap["this"], 1);
        EXPECT_EQ(wordMap["is"], 2);
        EXPECT_EQ(wordMap["a"], 2);
        EXPECT_EQ(wordMap.size(), 14); // Checking total unique valid words

        // Example 2
        writeTestContent("'I should use double quotes'");
        wordMap = occurrence_map(tempFilePath);
        EXPECT_EQ(wordMap["'i"], 1);
        EXPECT_EQ(wordMap["quotes'"], 1);
        EXPECT_EQ(wordMap.size(), 5); // Checking total unique valid words

        // Example 3
        writeTestContent("George Mallory's famous quote: \"My mind is in a state of constant rebellion.\"");
        wordMap = occurrence_map(tempFilePath);
        EXPECT_EQ(wordMap["george"], 1);
        EXPECT_EQ(wordMap["mallory's"], 1);
        EXPECT_EQ(wordMap["rebellion"], 1);
        EXPECT_EQ(wordMap.size(), 13); // Checking total unique valid words

        // Example 4
        writeTestContent("10XGenomics (a biotech company) is quoted as saying \"blah blah blah.\"");
        wordMap = occurrence_map(tempFilePath);
        EXPECT_EQ(wordMap["10xgenomics"], 1);
        EXPECT_EQ(wordMap["blah"], 3);
        EXPECT_EQ(wordMap.size(), 9); // Checking total unique valid words

        // Example 5
        writeTestContent("the)s are no%y6 wo!e4");
        wordMap = occurrence_map(tempFilePath);
        EXPECT_EQ(wordMap["are"], 1);
        EXPECT_EQ(wordMap.size(), 1); // Checking total unique valid words, should only be "are"
    }

}