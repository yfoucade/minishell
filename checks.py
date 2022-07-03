import subprocess
from glob import glob
from typing import List, Tuple
from colorama import Fore, Style

SOURCE_FOLDER = ["builtins"]
TESTS_FOLDER = "test/"

def find_sources() -> Tuple[List[str], List[str]]:
	"""
	Return a list of .c files found in every folder in SOURCE_FOLDER.
	"""
	c_sources, h_sources = [], []
	for folder in SOURCE_FOLDER:
		c_sources += glob(f"{folder}/*.c")
		h_sources += glob(f"{folder}/*.h")
	return c_sources, h_sources

def find_tests(path: str = TESTS_FOLDER) -> List[str]:
	"""
	Find all *_test.py files in the given path.
	"""
	return glob(f"{path}/*_test.py")

if __name__ == '__main__':
	c_sources, h_sources = find_sources()
	print("Checking norme... ", end="")
	try:
		subprocess.check_call(["norminette"] + c_sources + h_sources, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
		print(Fore.GREEN + "OK!" + Style.RESET_ALL)
	except:
		print(Fore.RED + "KO!" + Style.RESET_ALL)
		if input("Norme failed. Continue anyway? (y/N) ") != "y":
			exit(1)
	
	# TODO : Run tests
	tests = find_tests()
	for test in tests:
		print(f"Running test {test}...", end="")
		try:
			subprocess.check_call(["python3", test])
			print(Fore.GREEN + "OK!" + Style.RESET_ALL)
		except:
			print(Fore.RED + "KO!" + Style.RESET_ALL)
			if input("Test failed. Continue anyway? (y/N) ") != "y":
				exit(1)

	# TODO : Check symbols (nm -Dgu)

	branch = subprocess.check_output(["git", "rev-parse", "--abbrev-ref", "HEAD"]).decode("utf-8").strip()
	print("\n" + "-"*30 + "\n")
	subprocess.check_call(["git", "log", "--oneline", "--decorate", "--graph", "--color", "origin/ja-base..ja-base"])
	if input("Push these commits ? (y/N) ") != "y":
		exit(0)
	subprocess.check_call(["git", "push"])
