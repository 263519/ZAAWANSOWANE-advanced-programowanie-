#define ROTATE_SPEED 30
/*
* Przykladowy zestaw polecen«
*/
Begin_Parallel_Actions
Set Ob_A 2 0 0 30 0 0 // Polozenie obiektu A
Set Ob_B 10 10 5 0 0 0 // Polozenie obiektu B
End_Parallel_Actions
Begin_Parallel_Actions
Rotate Ob_A OX ROTATE_SPEED 40
End_Parallel_Actions
Begin_Parallel_Actions Pause 1000 /* Zawieszenie na 1 sek. */ End_Parallel_Actions
Begin_Parallel_Actions
Move Ob_A 10 10
Rotate Ob_B ROTATE_SPEED OZ 60 /* Rotate i Move wykonywane razem */
Move Ob_B 10 20 /* powoduja jazde po luku */
End_Parallel_Actions