|context> => |Fibonacci sequence>

fib |0> => |0>
fib |1> => |1>
n-1 |*> !=> arithmetic(|_self>, |->, |1>) |>
n-2 |*> !=> arithmetic(|_self>, |->, |2>) |>
fib |*> !=> arithmetic(fib n-1 |_self>, |+>, fib n-2 |_self>) |>

the |null> => fib |10>

