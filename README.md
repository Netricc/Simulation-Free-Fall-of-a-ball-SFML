# SFML C++ Ball Simulation

A very simple free fall of a ball

# Prerequisites

1. [Git](https://git-scm.com/)
2. [VSCode](https://code.visualstudio.com/)
3. [Homebrew](https://brew.sh)
4. [Make](https://www.gnu.org/software/make/#download)

# Setup

First, clone this repo

```
git clone https://github.com/beatzoid/sfml-macos
```

<br />

Then, open it in VSCode,

install SFML using homebrew

```
brew install sfml
```

and get the path to the installation

```
brew info sfml
```

You will see something like `/opt/homebrew/Cellar/sfml/2.5.1_2` in the output. If the numbers differ it's ok.
First, you need to edit the `Makefile` and change the `SFML_PATH` variable to the path you got above. Then, open `.vscode/c_cpp_properties.json` and change the second entry in the `includePath` array to the path you got.

Then, press `Cmd+Shift+B` in VSCode to build and `FN+F5` to run. If it works, you should see a window with a black background and cyan circle. Once you exit the program, you should also see the number "5" in the terminal. Congrats, you can now make whatever you want with SFML!

<br>

Then Just tyee `make` to build the project or `make clean` to clean build, then launche the program with `./main` in here : `/bin/main`.

# Contact

Email : nawabsn911@gmail.com
