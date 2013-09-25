while true
do
    sleep 1
    ./test1 > test1.out 
    ./ex1 < test1.out
    if [ $? -ne 0 ]; then
        break
    fi
done
