for ((i=1;i<=20;i++));do
echo $i
time ./tle1 < drive$i".in" > tmp".out"
done
