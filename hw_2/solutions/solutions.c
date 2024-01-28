// solutions.c

#include "solutions.h"

// Function to keep a running total of the arguments it's been called with
int running_total(int number) {
    static int total = 0; // Static variable to hold the running total
    total += number;      // Add the current number to the total
    return total;         // Return the updated total
}


// Function to reverse an array
int* reverse(const int* array, size_t length) {
    int* reversed = (int*) calloc(length, sizeof(int));
    if (reversed == NULL) {
        // Handle allocation failure
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        reversed[i] = array[length - 1 - i];
    }

    return reversed;
}

// Function to reverse an array in place
void reverse_in_place(int* array, size_t length) {
    for (size_t i = 0; i < length / 2; ++i) {
        int temp = array[i];
        array[i] = array[length - 1 - i];
        array[length - 1 - i] = temp;
    }
}

// Function to count the number of occurrences of a value in an array
int num_occurences(const int* array, size_t length, int value) {
    int count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (array[i] == value) {
            ++count;
        }
    }
    return count;
}
