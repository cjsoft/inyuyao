const
	mo:longint=1000000007;
	
var
	n,x,a0,b0,c0,i:longint;
	A,B,C,step:array[0..5000005]of int64;
	m,ans:int64;

function myrand:longint;
begin
	x:=(int64(x)*a0+b0) mod c0;
	exit(x);
end;

procedure swap(var a,b:int64);
var
	tmp:int64;
begin
	tmp:=a;
	a:=b;
	b:=tmp;
end;

procedure init;
begin
	read(n,x,a0,b0,c0);
	B[0]:=0;for i:=1 to (n+1) div 2 do B[i]:=B[i-1]+myrand+5;
	m:=B[(n+1) div 2]*2+1;
	for i:=1 to (n-(n+1) div 2) do C[i]:=m-((myrand mod (B[i]-B[i-1]-1))+B[i-1]+1);
	for i:=1 to (n-(n+1) div 2) div 2 do swap(C[i],C[(n-((n+1) div 2))-i+1]);
	for i:=1 to (n+1) div 2 do A[i]:=B[i];
	for i:=1 to (n-(n+1) div 2) do A[i+((n+1) div 2)]:=C[i];
end;

function max(a,b:int64):int64;
begin
	if a>b then exit(a);
	exit(b);
end;

procedure dfs(x:longint);
var
	i:longint;
	mx:int64;
begin
	if x>n then
	begin
		mx:=0;
		for i:=1 to n do mx:=max(mx,step[i]);
		ans:=(ans+mx) mod mo;
		exit;
	end;
	step[x]:=A[x];dfs(x+1);
	step[x]:=m-A[x];dfs(x+1);
end;

begin
	init;
	ans:=0;
	dfs(1);
	writeln(ans);
end.