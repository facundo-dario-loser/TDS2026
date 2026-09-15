import os
import subprocess
import sys

TEST_DIR        = "tests"
binary_name     = "c-tds.exe" if os.name == 'nt' else "c-tds"
COMPILER        = os.path.join("build", binary_name)
FLAG_COMPILADOR = sys.argv[1] if len(sys.argv) > 1 else "-debug"

if not os.path.exists(COMPILER):
    print(f"[ERROR] No se encontro el ejecutable en: {COMPILER}")
    sys.exit(1)

if not os.path.exists(TEST_DIR):
    print(f"[ERROR] No existe la carpeta de pruebas: {TEST_DIR}")
    sys.exit(1)

# los programas para testear
test_files = [f for f in os.listdir(TEST_DIR) if f.endswith(".ctds")]

if not test_files:
    print(f"[AVISO] No se encontraron archivos .ctds en la carpeta '{TEST_DIR}'.")
    sys.exit(0)

for file_name in test_files:
    file_path = os.path.join(TEST_DIR, file_name)
    
    print(f"Running: {COMPILER} {FLAG_COMPILADOR} {file_path}")

    result = None

    if FLAG_COMPILADOR == "-o":
        result = subprocess.run([COMPILER, "-o", "a", file_path])
    elif FLAG_COMPILADOR == "-debug":
        result = subprocess.run([COMPILER, "-debug", file_path])
    elif FLAG_COMPILADOR == "-opt":
        print("[TODO]: option -opt no yet implemented")
    elif FLAG_COMPILADOR == "-target":
        print("[TODO]: option -target no yet implemented")
    else:
        print("[ERROR]: invalid flag '" + FLAG_COMPILADOR + "'")

    msg = "program finished successfully" if result.returncode == 0 else "there was an error"
    print("return code: " + str(result.returncode) + " (" + msg + ")")
    
    print("\n")
    print("*" * 40) 
    print("\n")
