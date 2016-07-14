var
  n,i,k,sum:longint;
  l,r,a,b,oa,ob:array[-10..100100] of longint;

procedure qsort(l,r:longint);
var
  i,j,mid1,mid2,temp:longint;
begin
  i:=l;
  j:=r;
  mid1:=a[b[(l+r) div 2]];
  mid2:=b[(l+r) div 2];
  repeat
	while (a[b[i]]>mid1) or (a[b[i]]=mid1) and (b[i]<mid2) do inc(i);
	while (a[b[j]]<mid1) or (a[b[j]]=mid1) and (b[j]>mid2) do dec(j);
	if i<=j then begin
	  temp:=b[i];
	  b[i]:=b[j];
	  b[j]:=temp;
	  inc(i);
	  dec(j);
	end;
  until i>j;
  if i<r then qsort(i,r);
  if l<j then qsort(l,j);
end;
  
procedure qsort1(l,r:longint);
var
  i,j,mid,temp:longint;
begin
  i:=l;
  j:=r;
  mid:=b[(l+r) div 2];
  repeat
	while b[i]<mid do inc(i);
	while b[j]>mid do dec(j);
	if i<=j then begin
	  temp:=b[i];
	  b[i]:=b[j];
	  b[j]:=temp;
	  inc(i);
	  dec(j);
	end;
  until i>j;
  if i<r then qsort1(i,r);
  if l<j then qsort1(l,j);
end;

procedure dfs(i:longint);
var
  j:longint;
begin
  if i=n+1 then begin
	//for j:=1 to n do write(a[j],' ');writeln;
	inc(sum);
	for j:=1 to n do b[j]:=j;
	qsort(1,n);
	qsort1(1,k);
	//for j:=1 to k do write(b[j],' ');writeln;
	for j:=1 to k do
	  if j mod 4<=1 then inc(oa[b[j]]) else inc(ob[b[j]]);
	//for j:=1 to k do write(oa[j],' ',ob[j],'  ');writeln;
	exit;
  end;
  for j:=l[i] to r[i] do begin
	  a[i]:=j;
      dfs(i+1);
  end;
end;

begin
  assign(input,'assign.in');
  assign(output,'assign.out');
  reset(input);
  rewrite(output);
  readln(n);
  for i:=1 to n do read(l[i]);
  readln;
  for i:=1 to n do read(r[i]);
  readln;
  readln(k);
  sum:=0;
  fillchar(oa,sizeof(oa),0);
  fillchar(ob,sizeof(ob),0);
  dfs(1);
  for i:=1 to n do writeln(oa[i]/sum:0:6,' ',ob[i]/sum:0:6);
  close(input);
  close(output);
end.