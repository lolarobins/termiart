```
  ⣀⣀⡀                                  ⣶⣶⡆                   ⢀⣀⣀
 ⢠⣿⣿⠇                               ⢀⣀⣙⣛⠁                   ⣼⣿⡿
⠛⣿⣿⡟⠛⢣⣶⣿⠟⣻⣿⡞⢻⣿⣿⣿⣿⣿⡗⢻⣿⣿⣷⢿⣿⣷⡾⣿⣿⡇ ⠛⣿⣿⡿ ⢀⣴⣿⡿⠻⣿⣿⡟⠘⢻⣿⣿⣿⣿⣿⡟⢻⣿⣿⠛⠛
⢸⣿⣿⢁⣀⣿⣿⣷⡾⠿⠛⠁⣾⣿⡿⠁⠈⠉ ⣼⣿⡿⠁⣿⣿⡟⢠⣿⣿⢇⡀⢰⣿⣿⢃⡀⣿⣿⡟ ⣸⣿⣿⢁⡀⣾⣿⡿⠁⠈⠉ ⣿⣿⡏⣀
⢿⣿⣿⠟⠁⢿⣿⣧⣤⡾⠗⢰⣿⣿⠃   ⢰⣿⣿⠃⣸⣿⣿⠁⢾⣿⣿⡿⠃⢿⣿⣿⡿⠃⠻⣿⣷⣴⢿⣿⣿⠟⢱⣿⣿⠃   ⠸⣿⣿⡿⠋ 
```

## termiart - terminal art generator
terminal utility written in c to convert image files to fun terminal art designs!

### features
- supports truecolor terminals.
- generates unicode dot patterns from non-transparent png image pixels.

### examples

### usage
- `-i <input>` input file. **required**
- `-t <input_type>` input file type, defaults to png. **currently only supported**
- `-o <output>` output file, defaults to stdout.
- `-p <pattern>` specify desired pattern: currently only `dots`.
- `-c <color_opts>` color options specific to pattern. (example: `truecolor`, `truecolor-bold`)
- `-v` get program version.

### installation
- requires libpng as a dependency.
- run `make install` inside of termiart project directory.

### todo:
- resizing and scaling options to fit to terminal or desired px/char value.
- support gif animations.
- support svg and jpeg image files.
- font rasterization.
- gradient generation.
- 16 color output.
- neofetch color output support.
- more pattern options.
