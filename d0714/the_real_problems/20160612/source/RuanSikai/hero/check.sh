g++ mk.cpp -o mk
g++ bf.cpp -o bf -g
g++ hero.cpp -o hero -g
while true; do
	./mk
	time ./bf
	time ./hero
	if diff -b hero.out hero.ans
	then echo OK
	else exit 0
	fi
	echo ==============================
done

