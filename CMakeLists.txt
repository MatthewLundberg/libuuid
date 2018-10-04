cmake_minimum_required(VERSION 3.0.0)

project(uuid)

if(WIN32)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D_WIN32")
endif()

file(GLOB SOURCES *.c)
file(GLOB HEADERS *.h)

include(CheckCSourceRuns)
include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckFunctionExists)

macro(check_test_file FILE RESULT)
  file(READ ${FILE} _SOURCE)
  check_c_source_runs("${_SOURCE}" ${RESULT})
endmacro()
macro(add_cflags VAR)
  if(${VAR})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D${VAR}")
  endif()
endmacro()
macro(check_test_file_add FILE VAR)
  check_test_file(${FILE} ${VAR})
  add_cflags(${VAR})
endmacro()
macro (check_include_file_add FILE VAR)
  check_include_file(${FILE} ${VAR})
  add_cflags(${VAR})
endmacro()
macro (check_type_size_add TYPE VAR)
  check_type_size(${TYPE} ${VAR})
  add_cflags(${VAR})
endmacro()
macro (check_function_exists_add FUNC VAR)
  check_function_exists(${FUNC} ${VAR})
  add_cflags(${VAR})
endmacro()

check_test_file_add("cmake/HAVE_DECL__SC_HOST_NAME_MAX.c" HAVE_DECL__SC_HOST_NAME_MAX)
check_test_file_add("cmake/HAVE_GETEXECNAME.c" HAVE_GETEXECNAME)
check_include_file_add("inittypes.h" HAVE_INITTYPES_H)
check_type_size_add("loff_t" HAVE_LOFF_T)
check_include_file_add("net/if_dl.h" HAVE_NET_IF_DL_H)
check_include_file_add("net/if.h" HAVE_NET_IF_H)
check_include_file_add("netinet/in.h" HAVE_NETINET_IN_H)
# HAVE___PROGNAME
# HAVE_PROGRAM_INVOCATION_SHORT_NAME
# HAVE_SA_LEN
# HAVE_SCANF_MS_MODIFIER
check_function_exists_add("srand" HAVE_SRANDOM)
check_include_file_add("stdint.h" HAVE_STDINT_H)
check_include_file_add("stdlib.h" HAVE_STDLIB_H)
check_include_file_add("sys/file.h" HAVE_SYS_FILE_H)
check_include_file_add("sys/ioctl.h" HAVE_SYS_IOCTL_H)
check_include_file_add("sys/socket.h" HAVE_SYS_SOCKET_H)
check_include_file_add("sys/sockio.h" HAVE_SYS_SOCKIO_H)
check_include_file_add("sys/time.h" HAVE_SYS_TIME_H)
check_include_file_add("sys/un.h" HAVE_UN_H)
check_test_file_add("cmake/HAVE_TLS.c" HAVE_TLS)

check_include_file_add("unistd.h" HAVE_UNISTD_H)
check_function_exists_add("usleep" HAVE_USLEEP)

check_type_size_add("ssize_t" HAVE_SSIZE_T)
check_type_size_add("mode_t" HAVE_MODE_T)
check_include_file_add("sys/syscall.h" HAVE_SYS_SYSCALL_H)
check_include_file_add("winsock2.h" HAVE_WINSOCK2_H)


add_library(libuuid ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR})

install(FILES uuid.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/uuid)
install(TARGETS libuuid DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
