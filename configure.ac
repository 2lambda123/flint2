################################################################################ 
# preamble
################################################################################ 

define(FLINT_COPYRIGHT,[[
Copyright (C) 2023 Albin Ahlbäck

This file is part of FLINT.

FLINT is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License (LGPL) as published
by the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.  See <http://www.gnu.org/licenses/>.

]])
define(FLINT_COPYRIGHT_C,[[/*
    Copyright (C) 2023 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/]])

AC_COPYRIGHT(FLINT_COPYRIGHT)
AH_TOP(FLINT_COPYRIGHT_C)

AC_PREREQ(2.59)

define(FLINT_VERSION,[2.10.0-dev])

AC_INIT(FLINT, FLINT_VERSION, [https://github.com/flintlib/flint2/issues/], flint, [https://flintlib.org/])
AC_LANG(C)

# Every major version of Flint (1.0, 1.1, 1.2, etc.) gets
# a new major soname number.

# Every time a release happens where interfaces are added
# to Flint, the minor soname number gets incremented.

# Every patch that is made that doesn't change the Flint
# interface updates the patch number.

# However, if backwards incompatible changes are made, both
# the minor and patch numbers are set to 0. (Hopefully this
# doesn't happen in practice.)

# flint => soname
# 2.5.0 => 13.5.0
# 2.5.1 => 13.5.1
# 2.5.2 => 13.5.2
# 2.6.0 => 14.0.0
# 2.6.1 => 14.0.1
# 2.6.2 => 14.0.2
# 2.6.3 => 14.0.3
# 2.7.0 => 15.0.0
# 2.7.1 => 15.0.1
# 2.8.0 => 16.1.0
# 2.8.1 => 16.1.1
# 2.8.2 => 16.1.2
# 2.8.3 => 16.1.3
# 2.8.4 => 16.1.4
# 2.8.5 => 16.1.5
# 2.9.0 => 17.0.0
# 2.10.0 => 18.0.0

# NOTE: This must be after AC_INIT
FLINT_MAJOR=2
FLINT_MINOR=10
FLINT_PATCH=0
FLINT_MAJOR_SO=18
FLINT_MINOR_SO=0
FLINT_PATCH_SO=0

# Make sure that we are in the right directory
AC_CONFIG_SRCDIR(src/fmpz/link/fmpz_reentrant.c)

################################################################################ 
# initialize libtool
################################################################################ 

# Later we want to overwrite the default CFLAGS. Check now whether they are set
# or not as Libtool overwrites CFLAGS.
if test -n "${CFLAGS+x}";
then
    cflags_set="yes"
else
    cflags_set="no"
fi

if test -n "${TESTCFLAGS+x}";
then
    testcflags_set="yes"
else
    testcflags_set="no"
fi

LT_INIT

if test "$cflags_set" = "no";
then
    CFLAGS=
fi

################################################################################ 
# build system
################################################################################ 

if test -n "$target_alias";
then
    AC_MSG_ERROR([FLINT does not support the use of specifying --target.])
fi

# Get system triplet
AC_CANONICAL_HOST

################################################################################ 
# configure headers
################################################################################ 

AC_CONFIG_HEADERS(src/flint-config.h:src/config.h.in)

################################################################################ 
# features
################################################################################ 

AC_ARG_ENABLE(pthread,
[AS_HELP_STRING([--enable-pthread],[Enable pthread [default=yes]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-pthread. Need yes or no.])
    ;;
esac],
enable_pthread="yes")

AC_ARG_ENABLE(reentrant,
[AS_HELP_STRING([--enable-reentrant],[Build reentrant version of library [default=no]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-reentrant. Need yes or no.])
    ;;
esac],
enable_reentrant="no")

# Synonym for thread-safe. Only here for say to users that it is deprecated.
AC_ARG_ENABLE(tls)
AC_ARG_ENABLE(thread-safe,
[AS_HELP_STRING([--enable-thread-safe],[Enable thread-local storage [default=yes]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-tls. Need yes or no.])
    ;;
esac],
enable_thread_safe="yes")

if test -n "$enable_tls";
then
    AC_MSG_ERROR([--enable-tls is an old feature. Please use --enable-thread-safe instead.])
fi

AC_ARG_ENABLE(assert,
[AS_HELP_STRING([--enable-assert],[Enable use of asserts [default=no]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-assert. Need yes or no.])
    ;;
esac],
enable_assert="no")

AC_ARG_ENABLE(coverage,
[AS_HELP_STRING([--enable-coverage],[Enable test coverage [default=no]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-coverage. Need yes or no.])
    ;;
esac],
enable_coverage="no")

dnl TODO: This is currently not working because of the makefile.
AC_ARG_ENABLE(cxx,
[AS_HELP_STRING([--enable-cxx],[Enable C++ wrapper tests [default=no]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-cxx. Need yes or no.])
    ;;
esac],
enable_cxx="no")

AC_ARG_ENABLE(dependency-tracking,
[AS_HELP_STRING([--enable-dependency-tracking],[Enable GCC automated dependency tracking [default=yes]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-dependency-tracking. Need yes or no.])
    ;;
esac],
enable_dependency_tracking="yes")

################################################################################ 
# packages
################################################################################ 

AC_ARG_WITH(gmp_include,
[AS_HELP_STRING([--with-gmp-include=DIR],[GMP include directory])],
CPPFLAGS="$CPPFLAGS -I$withval"
gmp_include_path="$withval"
)

AC_ARG_WITH(gmp_lib,
[AS_HELP_STRING([--with-gmp-lib=DIR],[GMP library directory])],
LDFLAGS="$LDFLAGS -L$withval"
gmp_lib_path="$withval"
)

AC_ARG_WITH(gmp,
[AS_HELP_STRING([--with-gmp[[=DIR]]],[GMP install directory])],
if test "$with_gmp" = "no";
then
    AC_MSG_FAILURE([The use of GMP is mandatory.])
elif test "$with_gmp" = "yes";
then
    :
elif test -z "$gmp_include_path" && test -z "$gmp_lib_path";
then
    CPPFLAGS="$CPPFLAGS -I$withval/include"
    LDFLAGS="$LDFLAGS -L$withval/lib"
    gmp_include_path="$withval/include"
    gmp_lib_path="$withval/lib"
    with_gmp="yes"
else
    AC_MSG_FAILURE([Cannot use --with-gmp along with --with-gmp-include or --with-gmp-lib.])
fi,
with_gmp="yes"
)

AC_ARG_WITH(mpfr_include,
[AS_HELP_STRING([--with-mpfr-include=DIR],[MPFR include directory])],
CPPFLAGS="$CPPFLAGS -I$withval"
mpfr_include_path="$withval"
)

AC_ARG_WITH(mpfr_lib,
[AS_HELP_STRING([--with-mpfr-lib=DIR],[MPFR library directory])],
LDFLAGS="$LDFLAGS -L$withval"
mpfr_lib_path="$withval"
)

AC_ARG_WITH(mpfr,
[AS_HELP_STRING([--with-mpfr[[=DIR]]],[MPFR install directory])],
if test "$with_mpfr" = "no";
then
    AC_MSG_FAILURE([The use of MPFR is mandatory.])
elif test "$with_mpfr" = "yes";
then
    :
elif test -z "$mpfr_include_path" && test -z "$mpfr_lib_path";
then
    CPPFLAGS="$CPPFLAGS -I$withval/include"
    LDFLAGS="$LDFLAGS -L$withval/lib"
    mpfr_include_path="$withval/include"
    mpfr_lib_path="$withval/lib"
else
    AC_MSG_FAILURE([Cannot use --with-mpfr along with --with-mpfr-include or --with-mpfr-lib.])
fi,
with_mpfr="yes"
)

AC_ARG_WITH(blas_include,
[AS_HELP_STRING([--with-blas-include=DIR],[Use BLAS and specify its include directory])],
CPPFLAGS="$CPPFLAGS -I$withval"
blas_include_path="$withval"
)

AC_ARG_WITH(blas_lib,
[AS_HELP_STRING([--with-blas-lib=DIR],[Use BLAS and specify its library directory])],
LDFLAGS="$LDFLAGS -L$withval"
blas_lib_path="$withval"
)

AC_ARG_WITH(blas,
[AS_HELP_STRING([--with-blas[[=DIR]]],[Use BLAS and specify its install directory])],
if test "$with_blas" = "yes";
then
    :
elif test "$with_blas" = "no";
then
    if test -n "$blas_include_path" || test -n "$blas_lib_path";
    then
        AC_MSG_FAILURE([--with-blas-include or --with-blas-lib was specified but --with-blas=no.])
    fi
elif test -z "$blas_include_path" && test -z "$blas_lib_path";
then
    CPPFLAGS="$CPPFLAGS -I$withval/include"
    LDFLAGS="$LDFLAGS -L$withval/lib"
    blas_include_path="$withval/include"
    blas_lib_path="$withval/lib"
    with_blas="yes"
else
    AC_MSG_FAILURE([Cannot use --with-blas along with --with-blas-include or --with-blas-lib.])
fi,
with_blas="no"
)

if test "$with_blas" != "no" || test -n "$blas_include_path" || test -n "$blas_lib_path";
then
    with_blas="yes"
fi

AC_ARG_WITH(gc_include,
[AS_HELP_STRING([--with-gc-include=DIR],[Use GC and specify its include directory])],
CPPFLAGS="$CPPFLAGS -I$withval"
gc_include_path="$withval",
with_gc_include="no"
)

AC_ARG_WITH(gc_lib,
[AS_HELP_STRING([--with-gc-lib=DIR],[Use GC and specify its library directory])],
LDFLAGS="$LDFLAGS -L$withval"
gc_lib_path="$withval",
with_gc_lib="no"
)

AC_ARG_WITH(gc,
[AS_HELP_STRING([--with-gc[[=DIR]]],[Use GC and optionally specify its install directory])],
if test "$with_gc" = "yes";
then
    :
elif test "$with_gc" = "no";
then
    if test -n "$gc_include_path" || test -n "$gc_lib_path";
    then
        AC_MSG_FAILURE([--with-gc-include or --with-gc-lib was specified but --with-gc=no.])
    fi
elif test -z "$gc_include_path" && test -z "$gc_lib_path";
then
    CPPFLAGS="$CPPFLAGS -I$withval/include"
    LDFLAGS="$LDFLAGS -L$withval/lib"
    gc_include_path="$withval/include"
    gc_lib_path="$withval/lib"
    with_gc="yes"
else
    AC_MSG_FAILURE([Cannot use --with-gc along with --with-gc-include or --with-gc-lib.])
fi,
with_gc="no"
)

if test "$with_gc" != "no" || test -n "$gc_include_path" || test -n "$gc_lib_path";
then
    with_gc="yes"
fi

AC_ARG_WITH(ntl_include,
[AS_HELP_STRING([--with-ntl-include=DIR],[Use NTL and specify its include directory])],
CPPFLAGS="$CPPFLAGS -I$withval"
ntl_include_path="$withval"
)

AC_ARG_WITH(ntl_lib,
[AS_HELP_STRING([--with-ntl-lib=DIR],[Use NTL and specify its library directory])],
LDFLAGS="$LDFLAGS -L$withval"
ntl_lib_path="$withval"
)

AC_ARG_WITH(ntl,
[AS_HELP_STRING([--with-ntl[[=DIR]]],[Use NTL and optionally specify its install directory])],
if test "$with_ntl" = "yes";
then
    :
elif test "$with_ntl" = "no";
then
    if test -n "$ntl_include_path" || test -n "$ntl_lib_path";
    then
        AC_MSG_FAILURE([--with-ntl-include or --with-ntl-lib was specified but --with-ntl=no.])
    fi
elif test -z "$ntl_include_path" && test -z "$ntl_lib_path";
then
    CPPFLAGS="$CPPFLAGS -I$withval/include"
    LDFLAGS="$LDFLAGS -L$withval/lib"
    ntl_include_path="$withval/include"
    ntl_lib_path="$withval/lib"
    with_ntl="yes"
else
    AC_MSG_FAILURE([Cannot use --with-ntl along with --with-ntl-include or --with-ntl-lib.])
fi,
with_ntl="no"
)

if test "$with_ntl" != "no" || test -n "$ntl_include_path" || test -n "$ntl_lib_path";
then
    with_ntl="yes"
fi

################################################################################ 
# programs
################################################################################ 

AC_PROG_CC

if test "$with_ntl" = "yes" || test "$enable_cxx" = "yes";
then
    AC_PROG_CXX
fi

AC_PROG_MKDIR_P

################################################################################ 
# environment variables
################################################################################ 

AC_ARG_VAR([TESTCFLAGS], [Choose different C compiler flags for tests [default=CFLAGS]. Can be useful to compile library at a specific optimization level while compiling tests fast.])

AC_ARG_VAR(ABI, [Desired ABI])

AC_ARG_VAR(LDCONFIG, [ldconfig tool])

AC_ARG_VAR(TMPPATH, [Path to a directory meant for temporary files for host system (NOTE: Will probably become redundant in the future). Only relevant if host do not have read and write access to /tmp [default=/tmp].])

if test -z "$TMPPATH";
then
    TMPPATH="/tmp"
fi

AC_DEFINE_UNQUOTED([FLINT_TMPPATH], ["$TMPPATH"], [Define to set the default directory for temporary files])

################################################################################ 
# check programs and system
################################################################################ 

AC_C_INLINE

if test "$compiler_c_o" = "no";
then
    AC_MSG_ERROR([Compiler must support both -c and -o simultaneously!])
fi

AC_C_BIGENDIAN(flint_big_endian=yes)

case "$host_os" in
    darwin*)
        flint_lib="libflint-$FLINT_MAJOR_SO.dylib"
        flint_libname="libflint.dylib"
        extra_shared_flags="-install_name `pwd`/$flint_lib -compatibility_version $FLINT_MAJOR_SO.$FLINT_MINOR_SO -current_version $FLINT_MAJOR_SO.$FLINT_MINOR_SO.$FLINT_PATCH_SO"
        ;;
    cygwin|mingw*|msys)
        flint_lib="libflint-$FLINT_MAJOR_SO.dll"
        flint_libname="libflint.dll"
        flint_implib="$flint_libname.$libext"
        extra_shared_flags="-static-libgcc $wl--export-all-symbols,--out-implib,$flint_libname.a"
        ;;
    *)
        flint_lib="libflint.so.$FLINT_MAJOR_SO.$FLINT_MINOR_SO.$FLINT_PATCH_SO"
        flint_libname="libflint.so"
        extra_shared_flags="$wl-soname,libflint.so.$FLINT_MAJOR_SO"
        flint_solib="yes"
        ;;
esac

flint_lib_static="libflint.$libext"

if test "`uname -s`" = "android";
then
    extra_shared_flags="$wl-soname,libflint.so"
fi

AC_SUBST(WL,$wl)

AC_SUBST(FLINT_LIB,$flint_lib)
AC_SUBST(FLINT_LIBNAME,$flint_libname)
AC_SUBST(FLINT_IMPLIB,$flint_implib)
AC_SUBST(FLINT_LIB_STATIC,$flint_lib_static)
AC_SUBST(EXTRA_SHARED_FLAGS,$extra_shared_flags)

if test "$flint_solib" = "yes";
then
    AC_SUBST(FLINT_SOLIB,1)
else
    AC_SUBST(FLINT_SOLIB,0)
fi

case "$host_os" in
    cygwin|mingw*|msys)
        if test "$DLLTOOL" = "false";
        then
            AC_MSG_ERROR("Couldn't find any dlltool that is required to create import libraries for
Windows-type systems.")
        fi
        ;;
    *)
        ;;
esac

case "$host_cpu" in
    x86_64|ia64|sparc64|powerpc64*)
        fft_tuning_in="src/fft_tuning64.in"
        ;;
    *)
        fft_tuning_in="src/fft_tuning32.in"
        ;;
esac
AC_CONFIG_FILES([src/fft_tuning.h:$fft_tuning_in])

if test -z "$LDCONFIG";
then
    AC_MSG_CHECKING(for ldconfig)
    case "$build_os" in
        mingw*|cygwin|msys|darwin*|freebsd*)
            LDCONFIG="true"
            ;;
        *)
            LDCONFIG="true"
            if test "$FLINT_SOLIB" = "1";
            then
                if test ldconfig > /dev/null 2>&1;
                then
                    LDCONFIG="ldconfig"
                elif test -x /sbin/ldconfig;
                then
                    LDCONFIG="/sbin/ldconfig"
                fi
            fi
            ;;
    esac
    if test "$LDCONFIG" = "true";
    then
        ldconfig_res="skipped"
    else
        ldconfig_res="$LDCONFIG"
    fi
    AC_MSG_RESULT($ldconfig_res)
fi
AC_SUBST(LDCONFIG)

################################################################################ 
# check headers
################################################################################ 

# Mandatory headers
AC_CHECK_HEADERS([stdarg.h stdio.h stdlib.h stdint.h string.h math.h float.h errno.h gmp.h mpfr.h],,
                 AC_MSG_ERROR([Could not find a mandatory header!]))

# Optional headers
AC_CHECK_HEADERS([fenv.h alloca.h malloc.h sys/param.h unistd.h windows.h])

if test "$enable_pthread" = "yes";
then
    AC_CHECK_HEADER([pthread.h],,
                    AC_MSG_ERROR([Could not find pthread.h!]))
fi

if test "$enable_assert" = "yes";
then
    AC_CHECK_HEADER([assert.h],,
                    AC_MSG_ERROR([Could not find assert.h!]))
fi

if test "$enable_blas" = "yes";
then
    AC_CHECK_HEADER([cblas.h],,
                    AC_MSG_ERROR([Could not find cblas.h!]))
fi

if test "$enable_gc" = "yes";
then
    AC_CHECK_HEADER([gc.h],,
                    AC_MSG_ERROR([Could not find gc.h!]))
fi

if test "$enable_ntl" = "yes";
then
    AC_CHECK_HEADER([NTL/ZZ.h],,
                    AC_MSG_ERROR([Could not find NTL/ZZ.h!]))
fi

################################################################################ 
# check libraries
################################################################################ 

AC_CHECK_LIB(m,fabs,
[LIBS="-lm $LIBS"],
[AC_MSG_ERROR([The C math library was not found!])])

AC_CHECK_LIB(gmp,__gmpz_init,
[LIBS="-lgmp $LIBS"],
[AC_MSG_ERROR([GMP library was not found.  If you indeed have GMP installed, please
submit a bug report to <https://github.com/flintlib/flint2/issues/> so
that we can either fix the issue or give a more proper error message.])])

AC_CHECK_LIB(mpfr,mpfr_init,
[LIBS="-lmpfr $LIBS"],
[AC_MSG_ERROR([MPFR library was not found.  If you indeed have MPFR installed, please
submit a bug report to <https://github.com/flintlib/flint2/issues/> so
that we can either fix the issue or give a more proper error message.])])

if test "$enable_pthread" = "yes";
then
    # check if compiler accepts the preferred -pthread
    AX_CHECK_COMPILE_FLAG(-pthread,
    [LIBS="-pthread $LIBS"],
    # check if the compiler can do -lpthread
    AC_CHECK_LIB(pthread,pthread_create,
    [LIBS="-lpthread $LIBS"],
    [AC_MSG_ERROR([Couldn't link against POSIX threads via -pthread or -lpthread while
--enable-pthread was specified.])]))
fi

if test "$with_blas" = "yes";
then
    AC_CHECK_LIB(blas,cblas_dgemm,
    [LIBS="-lblas $LIBS"],
    [AC_MSG_ERROR([BLAS library was not found.  If you indeed have BLAS installed, please
submit a bug report to <https://github.com/flintlib/flint2/issues/> so
that we can either fix the issue or give a more proper error message.])])
fi

if test "$with_ntl" = "yes";
then
    AC_MSG_CHECKING([if linking simple code snippet of NTL works])
    SAVE_libs="$LIBS"
    LIBS="-lntl $LIBS"
    AC_LANG_PUSH([C++])
    dnl The following code snippet was taken from NTL's documentation
    AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
        [#include <NTL/ZZ.h>],
        [NTL::ZZ a, b, c;
std::cin >> a;
std::cin >> b;
c = (a+1)*(b+1);
std::cout << c << "\n";]
    )],
    [AC_MSG_RESULT([yes])],
    [AC_MSG_RESULT([no])
    AC_MSG_ERROR([NTL library was not found.  If you indeed have NTL installed, please
submit a bug report to <https://github.com/flintlib/flint2/issues/> so
that we can either fix the issue or give a more proper error message.])])
    AC_LANG_POP
    LIBS="$SAVE_libs"
fi

################################################################################ 
# check settings and environment
################################################################################ 

AC_SUBST(PIC_FLAG,$pic_flag)

if test "$enable_thread_safe" = "yes";
then
    AC_MSG_CHECKING([if $CC supports TLS handle])
    for tls_expression in "__thread" "_Thread_local" "__declspec(thread)"
    do
        AC_LINK_IFELSE([AC_LANG_PROGRAM([$tls_expression int myvariable = 0;],[])],
        [flint_success="yes"],[flint_success="no"])

        if test "$flint_success" = "yes";
        then
            AC_MSG_RESULT([$tls_expression])
            break
        fi
    done

    if test "$flint_success" = "no";
    then
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([--enable-thread-safe was specified, but $CC does not have any TLS handle.])
    fi
fi

AC_MSG_CHECKING([if cpu_set_t is supported])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#define _GNU_SOURCE
#include <sched.h>
#include <pthread.h>],
[cpu_set_t s;CPU_ZERO(&s); pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), 0);])],
[AC_DEFINE(FLINT_USES_CPUSET,1,Define if system has cpu_set_t)
 AC_MSG_RESULT([yes])],
[AC_MSG_RESULT([no])])

# ensure alloca works
AC_MSG_CHECKING([if alloca works])
AC_LINK_IFELSE([AC_LANG_PROGRAM(
[#ifndef alloca
# ifdef __GNUC__
#  define alloca __builtin_alloca
# else
#  ifdef _MSC_VER
#   include <malloc.h>
#   define alloca _alloca
#  else
#   include <alloca.h> /* We assume then that you have alloca.h */
#  endif
# endif
#endif],
[char * p = alloca(128);])],
[AC_MSG_RESULT([yes])],
[AC_MSG_RESULT([no])
AC_MSG_ERROR([Couldn't find alloca, which is required for FLINT. Please submit a bug
report to <https://github.com/flintlib/flint2/issues/> and specify your
operating system.])])

