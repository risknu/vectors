#include "vectors.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}


float* Vector2::to_list() {
    float* float_array = new float[2];
    float_array[0] = x;
    float_array[1] = y;
    return float_array;
}

extern "C" {
    Vector2* Vector2_new(float x, float y) {
        return new Vector2(x, y);
    }

    float* Vector2_to_list(Vector2* object) {
        return object->to_list();
    }

    void Vector2_free(Vector2* object) {
        delete object;
    }
}
