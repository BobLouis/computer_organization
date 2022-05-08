Immediate
在這裡我們需要根據不同的type產生不同的immediate，I type S type要做signed extension，LUI則要坐在後面12位補0

Register_Files
假如opcode是R type I type，就根據funct3 funct7給出對應的運算，算完放回rd，LUI則直接將immediate算好的值給回去

instr_addr == PC
因為這裡沒有branch 或是jump因此算完直接+4就好了

data_addr
算出data要存放的address裡，將rs值加上immdiate的值即是data_address


心得
這次作業難度跟上次差蠻多的，因為助教已經把大部分的code都寫完了，我們只要照上課老師教得把指令填一填就好了，比較值得注意就是要記的做signed extension 不然模擬會跑不出來。