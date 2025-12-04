g++ gen.cpp -O2 -std=c++20 -o gen

for i in {1..100}
do
    echo $i
    ./gen $i >../data/$i.in
done
