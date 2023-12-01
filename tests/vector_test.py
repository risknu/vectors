import unittest
import math
from rivector.wrapper import Vector2Wrapper

class Vector2WrapperMethods(unittest.TestCase):
    def setUp(self):
        self.vector = Vector2Wrapper(10, 10)

    def tearDown(self):
        del self.vector

    def test_set(self):
        self.vector.set(15, 20)
        self.assertEqual(self.vector, Vector2Wrapper(15, 20))

    def test_to_list(self):
        self.assertEqual(self.vector.to_list(), [10, 10])

    def test_sqr_magnitude(self):
        self.assertEqual(self.vector.sqr_magnitude, float((10**2) + (10**2)))

    def test_magnitude(self):
        self.assertEqual(f'{self.vector.magnitude:.6f}', f'{math.sqrt((10**2) + (10**2)):.6f}')

    def test_normalized(self):
        mag = math.sqrt((10**2) + (10**2))
        normalized_vector = self.vector.normalized()
        expected_vector = Vector2Wrapper(10 / mag, 10 / mag)
        self.assertEqual(normalized_vector, expected_vector)

    def test_dot(self):
        vector1 = Vector2Wrapper(20, 20)
        self.assertEqual(Vector2Wrapper.dot(self.vector, vector1), 10 * 20 + 10 * 20)

    def test_angle(self):
        vector1 = Vector2Wrapper(221, 24)
        self.assertEqual(Vector2Wrapper.angle(self.vector, vector1), 0.6772247552871704)

    def test_equals(self):
        vector1 = Vector2Wrapper(10, 10)
        self.assertTrue(Vector2Wrapper.equals(self.vector, vector1))
        
    def test_clamp_magnitude(self):
        max_length = 5.0
        clamped_vector = self.vector.clamp_magnitude(max_length)
        expected_vector = Vector2Wrapper(3.535533905029297, 3.535533905029297)
        self.assertEqual(clamped_vector, expected_vector)
        
    def test_distance(self):
        vector1 = Vector2Wrapper(5, 5)
        self.assertEqual(f'{self.vector.distance(vector1):.6f}', f'{math.sqrt(5**2 + 5**2):.6f}')
        
    def test_lerp_unclamped(self):
        vector1 = Vector2Wrapper(20, 20)
        t = 0.5
        lerped_vector = self.vector.lerp_unclamped(self.vector, vector1, t)
        expected_vector = Vector2Wrapper(15, 15)
        self.assertEqual(lerped_vector, expected_vector)

    def test_max(self):
        vector1 = Vector2Wrapper(5, 5)
        max_vector = Vector2Wrapper.max(self.vector, vector1)
        expected_vector = Vector2Wrapper(10, 10)
        self.assertEqual(max_vector, expected_vector)

    def test_min(self):
        vector1 = Vector2Wrapper(15, 15)
        min_vector = Vector2Wrapper.min(self.vector, vector1)
        expected_vector = Vector2Wrapper(10, 10)
        self.assertEqual(min_vector, expected_vector)

    def test_perpendicular(self):
        perpendicular_vector = self.vector.perpendicular(self.vector)
        expected_vector = Vector2Wrapper(-10, 10)
        self.assertEqual(perpendicular_vector, expected_vector)

    def test_move_towards(self):
        vector1 = Vector2Wrapper(15, 15)
        max_distance_delta = 5.0
        moved_vector = self.vector.move_towards(self.vector, vector1, max_distance_delta)
        expected_vector = Vector2Wrapper(13.535533905029297, 13.535533905029297)
        self.assertEqual(moved_vector, expected_vector)

    def test_reflect(self):
        vector1 = Vector2Wrapper(1, 0)
        reflected_vector = self.vector.reflect(self.vector, vector1)
        expected_vector = Vector2Wrapper(-10, 10)
        self.assertEqual(reflected_vector, expected_vector)

    def test_scale(self):
        scale_factor = 2.0
        scaled_vector = self.vector.scale(self.vector, scale_factor)
        expected_vector = Vector2Wrapper(20, 20)
        self.assertEqual(scaled_vector, expected_vector)

    def test_signed_angle(self):
        vector1 = Vector2Wrapper(35, 10)
        vector2 = Vector2Wrapper(5, 20)
        self.assertEqual(Vector2Wrapper.signed_angle(self.vector, vector1, vector2), 60.01836013793945)

    def test_properties(self):
        self.assertEqual(self.vector.x_coord, 10)
        self.assertEqual(self.vector.y_coord, 10)
        self.assertEqual(self.vector.one, Vector2Wrapper(1, 1))
        self.assertEqual(self.vector.zero, Vector2Wrapper(0, 0))
        self.assertEqual(self.vector.down, Vector2Wrapper(0, -1))
        self.assertEqual(self.vector.up, Vector2Wrapper(0, 1))
        self.assertEqual(self.vector.left, Vector2Wrapper(-1, 0))
        self.assertEqual(self.vector.right, Vector2Wrapper(1, 0))

if __name__ == '__main__':
    unittest.main()
