for ((i=1;i<=20;i++));do
echo $i
time ./std < draw$i".in" > tmp".out"
diff -b tmp.out draw$i.out
done
