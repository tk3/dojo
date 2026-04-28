open System

[<EntryPoint>]
let main _ =
    let rnd = Random()
    let randomArray = [| for _ in 1 .. 10 -> rnd.Next(1, 101) |]

    for i = 0 to randomArray.Length - 1 do
        let mutable target = i 
        let mutable minVal = randomArray[i]
        for j = i to randomArray.Length - 1 do
            if minVal > randomArray[j] then
                minVal <- randomArray[j]
                target <- j

        let tmp = randomArray[i]
        randomArray[i] <- randomArray[target]
        randomArray[target] <- tmp

    printfn "%A" randomArray

    0
