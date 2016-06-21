var s,ss:ansistring;
len,m,i,qaq,tat,p,j:longint;
tmp:ansistring;
vis:array[1..350000]of boolean;
ans:longint;
begin
assign(input,'POPLOCAVANJE.in');
assign(output,'POPLOCAVANJE.out');
reset(input);
rewrite(output);
readln(len);
readln(s);
readln(m);
for i:=1 to m do begin
	readln(tmp);
	ss:=s;
	for tat:=1 to 100000000 do begin
		p:=pos(tmp,ss);
		if p=0 then break;
		for j:=p to p+length(tmp)-1 do v[j]:=true;
		delete(ss,p,1);
		end;
	end;
for i:=1 to len do if not v[i] then inc(ans);
writeln(ans);
close(input);
close(output);
end.
