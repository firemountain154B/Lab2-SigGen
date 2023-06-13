#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vsinegen* top = new Vsinegen;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("sinegen.vcd");
    
    // init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en  = 0;
    top->incr= 1;    

    for (i = 0; i<100000; i++){

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk <2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            if(i == 30){
                top->rst = !top->rst;
            }
            top->eval ();
        }
        
        vbdPlot(int(top->dout1), 0, 255);
        vbdPlot(int(top->dout2), 0, 255);
        vbdCycle(i+1);
        
        if(i != 30){
        top->rst = (i<2)|(i == 15);}
        top->en  = (i>4);
        // either simulation finished, or 'q' is pressed
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
        exit(0);                // ... exit if finish OR 'q' pressed
        }
    tfp->close();
    exit(0);
}