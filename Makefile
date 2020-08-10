run1:
	g++ -std=c++11 calculator1.cpp -w -lGL -lglfw -lGLEW -lGLU -o bin/p
	./bin/p

run : Application.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o Shader.o stb_image.o Texture.o imgui.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o imgui_draw.o imgui_widgets.o
	g++ -std=c++11 -o bin/exe Application.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o Shader.o stb_image.o Texture.o imgui.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_demo.o imgui_draw.o imgui_widgets.o -w -lGL -lglfw -lGLEW -lGLU
	./bin/exe

Application.o : src/Application.cpp src/VertexBuffer.h src/IndexBuffer.h src/VertexArray.h src/VertexBufferLayout.h src/Shader.h src/vendor/stb_image/stb_image.h src/Texture.h src/vendor/imgui/imgui.h src/vendor/imgui/imgui_impl_opengl3.h src/vendor/imgui/imgui_impl_glfw.h 
	g++ -std=c++11 -c src/Application.cpp
	
imgui.o : src/vendor/imgui/imgui.cpp src/vendor/imgui/imconfig.h src/vendor/imgui/imgui_internal.h src/vendor/imgui/imstb_rectpack.h src/vendor/imgui/imstb_textedit.h src/vendor/imgui/imstb_truetype.h 
	g++ -std=c++11 -c src/vendor/imgui/imgui.cpp

imgui_demo.o : src/vendor/imgui/imgui_demo.cpp
	g++ -std=c++11 -c src/vendor/imgui/imgui_demo.cpp

imgui_draw.o : src/vendor/imgui/imgui_draw.cpp
	g++ -std=c++11 -c src/vendor/imgui/imgui_draw.cpp

imgui_widgets.o : src/vendor/imgui/imgui_widgets.cpp
	g++ -std=c++11 -c src/vendor/imgui/imgui_widgets.cpp

imgui_impl_opengl3.o : src/vendor/imgui/imgui_impl_opengl3.cpp
	g++ -std=c++11 -c src/vendor/imgui/imgui_impl_opengl3.cpp

imgui_impl_glfw.o : src/vendor/imgui/imgui_impl_glfw.cpp
	g++ -std=c++11 -c src/vendor/imgui/imgui_impl_glfw.cpp

IndexBuffer.o : src/IndexBuffer.cpp src/Renderer.h
	g++ -std=c++11 -c src/IndexBuffer.cpp

VertexBuffer.o : src/VertexBuffer.cpp src/Renderer.h
	g++ -std=c++11 -c src/VertexBuffer.cpp

Renderer.o : src/Renderer.cpp 
	g++ -std=c++11 -c src/Renderer.cpp

VertexArray.o : src/VertexArray.cpp 
	g++ -std=c++11 -c src/VertexArray.cpp

Shader.o : src/Shader.cpp
	g++ -std=c++11 -c src/Shader.cpp

stb_image.o : src/vendor/stb_image/stb_image.cpp
	g++ -std=c++11 -c src/vendor/stb_image/stb_image.cpp		

Texture.o : src/Texture.cpp
	g++ -std=c++11 -c src/Texture.cpp

clean :
	rm *.o bin/exe