AC_MSG_CHECKING([if $CC has popcount intrinsics])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([],[long int x = __builtin_popcountl(3);])],
    [AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([],[long long int x = __builtin_popcountll(3);])],
        [AC_MSG_RESULT([yes])
         has_popcount="yes"
         AC_DEFINE(FLINT_USES_POPCNT,1,[Define if system has popcount intrinsics])],
        [AC_MSG_RESULT([no])]
    )],
    [AC_MSG_RESULT([no])]
)

################################################################################ 
# CFLAGS
################################################################################ 

save_CFLAGS="$CFLAGS"
CFLAGS=""

# The following is needed for Clang to check for unknown options.
AX_CHECK_COMPILE_FLAG([-Werror=unknown-warning-option], [CFLAGS="-Werror=unknown-warning-option"])

if test "$enable_coverage" = "yes";
then
    AX_CHECK_COMPILE_FLAG([-fprofile-arcs -ftest-coverage],
    [save_CFLAGS="-fprofile-arcs -ftest-coverage $save_CFLAGS"],
    [AC_MSG_ERROR([$CC does not seem to support test coverage flags.])])
fi

if test -n "$ABI";
then
    AX_CHECK_COMPILE_FLAG([-m$ABI],
    [save_CFLAGS="-m$ABI $save_CFLAGS"],
    [AC_MSG_ERROR([$CC does not support the ABI flag -m$ABI])])
