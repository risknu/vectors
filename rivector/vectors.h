#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
    public:
        Vector2(float x, float y);

        float* to_list() const;
        float magnitude() const;
        float* normalized() const;

        float dot(const Vector2& a, const Vector2& b) const;
        float angle(const Vector2& a, const Vector2& b) const;

        float get_x() const;
        float get_y() const;
    private:
        float x;
        float y;
};

extern "C" {
    Vector2* Vector2_new(float x, float y);

    float* Vector2_to_list(const Vector2* object);
    float Vector2_magnitude(const Vector2* object);
    float* Vector2_normalized(const Vector2* object);

    float Vector2_dot(const Vector2* object, const Vector2& a, const Vector2& b);
    float Vector2_angle(const Vector2* object, const Vector2& a, const Vector2& b);

    float Vector2_get_x(const Vector2* object);
    float Vector2_get_y(const Vector2* object);

    void Vector2_free(Vector2* object);
}

#endif
