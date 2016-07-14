var
  n,m,i,j,t,p,q,dp,dq:longint;
  c,s:int64;
  x,y:array[1..100000]of int64;
  a,f:array[1..200000]of longint;
  h:array[1..100000]of boolean;

function
  cross(t,i,j:longint):int64;
begin
  exit((x[i]-x[t])*(y[j]-y[t])-(x[j]-x[t])*(y[i]-y[t]));
end;

procedure
  sort(l,r:longint);
var
  i,j,k,p:longint;
begin
  i:=l;j:=r;k:=a[(l+r) div 2];
  repeat
    while cross(t,a[i],k)>0 do inc(i);
    while cross(t,k,a[j])>0 do dec(j);
    if i<=j
    then begin
           p:=a[i];a[i]:=a[j];a[j]:=p;
           inc(i);dec(j);
         end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;

begin
  assign(input,'area.in');reset(input);
  assign(output,'area.out');rewrite(output);
  read(n);t:=1;
  for i:=1 to n do read(x[i],y[i]);
  for i:=2 to n do
    if (y[i]<y[t]) or ((y[i]=y[t]) and (x[i]<x[t]))
    then t:=i;
  for i:=1 to t-1 do a[i]:=i;
  for i:=t+1 to n do a[i-1]:=i;
  sort(1,n-1);m:=1;
  for i:=2 to n-1 do
    if cross(t,a[m],a[i])>0
    then m:=i
    else if abs(x[a[m]]-x[t])+abs(y[a[m]]-y[t])
            >abs(x[a[i]]-x[t])+abs(y[a[i]]-y[t])
         then h[i]:=true
         else begin
                h[m]:=true;
                m:=i;
              end;
  m:=1;f[1]:=t;
  for i:=1 to n-1 do
    begin
      if h[i] then continue;
      while (m>=2) and (cross(f[m-1],f[m],a[i])<=0) do dec(m);
      inc(m);f[m]:=a[i];
    end;
  if m<=2 then m:=0;
  if m=3 then begin s:=cross(f[1],f[2],f[3]);m:=0;end;
  for i:=1 to m do f[m+i]:=f[i];p:=2;j:=3;q:=4;
  for i:=1 to m do
    begin
      while cross(f[i],f[p],f[j])<=cross(f[i],f[p+1],f[j]) do inc(p);
      while cross(f[i],f[j],f[q])<=cross(f[i],f[j],f[q+1]) do inc(q);
      c:=cross(f[i],f[p],f[j])+cross(f[i],f[j],f[q]);
      while j<i+m-2 do
        begin
          inc(j);dp:=p;dq:=q;
          while cross(f[i],f[p],f[j])<=cross(f[i],f[p+1],f[j]) do inc(p);
          while cross(f[i],f[j],f[q])<=cross(f[i],f[j],f[q+1]) do inc(q);
          if cross(f[i],f[p],f[j])+cross(f[i],f[j],f[q])>c
          then c:=cross(f[i],f[p],f[j])+cross(f[i],f[j],f[q])
          else begin dec(j);p:=dp;q:=dq;break;end;
        end;
      if c>s then s:=c;
    end;
  writeln(s/2:0:1);close(input);close(output);
end.