from __future__ import annotations

from rivector.errors import MethodArgumentationError

from typing import Union, Any
import ctypes

cpp_library = ctypes.CDLL('rivector/lib/vectors.so')

cpp_library.Vector2_new.argtypes = [ctypes.c_float, ctypes.c_float]
cpp_library.Vector2_new.restype = ctypes.POINTER(ctypes.c_void_p)

cpp_library.Vector2_set.restype = None
cpp_library.Vector2_set.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]

cpp_library.Vector2_to_list.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_sqrmagnitude.restype = ctypes.c_float

cpp_library.Vector2_magnitude.restype = ctypes.c_float

cpp_library.Vector2_normalized.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_dot.restype = ctypes.c_float

cpp_library.Vector2_angle.restype = ctypes.c_float

cpp_library.Vector2_get_x.restype = ctypes.c_float
cpp_library.Vector2_get_y.restype = ctypes.c_float

cpp_library.Vector2_equals.restype = ctypes.c_bool

cpp_library.Vector2_get_y.restype = ctypes.c_float

cpp_library.Vector2_clamp_magnitude.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_distance.restype = ctypes.c_float

cpp_library.Vector2_lerp_unclamped.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_max.restype = ctypes.POINTER(ctypes.c_float * 2)
cpp_library.Vector2_min.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_perpendicular.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_move_towards.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_reflect.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_scale.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_signed_angle.restype = ctypes.c_float

cpp_library.Vector2_smooth_damp.restype = ctypes.POINTER(ctypes.c_float * 2)


