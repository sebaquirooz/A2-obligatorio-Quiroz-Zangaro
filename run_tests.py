# para correrlo:
# python test_run.py
# o:
# python3 test_run.py

import os
import subprocess
import time

COMPILADOR = "g++"
FLAGS = ["-std=c++17"]
MAX_EJERCICIOS = 50
POSIBLES_CARPETAS_TEST = ["tests", "test", "Tests", "Test"]

def existe(path):
    return os.path.isfile(path)

def normalizar(s):
    return s.replace("\r\n", "\n").strip()

def compilar(cpp, exe):
    return subprocess.run(
        [COMPILADOR, cpp, "-o", exe] + FLAGS,
        capture_output=True,
        text=True
    )

def ejecutar(exe, entrada):
    try:
        result = subprocess.run(
            [exe],
            input=entrada,
            capture_output=True,
            text=True
        )
        return result.stdout, result.stderr, result.returncode
    except Exception as e:
        return f"__ERROR__{e}", "", -999

def leer(path):
    with open(path, "r", encoding="utf-8") as f:
        return f.read()

def obtener_raiz_tests():
    for carpeta in POSIBLES_CARPETAS_TEST:
        if os.path.isdir(carpeta):
            return carpeta
    return None

def obtener_carpeta_ejercicio(raiz_tests, i):
    candidatos = [
        os.path.join(raiz_tests, f"ejercicio{i}"),
        os.path.join(raiz_tests, f"Ejercicio{i}"),
        os.path.join(raiz_tests, f"ej{i}"),
        os.path.join(raiz_tests, str(i)),
    ]

    for carpeta in candidatos:
        if os.path.isdir(carpeta):
            return carpeta

    return None

def clave_orden(nombre):
    if nombre.isdigit():
        return (0, int(nombre))
    return (1, nombre.lower())

def obtener_tests(carpeta):
    archivos = os.listdir(carpeta)
    archivos_set = set(archivos)
    tests = []

    for f in archivos:
        nombre = f.lower()
        base = None
        out_candidato = None

        if nombre.endswith(".in"):
            base = f[:-3]
            out_candidato = base + ".out"

        elif nombre.endswith(".in.txt"):
            base = f[:-7]
            out_candidato = base + ".out.txt"

        if base is not None:
            in_path = os.path.join(carpeta, f)
            out_path = os.path.join(carpeta, out_candidato)

            if out_candidato in archivos_set and os.path.isfile(out_path):
                tests.append((base, in_path, out_path))

    tests.sort(key=lambda x: clave_orden(x[0]))
    return tests

def correr():
    inicio_total = time.perf_counter()

    print("Carpeta actual:", os.getcwd())

    raiz_tests = obtener_raiz_tests()

    if raiz_tests is None:
        print("❌ No encontré carpeta test/tests en esta ubicación.")
        return

    print("Carpeta de tests encontrada:", raiz_tests)

    total = 0
    ok = 0
    encontrados = 0

    for i in range(6, MAX_EJERCICIOS + 1):
        cpp = f"ejercicio{i}.cpp"
        exe = f"ejercicio{i}.exe" if os.name == "nt" else f"./ejercicio{i}"

        if not existe(cpp):
            continue

        encontrados += 1
        print(f"\n===== EJERCICIO {i} =====")

        carpeta = obtener_carpeta_ejercicio(raiz_tests, i)

        if carpeta is None:
            print(f"⚠ No hay carpeta de tests para ejercicio{i}")
            continue

        tests = obtener_tests(carpeta)

        if not tests:
            print("⚠ No hay tests válidos")
            continue

        inicio_comp = time.perf_counter()
        comp = compilar(cpp, exe)
        tiempo_comp = time.perf_counter() - inicio_comp

        if comp.returncode != 0:
            print("❌ Error compilando")
            print(comp.stderr)
            continue

        print(f"✅ Compiló ({len(tests)} tests) [{tiempo_comp:.3f}s]")
        print("Usando carpeta:", carpeta)

        aprobados = 0

        for idx, (nombre, in_path, out_path) in enumerate(tests, 1):
            entrada = leer(in_path)
            esperado = leer(out_path)

            inicio_test = time.perf_counter()
            salida, stderr, code = ejecutar(exe, entrada)
            tiempo_test = time.perf_counter() - inicio_test

            total += 1

            salida_norm = normalizar(salida)
            esperado_norm = normalizar(esperado)

            if salida_norm == esperado_norm:
                print(f"✅ Test {idx} ({nombre}) [{tiempo_test:.4f}s]")
                ok += 1
                aprobados += 1
            else:
                print(f"❌ Test {idx} ({nombre}) [{tiempo_test:.4f}s]")
                print("Esperado:", esperado_norm)
                print("Obtenido:", salida_norm if salida_norm else "[vacío]")
                if stderr.strip():
                    print("Error:", stderr.strip())
                if code != 0:
                    print("Código de salida:", code)

        print(f"Resultado ejercicio {i}: {aprobados}/{len(tests)}")

    if encontrados == 0:
        print("❌ No encontré archivos ejercicioX.cpp")

    tiempo_total = time.perf_counter() - inicio_total

    print("\n======================")
    print(f"FINAL: {ok}/{total} tests OK")
    print(f"TIEMPO TOTAL: {tiempo_total:.3f}s")

if __name__ == "__main__":
    correr()