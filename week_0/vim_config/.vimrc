set tabstop=4
set number
set shiftwidth=4
set expandtab

set cursorline
set backspace=indent,eol,start

set colorcolumn=100
set nowrap
set smarttab

" set background=dark
set wildmenu
syntax on

"information abaut opened file"
set wildmenu
set laststatus=2
set statusline=%<%f\ [%Y%R%W]%1*%{(&modified)?'\ [+]\ ':''}%*%=%c%V,%l\ %P\ [%n]

"copy paste and scrolling with mouse"
 set mouse=a
 map <S-Insert> <MiddleMouse>
 map! <S-Insert> <MiddleMouse>

"key vombinations "
"saving"
imap <F2> <Esc>:w<CR>
map <F2> <Esc>:w<CR>
"reading a file"
imap <F3> <Esc>:read 
map <F3> <Esc>:read 

nnoremap ; :

nnoremap <silent> <F11> :NERDTreeToggle<CR>
map <C-Right> :bn<CR>
map <C-Left> :bp<CR>


"nnoremap <F9> :!gcc -o %< %

"compilation shourt cuts F% cumpile, F9 exec
" If some kind of C/C++ file is opened, check for Makefile and:
" - if file is present, bind F5 to make
" - if file is absent, bind F5 to "make without Makefile"
" In any case, if compilation wasn't successful, error list will be displayed
function! BindF5_C()
    "http://habrahabr.ru/blogs/vim/40369/
    if filereadable("Makefile")
        set makeprg=make
         map <f5>      :w<cr>:make<cr>:cw<cr>
        imap <f5> <esc>:w<cr>:make<cr>:cw<cr>
    else
         map <f5>      :w<cr>:make %:r<cr>:cw<cr>
        imap <f5> <esc>:w<cr>:make %:r<cr>:cw<cr>
    endif
endfunction
au FileType c,cc,cpp,cxx,h,hpp,hxx,s call BindF5_C()

function! BindF9_C()
    "http://habrahabr.ru/blogs/vim/40369/
    if filereadable("Makefile")
        set makeprg=make
         map <f9>      :w<cr>:make<cr>:cw<cr>:!./%<<cr>
        imap <f9> <esc>:w<cr>:make<cr>:cw<cr>:!./%<<cr>
    else
         map <f9>      :w<cr>:make %:r<cr>:cw<cr>:!./%<<cr>
        imap <f9> <esc>:w<cr>:make %:r<cr>:cw<cr>:!./%<<cr>
    endif
endfunction
au FileType c,cc,cpp,h,hpp,s call BindF9_C()
