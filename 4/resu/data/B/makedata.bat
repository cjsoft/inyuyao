gen 5 > B1.in
gen 49 > B2.in
gen 50 > B3.in
gen 80000 > B4.in
gen 90000 > B5.in
gen 99999 > B6.in
gen 100000 0 > B7.in
gen 100000 1 > B8.in
gen 100000 2 > B9.in
gen 100000 3 > B10.in
for /l %%a in (1, 1, 10) do (
	B < B%%a.in > B%%a.ans
)

