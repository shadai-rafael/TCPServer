#include "NetworkUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define MSB_32_BYTES_MASK 0xFF000000

char* network_convert_ip_n_to_p( uint32_t ip_addr, char *output_buffer){    
    uint8_t tmp_n = 0;
    uint32_t mask = MSB_32_BYTES_MASK;
    uint8_t shift_n = 24;
    char tmp_str[4];
    char* tmp_ip = (char*) malloc(16);
    memset(tmp_str, 0, 4);
    memset(tmp_ip, 0, 16);
    tmp_n = (uint8_t)((ip_addr & mask) >> shift_n);
    sprintf(tmp_str, "%d", tmp_n);
    strcat(tmp_ip,tmp_str);
    memset(tmp_str, 0, 4);
    for (size_t i = 0; i < 3; i++)
    {
        strcat(tmp_ip,".");
        shift_n-=8;
        mask = mask >> 8;
        tmp_n = (uint8_t)((ip_addr & mask) >> shift_n);
        sprintf(tmp_str, "%d", tmp_n);
        strcat(tmp_ip,tmp_str);
        memset(tmp_str, 0, 4);
    }

    if(output_buffer){
        memcpy(output_buffer,tmp_ip,16);
        free(tmp_ip);
        return NULL;        
    }
    return tmp_ip;
}

uint32_t network_convert_ip_p_to_n(const char *ip_addr){
    uint32_t ip_n = 0;
    char tmp[16];
    memcpy(tmp,ip_addr,16);
    char* token = strtok(tmp, ".");
    ip_n |= atoi(token);
    for(int i=0;i<3;i++){
        token = strtok(NULL, ".");
        ip_n = ip_n << 8;
        ip_n |= atoi(token);    
    }
    return ip_n;
}