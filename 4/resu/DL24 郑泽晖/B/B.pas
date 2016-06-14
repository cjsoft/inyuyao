var n,i,t:longint;
cnt:array[0..30]of longint;
ans:int64;
procedure chai(a:int64);
var i:longint;
begin
for i:=0 to 20 do if a and (1<<i) <> 0 then inc(cnt[i]);
end;
function get:int64;
var i:longint;
begin
get:=0;
for i:=0 to 20 do if cnt[i]>0 then begin
	get:=get+(1<<i);
	dec(cnt[i]);
	end;
get:=get*get;
end;
begin
assign(input,'B.in');
assign(output,'B.out');
reset(input);
rewrite(output);
fillchar(cnt,sizeof(cnt),0);
read(n);
ans:=0;
for i:=1 to n do begin
	read(t);
	chai(t);
	end;
for i:=1 to n do ans:=ans+get;
writeln(ans);
close(input);
close(output);
end.
