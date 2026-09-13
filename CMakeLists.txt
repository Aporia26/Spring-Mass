cmake_minimum_required(VERSION 3.22)
project(Spring-Mass VERSION 1.0 LANGUAGES CXX C)

# Required for SFML 3.x modern event parsing layout (event->is<...>)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================================================================
# CENTRALIZED ECOSYSTEM LOCATION MAPPING
# =========================================================================
set(GRAPHICS_ROOT "C:/Developer/Graphics")

include_directories(
    "${GRAPHICS_ROOT}/include"
    "${GRAPHICS_ROOT}/Include"
)
link_directories("${GRAPHICS_ROOT}/lib")

# Core Windows operating system drivers
set(WINDOWS_DRIVERS gdi32 user32 kernel32 shell32)

# =========================================================================
# CORE APPLICATION ASSEMBLY
# =========================================================================
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.c")

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

# =========================================================================
# LINK RUNWAY: Pure 2D SFML (Completely isolated from GLFW conflicts)
# =========================================================================
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    ${WINDOWS_DRIVERS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Fonts"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Fonts"
    COMMENT "Deploying runtime typography resources directly to executable sandbox..."
)



message(STATUS " Build configured for Pure SFML 2D Sandbox Application")