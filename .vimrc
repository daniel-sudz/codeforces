" syntax
syntax on

" windows bell sound
set belloff=all

" format
" https://stackoverflow.com/questions/1646850/in-vim-can-i-format-a-whole-file-and-end-with-the-cursor-where-it-started
map <silent> <C-f> gg=G<C-o><C-o> 

" disable swapfile due to docker mount issues
" https://github.com/moby/moby/issues/15793
set noswapfile

" spacing
set tabstop=4
set autoindent
set shiftwidth=4
set softtabstop=4
set smarttab
set expandtab
set smartcase

" theme
set background=dark
highligh TabLineFill cterm=NONE term=NONE ctermfg=black ctermbg=black
set number
set ruler
set nowrap

" compiling
autocmd filetype cpp nnoremap <F9> :w <Bar> :! clear && /usr/bin/time --format="compiled in \%e seconds" g++ $CFCOMPILE % -o ../out/%:r && /usr/bin/time --format="used \%U second of compute" ../out/%:r <CR>

" remap brackets autocomplete
inoremap { {}<Left>
inoremap {<CR> {<CR>}<Esc>O<tab>
inoremap {{ {
inoremap {} {}

" sync clipboard with system 
set clipboard=unnamed

