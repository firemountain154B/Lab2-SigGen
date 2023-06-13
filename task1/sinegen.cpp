#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

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

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en  = 0;

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
        
        vbdPlot(int(top->dout), 0, 255);
        if(i != 30){
        top->rst = (i<2)|(i == 15);}
        top->en  = (i>4);
        top->incr= 1;    
        // either simulation finished, or 'q' is pressed
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
        exit(0);                // ... exit if finish OR 'q' pressed
        }
    tfp->close();
    exit(0);
}