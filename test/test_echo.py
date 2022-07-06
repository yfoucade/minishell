import os
from utils.compile import compile_multiple
from utils.destroy import destroy_and_exit
from utils.run_test import run_cmp

__MAIN_SRC__ = "utils/mains/echo.c"

EXPECTED_OUTPUTS = [
	"foo bar bletch baz a b\n",
	"mars venus earth saturn a b\n",
	"moon moon sun sun a b\n",
	"abcdef abcdef abcdef abcdef a b\n",
	"0123456 0123456 0123456 0123456 a b\n",
	"salut     ciao a b\n",
	"foo bar bletch baz a b\n",
	"foo bar bletch baz b",
	"mars venus earth saturn b",
	"moon moon sun sun b",
	"abcdef abcdef abcdef abcdef b",
	"0123456 0123456 0123456 0123456 b",
	"0123456 0123456 0123456 b",
	"0123456 0123456 0123456 0123456 b",
]

if __name__ == '__main__':
	if os.getcwd().split("/")[-1] != "test":
		os.chdir("test")
	binary = "./" + compile_multiple([__MAIN_SRC__, "../builtins/echo.c"])
	for i in range(0, len(EXPECTED_OUTPUTS)):
		s, _, passed = run_cmp([binary, str(i + 1)], EXPECTED_OUTPUTS[i], 0)
		print("p" if passed else "f", end="")
	destroy_and_exit(binary, 0)