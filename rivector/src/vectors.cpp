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
        return new float[2]{0, 0};
    }
    return new float[2]{x / mag * max_length, y / mag * max_length};
}

// Returns the distance between a and b
float Vector2::distance(Vector2& b) const {
    float dx = x - b.x;
    float dy = y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Linearly interpolates between vectors a and b by t
float* Vector2::lerp_unclamped(Vector2& a, Vector2& b, float t) const {
    return new float[2]{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

// Returns a vector that is made from the largest components of two vectors
float* Vector2::max(Vector2& a, Vector2& b) const {
    float* result = new float[2];
    result[0] = (a.x > b.x) ? a.x : b.x;
    result[1] = (a.y > b.y) ? a.y : b.y;
    return result;
}

// Returns a vector that is made from the smallest components of two vector
float* Vector2::min(Vector2& a, Vector2& b) const {
    float* result = new float[2];
    result[0] = (a.x < b.x) ? a.x : b.x;
    result[1] = (a.y < b.y) ? a.y : b.y;
    return result;
}

// Returns the 2D vector perpendicular to this 2D vector. The result is always rotated 90-degrees in a counter-clockwise direction for a 2D coordinate system where the positive Y axis goes up
float* Vector2::perpendicular(Vector2& a) const {
    return new float[2]{-a.y, a.x};
}

// Moves a point current towards target
float* Vector2::move_towards(Vector2& a, Vector2& b, float max_distance_delta) const {
    float to_vector[2] = {b.x - a.x, b.y - a.y};
    float distance = std::hypot(to_vector[0], to_vector[1]);

    if (distance <= max_distance_delta || distance == 0) {
        return new float[2]{b.x, b.y};
    }

    return new float[2]{a.x + to_vector[0] / distance * max_distance_delta, a.y + to_vector[1] / distance * max_distance_delta};
}

// Reflects a vector off the vector defined by a normal
float* Vector2::reflect(Vector2& a, Vector2& b) const {
    float dot = 2 * (a.x * b.x + a.y * b.y);
    return new float[2]{a.x - dot * b.x, a.y - dot * b.y};
}

// Multiplies two vectors component-wise
float* Vector2::scale(Vector2& a, float scale) const {
    return new float[2]{a.x * scale, a.y * scale};
}

// Gets the signed angle in degrees between from and to
float Vector2::signed_angle(Vector2& a, Vector2& b) const {
    if (a.x == 0 && a.y == 0) return 0.0f;
    if (b.x == 0 && b.y == 0) return 0.0f;

    float angle = std::atan2(b.y, b.x) - std::atan2(a.y, a.x);
    angle = std::fmod((angle + M_PI), (2 * M_PI)) - M_PI;
    return angle * (180.0f / M_PI);
}

// Gets the signed angle in degrees between from and to
float* Vector2::smooth_damp(Vector2& a, Vector2& b, Vector2& c, float smooth_time, float max_speed, float delta_time) const {
    smooth_time = std::max(0.0001f, smooth_time);
    float omega = 2.0f / smooth_time;
    float x = omega * delta_time;
    float exp_x = 1.0f / (1.0f + std::exp(-x));

    float change[2] = {b.x - a.x * omega, b.y - a.y * omega};
    float velocity[2] = {c.x * exp_x, c.y * exp_x};
    return new float[2]{a.x + velocity[0] + change[0] * (1.0f - exp_x), a.y + velocity[1] + change[1] * (1.0f - exp_x)};
}

// Returns a dynamically allocated array representing the vector [x, y]
float* Vector2::to_list() const {
    return new float[2]{x, y};
}

// Calculates the sqr magnitude (length) of the vector
float Vector2::sqrmagnitude() const {
    return x * x + y * y;
}

// Calculates the magnitude (length) of the vector
float Vector2::magnitude() const {
    return std::hypot(x, y);
}

// Returns a dynamically allocated array representing the normalized vector
float* Vector2::normalized() const {
    float mag = magnitude();
    if (mag == 0) {
        return new float[2]{0, 0};
    }
    return new float[2]{x / mag, y / mag};
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
