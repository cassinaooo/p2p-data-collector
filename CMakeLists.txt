cmake_minimum_required(VERSION 3.7)
project(redes)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(
        RECEIVER_SRC
        include/fileutils.h
        include/protocoltypes.h
        include/protocolutils.h
        include/receiver.h
        include/receiversockets.h
        src/exec/receivermain.c
        src/receiver/receiver.c
        src/receiver/receiversockets.c
        src/utils/fileutils.c
        src/utils/protocolutils.c
)

set(
        SENDER_SRC
        include/fileutils.h
        include/protocoltypes.h
        include/protocolutils.h
        include/sender.h
        include/sendersockets.h
        src/exec/sendermain.c
        src/sender/sender.c
        src/sender/sendersockets.c
        src/utils/fileutils.c
        src/utils/protocolutils.c
)

set(
        TESTER_SRC
        include/tester.h
        include/fileutils.h
        include/protocoltypes.h
        include/protocolutils.h
        include/sender.h
        include/sendersockets.h
        include/receiver.h
        include/receiversockets.h
        src/exec/testmain.c
        src/sender/sender.c
        src/sender/sendersockets.c
        src/utils/fileutils.c
        src/utils/protocolutils.c
        src/receiver/receiver.c
        src/receiver/receiversockets.c
        src/tester.c
)

add_executable(sender ${SENDER_SRC})

add_executable(receiver ${RECEIVER_SRC})

add_executable(tester ${TESTER_SRC})