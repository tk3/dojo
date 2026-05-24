open System

let bubbleSort1 (array: 'T array) =
    for i = 0 to array.Length - 2 do
        for j = 0 to array.Length - 2 - i do
            if array[j] > array[j + 1] then
                let tmp = array[j]
                array[j] <- array[j + 1]
                array[j + 1] <- tmp
    ()

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

    let rnd = Random()
    let randomList = [ for _ in 1..10 -> rnd.Next(1, 101) ]
    let randomArray = Array.ofList randomList

    printfn "bubbleSort1       : %A" randomArray
    bubbleSort1 randomArray
    printfn "bubbleSort1 result: %A" randomArray

    let sortedList = bubbleSort2 randomList
    printfn "bubbleSort2       : %A" randomList
    printfn "bubbleSort2 result: %A" sortedList

    0
