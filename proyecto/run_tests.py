import os
import subprocess
import sys

binary_name     = "c-tds.exe" if os.name == 'nt' else "c-tds"
COMPILER        = os.path.join("build", binary_name)
FLAG_COMPILER = sys.argv[1] if len(sys.argv) > 1 else "-debug"
STAGE           = None
TEST_DIR        = None

if FLAG_COMPILER == "-o":
    TEST_DIR = sys.argv[2] if len(sys.argv) > 2 else ""

if FLAG_COMPILER == "-target":
    STAGE    = sys.argv[2] if len(sys.argv) > 2 else "assembly"
    TEST_DIR = sys.argv[3] if len(sys.argv) > 3 else ""

if FLAG_COMPILER == "-opt":
    pass

if FLAG_COMPILER == "-debug":
    TEST_DIR = sys.argv[2] if len(sys.argv) > 2 else ""

if not os.path.exists(COMPILER):
    print(f"[ERROR_PYTHON_SCRIPT]: couldn't find executable in: {COMPILER}")
    sys.exit(1)

if not os.path.exists(TEST_DIR):
    print(f"[ERROR_PYTHON_SCRIPT]: test folder doesn't exists: {TEST_DIR}")
    sys.exit(1)

test_files = [f for f in os.listdir(TEST_DIR) if f.endswith(".ctds")]

if not test_files:
    print(f"[ERROR_PYTHON_SCRIPT]: couldn't find .ctds files in folder '{TEST_DIR}'.")
    sys.exit(0)

flag_is_debug = (FLAG_COMPILER == "-debug")
tests_passed  = []
tests_failed  = []

for file_name in test_files:
    file_path = os.path.join(TEST_DIR, file_name)
    result    = None

    print("\n")

    if FLAG_COMPILER == "-o":
        print(f"Running: {COMPILER} -debug {file_path}")
        result = subprocess.run([COMPILER, "-o", "a", file_path])
        if (result.returncode == 0): 
            tests_passed.append(file_name)
            print("TEST PASSED")
        else:
            tests_failed.append(file_name)
            print("TEST FAILED")

    elif FLAG_COMPILER == "-debug":
        print(f"Running: {COMPILER} -debug {file_path}")
        result = subprocess.run([COMPILER, "-debug", file_path])
        if (result.returncode == 0): 
            tests_passed.append(file_name)
            print("TEST PASSED")
        else:
            tests_failed.append(file_name)
            print("TEST FAILED")
        print("\n")
        print("*" * 40)

    elif FLAG_COMPILER == "-opt":
        print("[TODO_PYTHON_SCRIPT]: option -opt no yet implemented")

    elif FLAG_COMPILER == "-target":
        print(f"Running: {COMPILER} -debug {file_path}")
        result = subprocess.run([COMPILER, "-target", STAGE, file_path])
        if (result.returncode == 0): 
            tests_passed.append(file_name)
            print("TEST PASSED")
        else:
            tests_failed.append(file_name)
            print("TEST FAILED")

    else:
        print("[ERROR_PYTHON_SCRIPT]: invalid flag '" + FLAG_COMPILER + "'")

print("\n")
print("****SUMMARY****")
print("test folder: " + TEST_DIR)
print("tests that passed: " + str(tests_passed))
print("tests that failed: " + str(tests_failed))
print("*" * 120)
print("\n")

