#light

let FizzBuzz x =
  match x with
  | x when x % 3 = 0 && x % 5 = 0 ->
    "Fizz Buzz"
  | x when x % 3 = 0 ->
    "Fizz"
  | x when x % 5 = 0 ->
    "Buzz"
  | x ->
    sprintf "%d" x

[<EntryPoint>]
let main (args: string[]) =
  [1..15] |> List.map (fun x -> FizzBuzz x) |> printfn "%A"
  0

