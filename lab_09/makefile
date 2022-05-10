_MAKE_OUT_DIR_ := $(shell mkdir -p out)
_MAKE_ASM_DIR_ := $(shell mkdir -p assembly)

.PHONY: math_sse math_fpu math_asm math pi run assembly clean

math_sse:
	g++ test_math.cpp -mno-80387 -DSSE -O0 -o test_math_sse.exe

math_fpu:
	g++ test_math.cpp -m80387 -mno-sse -DFLOAT_80 -O0 -o test_math_fpu.exe

math_asm:
	g++ test_math.cpp -masm=intel -DASM -O0 -o test_math_asm.exe

pi:
	g++ test_pi.cpp -masm=intel -o test_pi.exe

run: math_sse math_fpu math_asm pi
	@echo "SSE: "
	./test_math_sse.exe
	@echo "FPU: "
	./test_math_fpu.exe
	@echo "ASM: "
	./test_math_asm.exe
	@echo "PI: "
	./test_pi.exe

assembly:
	g++ -S test_math.cpp -mno-80387 -DSSE -O0 -o assembly/test_math_sse.s
	g++ -S test_math.cpp -m80387 -mno-sse -DFLOAT_80 -O0 -o assembly/test_math_fpu.s
	g++ -S test_math.cpp -masm=intel -DASM -O0 -o assembly/test_math_asm.s
	g++ -S test_pi.cpp -masm=intel -o assembly/test_pi.s

clean:
	rm -rf out/ assembly/ *.exe
