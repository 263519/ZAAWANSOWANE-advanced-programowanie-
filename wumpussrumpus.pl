/* -*- mode: Prolog; comment-column: 48 -*- */

/****************************************************************************
 *
 * Copyright (c) 2013 Witold Paluszynski
 *
 * I grant everyone the right to copy this program in whole or part, and
 * to use it for any purpose, provided the source is properly acknowledged.
 *
 * Udzielam kazdemu prawa do kopiowania tego programu w calosci lub czesci,
 * i wykorzystania go w dowolnym celu, pod warunkiem zacytowania zrodla.
 *
 ****************************************************************************/


/*
  This program implements a simple agent strategy for the wumpus world.
  The agent ignores all dangers of the wumpus world.
  The strategy is to go forward along the perimeter,
  turn left when reached the opposing wall,
  but first of all pick up gold if stumbled upon it,
  and exit the game if at home with gold.
  This version registers all steps on a stack, and uses it to reverse
  the actions after having found gold, thus properly returning home.

  Also demonstrates how to keep track of her own position and orientation.
  The agent assumes that the starting point is (1,1) and orientation "east".
*/

% auxiliary initial action generating rule
act(Action, Knowledge) :-
	not(gameStarted),
	assert(gameStarted),
	worldSize(X,Y),				%this is given
	assert(myWorldSize(X,Y)),
	assert(myPosition(1, 1, east)),		%this we assume by default
	assert(myTrail([])),
	assert(myVisited([1])),
	assert(haveGold(0)),
	act(Action, Knowledge).

act(Action, Knowledge) :- exit_if_breeze_or_stench_detected(Action, Knowledge).
act(Action, Knowledge) :- exit_after_gold(Action, Knowledge).
act(Action, Knowledge) :- go_back_step(Action, Knowledge).
act(Action, Knowledge) :- pick_up_gold(Action, Knowledge).
act(Action, Knowledge) :- go_down(Action, Knowledge).
act(Action, Knowledge) :- go_right(Action, Knowledge).
act(Action, Knowledge) :- go_up(Action, Knowledge).
act(Action, Knowledge) :- go_left(Action, Knowledge).
act(Action, Knowledge) :- exit_without_gold_available(Action, Knowledge).
act(Action, Knowledge) :- go_back(Action, Knowledge).

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
	haveGold(NGolds),
	Action = grab,	
	NewGold is NGolds + 1,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X,Y,Orient),
		     myTrail(Trail),
			 myVisited(Visited),
		     haveGold(NewGold)].

