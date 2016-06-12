for ((i=1;i<=20;i++));do
echo $i
time ./draw < draw$i".in" > draw$i".out"
done
