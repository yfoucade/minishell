import subprocess
import os
from utils.rnd_string import random_string
from typing import List

CC = "cc"
FLAGS = ["-Wall", "-Wextra", "-Werror"]

def compile(src: str, output_path: str = random_string(12)) -> str:
	"""
	Compile a C file and return the name of the executable.
	Returns None if compilation failed.
	"""
	try:
		subprocess.check_call([CC, *FLAGS, src, "-o", output_path])
	except:
		return None
	return output_path

def compile_multiple(srcs: List[str], output_path: str = random_string(12)) -> str:
	"""
	Compile multiple C files and return the name of the executable.
	Returns None if compilation failed.
	"""
	try:
		subprocess.check_call([CC, *FLAGS, *srcs, "-o", output_path])
	except:
		return None
	return output_path