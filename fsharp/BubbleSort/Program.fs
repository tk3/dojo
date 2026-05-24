open System

let bubbleSort1 =
    let rnd = Random()
    let randomArray = [| for _ in 1..10 -> rnd.Next(1, 101) |]

    for i = 0 to randomArray.Length - 2 do
        for j = 0 to randomArray.Length - 2 - i do
            if randomArray[j] > randomArray[j + 1] then
                let tmp = randomArray[j]
                randomArray[j] <- randomArray[j + 1]
                randomArray[j + 1] <- tmp
    printfn "BubbleSort1 result: %A" randomArray

let rec bubbleSort2 (list: 'T list) =
    let rec bubblePass lst =
        match lst with
        | [] -> [], false
        | [x] -> [x], false
        | x :: y :: ys ->
            if x > y then
                let rest, _ = bubblePass (x ::ys)
                y :: rest, true
            else
                let rest, swapped = bubblePass (y:: ys)
                x :: rest, swapped

    let sortedList, swapped = bubblePass list
    if swapped then
        bubbleSort2 sortedList
    else
        sortedList


[<EntryPoint>]
let main _ =

    bubbleSort1

    let rnd = Random()
    let randomList = [ for _ in 1..10 -> rnd.Next(1, 101) ]

    let sortedList = bubbleSort2 randomList
    printfn "bubbleSort2       : %A" randomList
    printfn "bubbleSort2 result: %A" sortedList

    0
