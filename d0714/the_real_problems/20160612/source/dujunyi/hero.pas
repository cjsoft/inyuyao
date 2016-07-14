var
  n,m,k,i,j,l:longint;
  s:int64;
  a,b,f,g:array[0..301,0..301]of int64;

function
  min(x,y:int64):int64;inline;
begin
  if x<y
  then exit(x)
  else exit(y);
end;

begin
  assign(input,'hero.in');reset(input);
  assign(output,'hero.out');rewrite(output);
  read(n,m,k);
  for i:=1 to n do
    for j:=1 to m do
      read(a[i,j]);
  fillchar(b,sizeof(b),127);
  for l:=1 to n do
    begin
      fillchar(g,sizeof(g),127);
      for i:=1 to m do
        for j:=1 to m do
          begin
            b[i,j]:=min(f[i,j]-(i+j)*k,min(b[i-1,j],b[i,j-1]));
            g[i,j]:=min(g[i,j],b[i,j]+(i+j)*k);
          end;
      for i:=1 to m do
        for j:=m downto 1 do
          begin
            b[i,j]:=min(f[i,j]-(i-j)*k,min(b[i-1,j],b[i,j+1]));
            g[i,j]:=min(g[i,j],b[i,j]+(i-j)*k);
          end;
      for i:=m downto 1 do
        for j:=1 to m do
          begin
            b[i,j]:=min(f[i,j]-(j-i)*k,min(b[i+1,j],b[i,j-1]));
            g[i,j]:=min(g[i,j],b[i,j]+(j-i)*k);
          end;
      for i:=m downto 1 do
        for j:=m downto 1 do
          begin
            b[i,j]:=min(f[i,j]+(i+j)*k,min(b[i+1,j],b[i,j+1]));
            g[i,j]:=min(g[i,j],b[i,j]-(i+j)*k);
          end;
      for i:=1 to m do
        for j:=1 to m do
          if i=j
          then f[i,j]:=1 shl 60
          else f[i,j]:=g[i,j]+a[l,i]+a[l,j];
    end;
  s:=f[1,1];
  for i:=1 to m do
    for j:=1 to m do
      s:=min(s,f[i,j]);
  writeln(s);close(input);close(output);
end.
