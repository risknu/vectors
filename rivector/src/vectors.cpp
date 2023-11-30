#include "../include/vectors.h"
#include <iostream>
#include <cmath>

// Constructor to initialize the Vector2 object with x and y components
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// Set x and y components of an existing Vector2.
void Vector2::set(float new_X, float new_Y) const {
    const_cast<Vector2*>(this)->x = new_X;
    const_cast<Vector2*>(this)->y = new_Y;
}

// Returns true if the given vector is exactly equal to this vector
bool Vector2::equals(Vector2& b) const {
    return x == b.x && y == b.y;
}

// Returns a copy of vector with its magnitude clamped to maxLength
float* Vector2::clamp_magnitude(float max_length) const {
    float mag = magnitude();
    if (mag == 0) {
        float* float_array = new float[2];
        float_array[0] = 0;
        float_array[1] = 0;
        return float_array;
    }
    float* float_array = new float[2];
    float_array[0] = x/mag*max_length;
    float_array[1] = y/mag*max_length;
    return float_array;
}

// Returns the distance between a and b
float Vector2::distance(Vector2& b) const {
    float dx = x - b.x;
    float dy = y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Linearly interpolates between vectors a and b by t
float* Vector2::lerp_unclamped(Vector2& a, Vector2& b, float t) const {
    float* float_array = new float[2];
    float_array[0] = a.x+(b.x-a.x)*t;
    float_array[1] = a.y+(b.y-a.y)*t;
    return float_array;
}

// Returns a vector that is made from the largest components of two vectors
float* Vector2::max(Vector2& a, Vector2& b) const {
    float* float_array = new float[2];
    float_array[0] = std::max(a.x, b.x);
    float_array[1] = std::max(a.y, b.y);
    return float_array;
}

// Returns a vector that is made from the smallest components of two vector
float* Vector2::min(Vector2& a, Vector2& b) const {
    float* float_array = new float[2];
    float_array[0] = std::min(a.x, b.x);
    float_array[1] = std::min(a.y, b.y);
    return float_array;
}

// Returns the 2D vector perpendicular to this 2D vector. The result is always rotated 90-degrees in a counter-clockwise direction for a 2D coordinate system where the positive Y axis goes up
float* Vector2::perpendicular(Vector2& a) const {
    float* float_array = new float[2];
    float_array[0] = -a.y;
    float_array[1] = a.x;
    return float_array;
}

// Moves a point current towards target
float* Vector2::move_towards(Vector2& a, Vector2& b, float max_distance_delta) const {
    float to_vector[2] = { b.x - a.x, b.y - a.y };
    double x_degree = std::pow(to_vector[0], 2);
    double y_degree = std::pow(to_vector[1], 2);
    float distance = std::sqrt(static_cast<float>(x_degree + y_degree));

    if (distance <= max_distance_delta || distance == 0) {
        // If the distance is less than or equal to max_distance_delta, or distance is 0, return the target vector b
        float* float_array = new float[2]{ b.x, b.y };
        return float_array;
    }

    // Move towards the target vector by at most max_distance_delta
    float* float_array = new float[2]{ a.x + to_vector[0] / distance * max_distance_delta, a.y + to_vector[1] / distance * max_distance_delta };
    return float_array;
}

// Reflects a vector off the vector defined by a normal
float* Vector2::reflect(Vector2& a, Vector2& b) const {
    float dot = 2 * (a.x * b.x + a.y * b.y);
    float* float_array = new float[2];
    float_array[0] = a.x - dot * b.x;
    float_array[1] = a.y - dot * b.y;
    return float_array;
}

// Multiplies two vectors component-wise
float* Vector2::scale(Vector2& a, float scale) const {
    float* float_array = new float[2];
    float_array[0] = a.x * scale;
    float_array[1] = a.y * scale;
    return float_array;
}

// Gets the signed angle in degrees between from and to
float Vector2::signed_angle(Vector2& a, Vector2& b) const {
    // Check for zero vectors
        if (a.x == 0 && a.y == 0) return 0.0f;
        if (b.x == 0 && b.y == 0) return 0.0f;

        // Calculate angle
        float angle = std::atan2(b.y, b.x) - std::atan2(a.y, a.x);

        // Normalize angle to the range [-pi, pi]
        angle = std::fmod((angle + M_PI), (2 * M_PI)) - M_PI;

        // Convert to degrees
        return angle * (180.0f / M_PI);
}

// Gets the signed angle in degrees between from and to
float* Vector2::smooth_damp(Vector2& a, Vector2& b, Vector2& c, float smooth_time, float max_speed, float delta_time) const {
    smooth_time = std::max(0.0001f, smooth_time);
    float omega = 2.0f / smooth_time;
    float x = omega * delta_time;
    float exp_x = 1.0f / (1.0f + std::exp(-x));

    float* chnage = new float[2];
    chnage[0] = b.x-a.x*omega;
    chnage[1] = b.y-a.y*omega;

    float* velocity = new float[2];
    velocity[0] = c.x*exp_x;
    velocity[1] = c.y*exp_x;

    float* result = new float[2];
    result[0] = a.x+velocity[0]+chnage[0]*(1.0f-exp_x);
    result[1] = a.y+velocity[1]+chnage[1]*(1.0f-exp_x);
    return result;
}

// Returns a dynamically allocated array representing the vector [x, y]
float* Vector2::to_list() const {
    float* float_array = new float[2];
    float_array[0] = x;
    float_array[1] = y;
    return float_array;
}

// Calculates the sqr magnitude (length) of the vector
float Vector2::sqrmagnitude() const {
    double x_degree = std::pow(x, 2);
    double y_degree = std::pow(y, 2);
    float result_sqr = static_cast<float>(x_degree + y_degree);
    return result_sqr;
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

    // Set x and y components of an existing Vector2.
    void Vector2_set(const Vector2* object, float new_X, float new_Y) {
        return object->set(new_X, new_Y);
    }

    // Converts a Vector2 object to a dynamically allocated array [x, y]
    float* Vector2_to_list(const Vector2* object) {
        return object->to_list();
    }

    // Calculates the sqr magnitude of a Vector2 object
    float Vector2_sqrmagnitude(const Vector2* object) {
        return object->sqrmagnitude();
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

    // Returns true if the given vector is exactly equal to this vector
    bool Vector2_equals(const Vector2* object, Vector2& b) {
        return object->equals(b);
    }

    // Returns a copy of vector with its magnitude clamped to maxLength
    float* Vector2_clamp_magnitude(const Vector2* object, float max_length) {
        return object->clamp_magnitude(max_length);
    }

    // Returns the distance between a and b
    float Vector2_distance(const Vector2* object, Vector2& b) {
        return object->distance(b);
    }

    // Linearly interpolates between vectors a and b by t
    float* Vector2_lerp_unclamped(const Vector2* object, Vector2& a, Vector2& b, float t) {
        return object->lerp_unclamped(a, b, t);
    }

    // Returns a vector that is made from the largest components of two vectors
    float* Vector2_max(const Vector2* object, Vector2& a, Vector2& b) {
        return object->max(a, b);
    }

    // Returns a vector that is made from the smallest components of two vector
    float* Vector2_min(const Vector2* object, Vector2& a, Vector2& b) {
        return object->min(a, b);
    }

    // Returns the 2D vector perpendicular to this 2D vector. The result is always rotated 90-degrees in a counter-clockwise direction for a 2D coordinate system where the positive Y axis goes up
    float* Vector2_perpendicular(const Vector2* object, Vector2& a) {
        return object->perpendicular(a);
    }

    // Moves a point current towards target
    float* Vector2_move_towards(const Vector2* object, Vector2& a, Vector2& b, float max_distance_delta) {
        return object->move_towards(a, b, max_distance_delta);
    }

    // Reflects a vector off the vector defined by a normal
    float* Vector2_reflect(const Vector2* object, Vector2& a, Vector2& b) {
        return object->reflect(a, b);
    }

    // Multiplies two vectors component-wise
    float* Vector2_scale(const Vector2* object, Vector2& a, float scale) {
        return object->scale(a, scale);
    }

    // Gets the signed angle in degrees between from and to
    float Vector2_signed_angle(const Vector2* object, Vector2& a, Vector2& b) {
        return object->signed_angle(a, b);
    }

    // Gets the signed angle in degrees between from and to
    float* Vector2_smooth_damp(const Vector2* object, Vector2& a, Vector2& b, Vector2& c, float smooth_time, float max_speed, float delta_time) {
        return object->smooth_damp(a, b, c, smooth_time, max_speed, delta_time);
    }

    // Frees the memory allocated for a Vector2 object
    void Vector2_free(Vector2* object) {
        delete object;
    }
}
