cmake_minimum_required(VERSION 3.22)

project(CPPDataStruct)

if(WIN32)
    include(GenerateExportHeader)
endif()

find_package(Boost 1.74 COMPONENTS log chrono thread program_options filesystem REQUIRED)

# logger
add_library(logger SHARED logger/src/lib/logger.cpp)
target_compile_definitions(logger PRIVATE BOOST_ALL_DYN_LINK)
target_include_directories(logger PRIVATE logger/src/include)
target_link_libraries(logger Boost::log)
if(WIN32)
    generate_export_header(logger)
endif()

# datastruct_async_signal
add_executable(datastruct_async_signal datastruct_async_signal/src/main.cpp)
target_compile_definitions(datastruct_async_signal PRIVATE BOOST_ALL_DYN_LINK)
target_include_directories(datastruct_async_signal PRIVATE logger/src/include)
target_link_libraries(datastruct_async_signal
    logger
    Boost::log
)

# datastruct_async_timer
add_executable(datastruct_async_timer datastruct_async_timer/src/main.cpp)
target_compile_definitions(datastruct_async_timer PRIVATE BOOST_ALL_DYN_LINK)
target_include_directories(datastruct_async_timer PRIVATE logger/src/include)
target_link_libraries(datastruct_async_timer
    logger
    Boost::log
)

# datastruct_big_integer
add_executable(datastruct_big_integer datastruct_big_integer/src/main.cpp)
target_include_directories(datastruct_big_integer PRIVATE
    logger/src/include
    datastruct_big_integer/src/include
)
target_link_libraries(datastruct_big_integer logger)

# datastruct_class
add_executable(datastruct_class
    datastruct_class/src/main.cpp
    datastruct_class/src/lib/engine.cpp
)
target_include_directories(datastruct_class PRIVATE
    logger/src/include
    datastruct_class/src/include
)
target_link_libraries(datastruct_class
    logger
)

# datastruct_class_template
add_executable(datastruct_class_template datastruct_class_template/src/main.cpp)
target_include_directories(datastruct_class_template PRIVATE
    logger/src/include
    datastruct_class_template/src/include
)
target_link_libraries(datastruct_class_template
    logger
)

# datastruct_file_operations
add_executable(datastruct_file_operations
    datastruct_file_operations/src/main.cpp
    datastruct_file_operations/src/lib/engine.cpp
)
target_include_directories(datastruct_file_operations PRIVATE
    logger/src/include
    datastruct_file_operations/src/include
)
if(WIN32)
    target_link_libraries(datastruct_file_operations
        logger
        Boost::program_options
        Boost::filesystem
        bcrypt
    )
else()
    target_link_libraries(datastruct_file_operations
        logger
        Boost::program_options
        Boost::filesystem
    )
endif()

# datastruct_float_multiprecision
add_executable(datastruct_float_multiprecision datastruct_float_multiprecision/src/main.cpp)
target_include_directories(datastruct_float_multiprecision PRIVATE
    logger/src/include
    datastruct_float_multiprecision/src/include
)
target_link_libraries(datastruct_float_multiprecision logger)

# datastruct_linkedlist
add_executable(datastruct_linkedlist
    datastruct_linkedlist/src/main.cpp
    datastruct_linkedlist/src/lib/engine.cpp
)
target_include_directories(datastruct_linkedlist PRIVATE
    logger/src/include
    datastruct_linkedlist/src/include
)
if(WIN32)
    target_link_libraries(datastruct_linkedlist logger bcrypt)
else()
    target_link_libraries(datastruct_linkedlist logger)
endif()

# datastruct_thread_timer
add_executable(datastruct_thread_timer datastruct_thread_timer/src/main.cpp)
target_compile_definitions(datastruct_thread_timer PRIVATE BOOST_ALL_DYN_LINK)
target_include_directories(datastruct_thread_timer PRIVATE logger/src/include)
target_link_libraries(datastruct_thread_timer
    logger
    Boost::log
    Boost::chrono
    Boost::thread
)

# datastruct_thread_timer_class
add_executable(datastruct_thread_timer_class
    datastruct_thread_timer_class/src/main.cpp
    datastruct_thread_timer_class/src/lib/engine.cpp
)
target_compile_definitions(datastruct_thread_timer_class PRIVATE BOOST_ALL_DYN_LINK)
target_include_directories(datastruct_thread_timer_class PRIVATE
    logger/src/include
    datastruct_thread_timer_class/src/include
)
target_link_libraries(datastruct_thread_timer_class
    logger
    Boost::log
    Boost::chrono
    Boost::thread
)

# datastruct_vector
add_executable(datastruct_vector datastruct_vector/src/main.cpp)
target_include_directories(datastruct_vector PRIVATE logger/src/include)
target_link_libraries(datastruct_vector logger)

# helloworld
add_executable(helloworld helloworld/src/main.cpp)
target_include_directories(helloworld PRIVATE logger/src/include)
target_link_libraries(helloworld logger)
