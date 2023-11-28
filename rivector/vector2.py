from __future__ import annotations

from rivector.wrapper import Vector2Wrapper
from rivector.abstract import VectorAbstractClass


class Vector2(Vector2Wrapper):
    def __init__(self, x: float = 0, y: float = 0):
        super().__init__(x, y)

    def __repr__(self) -> str:
        return f'<Vector2 ({self.x_coord}, {self.y_coord})>'
