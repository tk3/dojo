#light

let FizzBuzz x y =
  for i = x to y do
    if i % 3 = 0 && i % 5 = 0 then
      printfn "Fizz Buzz"
    elif i % 3 = 0 then
      printfn "Fizz"
    elif i % 5 = 0 then
      printfn "Buzz"
    else
      printfn "%d" i

[<EntryPoint>]
let main (args: string[]) =
  FizzBuzz 0 100
  0

