module MyModule1 =
    let module1Value = 100

    let module1Function x =
        x + module1Value

let a = MyModule1.module1Function 10
printfn "%d" a

