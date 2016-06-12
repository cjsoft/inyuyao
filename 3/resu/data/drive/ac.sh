for ((i=1;i<=20;i++));do
echo $i
time ./foo < drive$i".in" > drive$i".out"
done
