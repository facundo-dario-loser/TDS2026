import os
import subprocess
import sys

binary_name     = "c-tds.exe" if os.name == 'nt' else "c-tds"
COMPILER        = os.path.join("build", binary_name)
FLAG_COMPILADOR = sys.argv[1] if len(sys.argv) > 1 else "-debug"
STAGE           = None
TEST_DIR        = None

if FLAG_COMPILADOR == "-o":
    TEST_DIR = sys.argv[2] if len(sys.argv) > 2 else "tests"

if FLAG_COMPILADOR == "-target":
    STAGE    = sys.argv[2] if len(sys.argv) > 2 else "assembly"
    TEST_DIR = sys.argv[3] if len(sys.argv) > 3 else "tests" # por defecto el folder es /tests

if FLAG_COMPILADOR == "-opt":
    pass

if FLAG_COMPILADOR == "-debug":
    TEST_DIR = sys.argv[2] if len(sys.argv) > 2 else "tests" # por defecto el folder es /tests


if not os.path.exists(COMPILER):
    print(f"[ERROR_PYTHON_SCRIPT]: couldn't find executable in: {COMPILER}")
    sys.exit(1)

if not os.path.exists(TEST_DIR):
    print(f"[ERROR_PYTHON_SCRIPT]: test folder doesn't exists: {TEST_DIR}")
    sys.exit(1)

# los programas para testear
test_files = [f for f in os.listdir(TEST_DIR) if f.endswith(".ctds")]

if not test_files:
    print(f"[ERROR_PYTHON_SCRIPT]: couldn't find .ctds files in folder '{TEST_DIR}'.")
    sys.exit(0)

for file_name in test_files:
    file_path = os.path.join(TEST_DIR, file_name)
    result    = None

    print("\n")

    if FLAG_COMPILADOR == "-o":
        print(f"Running: {COMPILER} -o a {file_path}")
        result = subprocess.run([COMPILER, "-o", "a", file_path])
    elif FLAG_COMPILADOR == "-debug":
        print(f"Running: {COMPILER} -debug {file_path}")
        result = subprocess.run([COMPILER, "-debug", file_path])
        msg = "TEST PASSED" if result.returncode == 0 else "TEST FAILED"
        print(msg)
        print("\n")
        print("*" * 40)
    elif FLAG_COMPILADOR == "-opt":
        print("[TODO]: option -opt no yet implemented")
    elif FLAG_COMPILADOR == "-target":
        print(f"Running: {COMPILER} -target {STAGE} {file_path}")
        result = subprocess.run([COMPILER, "-target", STAGE, file_path])
    else:
        print("[ERROR]: invalid flag '" + FLAG_COMPILADOR + "'")

