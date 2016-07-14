var
  n,i,sum,a,b,c,d:longint;
  ans,s:extended;
  x,y,o:array[-10..100100] of longint;

function cro(a,b,c:longint):extended;
var
  x1,y1,x2,y2:extended;
begin
  x1:=x[b]-x[a];
  y1:=y[b]-y[a];
  x2:=x[c]-x[b];
  y2:=y[c]-y[b];
  exit(x1*y2-x2*y1);
end;

procedure qsort(l,r:longint);
var
  i,j,mid,temp:longint;
begin
  i:=l;
  j:=r;
  mid:=x[(l+r) div 2];
  repeat
    while x[i]<mid do inc(i);
	while x[j]>mid do dec(j);
	if i<=j then begin
	  temp:=x[i];
	  x[i]:=x[j];
	  x[j]:=temp;
	  temp:=y[i];
	  y[i]:=y[j];
	  y[j]:=temp;
	  inc(i);
	  dec(j);
	end;
  until i>j;
  if i<r then qsort(i,r);
  if l<j then qsort(l,j);
end;

begin
  assign(input,'area.in');
  assign(output,'area.out');
  reset(input);
  rewrite(output);
  readln(n);
  for i:=1 to n do readln(x[i],y[i]);
  qsort(1,n);
  sum:=2;
  o[1]:=1;
  o[2]:=2;
  for i:=3 to n do begin
	while cro(o[sum-1],o[sum],i)<0 do begin
	  dec(sum);
	  if sum=1 then break;
	end;
	inc(sum);
	o[sum]:=i;
  end;
  for i:=n-1 downto 1 do begin
	while cro(o[sum-1],o[sum],i)<0 do begin
	  dec(sum);
	  if sum=1 then break;
	end;
	inc(sum);
	o[sum]:=i;
  end;
  dec(sum);
  if sum<3 then begin
	writeln('0.0');
    close(input);
    close(output);
    halt;
  end;
  if sum=3 then begin
	ans:=abs(cro(o[1],o[2],o[3]))/2;
    writeln(ans:0:1);
    close(input);
    close(output);
    halt;
  end;
  ans:=-1;
  for a:=1 to sum do
	for b:=a+1 to sum do
	  for c:=b+1 to sum do
		for d:=c+1 to sum do begin
		  s:=(abs(cro(o[a],o[b],o[c]))+abs(cro(o[c],o[d],o[a])))/2;
		  if s>ans then ans:=s;
		end;
  writeln(ans:0:1);
  close(input);
  close(output);
end.