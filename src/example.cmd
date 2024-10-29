#define ROTATE_SPEED 30
/*
* Przykladowy zestaw polecen
*/
Set Ob_A 2 0 3 30 10 0 // Polozenie obiektu A
Set Ob_B 10 10 3 0 0 20 // Polozenie obiektu B
Rotate Ob_B OY ROTATE_SPEED 40
Pause 1000 /* Zawieszenie dziaªania na 1 sek. */
Move Ob_A 10 10
Rotate Ob_B OZ ROTATE_SPEED 60
Move Ob_B 10 20