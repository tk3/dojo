const val: string = process.argv[2];
console.log(hello(val));

function hello(name: string): string {
  return 'Hello, ' + name;
}

