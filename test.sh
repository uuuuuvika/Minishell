#!/bin/bash

commands=("ls" "ls -l" "ls -a")

# Directory to test
test_dir="test_dir"

# Create a test directory with some files and directories
mkdir -p $test_dir
touch $test_dir/file1
touch $test_dir/file2
mkdir $test_dir/dir1

# Test each command
for cmd in "${commands[@]}"; do
    # Run the command in bash and save the output
    bash_output=$(bash -c "cd $test_dir && $cmd")
    
    # Run the command in your shell and save the output
    my_shell_output=$(./minishell -c  "cd $test_dir && $cmd")

    # Compare the outputs
    if [ "$bash_output" == "$my_shell_output" ]; then
        echo "Test passed for command: $cmd"
    else
        echo "Test failed for command: $cmd"
        echo "Bash output:"
        echo "$bash_output"
        echo "My shell output:"
        echo "$my_shell_output"
    fi
done

# Clean up the test directory
rm -rf $test_dir
