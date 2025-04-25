/* -*- mode: Prolog; comment-column: 48 -*- */

/* Jovolog: Template for creating agent programs for the wumpus world based on
  Artifical Intelligence, A Modern Approach, Second Edition
  Chapter 7.2: The Wumpus World
  
*/

act(Action, Knowledge) :-
	% To avoid looping on act/2.
	not(gameStarted),
	assert(gameStarted),
	% Creating initial knowledge
	worldSize(X,Y), % world size
	assert(myWorldSize(X,Y)), % save to memory
	assert(myPosition(1,1,east)), % start possition
	assert(myTrail([])), % given trail
	assert(myVisited([1])), % visited poles
	assert(myGold(0)), % pick up gold
	act(Action, Knowledge).

% Agent actions
act(Action, Knowledge) :- exit_if_start_with_breeze_or_stench(Action, Knowledge). 
act(Action, Knowledge) :- go_back_step(Action, Knowledge). 
act(Action, Knowledge) :- pick_up_gold(Action, Knowledge). 
act(Action, Knowledge) :- go_down(Action, Knowledge). 
act(Action, Knowledge) :- go_right(Action, Knowledge). 
act(Action, Knowledge) :- go_up(Action, Knowledge). 
act(Action, Knowledge) :- go_left(Action, Knowledge). 
act(Action, Knowledge) :- exit_without_gold_available(Action, Knowledge).
act(Action, Knowledge) :- go_to_previous_position(Action, Knowledge). 

% Exit
exit_if_breeze_or_stench_detected(Action, Knowledge) :-
    (stench; breeze),
    myPosition(X,Y,Orient),
    X = 1,
    Y = 1,
    Action = exit,				
    write('exit_if_breeze_or_stench_detected called'), nl,
    Knowledge = [].		

exit_after_gold(Action, Knowledge) :-
	myGold(Gold), Gold > 0,
	myPosition(X,Y,Orient),
	X = 1,
	Y = 1,
	Action = exit,
    write('exit_after_gold called'), nl,				
	Knowledge = [].				

exit_without_gold_available(Action, Knowledge) :-
	myPosition(X,Y,Orient),
	X=1,
	Y=1,
	Action = exit,
    write('exit_without_gold_available called'), nl,	
	Knowledge = [].

pick_up_gold(Action, Knowledge) :-
	glitter,    
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	Action = grab,	
	NewGold is Gold + 1,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,Orient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(NewGold)].


% Go back to exit
go_back_step(Action, Knowledge) :-
	myGold(Gold), Gold > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	Trail = [[X_Old,Y_Old] | Trail_Tail],
	forwardStep(X, Y, Orient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = moveForward,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X_Old,Y_Old,Orient),
		     myTrail(Trail_Tail),
			 myVisited(Visited),
		     myGold(Gold)].

go_back_step(Action, Knowledge) :-
	myGold(Gold), Gold > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	shiftOrientLeft(Orient, NewOrient),
	Trail = [ [X_Old,Y_Old] | Trail_Tail ],
	forwardStep(X, Y, NewOrient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = turnLeft,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_back_step(Action, Knowledge) :-
	myGold(Gold), Gold > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

% Explore
go_down(Action, Knowledge) :-
	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, south, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = south,
	Action = moveForward,
	New_Trail = [ [X,Y] | Trail ], 
	New_Visited = [ New_Visited_XY | Visited ],
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
			 myPosition(New_X,New_Y,Orient),
		     myTrail(New_Trail),
			 myVisited(New_Visited),
		     myGold(Gold)].

go_down(Action, Knowledge) :-
	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
    

	forwardStep(X, Y, south, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = west,
	Action = turnLeft, 
	
    
    Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,south),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_down(Action, Knowledge) :-
	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, south, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_right(Action, Knowledge) :-
	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= Max_X,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, east, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = east, 
	Action = moveForward,
	New_Trail = [ [X,Y] | Trail ],
	New_Visited = [ New_Visited_XY | Visited ],
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(New_X,New_Y,Orient),
		     myTrail(New_Trail),
			 myVisited(New_Visited),
		     myGold(Gold)].

go_right(Action, Knowledge) :-

	not(breeze;stenchW),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= Max_X,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, east, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = south,
	Action = turnLeft,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,east),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_right(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= Max_X,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, east, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_up(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= Max_Y,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, north, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = north,
	Action = moveForward,
	New_Trail = [ [X,Y] | Trail ],
	New_Visited = [ New_Visited_XY | Visited ],
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(New_X,New_Y,Orient),
		     myTrail(New_Trail),
			 myVisited(New_Visited),
		     myGold(Gold)].

go_up(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= Max_Y,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, north, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = east,
	Action = turnLeft,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,north),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_up(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	Y \= Max_Y,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, north, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_left(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, west, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = west,
	New_Trail = [ [X,Y] | Trail ],
	New_Visited = [ New_Visited_XY | Visited ],
	Action = moveForward,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(New_X,New_Y,Orient),
		     myTrail(New_Trail),
			 myVisited(New_Visited),
		     myGold(Gold)].

go_left(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, west, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	Orient = north,
	Action = turnLeft,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,west),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_left(Action, Knowledge) :-

	not(breeze;stench),
	myWorldSize(Max_X,Max_Y),
	myPosition(X,Y,Orient),
	X \= 1,
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	forwardStep(X, Y, west, New_X, New_Y),
	New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
	not(member(New_Visited_XY,Visited)),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].


% Go back
go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),

	myGold(Gold),
	Trail = [ [X_Old,Y_Old] | Trail_Tail ],
	forwardStep(X, Y, Orient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = moveForward, % if the same go forward
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X_Old,Y_Old,Orient),
		     myTrail(Trail_Tail),
			 myVisited(Visited),
		     myGold(Gold)].

go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),

	myGold(Gold),
	shiftOrientLeft(Orient, NewOrient),
	Trail = [ [X_Old,Y_Old] | Trail_Tail ],
	forwardStep(X, Y, NewOrient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = turnLeft,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myGold(Gold),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
		     myGold(Gold)].

% Basic movment options
forwardStep(X, Y, east,  New_X, Y) :- New_X is (X+1).
forwardStep(X, Y, south, X, New_Y) :- New_Y is (Y-1).
forwardStep(X, Y, west,  New_X, Y) :- New_X is (X-1).
forwardStep(X, Y, north, X, New_Y) :- New_Y is (Y+1).

againstWall(X, Y, Orient, Max_X, Max_Y) :- X = Max_X, Orient = east.
againstWall(X, Y, Orient, Max_X, Max_Y) :- Y = Max_Y, Orient = north.
againstWall(X, Y, Orient, Max_X, Max_Y) :- X = 1, Orient = west.
againstWall(X, Y, Orient, Max_X, Max_Y) :- Y = 1, Orient = south.

shiftOrientLeft(east, north).
shiftOrientLeft(north, west).
shiftOrientLeft(west, south).
shiftOrientLeft(south, east).

shiftOrientRight(east, south).
shiftOrientRight(north, east).
shiftOrientRight(west, north).
shiftOrientRight(south, west).