go_back_step(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myTrail(Trail),
	Trail = [ [grab,X,Y,Orient] | Trail_Tail ],
	New_Trail = [ [turnRight,X,Y,Orient] | Trail_Tail ],
	Action = turnLeft,
	Knowledge = [gameStarted,
	             haveGold(NGolds),
		     myWorldSize(Max_X, Max_Y),
		     myPosition(X, Y, Orient),
		     myTrail(New_Trail)].

go_back_step(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myTrail([ [Action,X,Y,Orient] | Trail_Tail ]),
	Action = moveForward,
	Knowledge = [gameStarted,
	             haveGold(NGolds),
		     myWorldSize(Max_X, Max_Y),
		     myPosition(X, Y, Orient),
		     myTrail(Trail_Tail)].

go_back_step(Action, Knowledge) :- go_back_turn(Action, Knowledge).

go_back_turn(Action, Knowledge) :-
	haveGold(NGolds), NGolds > 0,
	myWorldSize(Max_X, Max_Y),
	myTrail([ [OldAct,X,Y,Orient] | Trail_Tail ]),
	((OldAct=turnLeft,Action=turnRight);(OldAct=turnRight,Action=turnLeft)),
	Knowledge = [gameStarted,
	             haveGold(NGolds),
		     myWorldSize(Max_X, Max_Y),
		     myPosition(X, Y, Orient),
		     myTrail(Trail_Tail)].

go_down(Action, Knowledge) :-
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    Y \= 1,
    can_move_south(X, Y, Max_X, Max_Y, Visited),
    determine_down_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

can_move_south(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, south, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

determine_down_action(south, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
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
                 haveGold(NGolds)].

determine_down_action(west, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, south),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

determine_down_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= south,
    Orient \= west,
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

go_right(Action, Knowledge) :-
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    X \= Max_X,
    can_move_east(X, Y, Max_X, Max_Y, Visited),
    determine_right_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

can_move_east(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, east, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

determine_right_action(east, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
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
                 haveGold(NGolds)].

determine_right_action(south, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, east),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

determine_right_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= east,
    Orient \= south,
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

go_up(Action, Knowledge) :-
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    Y \= Max_Y,
    can_move_north(X, Y, Max_X, Max_Y, Visited),
    determine_up_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

can_move_north(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, north, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

determine_up_action(north, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
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
                 haveGold(NGolds)].

determine_up_action(east, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, north),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

determine_up_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= north,
    Orient \= east,
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

go_left(Action, Knowledge) :-
    not(breeze; stench),
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    X \= 1,
    can_move_west(X, Y, Max_X, Max_Y, Visited),
    determine_left_action(Orient, X, Y, Max_X, Max_Y, Action, Knowledge).

can_move_west(X, Y, Max_X, Max_Y, Visited) :-
    myVisited(Visited),
    forwardStep(X, Y, west, New_X, New_Y),
    New_Visited_XY is (New_Y - 1) * Max_Y + New_X,
    not(member(New_Visited_XY, Visited)).

determine_left_action(west, X, Y, Max_X, Max_Y, moveForward, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
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
                 haveGold(NGolds)].

determine_left_action(north, X, Y, Max_X, Max_Y, turnLeft, Knowledge) :-
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, west),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

determine_left_action(Orient, X, Y, Max_X, Max_Y, turnRight, Knowledge) :-
    Orient \= west,
    Orient \= north,
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds),
    shiftOrientRight(Orient, NewOrient),
    Knowledge = [gameStarted,
                 myWorldSize(Max_X, Max_Y),
                 myPosition(X, Y, NewOrient),
                 myTrail(Trail),
                 myVisited(Visited),
                 haveGold(NGolds)].

go_back(Action, Knowledge) :-
	myWorldSize(Max_X, Max_Y),
	myPosition(X,Y,Orient),
	myTrail(Trail),
	myVisited(Visited),
	haveGold(NGolds),
	Trail = [ [X_Old,Y_Old] | Trail_Tail ],
	forwardStep(X, Y, Orient, New_X, New_Y),
	New_X = X_Old,
	New_Y = Y_Old,
	Action = moveForward,
	Knowledge = [gameStarted,
			 myWorldSize(Max_X, Max_Y),
		     myPosition(X_Old,Y_Old,Orient),
		     myTrail(Trail_Tail),
			 myVisited(Visited),
		     haveGold(NGolds)].

get_go_back_state(Max_X, Max_Y, X, Y, Orient, Trail, Visited, NGolds) :-
    myWorldSize(Max_X, Max_Y),
    myPosition(X, Y, Orient),
    myTrail(Trail),
    myVisited(Visited),
    haveGold(NGolds).

go_back(Action, Knowledge) :-
    get_go_back_state(Max_X, Max_Y, X, Y, Orient, Trail, Visited, NGolds),
    shiftOrientLeft(Orient, NewOrient),
    Trail = [[X_Old, Y_Old] | Trail_Tail],
    forwardStep(X, Y, NewOrient, New_X, New_Y),
    New_X = X_Old,
    New_Y = Y_Old,
    Action = turnLeft,
    Knowledge = [gameStarted,
                myWorldSize(Max_X, Max_Y),
                myPosition(X, Y, NewOrient),
                myTrail(Trail),
                myVisited(Visited),
                haveGold(NGolds)].

go_back(Action, Knowledge) :-
    get_go_back_state(Max_X, Max_Y, X, Y, Orient, Trail, Visited, NGolds),
    shiftOrientRight(Orient, NewOrient),
    Action = turnRight,
    Knowledge = [gameStarted,
                myWorldSize(Max_X, Max_Y),
                myPosition(X, Y, NewOrient),
                myTrail(Trail),
                myVisited(Visited),
                haveGold(NGolds)].

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
