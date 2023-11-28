from __future__ import annotations

from rivector import Vector2

if __name__ == '__main__':
    vector1 = Vector2(3, 5)
    vector2 = Vector2(5, 15)
    print(vector1.signed_angle(vector1, vector2))