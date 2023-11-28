#include "../include/vectors.h"
#include <iostream>
#include <cmath>

// Constructor to initialize the Vector2 object with x and y components
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// Returns a dynamically allocated array representing the vector [x, y]
float* Vector2::to_list() const {
    float* float_array = new float[2];
    float_array[0] = x;
    float_array[1] = y;
    return float_array;
}

// Calculates the magnitude (length) of the vector
float Vector2::magnitude() const {
    double x_degree = std::pow(x, 2);
    double y_degree = std::pow(y, 2);
    float result_sqrt = std::sqrt(static_cast<float>(x_degree + y_degree));
    return result_sqrt;
}

// Returns a dynamically allocated array representing the normalized vector
float* Vector2::normalized() const {
    float* float_array = new float[2];
    float mag = magnitude();
    if (mag == 0) {
        float_array[0] = 0;
        float_array[1] = 0;
        return float_array;
    }
    float_array[0] = x / mag;
    float_array[1] = y / mag;
    return float_array;
}

// Calculates the dot product between two Vector2 objects a and b
float Vector2::dot(const Vector2& a, const Vector2& b) const {
    return a.x * b.x + a.y * b.y;
}

// Calculates the angle (in radians) between two Vector2 objects a and b
float Vector2::angle(const Vector2& a, const Vector2& b) const {
    float dot_product = dot(a, b);
    float magnitude_a = a.magnitude();
    float magnitude_b = b.magnitude();
    if (magnitude_a == 0 || magnitude_b == 0) {
        return 0.0f;
    }
    float cosine_angle = dot_product / (magnitude_a * magnitude_b);
    return std::acos(std::max(-1.0f, std::min(1.0f, cosine_angle)));
}

// Getter function for the x component of the vector
float Vector2::get_x() const {
    return x;
}

// Getter function for the y component of the vector
float Vector2::get_y() const {
    return y;
}

// C interface for the Vector2 class

// Creates a new Vector2 instance with the given x and y components
extern "C" {
    Vector2* Vector2_new(float x, float y) {
        return new Vector2(x, y);
    }

    // Converts a Vector2 object to a dynamically allocated array [x, y]
    float* Vector2_to_list(const Vector2* object) {
        return object->to_list();
    }

    // Calculates the magnitude of a Vector2 object
    float Vector2_magnitude(const Vector2* object) {
        return object->magnitude();
    }

    // Returns a dynamically allocated array representing the normalized Vector2 object
    float* Vector2_normalized(const Vector2* object) {
        return object->normalized();
    }

    // Calculates the dot product between a Vector2 object and two vectors a and b
    float Vector2_dot(const Vector2* object, const Vector2& a, const Vector2& b) {
        return object->dot(a, b);
    }

    // Calculates the angle (in radians) between a Vector2 object and two vectors a and b
    float Vector2_angle(const Vector2* object, const Vector2& a, const Vector2& b) {
        return object->angle(a, b);
    }

    // Getter function for the x component of a Vector2 object
    float Vector2_get_x(const Vector2* object) {
        return object->get_x();
    }

    // Getter function for the y component of a Vector2 object
    float Vector2_get_y(const Vector2* object) {
        return object->get_y();
    }

    // Frees the memory allocated for a Vector2 object
    void Vector2_free(Vector2* object) {
        delete object;
    }
}
