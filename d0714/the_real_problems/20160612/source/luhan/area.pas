type data=record x,y:longint; end;
var s,p:array[0..200000]of data;
    t,n,i:longint; 
function mul(a,b,c:data):int64;
begin  exit(int64(b.x-a.x)*(c.y-a.y)-int64(c.x-a.x)*(b.y-a.y)); end;
function dis(a,b:data):int64;
begin exit(int64(a.x-b.x)*(a.x-b.x)+int64(a.y-b.y)*(a.y-b.y)); end;
function cmp(i,j:longint):boolean;
begin
  if mul(p[1],p[i],p[j])=0 then exit(dis(p[1],p[i])<dis(p[1],p[j]))
  else exit(mul(p[1],p[i],p[j])>0);
end;
procedure swap(var x,y:data);
var z:data; begin z:=x; x:=y; y:=z; end;
procedure qsort(l,r:longint);
var i,j:longint;
begin
  i:=l; j:=r; p[0]:=p[(l+r) div 2];
  while i<=j do 
    begin
      while cmp(i,0) do inc(i);
      while cmp(0,j) do dec(j);
      if i<=j then begin swap(p[i],p[j]); inc(i); dec(j); end;
    end;
  if i<r then qsort(i,r);
  if l<j then qsort(l,j);
end;
procedure granham;
var i,k:longint;
begin
  k:=1;
  for i:=2 to n do 
    if (p[i].y<p[k].y)or((p[i].y=p[k].y)and(p[i].x<p[k].x)) then k:=i;
  swap(p[1],p[k]);
  qsort(2,n);
   //for i:=1 to n do writeln(i,':',p[i].x,' ',p[i].y);
  t:=1; s[1]:=p[1];
  for i:=2 to n do 
    begin
      while (t>1)and(mul(s[t-1],p[i],s[t])>=0) do dec(t);
      inc(t); s[t]:=p[i];
    end;
//  for i:=1 to t do writeln(i,':',s[i].x:0:0,' ',s[i].y:0:0);
end;
procedure solve;
var i,j,k,l:longint;
    ans,pre,st:int64;
begin
  for i:=t+1 to 2*t do s[i]:=s[i-t];
  i:=1; j:=3; 
  ans:=0; pre:=0; k:=2; l:=4;
  while j<t+1 do 
    begin
      if k=j then inc(j);
      if j=l then inc(l);
      if j=t+1 then break;
      while mul(s[i],s[k+1],s[j])>mul(s[i],s[k],s[j]) do inc(k);
      while mul(s[j],s[l+1],s[i])>mul(s[j],s[l],s[i]) do inc(l);
      st:=mul(s[i],s[k],s[j])+mul(s[j],s[l],s[i]);
     // writeln(i,' ',k,' ',j,' ',l,' ',st:0:0);
      // writeln(mul(s[i],s[k],s[j]),' '
      if st>ans then ans:=st;
      if st>pre then begin j:=j+1; pre:=st; end
               else begin inc(i); dec(j); pre:=0; k:=i+1; l:=j+1; end;
       
    end;           
  writeln(ans/2:0:1);
end;
begin
  assign(input,'area.in');  reset(input);
  assign(output,'area.out'); rewrite(output);
  readln(n);
  for i:=1 to n do readln(p[i].x,p[i].y);
  granham;
  if t<3 then writeln(0.0);
  if t=3 then writeln(mul(s[1],s[2],s[3])/2:0:1);
  if t>3 then solve;
  close(input); close(output);
end.
