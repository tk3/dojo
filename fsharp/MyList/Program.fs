
type MyList<'T> =
    | Empty
    | Cons of 'T * MyList<'T>

let length list =
    let rec loop acc currentList =
        match currentList with
        | Empty -> acc
        | Cons(_, tail) -> loop (acc + 1) tail
    loop 0 list

let sum list =
    let rec loop acc currentList =
        match currentList with
        | Empty -> acc
        | Cons(x, tail) -> loop (acc + x) tail
    loop 0 list

let contains target list =
    let rec loop currentList =
        match currentList with
        | Empty -> false
        | Cons(x, tail) ->
            if x = target then true
            else loop tail
    loop list

let max list =
    match list with
    | Empty ->
        failwith "List is empty"
    | Cons(first, tail) ->
        let rec loop tail first =
            match tail with
            | Empty -> first
            | Cons(x, newTail) ->
                if first < x then loop newTail x
                else loop newTail first
        loop list 0

let maxSome list =
    match list with
    | Empty ->
        None
    | Cons(first, tail) ->
        let rec loop tail first =
            match tail with
            | Empty -> Some(first)
            | Cons(x, newList) ->
                if first < x then loop newList x
                else loop newList first
        let result = loop tail first
        Some(result)

let reverse list =
    let rec loop currentList acc =
        match currentList with
        | Empty ->
            acc
        | Cons(x, tail) ->
            let newAcc = Cons(x, acc)
            loop tail newAcc
    loop list Empty

let mapDouble list =
    let rec loop currentList acc =
        match currentList with
        | Empty ->
            reverse acc
        | Cons(x, tail) ->
            let newAcc = Cons(x * 2, acc)
            loop tail newAcc
    loop list Empty

let map f list =
    let rec loop currentList acc =
        match currentList with
        | Empty ->
            reverse acc
        | Cons(x, tail) ->
            let result = f x
            loop tail (Cons(result, acc))
    loop list Empty

let filter f list =
    let rec loop currentList acc =
        match currentList with
        | Empty ->
            reverse acc
        | Cons(x, tail) ->
            if (f x) then
                loop tail (Cons(x, acc))
            else
                loop tail acc
    loop list Empty

let rec fold f state list =
    match list with
    | Empty ->
        state
    | Cons(x, tail) ->
        let newState = f state x
        fold f newState tail

let foldMap f list =
    let reversedList = fold (fun acc x -> Cons(f x, acc)) Empty list
    reverse reversedList

let foldFilter f list =
    let folded =
        fold (fun acc x ->
            if f x then
                Cons(x, acc)
            else acc
        ) Empty list

    reverse folded


[<EntryPoint>]
let main argv =
    let list = Empty
    let list2 = Cons(1, list)
    let list3 = Cons(2, list2)
    let list4 = Cons(3, list3)
    let list5 = Cons(4, list4)
    printfn "%A" list5

    printfn "list5 length = %d" (length list5)

    printfn "list5 sum = %d" (sum list5)

    printfn "Has 2? %b" (contains 2 list5)
    printfn "Has 5? %b" (contains 5 list5)

    printfn "Max %d" (max list5)
    try
        printfn "Max %d" (max Empty)
    with
    | ex ->
        printfn "Message: %s" ex.Message

    printfn "MaxSome %A" (maxSome Empty)

    printfn "Reverse %A" (reverse list5)

    printfn "mapDouble %A" (mapDouble list5)

    printfn "map %A" (map (fun x -> x * 10) list5)

    printfn "filter %A" (filter (fun x -> x % 2 = 0) list5)

    printfn "fold(length) %A" (fold (fun acc x -> acc + 1) 0 list5)
    printfn "fold(sum) %A" (fold (fun acc x -> acc + x) 0 list5)
    printfn "fold(reverse) %A" (fold (fun acc x -> Cons(x, acc)) Empty list5)
    printfn "fold(map) %A" (foldMap (fun x -> x + 1) list5)
    printfn "fold(filter) %A" (foldFilter (fun x -> x = 3) list5)

    0

