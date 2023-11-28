from __future__ import annotations


class MethodArgumentationError(Exception):
    def __init__(self, message) -> None:
        super().__init__(message)
        