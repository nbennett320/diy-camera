# diy camera source code

### prerequisites (mac)

```
xcode-select --install
clang++ --version # <- make sure this works
```

### compiling/workspace stuff

```makefile
make # build default
make debug # debug build
make release # optimized release build
make clean # clean up binaries
```

I usually clean the binaries and recompile
like this:

```bash
make clean && make -j8
```

### how to run

```bash
./diy-camera --input ../my/file.jpg --amount 50 --filter bw
```

#### Arguments

- `-f`, `--file`
  - input file for debugging filters

#### Example

```bash
./diy-camera --input ../my/file.jpg --amount 50 --filter bw
```
