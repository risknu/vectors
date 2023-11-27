from __future__ import annotations

import ctypes

cpp_library = ctypes.CDLL('./example.so')

cpp_library.Vector2_new.argtypes = [ctypes.c_float, ctypes.c_float]
cpp_library.Vector2_new.restype = ctypes.POINTER(ctypes.c_void_p)

cpp_library.Vector2_to_list.restype = ctypes.POINTER(ctypes.c_float * 2)

class Vector2:
    def __init__(self, x: float = 0.0, y: float = 0.0):
        self.object = cpp_library.Vector2_new(x, y)

    def to_list(self):
        c_float_array_pointer = cpp_library.Vector2_to_list(self.object)
        float_array = list(c_float_array_pointer.contents)
        return float_array

    def __del__(self):
        cpp_library.Vector2_free(self.object)
