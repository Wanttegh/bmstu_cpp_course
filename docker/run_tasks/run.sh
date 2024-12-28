#!/bin/bash

echo "Running tasks"
pwd
cd bmstu_cpp_course/tasks
#find all exec files and run them
for f in $(find . -type f -executable -name "task_*"); do
    echo "Running $f"
    $f
done