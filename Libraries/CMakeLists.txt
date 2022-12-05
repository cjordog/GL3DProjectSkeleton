### imgui

file(GLOB IMGUI_SRC CONFIGURE_DEPENDS		
	"imgui/*.cpp"
	"imgui/backends/imgui_impl_glfw.cpp"
	"imgui/backends/imgui_impl_opengl3.cpp"
)

set(IMGUI_IMPL_OPENGL_LOADER_GLAD ON)
set(_IMGUI_WIN32 ON)
set(_CRT_SECURE_NO_WARNINGS ON)

add_library(imgui ${IMGUI_SRC})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		"imgui/" 
		"imgui/examples/" 
		"imgui/backends/" 
)

target_include_directories(imgui
	PUBLIC 
		"imgui/" 
		"imgui/examples/" 
		"glad/include"
		"glfw/include/"
)

### GLAD

set(_GLAD_WIN32 ON)

add_library(glad "glad/src/glad.c")

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		"glad/include/"
)

target_include_directories(glad  
	PUBLIC 
		"glad/include/"
)