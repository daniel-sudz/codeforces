" syntax
syntax on

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
autocmd vimenter * ++nested colorscheme gruvbox
set number
set ruler

" compiling
autocmd filetype cpp nnoremap <F9> :w <CR> :!clear && /usr/local/Cellar/gcc/*/bin/g++-12 -std=c++20 % -o %:r && ./%:r <CR>

" remap brackets autocomplete
inoremap { {}<Left>
inoremap {<CR> {<CR>}<Esc>O
inoremap {{ {
inoremap {} {}

