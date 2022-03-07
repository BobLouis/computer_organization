module traffic_light (
    input  clk,
    input  rst,
    input  pass,
    output reg R,
    output reg G,
    output reg Y
);

//write your code here
reg [2:0]state;
reg [9:0]cycle;

always @(posedge clk or posedge rst) begin
    if(rst)begin
        state <= 0;
        cycle <= 0;
        R <= 0;
        G <= 0;
        B <= 0;
    end
    else begin
        if(state == 0) begin //green 512
            R <= 0;
            G <= 1;
            B <= 0;
            
            if (cycle == 512) begin
                state <= 1;
                cycle <= 0;
            end
            else begin
                cycle <= cycle + 1;
            end
        end
        else if(state == 1) begin //None 64
            R <= 0;
            G <= 0;
            B <= 0;
            if (cycle == 64) begin
                state <= 2;
                cycle <= 0;
            end
            else begin
                cycle <= cycle + 1;
            end
        end
        else if(state == 2) begin //green 64
            R <= 0;
            G <= 1;
            B <= 0;
            if (cycle == 64) begin
                state <= 3;
                cycle <= 0;
            end
            else begin
                cycle <= cycle + 1;
            end
        end
        else if(state == 3) begin //None 64
            R <= 0;
            G <= 0;
            B <= 0;
            if (cycle == 64) begin
                state <= 4;
                cycle <= 0;
            end
            else begin
                cycle <= cycle + 1;
            end
        end
        else if(state == 4) begin //green 64
            R <= 0;
            G <= 1;
            B <= 0;
            if (cycle == 64) begin
                state <= 5;
                cycle <= 0;
            end
            else begin
                cycle <= cycle + 1;
            end
        end
    end
end


endmodule
