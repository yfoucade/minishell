import os
from typing import List
from utils.run_test import run_cmp
from utils.destroy import destroy_and_exit
from utils.compile import compile
from colorama import Fore, Style

__BUILTINS_FOLDER__ = os.path.join("builtins")
__CORRESPONDING_SRC__ = os.path.join(__BUILTINS_FOLDER__, "pwd.c")

def test(path: str, bin_path: str):
	os.chdir(path)
	print(f"{Fore.GREEN}Testing {path}{Style.RESET_ALL}", end="")
	current_directory = os.getcwd()
	expected, return_code, passed = run_cmp(bin_path, current_directory, 0)
	if not passed:
		print(Fore.RED + "Test failed: " + Style.RESET_ALL)
		print("Expected: " + expected)
		print("Return code: " + str(return_code))
		print("Actual: " + current_directory)
	else:
		print(Fore.GREEN + " OK!" + Style.RESET_ALL)

if __name__ == '__main__':
	base = os.getcwd()
	bin_path = compile(__CORRESPONDING_SRC__)
	full_bin_path = os.path.join(base, bin_path)
	test("../", full_bin_path)
	test(os.environ["HOME"], full_bin_path)
	test(os.path.join(base, "test"), full_bin_path)
	test("../", full_bin_path)
	os.chdir(base)
	destroy_and_exit(bin_path, 0)