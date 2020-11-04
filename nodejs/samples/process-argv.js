#!/usr/bin/env node

console.log('process.argv');
console.log(process.argv);
console.log(process.argv.slice(2));

/*
mkdir console-app
cd ./console-app/

#git init
#create a gitignore

npm init -y
npm install --save-dev webpack webpack-cli typescript ts-loader
npx tsc -init


cat <<EOF > ./webpack.config.js
module.exports = {
  entry: './src/index.ts',
  target: 'node',
  module: {
    rules: [
      {
        test: /\.ts$/,
        use: ['ts-loader'],
        exclude: /node_modules/
      }
    ]
  },
  resolve: {
    extensions: [ '.tsx', '.ts', '.js' ]
  }
};

EOF


mkdir ./src

cat <<EOF > ./src/index.ts
const val: string = process.argv[2];
console.log(hello(val));

function hello(name: string): string {
  return 'Hello, ' + name;
}

EOF


mkdir ./bin

cat <<EOF > ./bin/console-app.js
#!/usr/bin/env node
require('../dist/main.js');

EOF

----
# $ vi package.json "build" を追加する
# $ vi package.json "bin" を追加する

const fs = require('fs');

var json = JSON.parse(fs.readFileSync('./package.json', 'utf8'));

json['bin'] = { 'console-app': './bin/console-app.js' };
json['scripts']['build'] = 'webpack';
json['scripts']['exec'] = 'node dist/main.js';

fs.writeFileSync('./package.json.x', JSON.stringify(json, null, 2));

*/
