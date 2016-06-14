for /l %%a in (1, 1, 10) do (
	B < B%%a.in > B%%a.ans
)

