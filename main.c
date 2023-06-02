#define RAW_SPACE(addr)     (*(volatile unsigned long *)(addr))

#define SYKOM_CTRL_ADDR     (0x100470)		
#define SYKOM_ID_ADDR       ((SYKOM_CTRL_ADDR)+4)
#define SYKOM_UART_ADDR     ((SYKOM_CTRL_ADDR)+8)

# define SYKT_OS1 (( SYKOM_CTRL_ADDR ) +0x0990 )
# define SYKT_OS2 (( SYKOM_CTRL_ADDR ) +0x0190 ) 
# define COUNTER (( SYKOM_CTRL_ADDR ) +0x22c0 )

#define SYKOM_EXIT_VAL      (0x00003333)
#define SYKOM_UART_VAL      (0x00008888)



void my_simulation_exit(unsigned char ret_code) {
    RAW_SPACE(SYKOM_CTRL_ADDR) = SYKOM_EXIT_VAL | (((unsigned long)ret_code)<<16);
}



void my_putchar(unsigned char c) {
    RAW_SPACE(SYKOM_UART_ADDR)=SYKOM_UART_VAL | ((0x000000FF & (unsigned long)c)<<16);
}

 

unsigned long my_get_cpu_id(void) {
    return RAW_SPACE(SYKOM_ID_ADDR);
}


void putchars(unsigned char *s) {
    unsigned char* p = s;
    while (*p != '\0') {
        my_putchar(*p);
        p++;
    }
    
}



char val2hex(unsigned int i) {
    if (i >= 0 && i <= 9) {
        return i + '0';
    } else if (i >= 10 && i <= 15) {
        return i - 10 + 'A';
    } else {
        return 0; 
    }

}



void print_me(unsigned long v) {
    char hex_str[sizeof(unsigned long) * 2 + 1]; 
    const char hex_digits[] = "0123456789abcdef"; 
    
    int i = sizeof(unsigned long) * 2;  
    hex_str[i] = '\0';  
    
    do {
      i--;
      hex_str[i] = hex_digits[v % 16];  
      v /= 16;  
    } while (v != 0 && i > 0);
    
    putchars(&hex_str[i]);  

    
}


void store_os1(int i) {
	RAW_SPACE(SYKT_OS1) = i;
} 


void store_os2 (int i) {
	RAW_SPACE(SYKT_OS2) = i;
} 


void store_counter(int i) {
	RAW_SPACE(COUNTER) = i;
} 


unsigned long show_os1() { 
	return RAW_SPACE(SYKT_OS1);
}


unsigned long show_os2() { 
	return RAW_SPACE(SYKT_OS2);
}


unsigned long show_counter() {
 	return RAW_SPACE(COUNTER);
}


// zliczanie 

void show_counter1_test(){
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
       for(;;){
        i++;
    print_me (show_counter());
    putchars (" ");
    }

}

// 1 zatrymanie
void show_counter2_test(){
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
    for(;;){


        i++;
        if(i>10000){  
        store_counter(0x0);
        print_me(show_counter());
        putchars(" ");
        }else{

        print_me (show_counter());
         putchars (" ");}
    }
        
 }

// 1 NA TRZECIM BICIE
void show_counter3_test(){
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
    for(;;){
        i++;
        store_counter(0x8);
        print_me(show_counter());
        putchars(" ");
    }


}



void sleep(){
    int i=0;
    for(;;){
        i++;

        if(i==200000){
            break; 
        }
    }
}


void show_os1_test(){
    int i = 0;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    for(;;){
        i++;
    print_me(show_os1());
	putchars("\n"); 
    
    
    if(i==10000){
        break;
    }
    }
}


void show_os2_test(){
    int i = 0;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
     long temp=RAW_SPACE(SYKT_OS1);
    for(;;){
        i++;
    print_me(show_os2());
	putchars("\n"); 
    print_me(temp);
    putchars("OK\n");
    
    if(i==10000){
        break;
    }
    }
}



void store_show_os1_test(){
    
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
   int i =0;
   sleep();
   putchars("Dane Wejsciowe 700F\n");
   putchars("Dane Oczekiwane: 78000\n");
   putchars("Dane Otrzymane:");
   
    store_os1(0x700F);
    print_me(show_os1());
    putchars("\n");
    putchars("Zaszlo");
    putchars("\n");

}



void store_show_os2_test(){                     
    
 putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
   int i =0;
   sleep();
   putchars("Dane Wejsciowe: 700F\n");
   putchars("Dane Oczekiwane 38\n");
   putchars("Dane Otrzymane:");
   
    store_os2(0x700F);
    print_me(show_os2());
    putchars("\n");
    putchars("Zaszlo");
    putchars("\n");
}



void store_os2_test(){                     
    int i=0;
    for (;;) {
    i ++;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    putchars("Testowana wartość: 0xFF58C \n");
	putchars("Spodziewany wynik: 0001");
	store_os2(0xFF58C);
    putchars("\n");
}}




void store_os1_test(){                     
    
 putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
    for (;;) {
    i ++;
        putchars("Testowana wartość: 0xFF58C \n");
		putchars("Spodziewany wynik: 1111");
		store_os1(0xFF58C);
        
    }
}




void podtrzymanie_test(){
    int i = 0;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
   
    for(;;){
        i++;
    	putchars("Test podtrzymania:");
		store_os1(0xFF58C);
        RAW_SPACE(0x0574)= 0x5555 ;
        
    }
}




void neutralnosc_test(){
    int i = 0;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
   
    for(;;){
        i++;
    	putchars("Test neutralnosci: ");
		print_me(RAW_SPACE(0xFFFC)); //odczyt ze zlego adresu
		putchars("\n");
         if(i==10000){
    		break;
    	}
    }
}




int main ( void ) {
putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
putchars(" Test : \n ");

show_os1_test();
//store_os2_test();
//store_os1_test();
//show_counter1_test();
//show_counter3_test();
//show_counter1_test();

//store_show_os1_test();
//store_show_os2_test();
//neutralnosc_test();
//podtrzymanie_test();

my_simulation_exit(0);   	
return 0;
}