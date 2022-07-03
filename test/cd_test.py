import os
import sys
from utils.run_test import run_cmp
from utils.destroy import destroy_and_exit
from utils.compile import compile
from colorama import Fore, Style

__BUILTINS_FOLDER__ = os.path.join("builtins")
__CORRESPONDING_SRC__ = os.path.join(__BUILTINS_FOLDER__, "cd.c")

DOES_NOT_EXISTS = "cd : No such file or directory\n" + os.getcwd()

def get_full_path(relative: str) -> str:
	return os.path.abspath(os.path.join(os.getcwd(), relative))

TESTS = [
	{"args": ["..", "test"], "expect": get_full_path(".."), "return_code": 0},
	{"args": ["../../", "test"], "expect": get_full_path("../../"), "return_code": 0},
	{"args": ["../test", "test"], "expect": DOES_NOT_EXISTS, "return_code": 1},
	{"args": ["./", "test"], "expect": get_full_path("./"), "return_code": 0},
	{"args": ["", "test"], "expect": DOES_NOT_EXISTS, "return_code": 1}, 
	# XXX : ^ This test will return to HOME once parsing is updated ^
	{"args": ["doesnotexist", "test"], "expect": DOES_NOT_EXISTS, "return_code": 1},
]

if __name__ == '__main__':
	bin_path = "./" + compile(__CORRESPONDING_SRC__)
	for i, test in enumerate(TESTS):
		command = [bin_path] + test["args"]
		output, return_code, passed = run_cmp(command, test["expect"],
			test["return_code"])
		if not passed:
			print(f"\nTest failed #{i + 1}.\n\tExpected: '{test['expect']}'")
			print(f"\tGot: '{output}'")
			print(f"\tReturn code: {return_code}")
			print(f"\tExpected return code: {test['return_code']}")
	destroy_and_exit(bin_path, 0)