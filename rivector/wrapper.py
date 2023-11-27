from __future__ import annotations
import ctypes

cpp_library = ctypes.CDLL('./example.so')

cpp_library.Vector2_new.argtypes = [ctypes.c_float, ctypes.c_float]
cpp_library.Vector2_new.restype = ctypes.POINTER(ctypes.c_void_p)

cpp_library.Vector2_to_list.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_magnitude.restype = ctypes.c_float

cpp_library.Vector2_normalized.restype = ctypes.POINTER(ctypes.c_float * 2)

cpp_library.Vector2_dot.restype = ctypes.c_float

cpp_library.Vector2_angle.restype = ctypes.c_float

cpp_library.Vector2_get_x.restype = ctypes.c_float
cpp_library.Vector2_get_y.restype = ctypes.c_float

class Vector2(ctypes.Structure):
    _fields_ = [("x", ctypes.c_float), ("y", ctypes.c_float)]

    def __init__(self, x: float = 0.0, y: float = 0.0):
        self.object = cpp_library.Vector2_new(x, y)

    def to_list(self) -> list:
        c_float_array_pointer = cpp_library.Vector2_to_list(self.object)
        float_array = list(c_float_array_pointer.contents)
        return float_array
    
    def magnitude(self) -> float:
        magnitude_float = cpp_library.Vector2_magnitude(self.object)
        return magnitude_float

    def normalized(self) -> Vector2:
        c_float_array_pointer = cpp_library.Vector2_normalized(self.object)
        float_array = list(c_float_array_pointer.contents)
        return Vector2(float_array[0], float_array[1])
    
    def dot(self, a: Vector2 = None, b: Vector2 = None) -> float:
        if a is None or b is None:
            return
        c_float_pointer = cpp_library.Vector2_dot(self.object, a.object, b.object)
        return c_float_pointer
    
    def angle(self, a: Vector2 = None, b: Vector2 = None) -> float:
        if a is None or b is None:
            return
        c_float_pointer = cpp_library.Vector2_angle(self.object, a.object, b.object)
        return c_float_pointer
    
    @property
    def x_coord(self) -> float:
        x_float = cpp_library.Vector2_get_x(self.object)
        return x_float
    
    @property
    def y_coord(self) -> float:
        y_float = cpp_library.Vector2_get_y(self.object)
        return y_float
    
    @property
    def one(self) -> Vector2:
        return Vector2(1, 1)
    
    @property
    def zero(self) -> Vector2:
        return Vector2(0, 0)
    
    @property
    def down(self) -> Vector2:
        return Vector2(0, -1)
    
    @property
    def up(self) -> Vector2:
        return Vector2(0, 1)
    
    @property
    def left(self) -> Vector2:
        return Vector2(-1, 0)
    
    @property
    def right(self) -> Vector2:
        return Vector2(1, 0)

    def __del__(self) -> None:
        cpp_library.Vector2_free(self.object)

    def __repr__(self) -> str:
        return f'<Vector2 ({self.x_coord}, {self.y_coord})>'
