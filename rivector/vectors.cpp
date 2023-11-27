#include "vectors.h"
#include <iostream>
#include <cmath>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float* Vector2::to_list() const {
    float* float_array = new float[2];
    float_array[0] = x;
    float_array[1] = y;
    return float_array;
}

float Vector2::magnitude() const {
    double x_degree = std::pow(x, 2);
    double y_degree = std::pow(y, 2);
    float result_sqrt = std::sqrt(static_cast<float>(x_degree + y_degree));
    return result_sqrt;
}

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

float Vector2::dot(const Vector2& a, const Vector2& b) const {
    return a.x * b.x + a.y * b.y;
}

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

float Vector2::get_x() const {
    return x;
}

float Vector2::get_y() const {
    return y;
}

extern "C" {
    Vector2* Vector2_new(float x, float y) {
        return new Vector2(x, y);
    }

    float* Vector2_to_list(const Vector2* object) {
        return object->to_list();
    }

    float Vector2_magnitude(const Vector2* object) {
        return object->magnitude();
    }

    float* Vector2_normalized(const Vector2* object) {
        return object->normalized();
    }

    float Vector2_dot(const Vector2* object, const Vector2& a, const Vector2& b) {
        return object->dot(a, b);
    }

    float Vector2_angle(const Vector2* object, const Vector2& a, const Vector2& b) {
        return object->angle(a, b);
    }

    float Vector2_get_x(const Vector2* object) {
        return object->get_x();
    }

    float Vector2_get_y(const Vector2* object) {
        return object->get_y();
    }

    void Vector2_free(Vector2* object) {
        delete object;
    }
}
