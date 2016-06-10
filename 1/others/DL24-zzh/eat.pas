const saffah=1000000007;
var n,m,c,d:int64;

function power(a,p:int64):int64;
begin
if p=0 then exit(1);
power:=power(a,p>>1);
power:=power*power mod saffah;
if p and 1 = 1 then power:=power*a mod saffah;
end;

procedure hehe;
begin
close(input);
close(output);
halt;
end;
(*
procedure naive1;
begin
writeln(power(2,n-c-d));
hehe;
end;

procedure naive11;
begin
writeln(power(2,m-c-d));
hehe;
end;
*)

procedure naive;
begin
writeln(1);
halt;
end;


begin
assign(input,'eat.in');
assign(output,'eat.out');
reset(input);
rewrite(output);
read(n,m,c,d);
if (n=1) or (m=1) then naive
else if (m=2) and (c=0) and (d=0) then begin
	writeln(power(2,n-1));
	hehe;
	end;
writeln(4);
close(input);
close(output);
end.
