for i in {1..10}
do
    echo "Batch Test $i"
    ./test.sh
    mv testResult.txt TestResult/result$i.txt
    sleep 10
done
echo "COMPLETE ALL TESTS"
