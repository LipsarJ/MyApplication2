# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.4.1)

# Указываем имя проекта
project(MyApplication2)

# Добавляем библиотеку GLES
find_library(gles-lib GLESv3)

# Указываем путь к исходному файлу с рендерером на C++
add_library(native-lib SHARED src/main/cpp/native-lib.cpp)

include_directories(src/main/cpp/glm)

# Указываем, что библиотека должна линковаться с библиотекой GLES
target_link_libraries(native-lib ${gles-lib})

# Включаем сборку нативного кода из app/src/main/cpp
add_subdirectory(app/src/main/cpp)