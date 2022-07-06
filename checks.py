import os
import subprocess
from glob import glob
from typing import List, Tuple
from colorama import Fore, Style

SOURCE_FOLDER = ["builtins"]
TESTS_FOLDER = "test/"

CHARACTERS = {
	"p": {"color": Fore.GREEN, "text": "OK"},
	"f": {"color": Fore.RED, "text": "FAIL"},
	"c": {"color": Fore.YELLOW, "text": "CRASH"},
	"?": {"color": Fore.WHITE, "text": "?"}
}

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
	Find all test_*.(c|py) files in the given path.
	"""
	return glob(f"{path}/test_*.c") + glob(f"{path}/test_*.py")

def compile_and_run(test_path: str, sources: List[str], compiler: str = "cc",
	flags: List[str] = ["-Wall", "-Werror", "-Wextra"]) -> str:
	"""
	Compiles and run the test source, with the function source.
	After the execution, the built binary is deleted, and the stdout
	are returned
	:param test_path: Path to a test_xxxx.c file
	:return: Stdout
	"""
	binary_name = os.path.basename(test_path).replace("test_", "").replace(".c", "")
	compile_command = [compiler, "-o", binary_name, *flags, *sources, test_path]
	try:
		subprocess.check_call(compile_command)
	except:
		print(Fore.RED + "Compilation failed : {}".format(" ".join(compile_command)) + Style.RESET_ALL)
		return None
	try:
		output = subprocess.check_output(["./" + binary_name], stderr=subprocess.DEVNULL)
	except:
		output = "c"
	finally:
		os.remove(binary_name)
	return output if type(output) == str else output.decode("utf-8").strip()

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

	tests = find_tests()
	for test in tests:
		print(f"Running test {test}... ", end="")
		if test.endswith(".c"):
			source = os.path.join("builtins", os.path.basename(test).replace("test_", ""))
			test_output = compile_and_run(test, [source])
		else:
			test_output = subprocess.check_output(["python3", test], stderr=subprocess.DEVNULL).decode("utf-8").strip()
		for char in test_output:
			print(CHARACTERS[char]["color"] + char + Style.RESET_ALL, end="")
		print()

	# TODO : Check symbols (nm -Dgu)

	branch = subprocess.check_output(["git", "rev-parse", "--abbrev-ref", "HEAD"]).decode("utf-8").strip()
	print("\n" + "-"*30 + "\n")
	subprocess.check_call(["git", "log", "--oneline", "--decorate", "--graph", "--color", "origin/ja-base..ja-base"])
	if input("Push these commits ? (y/N) ") != "y":
		exit(0)
	subprocess.check_call(["git", "push"])
