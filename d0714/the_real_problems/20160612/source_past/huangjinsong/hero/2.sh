./mk
echo mk
./3 <1.in >3.out
echo 3
./2 <1.in >2.out
echo 2
diff 3.out 2.out 
