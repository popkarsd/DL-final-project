parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
echo $parent_path

g++ $parent_path/gen.cpp -O2 -std=c++20 -o $parent_path/gen

for i in {1..100}
do
    echo $i
    $parent_path//gen $i >$parent_path/../data/$i.in
done
