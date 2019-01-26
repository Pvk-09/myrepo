# Docreator

Welcome to **Docreator**, a simple tool to automatically create MarkDown documentation based on the comments in your projects!

# WHY?

Because I personally dislike writing docs(They're painful) and really really prefer writings comments(Which I don't, ironically...)!

# HOW?

# How to use?

The Usage is quite easy all you have to do is open Docreator.exe from a console and give it the path to the directory where your source and header files are(It's not yet recursive) it'll the automatically read all the files and create documentation based on the comments!

```docreator <path>``` 

## How to comment?

The commenting inside your file is easy as well, all you need to do is add in a little bit of syntax based comments to let docreator know you want that particular thing documented!

There are 4 major parts to commenting

### Classes

```cpp
//-->DOC_CLASS
// A simple wrapper for the std::string class!
class XString
{
  ...
};
```

### Structs

```cpp
//-->DOC_STRUCT
// A simple linked list struct!
struct linkedList
{
  ...
};
```

### Members

```cpp
//-->DOC_MEMBER
// A pointer to foreground Color.
NColor* foreground;
```

### Functions

```cpp
//-->DOC_FUNC
// calculate the sum of two given numbers.
// a: first number
// b: second number
// returns: the sum of the first and the second number
int Sum(int a, int b)
{
  return a + b;
}
```

###### **NOTE:** DO NOT USE THE FUNCTION DOCUMENTATION COMMENT (//-->DOC_FUNC) ON CONSTRUCTOR FUNCTIONS AS THEY REQUIRE ANOTHER METHOD OF PARSING MAINLY DUE TO THE USE OF THE "MEMBER INITIALIZER" CAPABILITY. 

###### //-->DOC_CTOR WILL BE ADDED SOON!

# LICENSE

MIT License

Copyright (c) 2018 Nirex0

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# CONTACT

Nirex.0@gmail.com
