var b:array[0..1000000,0..3]of longint;
    a:array[0..301,0..301]of longint;
    dis:array[0..1000000]of int64;
    p,pre,pret,vis:array[0..1000000]of longint;
    q:array[0..10000000]of longint;
    n,m,i,j,k,k1,ss,st,f,t:longint;
    ans:int64; 
procedure build(x,y,z,cost:longint);
begin inc(t); b[t,0]:=p[x]; p[x]:=t; b[t,1]:=y; b[t,2]:=z; b[t,3]:=cost; end;
procedure SPFA;
var u,i,l,r,t,x,y,z,cost:longint;
begin
  for u:=1 to 2 do
  begin
    for i:=ss to st do dis[i]:=maxlongint*maxlongint; dis[ss]:=0;
    l:=0; r:=1; q[1]:=ss; vis[ss]:=1;  
    while l<r do 
      begin
        inc(l); x:=q[l]; 
        t:=p[x];
        while t<>0 do
          begin
            y:=b[t,1]; z:=b[t,2]; cost:=b[t,3];
            if (z>0)and(dis[x]+cost<dis[y]) then
              begin
                dis[y]:=dis[x]+cost; pre[y]:=x; pret[y]:=t;
                if vis[y]=0 then begin inc(r); q[r]:=y; vis[y]:=1; end;
              end;
            t:=b[t,0];
          end;
        vis[x]:=0;
      end;
    
    ans:=ans+dis[st];
    x:=st;
    while x<>ss do
      begin
        t:=pret[x];
        dec(b[t,2],1); inc(b[t xor 1,2],1);
        x:=pre[x];
      end;
  end;
end;
begin
  assign(input,'hero.in');  reset(input);
  assign(output,'hero.out'); rewrite(output);
  readln(n,m,k);  t:=1;
  for i:=1 to n do 
    for j:=1 to m do 
      read(a[i,j]);
  f:=n*m;
  for i:=1 to n do
    for j:=1 to m do
    begin
      k1:=(i-1)*m+j; 
      build(k1,k1+f,1,a[i,j]); build(k1+f,k1,0,-a[i,j]);
      
      if j<m then begin 
      build(k1,k1+1,2,k); build(k1+1,k1,0,-k);
      build(k1+1,k1,2,k); build(k1,k1+1,0,-k); end;
      if i<n then begin build(k1+f,k1+m,1,0); build(k1+m,k1+f,0,0); end;
    end;
  ss:=0; st:=f*2+1; 
  for i:=1 to m do 
    begin build(0,i,1,0); build(i,0,0,0); end;
  for i:=1 to m do 
    begin build(st-i,st,1,0); build(st,st-i,0,0); end;
  SPFA; 
  writeln(ans);
  close(input); close(output);
end.
