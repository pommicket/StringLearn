# StringLearn
Rate strings, and then generate new ones using those ratings.

StringLearn works by keeping track of the frequencies of n-grams.

Executables can be found in the build directory, but if you want to compile the source code, just run `make` in the src directory.


**Windows**  
Creating a string with a *.stl file:
```bash
cd StringCreate/build/Windows
StringCreate <stlfile> [--stopX] -l <minlengthorlength> [-p newNgramChance]
```
For documentation, run:
```bash
StringCreate --help
```
Rating the string, and saving the rating to a *.stl file:
```bash
cd build/Windows
StringLearn <string> -r <rating> -s <stlfile>
```
For documentation, run:
```bash
StringLearn --help
```


**GNU/Linux**  
Creating a string with a *.stl file:
```bash
cd StringCreate/build/GNULinux
./StringCreate <stlfile> [--stopX] -l <minlengthorlength> [-p newNgramChance]
```
For documentation, run:
```bash
./StringCreate --help
```
Rating the string, and saving the rating to a *.stl file:
```bash
cd build/GNULinux
./StringLearn <string> -r <rating> -s <stlfile>
```
For documentation, run:
```bash
./StringLearn --help
```


Mac OS X is not supported.
