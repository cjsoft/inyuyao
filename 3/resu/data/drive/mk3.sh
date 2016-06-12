for ((i=1;i<=20;i++));do
echo $i
time ./tle3 < drive$i".in" > tmp".out"
diff tmp.out drive$i".out"
done
