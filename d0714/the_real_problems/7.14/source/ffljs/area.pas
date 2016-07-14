const n=100000+10;
type po=array[0..1]of int64;
function gpo(f1,f2:int64):po;
begin
    gpo[0]:=f1;
    gpo[1]:=f2;
end;
function waiji(f1,f2:po):int64;
begin
    exit(f1[0]*f2[1]-f1[1]*f2[0]);
end;
function sarea(f1,f2,f3:po):int64;
begin
    f1[0]:=f2[0]-f1[0];
    f1[1]:=f2[1]-f1[1];
    f2[0]:=f3[0]-f2[0];
    f2[1]:=f3[1]-f2[1];
    exit(waiji(f1,f2));
end;
var a:array[0..n]of po;
    nn,b1,b2,b3,b4:longint;
    d1,d2,d3,d4:int64;
    s,s1,s2:array[0..n]of longint;
    tb1,tb2,tb:array[0..n*2]of longint;
    ans,an2:int64;
    t1,t2:text;
function cho(f1,f2:longint):longint;
begin
    if a[f1][0]<=a[f2][0] then exit(1);
    exit(0);
end;
procedure sort(f1,f2:longint);
var f3,f4,f5,f6:longint;
begin
    if f1=f2 then exit;
    f3:=(f1+f2)div 2;
    sort(f1,f3);sort(f3+1,f2);
    s1[f3+1]:=n;s2[f2+1]:=n;
    for f4:=f1 to f3 do s1[f4]:=s[f4];
    for f5:=f3+1 to f2 do s2[f5]:=s[f5];
    f4:=f1;f5:=f3+1;
    for f6:=f1 to f2 do begin
	if cho(s1[f4],s2[f5])=1 then begin
	    s[f6]:=s1[f4];
	    inc(f4);
	end else begin
	    s[f6]:=s2[f5];
	    inc(f5);
	end;
    end;
end;
{function weifen(f1,f2,x:longint):int64;
begin
    exit(sarea(a[tb[f1]],a[tb[x+1]],a[tb[f2]])-sarea(a[tb[f1]],a[tb[x]],a[tb[f2]]));
end;}

function weifen(f1,f2,x:longint):int64;
begin
    exit(sarea(a[tb[f1]],a[tb[x]],a[tb[f2]]));
end;
function efsj(f1,f2:longint;var f3:longint):int64;
var ans,an2:int64;
begin
    if f2-f1<=1 then exit(0);
    while f1>=f3 do inc(f3);
    ans:=weifen(f1,f2,f3);
    an2:=weifen(f1,f2,f3+1);
    while (f3+1<f2)and(ans<an2) do begin
	inc(f3);
	ans:=weifen(f1,f2,f3);
	an2:=weifen(f1,f2,f3+1);
    end;
    exit(ans);
end;
function sifang(f1,f2:longint;var f3,f4:longint):int64;
begin
    exit(efsj(f1,f2,f3)+efsj(f2,f1+tb[0],f4));
end;
function effx(var f1,f2,l1,l2:longint):int64;
var an1,an2,an3:int64;r1,r2:longint;
begin
    while f1>=f2 do inc(f2);
    an1:=sifang(f1,f2,l1,l2);
    r1:=l1;r2:=l2;
    an2:=sifang(f1,f2+1,r1,r2);
    while (an2>=an1)and(f2+1<f1+tb[0]) do begin
	inc(f2);
	an1:=sifang(f1,f2,l1,l2);
	r1:=l1;r2:=l2;
	an2:=sifang(f1,f2+1,r1,r2);
    end;
    exit(an1);
end;

begin
    assign(t1,'area.in');reset(t1);
    assign(t2,'area.out');rewrite(t2);
    read(t1,nn);
    for b1:=1 to nn do for b2:=0 to 1 do read(t1,a[b1][b2]);
    a[n][0]:=maxlongint;
    a[n][1]:=maxlongint;
    for b1:=1 to nn do s[b1]:=b1;
    sort(1,nn);
    //for b1:=1 to nn do for b2:=0 to 1 do write(a[s[b1]][b2]);
    tb1[0]:=0;tb2[0]:=0;
    for b1:=1 to nn do begin
	while (tb1[0]>=2)and(sarea(a[tb1[tb1[0]-1]],a[tb1[tb1[0]]],a[s[b1]])<=0) do dec(tb1[0]);
	inc(tb1[0]);
	tb1[tb1[0]]:=s[b1];
    end;
    for b1:=1 to nn do begin
	while (tb2[0]>=2)and(sarea(a[tb2[tb2[0]-1]],a[tb2[tb2[0]]],a[s[b1]])>=0) do dec(tb2[0]);
	inc(tb2[0]);
	tb2[tb2[0]]:=s[b1];
    end;
    //for b1:=1 to tb2[0] do write(tb2[b1]);
    //for b1:=tb1[0] downto 1 do write(tb1[b1]);
    for b1:=0 to tb1[0] do tb[b1]:=tb1[b1];
    if tb[tb[0]]=tb2[tb2[0]] then dec(tb[0]);
    for b1:=tb2[0] downto 1 do begin
	inc(tb[0]);
	tb[tb[0]]:=tb2[b1];
    end;
    if tb[tb[0]]=tb[1] then dec(tb[0]);
    //writeln;
    for b1:=1 to tb[0] do tb[tb[0]+b1]:=tb[b1];
    tb[0]:=tb[0];
    //for b1:=1 to tb[0]*2 do write(tb[b1]);
    b1:=1;
    b2:=1;
    b3:=1;
    b4:=1;
    ans:=0;
    while b1<=tb[0] do begin
	an2:=effx(b1,b2,b3,b4);
	if an2>ans then ans:=an2;
	inc(b1);
    end;
    //writeln();
    writeln(t2,ans shr 1,'.',(ans and 1)*5);
    close(t1);
    close(t2);
end.    
