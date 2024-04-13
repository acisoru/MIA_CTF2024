`timescale 1ns / 1ns
`default_nettype none

module CPU_tester;
  reg clk, reset;

  CPU test_CPU_instance (
      clk,
      reset
  );

  initial begin
    clk   = 0;
    reset = 1;
    #40 reset = 0;
  end

  // Clock generation
  always begin
    #10 clk = ~clk;
  end

  // End simulation at time "100000" if HLT is not present (to prevent big log)
  initial begin
    #100000 $finish;
  end

  /*initial begin
    $dumpfile("cpu_out.vcd");
    $dumpvars(0, test_CPU_instance);
  end
*/
  /*initial
    #40
      $monitor(
          $stime,
          ,
          "Reset=",
          reset,
          ,
          "IP=",
          test_CPU_instance.IP,
          ,
          "IR=",
          test_CPU_instance.IR,
          ,
          "AC=",
          test_CPU_instance.AC,
          ,
          "State=",
          ,
          test_CPU_instance.state.name,
          ,,
          ,,
          ,,
          ,
          "MemW=",
          ,
          test_CPU_instance.write_enable
      );*/
endmodule
