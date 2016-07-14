@echo off
:for
data1
did1
hero
fc hero.out did1.out >nul
if errorlevel=1 (
	set/p=n <nul
	goto end
)
(
	set/p=y <nul
	goto for
)
:end