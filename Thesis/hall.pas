(* Heinz Lueneburg Uni KL *)
program hall;
(* Data structures:                         *)
 const size = 100;
       maxm= 100;
 type element=0..size;
      subset= set of element;
      index=1..maxm;

procedure matchmaker
(var s:setlist;
 var m: index;
 var v: SDR;
 var I: indexset;
 var J: subset;
 var noSDR: boolean);

var n,k,l :index;
    pp,z : element;
    X: sunset;
    chain: arrat [index] of index;
    notcont,add: boolean;

begin
  noSDR := false;
  X := [];
  n := 1; add := false;
  repeat
    if add then n:= n+1 else add :- true;
    J := s[n];
    I := [n];
    l := 1;
    k :=1;
    while ( J <= X) and ( k < n) do
        begin
           k:= 1;
           notcont:= false;
           repeat
             if not ( k in I ) and ( v[k] in J ) then 
               begin
                  I := I +[k];
                  notcont := not ( s[k] <= J );
                  if nontcont then
                    begin
                        j :- J + s[k];
                        chain[l] := k;
                        l := l+1;
                    end
              end;
              k := K +1;
          until ( k = n) or notcont
        end;
       if J <- X then
        noSDR :=  true
       else
        begin
          J := J -X;
          x:= 0;
          while not ( z in J)
          do
             z := z+1;
             X := X + [z];
             while not ( z in s[n]) do
                begin
                  l := l - 1;
                  while not ( z in s[chain[l]]) do l := l - 1;
                  pp := v[chain[l]];
                  v[chain[l]] := z;
                  z:= pp;
                end;
                v[n] := z
           enf
     unitl ( n = m ) or noSDR
end (* matachmaker *);



BEGIN
END.
