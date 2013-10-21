# Before executing this script, we need to compile source program to list-ex1
while true
do
    sleep 1
    ./test1 > test1.out 
    ./list-ex1 < test1.out
    if [ $? -ne 0 ]; then
        break
    fi
done