fi
AC_SUBST(ABI_FLAG)

case $host_cpu in
    sparc*)
        AX_CHECK_COMPILE_FLAG(-mno-relax,[DEFAULT_CFLAGS="-mno-relax $DEFAULT_CFLAGS"])
        ;;
    *)
        ;;
esac

AX_CHECK_COMPILE_FLAG([-Wall],[DEFAULT_CFLAGS="-Wall $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-Wno-stringop-overread],[DEFAULT_CFLAGS="-Wno-stringop-overread $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-Wno-stringop-overflow],[DEFAULT_CFLAGS="-Wno-stringop-overflow $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-O2],[DEFAULT_CFLAGS="-O2 $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-std=c99],[DEFAULT_CFLAGS="-std=c99 $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-pedantic],[DEFAULT_CFLAGS="-pedantic $DEFAULT_CFLAGS"])

dnl NOTE: The following flags shouldn't be default. They are leftovers from
dnl previous configure script
AX_CHECK_COMPILE_FLAG([-g],[DEFAULT_CFLAGS="-g $DEFAULT_CFLAGS"])
AX_CHECK_COMPILE_FLAG([-funroll-loops],[DEFAULT_CFLAGS="-funroll-loops $DEFAULT_CFLAGS"])

if test "$cflags_set" = "no";
then
    CFLAGS="$save_CFLAGS $DEFAULT_CFLAGS"
else
    CFLAGS="$save_CFLAGS"
    AX_CHECK_COMPILE_FLAG([$CFLAGS],[],AC_MSG_ERROR([Couldn't compile with given CFLAGS!]))
fi

if test "$testcflags_set" = "no";
then
    TESTCFLAGS="$CFLAGS"
else
    TESTCFLAGS="$TESTCFLAGS $save_CFLAGS"
fi

CPPFLAGS="-I./src $CPPFLAGS"

################################################################################ 
# substitutions and definitions
################################################################################ 

AC_SUBST(FLINT_MAJOR)
AC_SUBST(FLINT_MINOR)
AC_SUBST(FLINT_PATCH)
AC_SUBST(FLINT_MAJOR_SO)
AC_SUBST(FLINT_MINOR_SO)
AC_SUBST(FLINT_PATCH_SO)

AC_SUBST(GMP_LIB_PATH,$gmp_lib_path)
AC_SUBST(MPFR_LIB_PATH,$mpfr_lib_path)
AC_SUBST(BLAS_LIB_PATH,$blas_lib_path)
AC_SUBST(GC_LIB_PATH,$gc_lib_path)
AC_SUBST(NTL_LIB_PATH,$ntl_lib_path)

AC_SUBST(LIB_CPPFLAGS,["-DFLINT_NOSTDIO -DFLINT_NOSTDARG"])

# Configure fmpz's memory manager
if test "$with_gc" = "yes";
then
    if test "$enable_thread_safe" = "yes";
    then
        AC_MSG_ERROR([The Boehm-Demers-Weise garbage collector does not support thread-local storage!])
    fi
    fmpz_c="src/fmpz/link/fmpz_gc.c"
else
    if test "$enable_reentrant" = "yes";
    then
        fmpz_c="src/fmpz/link/fmpz_reentrant.c"
    else
        fmpz_c="src/fmpz/link/fmpz_single.c"
    fi
fi
AC_CONFIG_FILES([src/fmpz/fmpz.c:$fmpz_c])

if test "$enable_shared" = "yes";
then
    AC_SUBST(SHARED,1)
else
    AC_SUBST(SHARED,0)
fi

if test "$enable_static" = "yes";
then
    AC_SUBST(STATIC,1)
else
    AC_SUBST(STATIC,0)
fi

if test "$enable_coverage" = "yes";
then
    AC_SUBST(COVERAGE,1)
else
    AC_SUBST(COVERAGE,0)
fi

if test "$enable_dependency_tracking" = "yes";
then
    AC_SUBST(WANT_DEPS,1)
else
    AC_SUBST(WANT_DEPS,0)
fi

if test "$with_ntl" = "yes";
then
    AC_SUBST(WANT_NTL,1)
else
    AC_SUBST(WANT_NTL,0)
fi

if test "$with_blas" = "yes";
then
    AC_DEFINE(FLINT_USES_BLAS,1,[Define to enable BLAS.])
fi

if test "$with_gc" = "yes";
then
    AC_DEFINE(FLINT_USES_GC,1,[Define to enable the Boehm-Demers-Weise garbage collector.])
fi

if test "$flint_big_endian" = "yes";
then
    AC_DEFINE(FLINT_BIG_ENDIAN,1,[Define if system is big endian.])
fi

if test "$enable_pthread" = "yes";
then
    AC_DEFINE(FLINT_USES_PTHREAD,1,[Define to enable the use of pthread.])
fi

if test "$enable_thread_safe" = "yes";
then
    AC_DEFINE(FLINT_USES_TLS,1,[Define to enable thread-local storage.])
fi

if test "$enable_reentrant" = "yes";
then
    AC_DEFINE(FLINT_REENTRANT,1,[Define to enable reentrant.])
fi

if test "$enable_assert" = "yes";
then
    AC_DEFINE(FLINT_WANT_ASSERT,1,[Define to enable use of asserts.])
fi

################################################################################ 
# epilog
################################################################################ 

AC_CONFIG_FILES([Makefile flint.pc])
AC_OUTPUT

dnl Shorten the original help message
m4_cleardivert([HELP_BEGIN])dnl
m4_divert_push([HELP_BEGIN])dnl

if test "$ac_init_help" = "long";
then
    cat <<_ACEOF
\`configure' configures m4_ifset([AC_PACKAGE_STRING],
			[AC_PACKAGE_STRING],
			[this package]) to adapt to many kinds of systems.

Usage: $[0] [[OPTION]]... [[VAR=VALUE]]...

[To assign environment variables (e.g., CC, CFLAGS...), specify them as
VAR=VALUE.  See below for descriptions of some of the useful variables.

Defaults for the options are specified in brackets.

Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print \`checking ...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for \`--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or \`..']

Installation directories:
]AS_HELP_STRING([--prefix=PREFIX],
  [install architecture-independent files in PREFIX [$ac_default_prefix]])
AS_HELP_STRING([--exec-prefix=EPREFIX],
  [install architecture-dependent files in EPREFIX [PREFIX]])[

By default, \`make install' will install all the files in
\`$ac_default_prefix/include' and \`$ac_default_prefix/lib' etc.
You can specify an installation prefix other than \`$ac_default_prefix'
using \`--prefix', for instance \`--prefix=\$HOME'.

For better control, use the options below.

Fine tuning of the installation directories:
  --bindir=DIR            user executables [EPREFIX/bin]
  --libdir=DIR            object code libraries [EPREFIX/lib]
  --includedir=DIR        C header files [PREFIX/include]
_ACEOF

    cat <<_ACEOF]
    m4_divert_pop([HELP_BEGIN])dnl

dnl NOTE: There is supposed to be a missing `fi' here.