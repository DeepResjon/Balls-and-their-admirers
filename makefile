default:
	clang src/main.c -I"depencies/include" "depencies/bin/libraylib.a" -lopengl32 -lgdi32 -lwinmm