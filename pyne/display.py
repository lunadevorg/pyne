import _pyne

class Window:
	def __init__(self, title: str, width: int, height: int, flags: int = 0) -> None:
		self.__win = _pyne.Window(title, width, height, flags)
