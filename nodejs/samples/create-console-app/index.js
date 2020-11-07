#!/usr/bin/env node

const fs = require('fs');
const { spawnSync } = require('child_process');

console.log('process.argv');
console.log(process.argv);

const args = process.argv.slice(2);
const project_name = args[0];

// -----------------------------------------------------------------------------
// mkdir console-app
// cd ./console-app/
fs.mkdirSync(project_name);
process.chdir(project_name);

// -----------------------------------------------------------------------------
// git init
spawnSync('git', ['init'], { stdio: 'inherit' });

// -----------------------------------------------------------------------------
// create a gitignore
createGitignore();

// -----------------------------------------------------------------------------

spawnSync('npm', ['init', '-y'], { stdio: 'inherit' });
spawnSync('npm', ['install', '--save-dev', 'webpack', 'webpack-cli', 'typescript', 'ts-loader'], { stdio: 'inherit' });
spawnSync('npx', ['tsc', '-init'], { stdio: 'inherit' });



const webpackConfigFilename = './webpack.config.js';
const webpackConfigContent = `module.exports = {
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
`;

fs.writeFileSync(webpackConfigFilename, webpackConfigContent);

// -----------------------------------------------------------------------------

fs.mkdirSync('./src');

const sourceFilename = './src/index.ts';
const sourceContent = `const val: string = process.argv[2];
console.log(hello(val));

function hello(name: string): string {
  return 'Hello, ' + name;
}
`;

fs.writeFileSync(sourceFilename, sourceContent);

// -----------------------------------------------------------------------------

fs.mkdirSync('./bin');

const mainFilename = './bin/console-app.js';
const mainContent = `#!/usr/bin/env node
require('../dist/main.js');

`;


// -----------------------------------------------------------------------------

let json = JSON.parse(fs.readFileSync('./package.json', 'utf8'));

json['bin'] = { 'console-app': './bin/console-app.js' };
json['scripts']['build'] = 'webpack';
json['scripts']['exec'] = 'node dist/main.js';

fs.writeFileSync('./package.json.x', JSON.stringify(json, null, 2));

// -----------------------------------------------------------------------------

// create a gitignore
// https://github.com/github/gitignore/blob/master/Node.gitignore
function createGitignore() {
  const gitignoreNodejsUrl = 'https://github.com/github/gitignore/raw/master/Node.gitignore';
  const result = spawnSync('curl', ['-L', gitignoreNodejsUrl], {
    stdio: 'pipe',
    encoding: 'utf-8'
  });
  const savedOutput = result.stdout;
  fs.writeFileSync('gitignore', savedOutput);
}

