filetype plugin indent on
syntax on

setlocal autoindent

if has("autocmd")
  autocmd FileType c    setlocal sw=4 sts=0 ts=4
  autocmd FileType ruby setlocal sw=2 sts=0 ts=2 expandtab
end

augroup vimrcEx
  au BufRead * if line("'\"") > 0 && line("'\"") <= line("$") |
    \ exe "normal g`\"" | endif
augroup END

filetype plugin indent on
syntax on

set laststatus=2
set statusline=%<%f\ %m%r%h%w\ %=[%l,%v][%P][%{&fenc!=''?&fenc:&enc}][%{&ff}]

"
" Vundle.vim
" - git clone http://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
"
set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/vundle/
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'wakatime/vim-wakatime'

call vundle#end()            " required
filetype plugin indent on    " required

