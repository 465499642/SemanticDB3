|context> => |The Bottle's of Beer song>


n-1 |*> #=> arithmetic(|_self>, |->, |1>) |>

bottles |0> => |no more bottles>
bottles |1> => |1 bottle>
bottles |*> #=> |_self> __ |bottles>

first-line |*> #=> bottles |_self> __ |of beer on the wall,> __ bottles |_self> __ |of beer.>

second-line |*> #=> |Take one down and pass it around,> __ bottles n-1 |_self> __ |of beer on the wall.>
second-line |0> #=> |Go to the store and buy some more,> __ bottles max |bottles> __ |of beer on the wall.>

row |*> #=> first-line |_self> . second-line |_self> . |>

max |bottles> => |10>

the |result> => sdrop tidy print row sreverse sp2seq range(|0>, max |bottles>) |>

