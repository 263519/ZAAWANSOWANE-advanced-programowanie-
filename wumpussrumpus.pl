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
	assert(myVisitedStench([])),
	assert(haveGold(0)), % pick up NGolds
	act(Action, Knowledge).

% Agent actions
act(Action, Knowledge) :- exit_if_start_with_breeze_or_stench(Action, Knowledge). % if no way on entry
act(Action, Knowledge) :- exit_after_gold(Action, Knowledge). % if you got NGolds just exit
act(Action, Knowledge) :- go_to_base(Action, Knowledge). % if with NGolds without exit, go back
act(Action, Knowledge) :- pick_up_gold(Action, Knowledge). % if no NGolds but on the same pole, pick up
act(Action, Knowledge) :- go_down(Action, Knowledge). % if save move down
act(Action, Knowledge) :- go_right(Action, Knowledge). % if save move right
act(Action, Knowledge) :- go_up(Action, Knowledge). % if save move up
act(Action, Knowledge) :- go_left(Action, Knowledge). % if save move left
act(Action, Knowledge) :- exit_without_gold_available(Action, Knowledge). % if no movment and exit just leave
act(Action, Knowledge) :- go_to_previous_position(Action, Knowledge). % if no movment and no exit, go back

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
	haveGold(NGolds), NGolds > 0,
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
	myVisitedStench(VisitedStench),
	haveGold(NGolds),
	Action = grab,	
	NewGold is NGolds + 1,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,Orient),
		     myTrail(Trail),
			 myVisited(Visited),
			 myVisitedStench(VisitedStench),
		     haveGold(NewGold)].


% Go back to exit
go_to_base(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),
	Trail = [[X_Old,Y_Old]  | Trail_Tail],
	forwardStep(X, Y, Orient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = moveForward,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X_Old,Y_Old,Orient),
		     myTrail(Trail_Tail),
			 myVisited(Visited),
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

go_to_base(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),
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
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

go_to_base(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

% Explore - DOWN
go_down(Action, Knowledge) :-
    % Check common conditions first
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    Y \= 1,  % Make sure we're not at the bottom edge
    can_move_south(X, Y, Max_X, Max_Y, Visited),
    % Call appropriate action based on current orientation
    determine_down_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

% Helper predicate to check if we can move south
can_move_south(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, south, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

% Case 1: Already facing south, just move forward
determine_down_action(south, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    forwardStep(X, Y, south, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    New_Trail = [[X, Y] | Trail],
    New_Visited = [New_Visited_XY | Visited],
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(New_X, New_Y, south),
                 myTrail(New_Trail),
                 myVisited(New_Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 2: Facing west, need to turn left
determine_down_action(west, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, south),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 3: Facing north or east, turn right to eventually face south
determine_down_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= south,
    Orient \= west,
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Explore - RIGHT
go_right(Action, Knowledge) :-
    % Check common conditions first
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    X \= Max_X,  % Make sure we're not at the rightmost edge
    can_move_east(X, Y, Max_X, Max_Y, Visited),
    % Call appropriate action based on current orientation
    determine_right_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

% Helper predicate to check if we can move east
can_move_east(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, east, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

% Case 1: Already facing east, just move forward
determine_right_action(east, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    forwardStep(X, Y, east, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    New_Trail = [[X, Y] | Trail],
    New_Visited = [New_Visited_XY | Visited],
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(New_X, New_Y, east),
                 myTrail(New_Trail),
                 myVisited(New_Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 2: Facing south, need to turn left
determine_right_action(south, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, east),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 3: Facing north or west, turn right to eventually face east
determine_right_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= east,
    Orient \= south,
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Explore - UP
go_up(Action, Knowledge) :-
    % Check common conditions first
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    Y \= Max_Y,  % Make sure we're not at the top edge
    can_move_north(X, Y, Max_X, Max_Y, Visited),
    % Call appropriate action based on current orientation
    determine_up_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

% Helper predicate to check if we can move north
can_move_north(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, north, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

% Case 1: Already facing north, just move forward
determine_up_action(north, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    forwardStep(X, Y, north, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    New_Trail = [[X, Y] | Trail],
    New_Visited = [New_Visited_XY | Visited],
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(New_X, New_Y, north),
                 myTrail(New_Trail),
                 myVisited(New_Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 2: Facing east, need to turn left
determine_up_action(east, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, north),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 3: Facing south or west, turn right to eventually face north
determine_up_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= north,
    Orient \= east,
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Explore - LEFT
go_left(Action, Knowledge) :-
    % Check common conditions first
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    X \= 1,  % Make sure we're not at the leftmost edge
    can_move_west(X, Y, Max_X, Max_Y, Visited),
    % Call appropriate action based on current orientation
    determine_left_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

% Helper predicate to check if we can move west
can_move_west(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, west, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

% Case 1: Already facing west, just move forward
determine_left_action(west, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    forwardStep(X, Y, west, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    New_Trail = [[X, Y] | Trail],
    New_Visited = [New_Visited_XY | Visited],
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(New_X, New_Y, west),
                 myTrail(New_Trail),
                 myVisited(New_Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 2: Facing north, need to turn left
determine_left_action(north, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, west),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Case 3: Facing south or east, turn right to eventually face west
determine_left_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= west,
    Orient \= north,
    myTrail(Trail),
    myVisited(Visited),
    myVisitedStench(VisitedStench),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 myVisitedStench(VisitedStench),
                 haveGold(NGolds)].

% Go back
go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),

	haveGold(NGolds),
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
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),

	haveGold(NGolds),
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
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

go_to_previous_position(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	myVisitedStench(VisitedStench),
	haveGold(NGolds),
	shiftOrientRight(Orient, NewOrient),
	Action = turnRight,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,NewOrient),
		     myTrail(Trail),
			 myVisited(Visited),
			 myVisitedStench(VisitedStench),
		     haveGold(NGolds)].

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
