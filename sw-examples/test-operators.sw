op1 |*> #=> |op1:> __ |_self>
op2 |*> #=> |op2:> __ |_self>
op3 |*> #=> |op3:> __ |_self>
op4 |*> #=> |op4:> __ |_self>
op5 |*> #=> |op5:> __ |_self>
op6 |*> #=> |op6:> __ |_self>
op7 |*> #=> |op7:> __ |_self>
op8 |*> #=> |op8:> __ |_self>
op9 |*> #=> |op9:> __ |_self>

op |foo> #=> (op1 + op2 op3 - op4 op5 . op6 ) |a>
op |bah> => op |foo>

op |bah2> => (op1 . op2) |b>
op |bah3> => (op1 - op4 op5 . op6 ) |c>
op |bah4> => (op1 + op2 op3 - op4 op5 . op6 ) |d>

-- op |foo2> #=> (op1 + op2 op3 - op4 op5 . op6 + op7 ) |e>
-- op |foo2> #=> (op1 + op2 op3 . op4 op5 - op6 + op7 ) |e>
op |foo2> #=> (op1 . op4 op5 - op6 + op7 ) |e>
op |bah5> => op |foo2>

-- op |foo3> #=> op1 |f> . op2 |f>
op |foo3> #=> |y> . |z>
op |bah6> => op |foo3>

