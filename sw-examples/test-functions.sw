the |range> => range(|1>, |6>, |0.5>) |>
the |sum> => arithmetic(|3>, |+>, |5>) |>
the |simm> => simm(|a> + |b> + |c>, |b>) |>

range |*> #=> range(|1>, |_self>) |>
the |range2> => range |4>

the |seq range> => sp2seq the |range2>
the |empty seq range> => sdrop tidy the |seq range>

the |negative range> => range(|-5>, |5>) |>
the |2nd negative range> => range(-|5>, |5>) |>

-- bugs out, in infinite loop of some sort:
-- the |bracket sp> => (|a> -2|b> . |c> -7|d> . |x> + 3|y>)

the |sp> => |a> -2|b> . |c> -7|d> . |x> + 3|y>
the |dropped sp> => sdrop the |sp>
