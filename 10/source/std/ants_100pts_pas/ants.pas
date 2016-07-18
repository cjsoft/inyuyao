const
	mo:longint=1000000007;
	
var
	n,x,a0,b0,c0,i:longint;
	bin:array[0..5000005]of longint;
	A,B,C:array[0..5000005]of int64;
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

function Add(a,b:longint):longint;
begin
	if a+b>=mo then exit(a+b-mo);
	exit(a+b);
end;

procedure Update(i,j:longint);
begin
	if i-j>=0 then ans:=Add(ans,max(A[i],m-A[j]) mod mo*bin[i-j] mod mo);
	if j=i+1 then ans:=Add(ans,max(A[i],m-A[j]) mod mo);
end;

procedure Solve;
var
	i,j:longint;
begin
	bin[0]:=1;for i:=1 to n do bin[i]:=Add(bin[i-1],bin[i-1]);
	i:=1;j:=n;Update(i,j);
	while ((i<n) or (j>1)) do
	begin
		if i<n then
		begin
			if ((j=1)or(A[i+1]<m-A[j-1])) then inc(i)
			else dec(j);
		end
		else dec(j);
		Update(i,j);
	end;
end;

begin
	assign(input,'ants.in');reset(input);
	assign(output,'ants.out');rewrite(output);
	init;
	Solve;
	writeln(ans);
	close(input);close(output);
end.
