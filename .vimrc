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
autocmd filetype cpp nnoremap <F9> :w <Bar> :! bash -c 'clear && bash -c "$CFCOMPILE % -o %:r" && echo "compiled" && time ./%:r' <CR>

" remap brackets autocomplete
inoremap { {}<Left>
inoremap {<CR> {<CR>}<Esc>O<tab>
inoremap {{ {
inoremap {} {}

" debug
packadd termdebug
autocmd filetype cpp nnoremap <F8> :w <Bar> :! bash -c "$CFCOMPILE % -o %:r" <Bar> :Termdebug %:r <CR> 
let g:termdebug_wide=1 " https://stackoverflow.com/questions/58471029/initial-window-split-in-termdebug-vim

