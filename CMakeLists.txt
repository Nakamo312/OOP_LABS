cmake_minimum_required(VERSION 3.11)

project(characters-v1 CXX)

set(CMAKE_CXX_STANDARD 23)

# Специфичные настройки для компилятора Visual Studio
if(MSVC)
    # Генерируем статическую заглушку для динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Подключаем googletest
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Объявляем библиотеку
add_library(characters-v1 SHARED
    "include/Character/Character.h"
    "src/Character.cc"

)
add_library(app-v1 SHARED

    "include/Application/Application.h"
    "src/Application.cc"

)
target_include_directories(characters-v1 PUBLIC "include")
target_include_directories(app-v1 PUBLIC "include")

add_executable(character-v1-app  "consoleApp/App.cc" )
target_link_libraries(character-v1-app  characters-v1 )
target_link_libraries(character-v1-app  app-v1 )


# Объявляем тесты
add_executable(character-v1-tests "test/Character_tests.cc")
target_link_libraries(character-v1-tests characters-v1 GTest::gtest_main)