class Vector2Wrapper(ctypes.Structure):
    _fields_ = [("x", ctypes.c_float), ("y", ctypes.c_float)]

    def __init__(self, x: float = 0.0, y: float = 0.0):
        self.object = cpp_library.Vector2_new(x, y)

    def set(self, x: float = 0.0, y: float = 0.0) -> None:
        cpp_library.Vector2_set(self.object, x, y)

    def to_list(self) -> list:
        c_float_array_pointer = cpp_library.Vector2_to_list(self.object)
        float_array = list(c_float_array_pointer.contents)
        return float_array
    
    @property
    def sqr_magnitude(self) -> float:
        sqrmagnitude_float = cpp_library.Vector2_sqrmagnitude(self.object)
        return sqrmagnitude_float
    
    @property
    def magnitude(self) -> float:
        magnitude_float = cpp_library.Vector2_magnitude(self.object)
        return magnitude_float

    def normalized(self) -> Vector2Wrapper:
        c_float_array_pointer = cpp_library.Vector2_normalized(self.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    @classmethod
    def dot(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> float:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `dot` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_pointer = cpp_library.Vector2_dot(a.object, a.object, b.object)
        return c_float_pointer
    
    @classmethod
    def angle(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> float:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `angle` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_pointer = cpp_library.Vector2_angle(a.object, a.object, b.object)
        return c_float_pointer
    
    @classmethod
    def equals(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> bool:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `equals` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_pointer = cpp_library.Vector2_equals(a.object, a.object, b.object)
        return c_pointer
    
    def clamp_magnitude(self, max_length: float = 0.0) -> Vector2Wrapper:
        c_float_array_pointer = cpp_library.Vector2_clamp_magnitude(self.object, max_length)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    def distance(self, b: Vector2Wrapper = None) -> float:
        if b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `distance` function, the arguments `b: Vector2Wrapper`, check your code')
        c_pointer = cpp_library.Vector2_distance(self.object, b.object)
        return c_pointer
    
    def lerp_unclamped(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None, t: float = 0.0) -> Vector2Wrapper:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `lerp_unclamped` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_lerp_unclamped(self.object, a.object, b.object, t)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    @classmethod
    def max(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> Vector2Wrapper:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `max` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_max(a.object, a.object, b.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    @classmethod
    def min(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> Vector2Wrapper:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `min` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_min(a.object, a.object, b.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    def perpendicular(self, a: Vector2Wrapper = None) -> Vector2Wrapper:
        if a is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `perpendicular` function, the arguments `a: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_perpendicular(self.object, a.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    def move_towards(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None, max_distance_delta: float = 0.0) -> Vector2Wrapper:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `move_towards` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_move_towards(self.object, a.object, b.object, max_distance_delta)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])

    def reflect(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None) -> Vector2Wrapper:
        if a is None or b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `reflect` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_reflect(self.object, a.object, b.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    def scale(self, a: Vector2Wrapper = None, scale: float = 0.0) -> Vector2Wrapper:
        if a is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `scale` function, the arguments `a: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_scale(self.object, a.object, scale)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    def signed_angle(self, b: Vector2Wrapper = None) -> float:
        if b is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `signed_angle` function, the arguments `b: Vector2Wrapper`, check your code')
        c_pointer = cpp_library.Vector2_signed_angle(self.object, b.object)
        return c_pointer
    
    def smooth_damp(self, a: Vector2Wrapper = None, b: Vector2Wrapper = None, c: Vector2Wrapper = None, smooth_time: float = 0.0, max_speed: float = 0.0, delta_time: float = 0.0) -> Vector2Wrapper:
        if a is None or b is None or c is None:
            raise MethodArgumentationError(
                'It looks like you did not specify the arguments in the `smooth_damp` function, the arguments `a: Vector2Wrapper, b: Vector2Wrapper, c: Vector2Wrapper`, check your code')
        c_float_array_pointer = cpp_library.Vector2_scale(self.object, a.object, b.object, c.object, smooth_time, max_speed, delta_time)
        float_array = list(c_float_array_pointer.contents)
        return Vector2Wrapper(float_array[0], float_array[1])
    
    @property
    def x_coord(self) -> float:
        x_float = cpp_library.Vector2_get_x(self.object)
        return x_float
    
    @property
    def y_coord(self) -> float:
        y_float = cpp_library.Vector2_get_y(self.object)
        return y_float
    
    @property
    def one(self) -> Vector2Wrapper:
        return Vector2Wrapper(1, 1)
    
    @property
    def zero(self) -> Vector2Wrapper:
        return Vector2Wrapper(0, 0)
    
    @property
    def down(self) -> Vector2Wrapper:
        return Vector2Wrapper(0, -1)
    
    @property
    def up(self) -> Vector2Wrapper:
        return Vector2Wrapper(0, 1)
    
    @property
    def left(self) -> Vector2Wrapper:
        return Vector2Wrapper(-1, 0)
    
    @property
    def right(self) -> Vector2Wrapper:
        return Vector2Wrapper(1, 0)
    
    def __add__(self, a: Union[Vector2Wrapper, float, int]) -> Vector2Wrapper:
        if isinstance(a, (int, float)):
            self.set(self.x_coord+a, self.y_coord+a)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        elif isinstance(a, Vector2Wrapper):
            self.set(self.x_coord+a.x_coord, self.y_coord+a.y_coord)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        
    def __contains__(self, a: Union[int, float]) -> bool:
        if a == self.x_coord:
            return True
        elif a == self.y_coord:
            return True
        return False
    
    def __truediv__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (int, float)):
            self.set(self.x_coord/a, self.y_coord/a)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        elif isinstance(a, Vector2Wrapper):
            self.set(self.x_coord/a.x_coord, self.y_coord/a.y_coord)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        
    def __mul__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (int, float)):
            self.set(self.x_coord*a, self.y_coord*a)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        elif isinstance(a, Vector2Wrapper):
            self.set(self.x_coord*a.x_coord, self.y_coord*a.y_coord)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        
    def __neg__(self) -> Vector2Wrapper:
        return Vector2Wrapper(-self.x_coord, -self.y_coord)

    def __sub__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (int, float)):
            self.set(self.x_coord-a, self.y_coord-a)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        elif isinstance(a, Vector2Wrapper):
            self.set(self.x_coord-a.x_coord, self.y_coord-a.y_coord)
            return Vector2Wrapper(self.x_coord, self.y_coord)
        
    def __lt__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a < self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord < self.x_coord and a.y_coord < self.y_coord:
                return True
            return False
        
    def __gt__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a > self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord > self.x_coord and a.y_coord > self.y_coord:
                return True
            return False
        
    def __ge__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a >= self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord >= self.x_coord and a.y_coord >= self.y_coord:
                return True
            return False
        
    def __le__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a <= self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord <= self.x_coord and a.y_coord <= self.y_coord:
                return True
            return False
        
    def __eq__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a == self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord == self.x_coord and a.y_coord == self.y_coord:
                return True
            return False
        
    def __ne__(self, a: Union[int, float, Vector2Wrapper]) -> Vector2Wrapper:
        if isinstance(a, (float, int)):
            if a != self.x_coord+self.y_coord:
                return True
            return False
        elif isinstance(a, Vector2Wrapper):
            if a.x_coord != self.x_coord and a.y_coord != self.y_coord:
                return True
            return False

    def __repr__(self) -> str:
        return f'<Vector2 ({self.x_coord}, {self.y_coord})>'

    def __del__(self) -> None:
        cpp_library.Vector2_free(self.object)
