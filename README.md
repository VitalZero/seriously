Seriously C++ serialization library
===================================

_Seriously_ is an header-only C++ serialization library, without external
dependencies (besides the standard library) and with minimal overhead.

Serialized data is encoded in a portable fashion (i.e. words are encoded in network
byte order, ...).

Example Code
------------

The higher-level API:

```c++

#include <iostream>
#include <string>
#include <stdint.h>

#include "Seriously.h"

void myfunc()
{
	seriously::Packer<1024> packer;		// a 1024 byte serialization buffer

	int32_t value1 = 83656;
	bool value2 = true;
	int16_t value3 = -2345;
	std::string value4("only an example");

	packer << value1 << value2 << value3 << value4;

	std::cout << "packed size: " << packer.size() << std::endl;
	// packer.data() contains the serialized data

	int32_t restored1;
	bool restored2;
	int16_t restored3;
	std::string restored4;

	packer >> restored1 >> restored2 >> restored3 >> restored4;

	std::cout << "unpacked: " << restored1 << " " << (restored2 ? "t" : "f") << " " << restored3 << " " << restored4 << std::endl;
}
```

It's possible to extend support to more esotic types by implementing a Traits struct for each additonal type.

See the [test_seriously.cpp](test_seriously.cpp) unit test file for a more complete API coverage.

Usage
-----

Just copy the [Seriously.h](Seriously.h) and [Seriously.impl.hpp](Seriously.impl.hpp) files into your source code and include only the former.

License
-------

Seriously is distributed under the Apache License, Version 2.0
See the [NOTICE](NOTICE) file distributed with this work for
additional information regarding copyright ownership.
The author licenses this file to you under the Apache
License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
