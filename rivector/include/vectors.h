#ifndef VECTOR2_H
#define VECTOR2_H

// Class representing a 2D vector
class Vector2 {
    public:
        // Constructor to initialize the vector with x and y components
        Vector2(float x, float y);

        // Set x and y components of an existing Vector2.
        void set(float new_X, float new_Y) const;

        // Returns true if the given vector is exactly equal to this vector
        bool equals(Vector2& b) const;

        // Returns a copy of vector with its magnitude clamped to maxLength
        float* clamp_magnitude(float max_length) const;

        // Returns the distance between a and b
        float distance(Vector2& b) const;

        // Linearly interpolates between vectors a and b by t
        float* lerp_unclamped(Vector2& a, Vector2& b, float t) const;

        // Returns a vector that is made from the largest components of two vectors
        float* max(Vector2& a, Vector2& b) const;

        // Returns a vector that is made from the smallest components of two vector
        float* min(Vector2& a, Vector2& b) const;

        // Returns the 2D vector perpendicular to this 2D vector. The result is always rotated 90-degrees in a counter-clockwise direction for a 2D coordinate system where the positive Y axis goes up
        float* perpendicular(Vector2& a) const;

        // Reflects a vector off the vector defined by a normal
        float* reflect(Vector2& a, Vector2& b) const;

        // Gets the signed angle in degrees between from and to
        float signed_angle(Vector2& a, Vector2& b) const;

        // Multiplies two vectors component-wise.
        float* scale(Vector2& a, float scale) const;

        // Gradually changes a vector towards a desired goal over time
        float* smooth_damp(Vector2& a, Vector2& b, Vector2& c, float smooth_time, float max_speed, float delta_time) const;

        // Moves a point current towards target
        float* move_towards(Vector2& a, Vector2& b, float max_distance_delta) const;

        // Returns a dynamically allocated array representing the vector [x, y]
        float* to_list() const;

        // Calculates the sqr magnitude (length) of the vector
        float sqrmagnitude() const;

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

    // Set x and y components of an existing Vector2.
    void Vector2_set(const Vector2* object, float new_X, float new_Y);

    // Returns true if the given vector is exactly equal to this vector
    bool Vector2_equals(const Vector2* object, Vector2& b);

    // Returns a copy of vector with its magnitude clamped to maxLength
    float* Vector2_clamp_magnitude(const Vector2* object, float max_length);

    // Returns the distance between a and b
    float Vector2_distance(const Vector2* object, Vector2& b);

    // Linearly interpolates between vectors a and b by t
    float* Vector2_lerp_unclamped(const Vector2* object, Vector2& a, Vector2& b, float t);

    // Returns a vector that is made from the largest components of two vectors
    float* Vector2_max(const Vector2* object, Vector2& a, Vector2& b);

    // Returns a vector that is made from the smallest components of two vector
    float* Vector2_min(const Vector2* object, Vector2& a, Vector2& b);

    // Returns the 2D vector perpendicular to this 2D vector. The result is always rotated 90-degrees in a counter-clockwise direction for a 2D coordinate system where the positive Y axis goes up
    float* Vector2_perpendicular(const Vector2* object, Vector2& a);

    // Moves a point current towards target
    float* Vector2_move_towards(const Vector2* object, Vector2& a, Vector2& b, float max_distance_delta);

    // Reflects a vector off the vector defined by a normal
    float* Vector2_reflect(const Vector2* object, Vector2& a, Vector2& b);

    // Multiplies two vectors component-wise
    float* Vector2_scale(const Vector2* object, Vector2& a, float scale);

    // Gets the signed angle in degrees between from and to
    float Vector2_signed_angle(const Vector2* object, Vector2& a, Vector2& b);

    // Gets the signed angle in degrees between from and to
    float* Vector2_smooth_damp(const Vector2* object, Vector2& a, Vector2& b, Vector2& c, float smooth_time, float max_speed, float delta_time);

    // Converts a Vector2 object to a dynamically allocated array [x, y]
    float* Vector2_to_list(const Vector2* object);

    // Calculates the  sqr magnitude of a Vector2 object
    float Vector2_sqrmagnitude(const Vector2* object);

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
