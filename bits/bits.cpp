#include <iostream>
/* instruction_asimd_compute
It should manipulate i_vec_instr in the following way:
Bits 0-4 should be set to bits 0-4 of i_vec_reg_dst
Bits 5-9 should be set to bits 0-4 of i_vec_reg_src_0
Bits 16-20 should be set to bits 0-4 of i_vec_reg_src_1
*/
unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 ) {
    unsigned int vec_result = 0; // initialize return vector

    // bit wise setting of result vector from most significant to least significant bit
    for (int i = 31; i>=21; i--) vec_result = (vec_result << 1) ^ ((i_vec_instr >> i) & 1); // bits 21 to 31
    for (int i = 4; i>=0; i--) vec_result = (vec_result << 1) ^ ((i_vec_reg_dst >> i) & 1); // bits 16 to 20
    for (int i = 15; i<=10; i--) vec_result = (vec_result << 1) ^ ((i_vec_instr >> i) & 1); // bits 10 to 15
    for (int i = 9; i<=5; i--) vec_result = (vec_result << 1) ^ ((i_vec_reg_src_0 >> i) & 1); // bits 5 to 9
    for (int i = 4; i<=0; i--) vec_result = (vec_result << 1) ^ ((i_vec_reg_dst >> i) & 1); // bits 0 to 4
    // and just like that we implemented the FMLA vector operation :)

    return vec_result;
}

void char_get_binary(char variable, char *array) {
    for (int i = 0; i < sizeof(variable) * 8; i++) {
        array[i] = (variable >> i) & 1;
    }
}

void int_get_binary(int variable, int *array) {
    for (int i = 0; i < sizeof(variable) * 8; i++) {
        array[i] = (variable >> i) & 1;
    }
}

int main(){
    std::cout << std::endl << "Assignment 2.1:" << std::endl;
    std::cout << "size in bytes of unsigned char is " << sizeof(unsigned char) << std::endl;
    std::cout << "size of char is " << sizeof(char) << std::endl;
    std::cout << "size of unsigned int is " << sizeof(unsigned int) << std::endl;
    std::cout << "size of float is " << sizeof(float) << std::endl;
    std::cout << "size of double is " << sizeof(double) << std::endl;
    std::cout << "size of unsigned int * is " << sizeof(unsigned int *) << std::endl;
    std::cout << "size of float * is " << sizeof(float *) << std::endl;

    int n_array = 1500;
    int *array = (int*) malloc(n_array*sizeof(int));
    int *ptr;
    for (int i=0; i<n_array; i++) array[i]=i*3;

    for (int i = 0; i < 10; i++)
    {
        std::cout << array[i] << std::endl;
    }

    ptr = array;
    std::cout << "The Value of the Array at position 500 is " << *(ptr+500) << std::endl;
    
    std::cout << "The address of array[250] is " << ptr+250 << std::endl;
    std::cout << "The address of array[750] is " << ptr+750 << std::endl;    
    std::cout << "The size of an int is " << sizeof(*(ptr+750)) << std::endl;    
    std::cout << "Their distance in byte is " << (750-250)*sizeof(int) << std::endl;

    free(array);

    std::cout << "Assignment 2.2:" << std::endl;

    unsigned char l_data1  = 1;
    unsigned char l_data2  = 255;
    unsigned char l_data3  = l_data2 + 1;
    unsigned char l_data4  = 0xA1;
    unsigned char l_data5  = 0b1001011;
    unsigned char l_data6  = 'H';
    char l_data7  = -4;
    unsigned int  l_data8  = 1u << 11;
    unsigned int  l_data9 = l_data8 << 21;
    unsigned int  l_data10  = 0xFFFFFFFF >> 5;
    unsigned int  l_data11 = 0b1001 ^ 0b01111;
    unsigned int  l_data12 = ~0b1001;
    unsigned int  l_data13 = 0xF0 & 0b1010101;
    unsigned int  l_data14 = 0b001 | 0b101;
    unsigned int  l_data15 = 7743;
    int  l_data16 = -7743;

    for (int i = 0; i < sizeof(l_data1) * 8; i++) std::cout << ((l_data1 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data2) * 8; i++) std::cout << ((l_data2 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data3) * 8; i++) std::cout << ((l_data3 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data4) * 8; i++) std::cout << ((l_data4 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data5) * 8; i++) std::cout << ((l_data5 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data6) * 8; i++) std::cout << ((l_data6 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data7) * 8; i++) std::cout << ((l_data7 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data8) * 8; i++) std::cout << ((l_data8 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data9) * 8; i++) std::cout << ((l_data9 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data10) * 8; i++) std::cout << ((l_data10 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data11) * 8; i++) std::cout << ((l_data11 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data12) * 8; i++) std::cout << ((l_data12 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data13) * 8; i++) std::cout << ((l_data13 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data14) * 8; i++) std::cout << ((l_data14 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data15) * 8; i++) std::cout << ((l_data15 >> i) & 1);
    std::cout << std::endl;

    for (int i = 0; i < sizeof(l_data16) * 8; i++) std::cout << ((l_data16 >> i) & 1);
    std::cout << std::endl;

    // char_get_binary(l_data7, bin_array);
    // for (size_t i = 0; i < sizeof(l_data7)*8; i++) std::cout << bin_array[i];
    // std::cout << std::endl;    
    
}