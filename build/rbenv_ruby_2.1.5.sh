#!/bin/sh

sudo yum -y install gcc readline-devel libyaml-devel openssl-devel
# sudo apt install -y libreadline-dev libyaml-dev libssl-dev

git clone https://github.com/sstephenson/rbenv.git ~/.rbenv
echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(rbenv init -)"' >> ~/.bashrc
source ~/.bashrc
git clone https://github.com/sstephenson/ruby-build.git ~/.rbenv/plugins/ruby-build
rbenv install 2.1.5
rbenv global 2.1.5
