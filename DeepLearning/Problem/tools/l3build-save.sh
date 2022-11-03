test_dir="./testfiles";

for path in "$test_dir"/*.lvt; do
    test="$(basename "$path" .lvt)";
    l3build save "$test" || exit 1;
done
