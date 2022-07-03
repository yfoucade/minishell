import os
import random
import string
from typing import List
from utils.run_test import run_cmp
from utils.destroy import destroy_and_exit
from utils.compile import compile
from colorama import Fore, Style

__BUILTINS_FOLDER__ = os.path.join("builtins")
__CORRESPONDING_SRC__ = os.path.join(__BUILTINS_FOLDER__, "echo.c")

OUTPUT = ""
RND_STR = lambda n: ''.join(random.choice(string.ascii_letters) for i in range(n))

def get_full_path(relative: str) -> str:
	return os.path.abspath(os.path.join(os.getcwd(), relative))

TESTS = []

def create_test(args: List[str], expect: str, expect_return_code: int):
	TESTS.append({"args": args, "expect": expect, "return_code": expect_return_code})

def init_tests():
	s = RND_STR(10)
	create_test(args=[s], expect=s + "\n", expect_return_code=0)
	create_test(args=["-n", s], expect=s, expect_return_code=0)
	create_test(args=["-n", "-n", "-nnnnnnnnnnn", s], expect=s, expect_return_code=0)
	create_test(args=["-n", "-n", "-n", s], expect=s, expect_return_code=0)
	create_test(args=["-nnnnnnn", s], expect=s, expect_return_code=0)
	s = RND_STR(2000)
	create_test(args=[s], expect=s + "\n", expect_return_code=0)
	create_test(args=["-n", "-n", "-n", s], expect=s, expect_return_code=0)
	create_test(args=["-nnnnnnn", s], expect=s, expect_return_code=0)
	create_test(args=["-N", "-n", "-n", s], expect="-N -n -n " + s + "\n", expect_return_code=0)

if __name__ == '__main__':
	init_tests()
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