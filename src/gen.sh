parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
echo $parent_path

g++ $parent_path/gen.cpp -O2 -std=c++20 -o $parent_path/gen

mkdir $parent_path/../data

for i in {1..15000}
do
    if (( i % 100 == 0)); then
        echo $i
    fi
    $parent_path//gen $i >$parent_path/../data/$i.in
done
