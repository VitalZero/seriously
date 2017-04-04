#ifndef SERIOUSLY_CONFIG_H
#define SERIOUSLY_CONFIG_H

#cmakedefine COMPILER_SUPPORTS_CXX0X 1
#cmakedefine COMPILER_SUPPORTS_CXX11 1

#cmakedefine HAVE_STDINT_H 1
#cmakedefine HAVE_STDDEF_H 1
#cmakedefine HAVE_UNISTD_H 1
#cmakedefine HAVE_SYS_TYPES_H 1
#cmakedefine HAVE_ARPA_INET_H 1
#cmakedefine HAVE_WINDOWS_H 1
#cmakedefine HAVE_BASETSD_H 1

/* Define to 1 if you have the system is little endian */
#cmakedefine IS_LITTLE_ENDIAN 1

/* Define to 1 if you have the system is big endian */
#cmakedefine IS_BIG_ENDIAN 1

/* Define to 1 if you have the size_t type. */
#cmakedefine HAVE_SIZE_T 1

/* Define to 1 if you have the ssize_t type. */
#cmakedefine HAVE_SSIZE_T 1

/* Define to 1 if you have the Windows SSIZE_T type. */
#cmakedefine HAVE_WIN_SSIZE_T 1

#define SIZEOF_SHORT @SIZEOF_SHORT@
#define SIZEOF_INT @SIZEOF_INT@
#define SIZEOF_LONG @SIZEOF_LONG@
#define SIZEOF_UNSIGNED_LONG @SIZEOF_UNSIGNED_LONG@
#define SIZEOF_LONG_LONG @SIZEOF_LONG_LONG@
#define SIZEOF_FLOAT @SIZEOF_FLOAT@
#define SIZEOF_DOUBLE @SIZEOF_DOUBLE@
#define SIZEOF_SIZE_T @SIZEOF_SIZE_T@
#define SIZEOF_SSIZE_T @SIZEOF_SSIZE_T@

/* Define to 1 if an explicit template for size_t is not needed if all the uint*_t types are there */
#cmakedefine DOESNT_NEED_TEMPLATED_SIZE_T 1

/* Define to 1 if an explicit template for ssize_t is not needed if all the int*_t types are there */
#cmakedefine DOESNT_NEED_TEMPLATED_SSIZE_T 1

/* Define to 1 if an explicit template for size_t is allowed even if all the uint*_t types are there */
#cmakedefine ALLOWS_TEMPLATED_SIZE_T 1

/* Define to 1 if an explicit template for ssize_t is allowed even if all the int*_t types are there */
#cmakedefine ALLOWS_TEMPLATED_SSIZE_T 1

/* Define to 1 if uint32_t is same as unsigned long long */
#cmakedefine UINT32_IS_ULL 1

/* Define to 1 if uint32_t is same as unsigned long */
#cmakedefine UINT32_IS_UL 1

/* Define to 1 if uint32_t is same as unsigned int */
#cmakedefine UINT32_IS_UI 1

/* Define to 1 if uint64_t is same as unsigned long long */
#cmakedefine UINT64_IS_ULL 1

/* Define to 1 if uint64_t is same as unsigned long */
#cmakedefine UINT64_IS_UL 1

/* Define to 1 if uint64_t is same as unsigned int */
#cmakedefine UINT64_IS_UI 1

/* Define to 1 if size_t is same as unsigned long long */
#cmakedefine SIZE_T_IS_ULL 1

/* Define to 1 if size_t is same as unsigned long */
#cmakedefine SIZE_T_IS_UL 1

/* Define to 1 if size_t is same as unsigned int */
#cmakedefine SIZE_T_IS_UI 1

/* Define to 1 if ssize_t is same as long long */
#cmakedefine SSIZE_T_IS_LL 1

/* Define to 1 if ssize_t is same as long */
#cmakedefine SSIZE_T_IS_L 1

/* Define to 1 if ssize_t is same as int */
#cmakedefine SSIZE_T_IS_I 1

#endif /* SERIOUSLY_CONFIG_H */
