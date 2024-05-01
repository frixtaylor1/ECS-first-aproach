cmake_minimum_required(VERSION 3.22.1)
project(game_development LANGUAGES CXX)

# Define los flags de compilación
set(CXXFLAGS "-Wall -Werror -Wpedantic -O3")
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

# Establece las rutas de los directorios
set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Encuentra Raylib en el sistema
find_package(raylib REQUIRED)

# Si Raylib se encuentra, incluye sus bibliotecas e incluye directorios
if(raylib_FOUND)
    include_directories(${raylib_INCLUDE_DIRS})
    
    # Recopila todos los archivos fuente en el directorio fuente y sus subdirectorios
    file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIRECTORY}/*.cpp)
    
    # Crea el ejecutable con los archivos fuente y el directorio de inclusión
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    
    # Enlaza las bibliotecas de Raylib al ejecutable
    target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
else()
    message(FATAL_ERROR "Raylib no encontrado. Asegúrate de haberlo instalado correctamente.")
endif()
