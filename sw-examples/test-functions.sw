the |range> => range(|1>, |6>, |0.5>) |>
the |sum> => arithmetic(|3>, |+>, |5>) |>
the |simm> => simm(|a> + |b> + |c>, |b>) |>

range |*> #=> range(|1>, |_self>) |>
the |range2> => range |4>

the |seq range> => sp2seq the |range2>
the |empty seq range> => sdrop tidy the |seq range>
