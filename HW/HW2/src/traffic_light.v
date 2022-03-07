module traffic_light (
    input  clk,
    input  rst,
    input  pass,
    output reg R,
    output reg G,
    output reg Y
);

reg [2:0]state, next_state;
reg [9:0]counter;
reg counter_reset;
//write your code here
always @(posedge clk or posedge rst) begin
    if(rst)begin
        state <= 0;
    end
    else begin
        if(pass)begin
            state <= 0;
        end
        else begin
            state <= next_state;
        end
    end
end

//handle output
always @(state or counter) begin
    case(state)
        3'd0: begin//green 512
           if(counter == 511)begin
               counter_reset = 1;
               next_state = 1;
           end 
           else begin
               counter_reset = 0;
               next_state = 0;
           end
           R = 0;
           G = 1;
           Y = 0;
        end 
        3'd1: begin//none 64
            if(counter == 63)begin
               counter_reset = 1;
               next_state = 2;
           end 
           else begin
               counter_reset = 0;
               next_state = 1;
           end
           R = 0;
           G = 0;
           Y = 0;
        end
        3'd2: begin//green 64
            if(counter == 63)begin
               counter_reset = 1;
               next_state = 3;
           end 
           else begin
               counter_reset = 0;
               next_state = 2;
           end
           R = 0;
           G = 1;
           Y = 0;
        end
        3'd3: begin//none 64
            if(counter == 63)begin
               counter_reset = 1;
               next_state = 4;
           end 
           else begin
               counter_reset = 0;
               next_state = 3;
           end
           R = 0;
           G = 0;
           Y = 0;
        end
        3'd4: begin//green 64
            if(counter == 63)begin
               counter_reset = 1;
               next_state = 5;
           end 
           else begin
               counter_reset = 0;
               next_state = 4;
           end
           R = 0;
           G = 1;
           Y = 0;
        end
        3'd5: begin//yellow 256
            if(counter == 255)begin
               counter_reset = 1;
               next_state = 6;
           end 
           else begin
               counter_reset = 0;
               next_state = 5;
           end
           R = 0;
           G = 0;
           Y = 1;
        end
        3'd6: begin//red 512
            if(counter == 511)begin
               counter_reset = 1;
               next_state = 0;
           end 
           else begin
               counter_reset = 0;
               next_state = 6;
           end
           R = 1;
           G = 0;
           Y = 0;
        end
    endcase  
end

//handle counter
always @(posedge clk) begin
    if((pass && state != 0) || counter_reset == 1|| rst)begin
        counter <= 0;
    end
    else begin
        counter <= counter + 1;
    end
end
endmodule
