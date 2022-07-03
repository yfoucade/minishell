import os
from typing import List
from utils.run_test import run_cmp
from utils.destroy import destroy_and_exit
from utils.compile import compile
from colorama import Fore, Style

__BUILTINS_FOLDER__ = os.path.join("builtins")
__CORRESPONDING_SRC__ = os.path.join(__BUILTINS_FOLDER__, "env.c")

# Print the environment variables
expected = ""
for key in os.environ.keys():
	expected += key + "=" + os.environ[key] + "\n"


if __name__ == '__main__':
	bin_path = "./" + compile(__CORRESPONDING_SRC__)
	command = [bin_path]
	output, return_code, passed = run_cmp(command, expected, 0)
	if not passed:
		print(f"\nTest failed #{i + 1}.\n\tExpected: '{expected}'")
		print(f"\tGot: '{output}'")
		print(f"\tReturn code: {return_code}")
		print(f"\tExpected return code: {0}")
	destroy_and_exit(bin_path, 0)