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

the |words> => |the> + |hungry> . |dog> + |ate> . |some> . |food>
print-the |words> => print the |words>

the |ranked list> => rank split |Fred Sam Robert Max>
the |shuffled ranked list> => shuffle the |ranked list>

the |1st intersection> => intersection(3|a> + 1.2|b>, 3.5|a> + 0.9|b> + 5.13|c>) |>
the |2nd intersection> => intersection(|a1> + |a2> . 0.3|b1> + 0.5|b2>, 3|a1> + 0.9|a2> . 0.7|b2>) |>

-- test our similarity measure:
test |simm 1> => simm(|a>, |b>) |>
test |simm 2> => simm(3|a> + 1.2|b>, 3.5|a> + 0.9|b> + 5.13|c>) |>
test |simm 3> => simm(|a1> + |a2> . 0.3|b1> + 0.5|b2>, 3|a1> + 0.9|a2> . 0.7|b2>) |>

test |scaled simm 1> => scaled-simm(|a>, |b>) |>
test |scaled simm 2> => scaled-simm(3|a> + 1.2|b>, 3.5|a> + 0.9|b> + 5.13|c>) |>
test |scaled simm 3> => scaled-simm(|a1> + |a2> . 0.3|b1> + 0.5|b2>, 3|a1> + 0.9|a2> . 0.7|b2>) |>

