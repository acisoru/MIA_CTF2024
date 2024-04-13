`timescale 1ns / 1ns
`default_nettype none

module alu_and16 (
    input  wire [15:0] a,
    b,
    output wire [15:0] result
);
  assign result = a & b;
endmodule

module alu_fulladder16 (
    input wire [15:0] a,
    b,
    input wire carryIN,
    output wire [15:0] result,
    output wire carryOUT
);

  wire [16:0] carry;
  assign carry[0] = carryIN;
  assign carryOUT = carry[16];

  assign result[15:0] = (a[15:0] ^ b[15:0]) ^ carry[15:0];
  assign carry[16:1] = (a[15:0] & b[15:0]) | (a[15:0] ^ b[15:0]) & carry[15:0];

endmodule

module ALU (
    input wire [15:0] a,
    b,
    input wire ADD1,
    ANDORADD,
    input wire NEG,

    output wire [15:0] result,
    output wire carry_flag
);

  wire [15:0] and16_result;
  wire [15:0] fulladder16_result;
  wire carryOut;

  wire [15:0] b_modified;
  assign b_modified = NEG ? ~b : b;

  alu_and16 and16_i (
      a,
      b_modified,
      and16_result
  );
  alu_fulladder16 fulladder16_i (
      a,
      b_modified,
      ADD1,
      fulladder16_result,
      carry_flag
  );

  assign result = ANDORADD ? and16_result : fulladder16_result;
endmodule


module MEMORY (
    input wire clk,
    input wire write_enable,
    input wire [7:0] address,
    input wire [15:0] data_in,
    output reg [15:0] data_out
);

  reg [15:0] MEMORY_block[0:255];

  initial begin
    $readmemh("mem.hex.txt", MEMORY_block);
  end

  always @(negedge clk) begin
    if (write_enable) MEMORY_block[address] <= data_in;
    else data_out <= MEMORY_block[address];
  end
endmodule

module CPU (
    input wire clk,
    input wire reset
);
  integer f;
  initial begin
    f = $fopen("output.txt", "w");
  end
  //////////// REGISTERS ////////////
  reg [7:0] IP;  // instruction pointer
  reg [15:0] IR;  // instruction register
  reg [15:0] AC;  // accumulator
  reg [15:0] DR;  // accumulator "number 2" (data register)

  //////////// MEMORY ////////////
  reg [15:0] data_in;
  wire [15:0] data_out;
  reg write_enable;  // R/W switch (0) = READ; (1) = WRITE
  reg [7:0] current_addr;
  MEMORY memory (
      .clk(clk),
      .write_enable(write_enable),
      .address(current_addr),
      .data_in(data_in),
      .data_out(data_out)
  );

  //////////// ALU ////////////

  // alu_in
  // wire [15:0] a, b;
  // wire ADD1, ANDORADD, NEG;
  reg ADD1_reg, ANDORADD_reg, NEGATE_reg;


  // alu_out
  wire [15:0] result;
  wire carry_flag;

  ALU ALU_i (
      .a(AC),
      .b(DR),
      .ADD1(ADD1_reg),
      .ANDORADD(ANDORADD_reg),
      .NEG(NEGATE_reg),
      .result(result),
      .carry_flag(carry_flag)
  );

  // IR decoding
  wire [7:0] opcode = IR[15:8];
  wire [7:0] second_part = IR[7:0];



  typedef enum {
    INFETCH,
    EXEC
  } cpu_state_t;

  cpu_state_t state;

  reg ALU_to_AC;
  always @(posedge clk or posedge reset) begin
    if (reset) begin
      IP <= 0;
      IR <= 0;
      AC <= 0;
      DR <= 0;
      current_addr <= 0;
      write_enable <= 0;
      ALU_to_AC <= 0;
      state <= INFETCH;
    end else begin
      case (state)
        INFETCH: begin
          write_enable <= 0;  // read mode
          IP <= IP + 1;
          current_addr <= IP;

          state <= EXEC;  // jump to next

          if (ALU_to_AC) begin
            $display($stime,, "result_to_ALU result=%h", result);
            AC <= result;
            ALU_to_AC <= 0;
          end

          $strobe($stime,, "INFETCH by addr=%h; IP=%h", current_addr, IP);
        end
        EXEC: begin
          IR = data_out;  // write CURRENT instr.
          $strobe($stime,, "EXEC of Inst=%h (IR=%h): AC=%h", opcode, IR, AC);
          case (opcode)

            8'hAA:
            begin
              AC <= second_part;
              state <= INFETCH;
            end

            8'hFF:
            begin
              $display($stime,, "exec stop");
              $finish;
            end

            8'hBB:
            begin
              ADD1_reg <= 0;
              ANDORADD_reg <= 0;
              NEGATE_reg <= 0;
              ALU_to_AC <= 1;
              state <= INFETCH;
            end


            8'hCC:
            begin
              ADD1_reg <= 0;
              ANDORADD_reg <= 1;
              NEGATE_reg <= 0;
              ALU_to_AC <= 1;
              state <= INFETCH;
            end


            8'hDD:
            begin
              ADD1_reg <= 1;
              ANDORADD_reg <= 0;
              NEGATE_reg <= 1;
              ALU_to_AC <= 1;
              state <= INFETCH;
            end

            8'h77:
			begin
              $display($stime,, "OUT");
              $fwrite(f, "%h\n", AC);
              state <= INFETCH;

            end
            8'hEE:
            begin
              DR <= second_part;
              state <= INFETCH;
            end


            default: begin
              state <= INFETCH;
            end

          endcase
        end

      endcase
    end
  end
endmodule
