open System.Linq

[<EntryPoint>]
let main argv = 
    let numbers = seq {0..100000}
    let result = numbers.AsParallel()
                        .Where(fun n -> n % 2 = 0)
                        .Select(fun n -> n * n)
                        .Aggregate(fun acc n -> acc + n)
    printf "%d" result
    0
