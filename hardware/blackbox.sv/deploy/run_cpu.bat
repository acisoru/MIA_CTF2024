@echo off
iverilog -Wall -g2012 -o task_sim src/design.sv src/testbench.sv
vvp task_sim
del task_sim
REM del *.vcd
REM pause