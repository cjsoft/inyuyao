uses math;
function target(f1:longint):longint;
begin
    exit((f1 shr 1)and 1);
end;
const n=20;jp=13;
var //a:array[0..(1 shl n)+1]of double;
    kk,nn,b1,b2,b3,b4:longint;
    l,r,lx,rx:array[0..n]of longint;
    up,down:longint;
    bc:array[0..(1 shl jp)+1]of longint;
    p:array[0..1,0..n]of double;
    h1,h2:array[0..n]of double;
    d1,d2,d3,d4:double;
    t1,t2:text;
function bitcount(f1:longint):longint;
begin
    exit(bc[f1 shr jp]+bc[f1 and((1 shl jp)-1)]);
end;



function getans(f1:longint):double;
var f2,f3,f4,f5,f6:longint;ans:double;
begin
    ans:=0;
    if kk=nn then exit(1);
    if kk=0 then exit(0);
    down:=maxlongint;
    up:=0;
    for f2:=1 to nn do if (f1 and(1 shl(f2-1)))=0 then begin
	down:=min(down,l[f2]);
    end else begin
	up:=max(up,r[f2]);
    end;
    for f2:=down to up do begin
	h1[0]:=1;
	for f3:=1 to nn do begin
	    if (f1 and (1 shl(f3-1)))<>0 then begin
		h1[f3]:=h1[f3-1]*min(1,(r[f3]-f2+1)/(r[f3]-l[f3]+1));
		if r[f3]-f2+1<0 then h1[f3]:=0;
	    end else begin
		h1[f3]:=h1[f3-1]*min(1,(f2-l[f3])/(r[f3]-l[f3]+1));
		if f2-l[f3]<0 then h1[f3]:=0;
	    end;
	end;
	h2[nn+1]:=1;
	for f3:=nn downto 1 do begin
	    if (f1 and(1 shl(f3-1)))<>0 then begin
		h2[f3]:=h2[f3+1]*min(1,(r[f3]-f2)/(r[f3]-l[f3]+1));
		if r[f3]-f2<0 then h2[f3]:=0;
	    end else begin
		h2[f3]:=h2[f3+1]*min(1,(f2-l[f3]+1)/(r[f3]-l[f3]+1));
		if f2-l[f3]+1<0 then h2[f3]:=0;
	    end;
	end;
	for f3:=1 to nn do begin
	    if (l[f3]<=f2)and(f2<=r[f3])and((f1 and(1 shl(f3-1)))=0) then
	    ans:=ans+h1[f3-1]*h2[f3+1]/(r[f3]-l[f3]+1);
	end;
    end;
    exit(ans);
end;


begin
    assign(t1,'assign.in');reset(t1);
    assign(t2,'assign.out');rewrite(t2);
    bc[0]:=0;
    for b1:=1 to (1 shl jp)-1 do if (b1 and 1)=1 then bc[b1]:=bc[b1-1]+1 else bc[b1]:=bc[b1 shr 1];
    fillchar(lx,sizeof(lx),0);
    fillchar(rx,sizeof(rx),0);
    read(t1,nn);
    for b1:=1 to nn do read(t1,l[b1]);
    for b1:=1 to nn do read(t1,r[b1]);
    for b1:=1 to nn do lx[b1]:=l[b1];
    for b1:=1 to nn do rx[b1]:=r[b1];
    for b1:=1 to nn do begin
	for b2:=1 to nn-1 do if lx[b2]>lx[b2+1] then begin
	    b3:=lx[b2];
	    lx[b2]:=lx[b2+1];
	    lx[b2+1]:=b3;
	end;
    end;
    for b1:=1 to nn do begin
	for b2:=1 to nn-1 do if rx[b2]>rx[b2+1] then begin
	    b3:=rx[b2];
	    rx[b2]:=rx[b2+1];
	    rx[b2+1]:=b3;
	end;
    end;
    read(t1,kk);
    up:=rx[nn-kk];
    down:=lx[nn-kk];
    for b1:=0 to ((1 shl nn)-1) do if bitcount(b1)=kk then begin
	d1:=getans(b1);
	b3:=1;
	for b2:=1 to kk do begin
	    while (b1 and(1 shl(b3-1)))=0 do inc(b3);
	    p[target(b2),b3]:=p[target(b2),b3]+d1;
	    inc(b3);
	end;
    end;
    for b1:=1 to nn do writeln(t2,p[0,b1]:0:6,' ',p[1,b1]:0:6);
    close(t1);close(t2);
end.