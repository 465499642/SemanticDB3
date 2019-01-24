op1 |y> => |op1: y>
op2 |op1: y> => |op2: op1: y>
op |foo> #=> op2 3^4 op1 |y>

op1 |x> => |op1: x>
op2 |op1: x> => |op2: op1: x>
op |bah> !=> op2 3^4 op1 |x>

op |foo2> !=> op2 3^3 op1 (2|x> + 7|y>)

op |foo3> !=> op2 3^3 op1 2 |x> - op1 7 |y> . op1 |x> __ op1 |y>

