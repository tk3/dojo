// https://learn.microsoft.com/ja-jp/dotnet/fsharp/language-reference/lists
printfn "Hello from F#"

let l = [ 1; 2; 3 ]
printfn "%A" l

let listOfSqures = [ for i in 1..10 -> i * i ]
printfn "%A" listOfSqures

let list1 = [ 1; 2 ]
let list2 = [ 3; 4 ]
let list3 = list1 @ list2
printfn "%A" list3

let listEmpty = List.empty
printfn "%A" listEmpty

let list4 = [ 1; 2; 3; ]
printfn "list4.IsEmpty is %b" (list4.IsEmpty)
printfn "list4.Length is %d" (list4.Length)
printfn "list4.Head is %d" (list4.Head)
printfn "list4.Tail is %A" (list4.Tail)
printfn "list4.Tail.Head is %d" (list4.Tail.Head)
printfn "list4.Item(1) is %d" (list4.Item(1))

let rec sum list =
    match list with
    | head :: tail -> head + sum tail
    | [] -> 0
printfn "sum(5) is %d" (sum [ 2; 4; 8 ])

let list5 = [ 1; 2; 3; ]
let list6 = [ 4; 5; 6; ]
List.iter (fun x -> printfn "List.iter: element is %d" x) list5
List.iteri (fun i x -> printfn "List.iter1: element %d is %d" i x) list5
List.iter2 (fun x y -> printfn "List.iter2: element are %d %d" x y) list5 list6
List.iteri2 (fun i x y ->
                printfn "List.iteri2: element %d of list5 is %d element %d of list6 is %d" i x i y) list5 list6

let list7 = [ 1; 2; 3; ]
let newList = List.map (fun x -> x + 1) list7
printfn "%A" newList

let list8 = [ 1; 2; 3; ]
let list9 = [ 4; 5; 6; ]
let sumList = List.map2 (fun x y -> x + y) list8 list9
printfn "%A" sumList

let newList2 = List.map3 (fun x y z -> x + y + z) list8 list9 [ 2; 3; 4 ]
printfn "%A" newList2

let newListAndIndex = List.mapi (fun i x -> x + i) list8
printfn "%A" newListAndIndex

