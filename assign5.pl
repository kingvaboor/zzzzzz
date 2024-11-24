% facts 
likes(John,Sim).
likes(Sim,John).
likes(Dan,Lol).
likes(Lol,Sim).

% Rules

friends(X,Y) :-
likes(X,Y) ,
likes(Y,X).
