gen 5 > C1.in
gen 19 > C2.in
gen 20 > C3.in
gen 99 > C4.in
gen 100 > C5.in
gen 999 > C6.in
gen 1000 > C7.in
gen 99999 > C8.in
gen 100000 0 > C9.in
gen 100000 1 > C10.in
for /l %%a in (1, 1, 10) do (
	C < C%%a.in > C%%a.ans
)

