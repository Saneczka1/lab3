#define RAW_SPACE(addr)     (*(volatile unsigned long *)(addr))

#define SYKOM_CTRL_ADDR     (0x100630)		
#define SYKOM_ID_ADDR       ((SYKOM_CTRL_ADDR)+4)
#define SYKOM_UART_ADDR     ((SYKOM_CTRL_ADDR)+8)

# define SYKT_OS1 (( SYKOM_CTRL_ADDR ) +0x0990 )
# define SYKT_OS2 (( SYKOM_CTRL_ADDR ) +0x0b90 ) //pozmieniac
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
    unsigned char hex_digits [16];
    
    int i = sizeof(unsigned long) * 2;  
    hex_str[i] = '\0';  
    
    do {
      i--;
      hex_str[i] = hex_digits[v % 16];  
      v /= 16;  
    } while (v != 0 && i > 0);
    
    putchars(&hex_str[i]);  

    
}

/*
void print_me ( unsigned long v) {
unsigned int remainder ;
unsigned char hex_digits [16];
int i = 0;
do {
remainder = v % 16;
hex_digits [i ++] = val2hex ( remainder );
v = v / 16;
} while ( v != 0) ;
for ( int j = i - 1; j >= 0; j - -) {
my_putchar ( hex_digits [j ]) ;
}
}

*/
int *os1_ptr = (int *)SYKT_OS1;
int *os2_ptr = (int *)SYKT_OS2;
int *counter_ptr = (int *)COUNTER;

void store_os1(int integ) {
    *os1_ptr = integ;
}

void store_os2(int integ) {
    *os2_ptr = integ;
}

void store_counter(int integ) {
    *counter_ptr = integ;
}

unsigned long show_os1() {
    return (unsigned long)(*os1_ptr);
}

unsigned long show_os2() {
    return (unsigned long)(*os2_ptr);
}

unsigned long show_counter() {
    return (unsigned long)(*counter_ptr);
}



int main ( void ) {
putchars("RISCV-APP: test ("__FILE__", "__DATE__", "__TIME__")\n");


putchars (" Test : \n ") ;
int i = 0;
//for (;;) {
//i ++;
// odczyty na osiach 
/* Os 1*/
 print_me(show_os1());
 putchars("\n ") ;
/* Os 2*/
 print_me(show_os2());
 putchars("\n") ;
 print_me(show_counter());
/* Test 2 - zapis na osiach */
//if (i ==1000) {
/* Os 1*/
//     putchars (" Testowana w a r t o Ż : 0x7C57BA \n ") ;
//     putchars (" Spodziewany wynik : 1111") ;
//     store_os1 (0x7C57BC);
    /* Os 2*/
//     putchars (" Testowana w a r t o Ż : 0 xBABA \n ") ;
//     putchars (" Spodziewany wynik : 0101") ;
//     store_os2 (0xBABC);
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
store_counter (0x4);
print_me (show_counter());
putchars (" ") ;
//}
my_simulation_exit (0) ;
return 0;}

