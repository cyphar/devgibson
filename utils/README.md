utils/
======

## Parsing the Hackers script

```
$ python2 parser.py hackers.txt > parsed.txt
$ xxd -i parsed.txt > data.h
$ vim data.h  # and patch it up by hand
```
