#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor
    Complex() : real(0), imag(0) {}

    // Constructor with real and imaginary parts
    Complex(double real, double imag) : real(real), imag(imag) {}

    // Constructor from string
    Complex(const std::string& s) {
        if (s.empty())
            throw std::invalid_argument("Empty string");

        if (s.find(',') != std::string::npos) {
            // Parse complex number in the form (real, imag)
            std::istringstream iss(s);
            char discard;
            iss >> discard >> real >> discard >> imag >> discard;
        } else if (s.find('>') != std::string::npos) {
            // Parse complex number in the form (magnitude > angle)
            std::istringstream iss(s);
            char discard;
            double magnitude, angle_degrees;
            iss >> discard >> magnitude >> discard >> angle_degrees >> discard;
            double angle_radians = angle_degrees * M_PI / 180.0;
            real = magnitude * cos(angle_radians);
            imag = magnitude * sin(angle_radians);
        } else {
            throw std::invalid_argument("Invalid string format");
        }
    }

    // Getter methods for real and imaginary parts
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Method to calculate magnitude
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // Method to calculate angle in degrees
    double angle() const {
        return atan2(imag, real) * 180.0 / M_PI;
    }

    // Method to calculate complex conjugate
    Complex conjugate() const {
        return Complex(real, -imag);
    }

    // Overloaded addition operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overloaded subtraction operator
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Overloaded multiplication operator
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    // Overloaded division operator
    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        double realPart = (real * other.real + imag * other.imag) / denom;
        double imagPart = (imag * other.real - real * other.imag) / denom;
        return Complex(realPart, imagPart);
    }

    // Method to print the complex number
    void print() const {
        std::cout << "(" << real << ", " << imag << ")" << std::endl;
    }
};

int main() {
    // Test cases
    Complex c1(1, 2);
    Complex c2("(3,4)");

    // Print the complex numbers
    c1.print(); // Output: (1, 2)
    c2.print(); // Output: (3, 4)

    // Print magnitude and angle of c1
    std::cout << "Magnitude of c1: " << c1.magnitude() << std::endl; // Output: Magnitude of c1: 2.23607
    std::cout << "Angle of c1: " << c1.angle() << std::endl; // Output: Angle of c1: 63.4349

    // Perform arithmetic operations and print results
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = c1 * c2;
    Complex c6 = c1 / c2;

    std::cout<<"Addition: ";
    c3.print(); // Output: (4, 6)
    std::cout<<"Subtraction: ";
    c4.print(); // Output: (-2, -2)
    std::cout<<"Multiplication: ";
    c5.print(); // Output: (-5, 10)
    std::cout<<"Division: "; 
    c6.print(); // Output: (0.44, 0.08)

    return 0;
}
