task101:
	g++ Task_101.cpp -I"C:\SDL2-2.32.10\x86_64-w64-mingw32\include\SDL2" -L"C:\SDL2-2.32.10\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -mwindows -o Task_101.exe

task102:
	g++ Task_102.cpp -I"C:\SDL2-2.32.10\x86_64-w64-mingw32\include\SDL2" -L"C:\SDL2-2.32.10\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -mwindows -o Task_102.exe

task103:
	g++ Task_103.cpp -I"C:\SDL2-2.32.10\x86_64-w64-mingw32\include\SDL2" -L"C:\SDL2-2.32.10\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -mwindows -o Task_103.exe

clean:
	del Task_101.exe Task_102.exe Task_103.exe