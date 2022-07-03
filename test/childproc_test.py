import os
import subprocess
from typing import List
from utils.run_test import run_cmp
from utils.destroy import destroy_and_exit
from utils.compile import compile_multiple
from colorama import Fore, Style

__SRC_FOLDER__ = os.path.join("childproc")
__CORRESPONDING_SRCS__ = [
	os.path.join(__SRC_FOLDER__, "print_open.c"),
	os.path.join(__SRC_FOLDER__, "redir_open.c"),
	os.path.join(__SRC_FOLDER__, "test_main.c"),
]

def run_ls() -> str:
	return subprocess.check_output(["ls"]).decode("utf-8").strip()

# TODO : Improve testing (loops and dicts, rather than hardcoded tests)
if __name__ == '__main__':
	bin_path = "./" + compile_multiple(__CORRESPONDING_SRCS__)
	if subprocess.check_output([bin_path, "stdout"]).decode().strip() == run_ls():
		print(Fore.GREEN + "Test #0 OK!" + Style.RESET_ALL)
	else:
		print(Fore.RED + f"Test #0 failed!" + Style.RESET_ALL)
	subprocess.check_call([bin_path, "test.txt"])
	with open("test.txt") as f:
		if f.read().strip() == run_ls():
			print(Fore.GREEN + "Test #1 OK!" + Style.RESET_ALL)
		else:
			print(Fore.RED + f"Test #1 failed!" + Style.RESET_ALL)
	try:
		os.remove("test.txt")
	except:
		pass
	destroy_and_exit(bin_path, 0)