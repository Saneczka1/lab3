/* verilator lint_off MULTIDRIVEN */
/* verilator lint_off UNDRIVEN */
/* verilator lint_off UNUSED */
/* verilator lint_off WIDTH */

module gpioemu ( n_reset , saddress [15:0] , srd , swr , sdata_in [31:0] , sdata_out [31:0] ,
gpio_in [31:0] , gpio_latch , gpio_out [31:0] , clk , gpio_in_s_insp [31:0]) ;

input n_reset ;
input [15:0] saddress ;
input srd ;
input swr ;
input [31:0] sdata_in ;
output [31:0] sdata_out ;

input [31:0] gpio_in ;
input gpio_latch ;

output [31:0] gpio_out ;
reg [31:0] gpio_in_s ;
reg [31:0] gpio_out_s ;
reg [31:0] sdata_out_s ;

output [31:0] gpio_in_s_insp ;

input clk ;
reg [7:0] counter_s ;
reg [2:0] status ;


// odpowiedz na reset
always @( negedge n_reset )
begin
	gpio_in_s <= 0;
	gpio_out_s <= 0;
	sdata_out_s <= 0;
	status <= 2;
	counter_s <=252;
end


always @( posedge gpio_latch )
begin
	gpio_in_s <= gpio_in ;
end


// zapisywanie z magistrali do adresu
always @( posedge swr )
begin
	//oś pierwsza 
		if (saddress == 16'h0990)
			gpio_out_s[3:0] <= sdata_in[18:15];     
	else if (saddress == 16'h0190)
			gpio_out_s[15:12] <= sdata_in[6:3];
	else if (saddress ==16'h22c0)
		begin
			status[2:0] <= sdata_in [22:20];
		end
	
end



// odczytywanie spod adresu
always @( posedge srd )
begin
	//oś pierwsza 0x0990
		if (saddress == 16'h0990)
			sdata_out_s <=gpio_in_s[3:0] << 15; // dane są na [18:15]
		//oś druga 0x0b90
	else if (saddress == 16'h0190)
			sdata_out_s <= gpio_in_s[15:12] << 3; // dane są na [6:3]
	else if ( saddress == 16'h22c0 )
		begin
			sdata_out_s [0] <= status [1];
			sdata_out_s <= counter_s ;
		end
	else
		sdata_out_s <='h0;
end


// licznik
always @( posedge clk )
begin
		
	if ( status [2]== 1)
			counter_s <= 252;
			status [2] <=0;
			status [1] <=1;
	if ( counter_s != 255 && status [1]==1)
		counter_s <= counter_s + 1;
	if ( counter_s == 255) begin
		status [0] <= 1;
		counter_s <=252;
	end
	//status [1] <=1;
end


//state = {rozpoczęcie zliczania od wart. początkowej, zatrzymanie zliczania, osiągnięcie maks wart}


assign sdata_out = sdata_out_s;
assign gpio_out = gpio_out_s;
	
endmodule
