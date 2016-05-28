package main

import (
	"fmt"
	"go/parser"
	"go/token"
	"go/ast"
)

func main() {
	fset := token.NewFileSet()

	f, err := parser.ParseFile(fset, "example_test.go", nil, 0)
	if err != nil {
		fmt.Println(err)
		return
	}

	for _, s := range f.Imports {
		fmt.Println(s.Path.Value)
	}

	for _, decl := range f.Decls {
		ast.Inspect(decl, func(node ast.Node) bool {
			fn, ok := node.(*ast.FuncDecl)
			if !ok {
				return false
			}
			fnName := fn.Name.Name
			for _, param := range fn.Type.Params.List {
				typeName := param.Type.(*ast.Ident).Name
				for _, name := range param.Names {
					println(fnName, name.Name, typeName)
				}
			}
			return false
		})
	}
}
