cmake_minimum_required(VERSION 3.3)
project(seriously)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(CheckIncludeFiles)
include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)

CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES (stddef.h HAVE_STDDEF_H)
CHECK_INCLUDE_FILES (unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILES (sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES (arpa/inet.h HAVE_ARPA_INET_H)
CHECK_INCLUDE_FILES (Windows.h HAVE_WINDOWS_H)
CHECK_INCLUDE_FILES (BaseTsd.h HAVE_BASETSD_H)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  int main() {
    uint32_t number = 0x1A2B3C4D;
    unsigned char *numPtr = (unsigned char *) &number;
    if (numPtr[0] != 0x4D) abort();
    return 0;
  }
" IS_LITTLE_ENDIAN)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  int main() {
    uint32_t number = 0x1A2B3C4D;
    unsigned char *numPtr = (unsigned char *) &number;
    if (numPtr[0] != 0x1A) abort();
    return 0;
  }
" IS_BIG_ENDIAN)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint16_t r = htons(1); return 0; }
" HAVE_HTONS)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint16_t r = ntohs(1); return 0; }
" HAVE_NTOHS)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint32_t r = htonl(1); return 0; }
" HAVE_HTONL)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint32_t r = ntohl(1); return 0; }
" HAVE_NTOHL)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint64_t r = htonll(1); return 0; }
" HAVE_HTONLL)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  int main() { uint64_t r = ntohll(1); return 0; }
" HAVE_NTOHLL)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  int main() { size_t s = 1; return 0; }
" HAVE_SIZE_T)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  int main() { ssize_t s = -1; return 0; }
" HAVE_SSIZE_T)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #else
  #error \"not on Windows / MSC\"
  #endif
  int main() { ssize_t s = -1; return 0; }
" HAVE_WIN_SSIZE_T)

check_cxx_source_compiles("
	#include <stdint.h>
	#include <stddef.h>

	template <typename T>
	struct Traits;

	template <>
	struct Traits<uint8_t>
	{ typedef uint8_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint16_t>
	{ typedef uint16_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint32_t>
	{ typedef uint32_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint64_t>
	{ typedef uint64_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<size_t>
	{ typedef size_t type; static size_t size() { return sizeof(type); } };

	int main() { size_t size = Traits<size_t>::size(); size++; }
" ALLOWS_TEMPLATED_SIZE_T)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #endif

  template <typename T>
  struct Traits;

  template <>
  struct Traits<int8_t>
  { typedef int8_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int16_t>
  { typedef int16_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int32_t>
  { typedef int32_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int64_t>
  { typedef int64_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<ssize_t>
  { typedef ssize_t type; static size_t size() { return sizeof(type); } };

  int main() { ssize_t size = Traits<ssize_t>::size(); size++; }
" ALLOWS_TEMPLATED_SSIZE_T)

check_cxx_source_compiles("
	#include <stdint.h>
	#include <stddef.h>

	template <typename T>
	struct Traits;

	template <>
	struct Traits<uint8_t>
	{ typedef uint8_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint16_t>
	{ typedef uint16_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint32_t>
	{ typedef uint32_t type; static size_t size() { return sizeof(type); } };

	template <>
	struct Traits<uint64_t>
	{ typedef uint64_t type; static size_t size() { return sizeof(type); } };

	int main() { size_t size = Traits<size_t>::size(); size++; }
" DOESNT_NEED_TEMPLATED_SIZE_T)

check_cxx_source_compiles("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #endif

  template <typename T>
  struct Traits;

  template <>
  struct Traits<int8_t>
  { typedef int8_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int16_t>
  { typedef int16_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int32_t>
  { typedef int32_t type; static size_t size() { return sizeof(type); } };

  template <>
  struct Traits<int64_t>
  { typedef int64_t type; static size_t size() { return sizeof(type); } };

  int main() { size_t size = Traits<ssize_t>::size(); size++; }
" DOESNT_NEED_TEMPLATED_SSIZE_T)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
 template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint32_t, unsigned long long>::value) abort(); }
" UINT32_IS_ULL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint32_t, unsigned long>::value) abort(); }
" UINT32_IS_UL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint32_t, unsigned int>::value) abort(); }
" UINT32_IS_UI)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint64_t, unsigned long long>::value) abort(); }
" UINT64_IS_ULL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint64_t, unsigned long>::value) abort(); }
" UINT64_IS_UL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<uint64_t, unsigned int>::value) abort(); }
" UINT64_IS_UI)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<size_t, unsigned long long>::value) abort(); }
" SIZE_T_IS_ULL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<size_t, unsigned long>::value) abort(); }
" SIZE_T_IS_UL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <stdlib.h>
  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<size_t, unsigned int>::value) abort(); }
" SIZE_T_IS_UI)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <stdlib.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #endif

  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<ssize_t, long long>::value) abort(); }
" SSIZE_T_IS_LL)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <stdlib.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #endif

  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<ssize_t, long>::value) abort(); }
" SSIZE_T_IS_L)

check_cxx_source_runs("
  #include <stdint.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <stdlib.h>
  #if defined(_MSC_VER)
  #include <BaseTsd.h>
  typedef SSIZE_T ssize_t;
  #endif

  template<class T, class U>
  struct is_same {
      enum { value = 0 };
  };
  template<class T>
  struct is_same<T, T> {
      enum { value = 1 };
  };
  int main() { if (! is_same<ssize_t, int>::value) abort(); }
" SSIZE_T_IS_I)

SET(CMAKE_EXTRA_INCLUDE_FILES stdint.h)
CHECK_TYPE_SIZE(size_t SIZEOF_SIZE_T LANGUAGE CXX)
CHECK_TYPE_SIZE(ssize_t SIZEOF_SSIZE_T LANGUAGE CXX)
CHECK_TYPE_SIZE(short SIZEOF_SHORT LANGUAGE CXX)
CHECK_TYPE_SIZE(int SIZEOF_INT LANGUAGE CXX)
CHECK_TYPE_SIZE(long SIZEOF_LONG LANGUAGE CXX)
CHECK_TYPE_SIZE("unsigned long" SIZEOF_UNSIGNED_LONG LANGUAGE CXX)
CHECK_TYPE_SIZE("long long" SIZEOF_LONG_LONG LANGUAGE CXX)
CHECK_TYPE_SIZE(float SIZEOF_FLOAT LANGUAGE CXX)
CHECK_TYPE_SIZE(double SIZEOF_DOUBLE LANGUAGE CXX)
SET(CMAKE_EXTRA_INCLUDE_FILES)

configure_file (config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )

set(SOURCE_FILES
    test_seriously.cpp
    catch.hpp
    Seriously.h
    Seriously.impl.hpp)

add_executable(test_seriously ${SOURCE_FILES})
