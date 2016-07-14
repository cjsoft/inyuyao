./mk
echo mk
./1 <1.in >1.out
echo 1
./2 <1.in >2.out
echo 2
diff 1.out 2.out 
