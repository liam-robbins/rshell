INPUTS=("[ commandTest.cpp ]")

for input in "${INPUTS[@]}"
do
    echo "./commandTest ${input}"
    output=$(./commandTest ${input})
    echo "Output: \"${output}\""
    echo "Input: \"${input}\""
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done