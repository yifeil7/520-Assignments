#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {


public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);

    // New methods to be declared
    void push(const ElementType& value);
    ElementType pop();
    void push_front(const ElementType& value);
    ElementType pop_front();
    
    //concat method
    TypedArray<ElementType> concat(const TypedArray<ElementType>& other) const;

    // reverse method
    TypedArray<ElementType>& reverse();

    //plus
    TypedArray operator+(const TypedArray& rhs) const;


private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

// Push an element to the end of the TypedArray
template <typename ElementType>
void TypedArray<ElementType>::push(const ElementType& value) {
    set(size(), value); // size() gives the next index where the new item should be placed
}

// Pop an element from the end of the TypedArray
template <typename ElementType>
ElementType TypedArray<ElementType>::pop() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType poppedElement = get(size() - 1);
    end = index_to_offset(size() - 1); // Reduce the size by one
    return poppedElement;
}


// push front
template <typename ElementType>
void TypedArray<ElementType>::push_front(const ElementType& value) {
    if (size() == 0) {
        // Array is empty, so insert the first element in the middle
        set(0, value);
    } else {
        // Check if there's space at the front; if not, extend the buffer
        if (origin == 0) {
            extend_buffer();
            origin = capacity / 2; // Reset origin to the middle of the new buffer
            end = origin + size(); // Adjust end based on new size
        } else {
            origin--; // Decrement origin to add space at the front
        }
        buffer[origin] = value;
    }
}


// Pop an element from the front of the TypedArray
template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }
    ElementType poppedElement = get(0);
    origin = index_to_offset(1); // Move origin forward to remove the first element
    return poppedElement;
}

//concat
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray<ElementType>& other) const {
    TypedArray<ElementType> result;

    // Add elements from the current array
    for (int i = 0; i < this->size(); ++i) {
        result.push(this->safe_get(i));
    }

    // Add elements from the other array
    for (int i = 0; i < other.size(); ++i) {
        result.push(other.safe_get(i));
    }

    return result;
}

//reverse
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {
    int n = this->size();
    for (int i = 0; i < n / 2; ++i) {
        // Correctly calculating the offset for the current and mirror index
        ElementType temp = this->get(i);
        this->set(i, this->get(n - i - 1));
        this->set(n - i - 1, temp);
    }
    return *this;
}

//plus
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& rhs) const {
    TypedArray<ElementType> result;
    // Use this->size() to access the size of the left-hand side TypedArray
    for (int i = 0; i < this->size(); ++i) {
        // Use safe_get for const-safe element access
        result.set(i, this->safe_get(i));
    }
    int thisSize = this->size(); // Store the size of the lhs TypedArray to offset the rhs elements correctly
    for (int i = 0; i < rhs.size(); ++i) {
        // Use rhs.safe_get for const-safe element access on the right-hand side TypedArray
        result.set(thisSize + i, rhs.safe_get(i));
    }
    return result;
}



// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}




#endif