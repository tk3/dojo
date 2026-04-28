// https://learn.microsoft.com/ja-jp/dotnet/fsharp/language-reference/lists
printfn "Hello from F#"

let sample1 =
    let l = [ 1; 2; 3 ]
    printfn "%A" l
sample1

let sample2 =
    let listOfSqures = [ for i in 1..10 -> i * i ]
    printfn "%A" listOfSqures
sample2

let sample3 =
    let list1 = [ 1; 2 ]
    let list2 = [ 3; 4 ]
    let list3 = list1 @ list2
    printfn "%A" list3
sample3

let sample4 =
    let listEmpty = List.empty
    printfn "%A" listEmpty
sample4

let sample5 =
    let list = [ 1; 2; 3; ]
    printfn "list.IsEmpty is %b" (list.IsEmpty)
    printfn "list.Length is %d" (list.Length)
    printfn "list.Head is %d" (list.Head)
    printfn "list.Tail is %A" (list.Tail)
    printfn "list.Tail.Head is %d" (list.Tail.Head)
    printfn "list.Item(1) is %d" (list.Item(1))
sample5

let sample6 =
    let rec sum list =
        match list with
        | head :: tail -> head + sum tail
        | [] -> 0
    printfn "sum(5) is %d" (sum [ 2; 4; 8 ])
sample6

let sample7 =
    let list1 = [ 1; 2; 3; ]
    let list2 = [ 4; 5; 6; ]
    List.iter (fun x -> printfn "List.iter: element is %d" x) list1
    List.iteri (fun i x -> printfn "List.iter1: element %d is %d" i x) list1
    List.iter2 (fun x y -> printfn "List.iter2: element are %d %d" x y) list1 list2
    List.iteri2 (fun i x y ->
                    printfn "List.iteri2: element %d of list5 is %d element %d of list6 is %d" i x i y) list1 list2
sample7

let sample8 =
    let list = [ 1; 2; 3; ]
    let newList = List.map (fun x -> x + 1) list
    printfn "%A" newList
sample8

let sample9 =
    let list1 = [ 1; 2; 3; ]
    let list2 = [ 4; 5; 6; ]
    let sumList = List.map2 (fun x y -> x + y) list1 list2
    printfn "%A" sumList
sample9

let sample10 =
    let list1 = [ 1; 2; 3; ]
    let list2 = [ 4; 5; 6; ]
    let newList2 = List.map3 (fun x y z -> x + y + z) list1 list2 [ 2; 3; 4 ]
    printfn "%A" newList2
sample10

let sample11 =
    let list = [ 1; 2; 3; ]
    let newListAndIndex = List.mapi (fun i x -> x + i) list
    printfn "%A" newListAndIndex
sample11

let sample12 =
    let list1 = [ 1; 2; 3; ]
    let collectList = List.collect (fun x -> [for i in 1..3 -> x * i]) list1
    printfn "%A" collectList

