var  p1,p2,a,b,l,r:array[0..10000]of longint;
     n,i,k,s,minl,maxr:longint;
   
procedure swap(var x,y:longint);
var z:longint; begin z:=x; x:=y; y:=z; end;
procedure qsort(l,r:longint);
var i,j,x:longint;
begin
  i:=l; j:=r; x:=a[(l+r) div 2];
  while i<=j do 
    begin
      while a[i]>x do inc(i);
      while a[j]<x do dec(j);
      if i<=j then begin swap(a[i],a[j]);  inc(i); dec(j); end;
    end;
  if (i<r)and(i<=k) then qsort(i,r);
  if (l<j)and(j>=k) then qsort(l,j);
end;
procedure check;
var i,x,t,t1:longint;
begin
  inc(s);
  for i:=1 to n do  a[i]:=b[i]; 
  qsort(1,n);
  x:=a[k];
  t:=0; t1:=0;
  //writeln(s,' ',b[1],' ',b[2],' ',b[3],' ',b[4],' ',x);
  for i:=1 to n do 
    if b[i]>x then inc(t1);
  t1:=k-t1;
  for i:=1 to n do
    if b[i]>=x then
      begin
        if b[i]=x then begin  dec(t1); if t1<0 then continue; end;
        inc(t); 
        if t mod 4<=1 then inc(p1[i]) else inc(p2[i]);
        if t=k then exit;
      end;  
end;
procedure dfs(dep:longint);
var  i:longint;
begin
  if dep>n then check
           else for i:=l[dep] to r[dep] do
                 begin
                   b[dep]:=i;
                   dfs(dep+1);
                 end; 
end;
function min(x,y:longint):longint;
begin if x<y then exit(x) else exit(y); end;
function max(x,y:longint):longint;
begin if x>y then exit(x) else exit(y); end;
begin
  assign(input,'assign.in');  reset(input);
  assign(output,'assign.out'); rewrite(output);
  readln(n);
  minl:=maxlongint; maxr:=0;
  for i:=1 to n do begin read(l[i]); minl:=min(minl,l[i]); end;
  for i:=1 to n do begin read(r[i]); maxr:=max(maxr,r[i]); end;
  readln(k);
  dfs(1);
  for i:=1 to n do 
    writeln(p1[i]/s:0:6,' ',p2[i]/s:0:6);
  close(input); close(output);
end.
