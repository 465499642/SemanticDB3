op |*> #=> |op:> __ |_self>

op2 |foo> => op |x>

op3 |*> #=> |op3:> __ |_self3>

op4 |*> !=> |op4:> __ |_self>
op5 |bah> => op4 |a>

op6 (*) #=> |one>
op7 (*,*) #=> |two>

op8 (*,*) #=> 3|_self0> . 5|_self1> . 7|_self2>

op9 |bah> #=> fn( 2|x> + 3.2|y> - 5.7|z> ) |>
op10 |bah> #=> fn(3|Sam>, |x> + op|y>) |>
op11 |bah> #=> fn(|x>, |y> , |z>) |>

op12 |bah> #=> ( op1 + op2 op3 - op4 op5) |>

