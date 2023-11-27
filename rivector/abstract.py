from __future__ import annotations

from dataclasses import dataclass
from abc import ABC


@dataclass
class VectorAbstractClass(ABC):
    def __init__(self) -> None:
        super().__init__()
        