# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.4.1)

# Добавляем исходные файлы для нашего нативного модуля
add_library(native-lib SHARED native-lib.cpp MyGLRenderer.cpp MyGLRenderer.h)

# Добавляем папку с заголовочными файлами glm
include_directories(src/main/cpp/glm)

# Находим и указываем библиотеку OpenGL ES
find_library(gles-lib GLESv3)

# Связываем наш нативный модуль с библиотекой GLES
target_link_libraries(native-lib ${gles-lib})

# Добавляем папку с библиотеками, если нужно (если это требуется для других модулей)
set_target_properties(native-lib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})