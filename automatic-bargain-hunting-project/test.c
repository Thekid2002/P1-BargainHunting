#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/**
 * Turns string into lowered characters
 */
void string_lower( char *string ) {
    for ( int i = 0; i < strlen( string ); ++i ) {
        string[i] = tolower( string[i] );
    }
}

void string_lower_test() {
    char string[] = "TeSt";
    string_lower(string);
    for ( int i = 0; i < strlen( string ); ++i ) {
        if(!islower(string[i])) {
            printf("Test Failed\n");
            return;
        }
    }
    printf("Test Succesed\n");
}


int scan_int(char input_string[20]) {
    int input;
    //scanf( " %s", input_string );
    if ( isalpha( input_string[0] )) {
        return -1;
    }
    sscanf( input_string, " %d", &input );
    return input;
}

void test_num_5(){
    int output = scan_int("5");
    printf("Testing for number '5'\n");
    if(output == -1){
        printf("Test Falied\n");
    }
    else{
        printf("Test Succeeded\n");
    }
    printf("\n");
}

void test_char_t(){
    int output = scan_int("t");
    printf("Testing for char 't'\n");
    if(output == -1){
        printf("Test Succeeded\n");
    }
    else{
        printf("Test Falied\n");
    }
    printf("\n");
}

void test_combination(){
    int output = scan_int("5t");
    printf("Testing for char '5t'\n");
    if(output == -1){
        printf("Test Falied\n");
    }
    else{
        printf("Test Succeeded\n");
    }
    printf("\n");
}

int main() {
    test_num_5();
    test_char_t();
    test_combination();
    string_lower_test();
}