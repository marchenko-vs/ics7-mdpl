set path=%path%D:\masm32\bin

ml /c /coff main.asm
link /SUBSYSTEM:WINDOWS main.obj
