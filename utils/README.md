utils/
======

## Parsing the Hackers script

```
$ python2 parser.py hackers.txt 2>/dev/null | head -n740 > ../scripts/hackers.h
```

Where `740` = `number of lines` - `number of credit lines`.
