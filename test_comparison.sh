#!/bin/bash

# Test comparison script for MapReduce implementations
# Usage: ./test_comparison.sh <operation> <input_files...>

# Check if at least operation is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 <operation> <input_files...>"
    echo "Operations: wordcount, numbersum, departmax, average"
    exit 1
fi

OPERATION=$1
shift  # Remove operation from arguments, rest are input files

# Define output files
CORRECT_OUTPUT="word_count_correct"
USER_OUTPUT="word_count_user"

# Clean up previous outputs
rm -f "$CORRECT_OUTPUT" "$USER_OUTPUT"

echo "=== Running MapReduce Comparison Test ==="
echo "Operation: $OPERATION"
echo "Input files: $@"
echo

# Run the correct implementation (main_cmp)
echo "Running correct implementation (MapReduceCmp)..."
./build/MapReduceCmp "$OPERATION" "$@" > "$CORRECT_OUTPUT" 2>&1
CORRECT_EXIT_CODE=$?

if [ $CORRECT_EXIT_CODE -ne 0 ]; then
    echo "Error: Correct implementation failed with exit code $CORRECT_EXIT_CODE"
    echo "Output from correct implementation:"
    cat "$CORRECT_OUTPUT"
    exit 1
fi

echo "Correct implementation completed successfully."

# Run the user implementation (main)
echo "Running user implementation (MapReduce)..."
./build/MapReduce "$OPERATION" "$@" > "$USER_OUTPUT" 2>&1
USER_EXIT_CODE=$?

if [ $USER_EXIT_CODE -ne 0 ]; then
    echo "Error: User implementation failed with exit code $USER_EXIT_CODE"
    echo "Output from user implementation:"
    cat "$USER_OUTPUT"
    exit 1
fi

echo "User implementation completed successfully."
echo

# Show outputs for comparison
echo "=== Correct Implementation Output ==="
cat "$CORRECT_OUTPUT"
echo
echo "=== User Implementation Output ==="
cat "$USER_OUTPUT"
echo

# Run the Python checker
echo "=== Running Comparison Check ==="
python3 checker.py "$CORRECT_OUTPUT" "$USER_OUTPUT"
CHECKER_EXIT_CODE=$?

echo
if [ $CHECKER_EXIT_CODE -eq 0 ]; then
    echo "✅ TEST PASSED: Outputs match!"
    exit 0
else
    echo "❌ TEST FAILED: Outputs do not match!"
    exit 1
fi
