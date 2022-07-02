import os

def destroy_and_exit(bin_path: str, code: int):
	if os.path.exists(bin_path):
		os.remove(bin_path)
	else:
		print("The binary does not exist. [{}]".format(bin_path))
	exit(code)