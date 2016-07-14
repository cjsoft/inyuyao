//uses math;
function min(a,b:int64):int64;
begin
    if a<=b then exit(a) else exit(b);
end; 
const n=300+10;
var a:array[0..n,0..n]of int64;
    i:array[0..n]of int64;
    mm,nn,b1,b2,b3,b4,b5:longint;
    kk:int64;
    ans:int64;
    t1,t2:text;
begin
    assign(t1,'hero.in');reset(t1);
    assign(t2,'hero.out');rewrite(t2);
    read(t1,nn,mm,kk);
    fillchar(a,sizeof(a),$30);
    for b1:=1 to mm do read(t1,i[b1]);
    for b1:=1 to mm-1 do for b2:=b1+1 to mm do a[b1,b2]:=i[b1]+i[b2];
    for b2:=1 to mm-2 do for b3:=b2+2 to mm do a[b2,b3]:=min(a[b2,b3-1]+kk,a[b2,b3]);
    for b2:=2 to mm-1 do for b3:=b2+1 to mm do a[b2,b3]:=min(a[b2-1,b3]+kk,a[b2,b3]);
    for b2:=1 to mm-2 do for b3:=b2+2 to mm do a[b2,b3]:=min(a[b2+1,b3]+kk,a[b2,b3]);
    for b2:=1 to mm-2 do for b3:=b2+1 to mm-1 do a[b2,b3]:=min(a[b2,b3+1]+kk,a[b2,b3]);

    for b1:=2 to nn do begin
	for b2:=1 to mm do read(t1,i[b2]);
	for b2:=1 to mm-1 do for b3:=b2+1 to mm do a[b2,b3]:=a[b2,b3]+i[b2]+i[b3];
	for b2:=1 to mm-2 do for b3:=b2+2 to mm do a[b2,b3]:=min(a[b2,b3-1]+kk,a[b2,b3]);
	for b2:=2 to mm-1 do for b3:=b2+1 to mm do a[b2,b3]:=min(a[b2-1,b3]+kk,a[b2,b3]);
	for b2:=1 to mm-2 do for b3:=b2+2 to mm do a[b2,b3]:=min(a[b2+1,b3]+kk,a[b2,b3]);
	for b2:=1 to mm-2 do for b3:=b2+1 to mm-1 do a[b2,b3]:=min(a[b2,b3+1]+kk,a[b2,b3]);
    end;
    ans:=a[0,0];
    for b1:=1 to mm-1 do for b2:=b1+1 to mm do ans:=min(ans,a[b1,b2]);
    writeln(t2,ans);
    close(t1);
    close(t2);
end.
