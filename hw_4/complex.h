#ifndef COMPLEX
#define COMPLEX

class Complex {
public:
    Complex(double x = 0.0, double y = 0.0) : re(x), im(y) {}

    double real() const { return re; }
    double imaginary() const { return im; }
    Complex conjugate() const { return Complex(re, -im); }

    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator*(const Complex& a, const Complex& b);
    friend bool operator==(const Complex& a, const Complex& b);

private:
    double re, im;
};

Complex operator+(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
bool operator==(const Complex& a, const Complex& b);

#endif
