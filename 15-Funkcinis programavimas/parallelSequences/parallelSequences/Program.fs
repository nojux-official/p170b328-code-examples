open FSharp.Collections.ParallelSeq

[<EntryPoint>]
let main _ = 
    let numbers = seq {0L..100000L}
    let result = numbers |> PSeq.filter(fun n -> n % 2L = 0)
                         |> PSeq.map(fun n -> n * n)
                         |> PSeq.reduce(fun acc n -> acc + n)
                        
    printf $"%d{result}"
    0