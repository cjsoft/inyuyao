var
  n,k,i,t:longint;
  l,r,a,f,x,y:array[1..25]of longint;

procedure
  calc(t:longint);
var
  i,j:longint;
begin
  if t=n+1
  then begin
         for i:=1 to n do
           a[i]:=i;
         for i:=1 to n do
           for j:=i+1 to n do
             if (f[a[i]]<f[a[j]]) or ((f[a[i]]=f[a[j]]) and (a[i]>a[j]))
             then begin t:=a[i];a[i]:=a[j];a[j]:=t;end;
         for i:=1 to k do
           for j:=i+1 to k do
             if a[i]>a[j]
             then begin t:=a[i];a[i]:=a[j];a[j]:=t;end;
         for i:=1 to k do
           if i mod 4<=1
           then inc(x[a[i]])
           else inc(y[a[i]]);
         exit;
       end
  else for i:=l[t] to r[t] do
         begin
           f[t]:=i;
           calc(t+1);
         end;
end;

begin
  assign(input,'assign.in');reset(input);
  assign(output,'assign.out');rewrite(output);
  read(n);
  for i:=1 to n do read(l[i]);
  for i:=1 to n do read(r[i]);
  read(k);calc(1);
  t:=1;for i:=1 to n do t:=t*(r[i]-l[i]+1);
  for i:=1 to n do
    writeln(x[i]/t:0:6,' ',y[i]/t:0:6);
end.