for file in mmult*.in
do
    ./mmult < $file > ${file/%in/out} 
done

for file in mmult*.in
do
    diff ${file/%in/ans} ${file/%in/out}
done

rm -rf mmult*.out

