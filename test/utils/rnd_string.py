import random
import string

CHARSET = string.ascii_letters + string.digits

def random_string(length: int) -> str:
	"""
	Return a random string of length characters.
	"""
	return "".join(random.choice(CHARSET) for _ in range(length))