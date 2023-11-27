#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    Vector2(float x, float y);

    float* to_list();

private:
    float x;
    float y;
};

extern "C" {
    Vector2* Vector2_new(float x, float y);

    float* Vector2_to_list(Vector2* object);
    void Vector2_free(Vector2* object);
}

#endif
