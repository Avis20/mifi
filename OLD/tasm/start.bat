@echo off
echo Create Assembler file
tasm /zi prog1.asm
tlink.exe /v prog1.obj