import subprocess
from typing import Tuple, List

def run_raw(args: List[str]) -> Tuple[str, int]:
	"""
	Run a binary and return the output (stdout + stderr) and the return code.
	"""
	process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	output, error = process.communicate()
	return output.decode("utf-8"), process.returncode

def run_cmp(args: List[str], expected: str,
		expected_return_code: int) -> Tuple[str, int, bool]:
	"""
	Run a binary and compare the output with the expected output.
	Return the output, return code and a boolean indicating if the test passed.
	"""
	output, return_code = run_raw(args)
	return (output,
		return_code, return_code == expected_return_code and output == expected)