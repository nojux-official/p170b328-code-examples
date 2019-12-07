open FSharp.Collections.ParallelSeq

[<EntryPoint>]
let main argv = 
    let numbers = seq {0..100000}
    let result = numbers |> PSeq.filter(fun n -> n % 2 = 0)
                         |> PSeq.map(fun n -> n * n)
                         |> PSeq.reduce(fun acc n -> acc + n)
                        
    printf "%d" result
    0
