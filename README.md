# morse.c

A simple cli to transform text to morse and morse to text.

## Usage

```
$ morse -e "Hello World"
.... . .-.. .-.. --- / .-- --- .-. .-.. -..
```

```
$ morse -d ".... . .-.. .-.. --- / .-- --- .-. .-.. -.."
HELLO WORLD
```

```
$ morse -h
Usage: morse [options...]
 -e, --encode <text>  Encode the text and show the morse value
 -d, --decode <morse> Decode the morse and show the text value
 -h, --help           Show this help message and quit
 -v, --version        Show version number and quit
```

## Build

This is the recommended way to build this project :

```
gcc src/morse.c -Wall -O3 -march=native -o bin/morse
```
