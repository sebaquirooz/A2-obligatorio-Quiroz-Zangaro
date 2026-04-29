#!/bin/bash

# Uso:
# ./run_tests.sh ejercicio3.cpp tests/ejercicio3

SOURCE_FILE=$1
TEST_DIR=$2
EXECUTABLE="programa_test"
MYOUT="test.myout.txt"

if [ -z "$SOURCE_FILE" ] || [ -z "$TEST_DIR" ]; then
    echo "Uso: ./run_tests.sh archivo.cpp carpeta_tests"
    echo "Ejemplo: ./run_tests.sh ejercicio3.cpp tests/ejercicio3"
    exit 1
fi

echo "Compilando..."
g++ -std=c++11 -o "$EXECUTABLE" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Error de compilación."
    exit 1
fi

echo "Compilación correcta."
echo

for IN_FILE in "$TEST_DIR"/*.in.txt; do
    BASE_NAME=$(basename "$IN_FILE" .in.txt)
    OUT_FILE="$TEST_DIR/$BASE_NAME.out.txt"

    if [ ! -f "$OUT_FILE" ]; then
        echo "No existe archivo esperado para: $IN_FILE"
        continue
    fi

    echo "Probando caso: $BASE_NAME"

    ./"$EXECUTABLE" < "$IN_FILE" > "$MYOUT"

    if diff -q "$MYOUT" "$OUT_FILE" > /dev/null; then
        echo "Correcto"
    else
        echo "Incorrecto"
        echo
        echo "Tu salida:"
        cat "$MYOUT"
        echo
        echo "Salida esperada:"
        cat "$OUT_FILE"
        echo
        echo "Diferencias:"
        diff "$MYOUT" "$OUT_FILE"
    fi

    echo "--------------------------"
done