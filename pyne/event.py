import _pyne
from typing import Callable

def handler(event_id: int):
    def decorator(func: Callable):
        _pyne.attach_handler(event_id, func)
        return func
    return decorator
