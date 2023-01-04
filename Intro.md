Create a new empty C++ project, called AdventOfCode2022.

# Create the main loop

First of all, always start with the main loop.
Pretty straight forward step:

Add a new item as a new CPP Source file, called main.cpp.

![Pasted image 20221202101011](https://user-images.githubusercontent.com/14072620/206445947-31654e33-4ba8-463e-975d-a4dc24ceceed.png)

![Pasted image 20221202101047](https://user-images.githubusercontent.com/14072620/206445977-0e29dbe6-5f45-4dc4-b224-2e5acd3d03b2.png)

# Entry point code

Put the code inside the main.cpp file:

```
#include <iostream>

extern void Day1();

int main()
{
  Day1();

  system( "pause" ); // only for windows
  return 0;
}
```

We are now ready for [Day 1](https://github.com/gastoudou/AdventOfCode2022/blob/main/Day1/Day1.md).

# Code explanation

`#include <iostream>` create a reference to the stream input/output system on the standard library. This will allow us to call functions to display text in the console (pretty huge file btw).

`extern void Day1();` declaration of the Day1() function. This function is declared as extern, because it will be defined in the Day1.cpp file.

`int main()` entry point of the program. No arguments here, as we are managing everything by hand in the DayXX functions.

`Day1();` call of the DayXX function.

`system( "pause" );` this is a windows specific function to print "Press any key to continue" and wait for an input. It could be replaced by `std::cout << std::endl << "Press any key to continue." << std::endl; std::cin.ignore();`

`return 0;` not necessary, but usually, we are returning 0 if everything went right.

# An easy way to include standard libraries

If we continue like that, we will need to include for most of the files the iostream header, or vector, or map, etc.
One way to avoid it is to use pre compiled header.
The advantage of using these pre-compiled headers is also that these files are not changing too much, so they are not going to be recompiled all the time, only when changed.

### How to use pre compiled headers in Visual Studio:

- add 2 files (stdafx.h and stdafx.cpp, default names)
- right click on the solution, and go to properties. Under C/C++, select Precompiled Headers, and change to **Use (/Yu)**
![Pasted image 20221202104441](https://user-images.githubusercontent.com/14072620/206446031-102e662b-8c3f-47ff-87ae-cc1175b1c84c.png)
- Edit stdafx.cpp and add `#include "stdafx.h"`
- Edit stdafx.h and add `#include <iostream>`
- right click on stdafx.cpp, and go to properties. Under C/C++, select Precompiled Headers, and change to **Create (/Yc)**
![Pasted image 20221202104756](https://user-images.githubusercontent.com/14072620/206446078-a92aa2b7-a5ef-40d1-8f35-6ea76c16b748.png)
- You **MUST** now use `#include "stdafx.h"` in all of your source files.

