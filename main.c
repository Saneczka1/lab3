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
    unsigned int remainder;
    unsigned char hex_digits[16];
    int i = 0;

    do {
        remainder = v % 16;
        hex_digits[i++] = val2hex(remainder);
        v = v / 16;
    } while (v != 0);

    for (int j = i - 1; j >= 0; j--) {
        my_putchar(hex_digits[j]);
    }
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


// 1 NA PIERWSZYM BICIE

void show_counter1_test(){
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
       for(;;){
        i++;
    print_me (show_counter());
    putchars (" ");
    }

}

// 1 NA DRUGIM BICIE
void show_counter2_test(){
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
    int i=0;
    for(;;){
        i++;
        print_me (show_counter());
         putchars (" ");
    }
        if(i>10000){  
        store_counter(0x4);
        print_me(show_counter());
        putchars(" ");
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
////////////////////////
////////////////////////
////////////////////
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
		store_os1 (0x700F );
        RAW_SPACE (0x0574)= 0x5555 ;
        
    }
}



void neutralnosc_test(){
    int i = 0;
    putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
   
    for(;;){
        i++;
    	putchars("Test neutralnosci: ");
		print_me(RAW_SPACE(0xFFFF)); //odczyt ze zlego adresu
		putchars("\n");
         if(i==10000){
    		break;
    	}
    }
}




int main ( void ) {
putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");
putchars(" Test : \n ");


//store_os2_test();
show_counter2_test();

//store_show_os1_test();
//store_show_os2_test();
//neutralnosc_test();
//podtrzymanie_test();







//int i=0;

//for (;;) {
//i ++;
// odczyty na osiach 
/* Os 1*/
//store_os1(0xAFDBCE);
// print_me(show_os1());
// putchars("\n");
/* Os 2*/
 //store_os2(0x111222);
 //print_me(show_os2());
 //putchars("\n") ;
 //print_me(show_counter());
/* Test 2 - zapis na osiach */ //                           działa
//if (i ==1000) {
/* Os 1
     putchars(" Testowana w a r t o Ż : 0xabcdec \n ") ;
     putchars(" Spodziewany wynik : 0111") ;
     store_os1(0xabcdec);
    if (show_os1() == 7) {
    putchars("OK");
} else {
    putchars("NOT OK");
}
    /* Os 2*/
 //    putchars (" Testowana w a r t o Ż : 0x123456 \n ") ;
  //   putchars (" Spodziewany wynik : 0100") ;
   //  store_os2(0x123456);
   // if (show_os2() == 4) {
   // putchars("OK");
//} else {
   // putchars("NOT OK");
//}
//    }
/* Test 3 - test podtrzymania */
// putchars (" Test podtrzymania ") ;
// store_os1 (0 x7C57BA );
// RAW_SPACE (0 x0570 )= 0 x5555 ; // zapisanie wartosci na zly adres
/* Test 4 - test neutralnosci */
// print_me ( RAW_SPACE (0 xFFFF )) ; // odczyt ze zlego adresu
// putchars ("\n ") ;
/* Test 5 - test licznika */
// unsigned long counter_value = show_counter () ;
/*1 na pierwszym bicie */
// store_counter (0 x2 ) ;
// print_me ( show_counter () );
// putchars (" ") ;
/*1 na drugim bicie */
//store_counter(0x4);
//print_me(show_counter());
//putchars(" ");
//}
//my_simulation_exit(0);
//}
my_simulation_exit(0);   	
return 0;
}