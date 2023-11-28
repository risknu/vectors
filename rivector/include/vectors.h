#ifndef VECTOR2_H
#define VECTOR2_H

// Class representing a 2D vector
class Vector2 {
    public:
        // Constructor to initialize the vector with x and y components
        Vector2(float x, float y);

        // Returns a dynamically allocated array representing the vector [x, y]
        float* to_list() const;

        // Calculates the magnitude (length) of the vector
        float magnitude() const;

        // Returns a dynamically allocated array representing the normalized vector
        float* normalized() const;

        // Calculates the dot product between two vectors a and b
        float dot(const Vector2& a, const Vector2& b) const;

        // Calculates the angle (in radians) between two vectors a and b
        float angle(const Vector2& a, const Vector2& b) const;

        // Getter function for the x component of the vector
        float get_x() const;

        // Getter function for the y component of the vector
        float get_y() const;

    private:
        // Private variables to store the x and y components of the vector
        float x;
        float y;
};

// C interface for the Vector2 class
extern "C" {
    // Creates a new Vector2 instance with the given x and y components
    Vector2* Vector2_new(float x, float y);

    // Converts a Vector2 object to a dynamically allocated array [x, y]
    float* Vector2_to_list(const Vector2* object);

    // Calculates the magnitude of a Vector2 object
    float Vector2_magnitude(const Vector2* object);

    // Returns a dynamically allocated array representing the normalized Vector2 object
    float* Vector2_normalized(const Vector2* object);

    // Calculates the dot product between a Vector2 object and two vectors a and b
    float Vector2_dot(const Vector2* object, const Vector2& a, const Vector2& b);

    // Calculates the angle (in radians) between a Vector2 object and two vectors a and b
    float Vector2_angle(const Vector2* object, const Vector2& a, const Vector2& b);

    // Getter function for the x component of a Vector2 object
    float Vector2_get_x(const Vector2* object);

    // Getter function for the y component of a Vector2 object
    float Vector2_get_y(const Vector2* object);

    // Frees the memory allocated for a Vector2 object
    void Vector2_free(Vector2* object);
}

#endif
