testcases_dir="./testcases"

# Loop through numbers 5 to 9
for a in {5..9}; do
    echo "------------------ $a"
    py.exe GeneradorAzar.py <<< "$a"

    # Iterate through each folder in the testcases directory
    for folder in "$testcases_dir"/*; do
        if [ -d "$folder" ]; then
            last_folder=$(basename "$folder")

            # Run the main program using the test.txt file in the folder
            ./main < "$folder/test.txt"
            echo ""
        fi
    done

done
