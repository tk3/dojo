open System

[<EntryPoint>]
let main _ =
    let rnd = Random()
    let randomArray = [| for _ in 1..10 -> rnd.Next(1, 101) |]

    for i = 0 to randomArray.Length - 2 do
        for j = 0 to randomArray.Length - 2 - i do
            if randomArray[j] > randomArray[j + 1] then
                let tmp = randomArray[j]
                randomArray[j] <- randomArray[j + 1]
                randomArray[j + 1] <- tmp

    printfn "%A" randomArray
    0
