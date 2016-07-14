var
  n,m,k,i,j,i1,j1:longint;
  kk,s,ans:int64;
  a:array[-1..51,-1..51] of int64;
  f:array[-1..51,-1..51,-1..51] of int64;

begin
  assign(input,'hero.in');
  assign(output,'hero.out');
  reset(input);
  rewrite(output);
  readln(n,m,kk);
  for i:=1 to n do begin
	for j:=1 to m do read(a[i,j]);
	readln;
  end;
  for i:=1 to m do
	for j:=1 to m do begin
	  if i=j then continue;
	  f[1,i,j]:=a[1,i]+a[1,j];
	end;
  for k:=2 to n do
	for i:=1 to m do
	  for j:=1 to m do begin
		if i=j then continue;
		f[k,i,j]:=-1;
		for i1:=1 to m do
		  for j1:=1 to m do begin
			if i1=j1 then continue;
			s:=f[k-1,i1,j1]+abs(i-i1)*kk+abs(j-j1)*kk;
			if (f[k,i,j]=-1) or (s<f[k,i,j]) then f[k,i,j]:=s;
		  end;
		inc(f[k,i,j],a[k,i]+a[k,j]);
	  end;
  ans:=-1;
  for i:=1 to m do
	for j:=1 to m do begin
	  if i=j then continue;
	  if (ans=-1) or (f[n,i,j]<ans) then ans:=f[n,i,j];
	end;
  writeln(ans);
  close(input);
  close(output);
end.
	  
// f[k,i,j]=min{f[k-1,i1,j1]+k*(abs(i-i1)+abs(j-j1))}+a[i,j]