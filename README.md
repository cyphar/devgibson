## `/dev/gibson` ##
Because sometimes you feel like there aren't enough Hackers in your goddamn kernel.
We're here to fix you right up.

[![They're in the Kernel!](http://img.youtube.com/vi/szsagYpsyig/0.jpg)](http://youtu.be/szsagYpsyig)

### Dependencies ###
In order to build `/dev/gibson` you need to have the relevant kernel header pages as well as a working build toolchain.

### Building ###
What use is a cool-ass one-time project if you can't `make` it?

```shell
$ make
make -C /lib/modules/<kernel>/build M=<pwd>
make[1]: Entering directory '/usr/lib/modules/<kernel>/build'
  LD      <pwd>/built-in.o
  CC [M]  <pwd>/plague.o
  CC [M]  <pwd>/scripts/hackers.o
  LD [M]  <pwd>/gibson.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      <pwd>/gibson.mod.o
  LD [M]  <pwd>/gibson.ko
make[1]: Leaving directory '/usr/lib/modules/<kernel>/build'
```

### Usage ###
Now that you've got the compiled module, time to inject that bad boy into your precious kernel.
Here be dragons and creatures that will make you fear the dreaded "Oops!".

```shell
$ sudo insmod gibson.ko
```

If you don't have `sudo`, you need to hack the gibson a bit harder before you can get into the kernel.

### License ###
```
devgibson: hackers in 'yo kernel!
Copyright (C) 2015 @cyphar <cyphar@cyphar.com>
Copyright (C) 2015 @sysr-q <chris@gibsonsec.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
