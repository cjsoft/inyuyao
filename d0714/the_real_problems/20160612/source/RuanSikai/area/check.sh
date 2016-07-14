g++ mk.cpp -o mk
g++ bf.cpp -o bf -g
g++ area.cpp -o area
while true; do
	./mk
	time ./bf
	time ./area
	if diff -b area.out area.ans
	then echo OK
	else exit 0
	fi
	echo ==============================
done

