op1 |y> => |op1: y>
op2 |op1: y> => |op2: op1: y>
op |foo> !=> op2 3^4 op1 |y>

op1 |x> => |op1: x>
op2 |op1: x> => |op2: op1: x>
op |bah> !=> op2 3^4 op1 |x>

op |foo2> !=> op2 3^3 op1 (2|x> + 7|y>)

op |foo3> !=> op2 3^3 op1 2 |x> - op1 7 |y> . op1 |x> __ op1 |y>

op |foo4> !=> - op2 3^3 op1 2 |x>

op3 |op2: op1: x> => |op3: op2: op1: x>
op5 |y> => |op5: y>
op4 |op5: y> => |op4: op5: y>
op2 |op4: op5: y> => |op2: op4: op5: y>
op3 |op2: op4: op5: y> => |op3: op2: op4: op5: y>
op6 |z> => |op6: z>
op2 |op6: z> => |op2: op6: z>
op3 |op2: op6: z> => |op3: op2: op6: z>

op |foo5> !=> (  ( (2 op1 |x> + op4 op5 |y> - op6 |z>) )  )
op |foo6> !=> op2 (2 op1 |x> + op4 op5 |y> - op6 |z>)
op |foo7> #=> op3 7^2 op2 (2 op1 |x> + op4 op5 |y> - op6 |z>)

