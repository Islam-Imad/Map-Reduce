#!/bin/bash

# Comprehensive test runner for MapReduce implementations
# Usage: ./run_all_tests.sh

echo "=== MapReduce Implementation Test Suite ==="
echo

# Test cases: operation and input files
declare -a TEST_CASES=(
    "wordcount samples/word_count_1.txt"
    "wordcount samples/word_count_2.txt"
    "wordcount samples/word_count_3.txt"
    "numbersum samples/numbers_sum.txt"
    "departmax samples/department_max_1.txt"
    "average samples/averages.txt"
)

PASSED=0
FAILED=0
TOTAL=0

for test_case in "${TEST_CASES[@]}"; do
    TOTAL=$((TOTAL + 1))
    echo "=== Test Case $TOTAL: $test_case ==="
    
    # Check if input files exist
    operation=$(echo $test_case | cut -d' ' -f1)
    files=$(echo $test_case | cut -d' ' -f2-)
    
    # Check if all files exist
    all_files_exist=true
    for file in $files; do
        if [ ! -f "$file" ]; then
            echo "⚠️  SKIPPED: Input file $file does not exist"
            all_files_exist=false
            break
        fi
    done
    
    if [ "$all_files_exist" = false ]; then
        echo
        continue
    fi
    
    # Run the test
    if ./test_comparison.sh $test_case > /tmp/test_output_$TOTAL.log 2>&1; then
        echo "✅ PASSED"
        PASSED=$((PASSED + 1))
    else
        echo "❌ FAILED"
        FAILED=$((FAILED + 1))
        echo "Error details:"
        cat /tmp/test_output_$TOTAL.log | tail -10
    fi
    echo
done

echo "=== Test Summary ==="
echo "Total tests: $TOTAL"
echo "Passed: $PASSED"
echo "Failed: $FAILED"

if [ $FAILED -eq 0 ]; then
    echo "🎉 All tests passed!"
    exit 0
else
    echo "💥 Some tests failed!"
    exit 1
fi
