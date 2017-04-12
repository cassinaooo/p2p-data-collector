#include <protocoltypes.h>
#include "protocolutils.h"

/**
 * preenche um header
 *
 * malloca um Header, deve ser desalocado no caller
 *
 * @param clientname: nome do cliente que deseja enviar os arquivos, o HOST
 * @param filename: nome do arquivo que esta sendo enviado
 * @param filesize: tamanho do arquivo
 * @param checksum: checksum para arquivo
 * @return um ponteiro para o Header preenchido
 */

Header *newheader(const char * clientname, const char * filename, __off_t filesize, const unsigned int checksum){

    debug("attempting to create new header %s %s %ld %ld\n", clientname, filename, filesize, checksum);
    
    Header *new = malloc(sizeof(Header));

    strcpy(new->client_name, clientname);
    strcpy(new->filename, filename);

    new->filesize = filesize;
    new->checksum = checksum;
    
    return new;
}

/**
 * imprime um header na tela de maneira humanamente legivel
 * @param h: o ponteiro para o header que se deseja imprimir
 */

void printheader(const Header * h){
    debug("%s\n", "------ HEADER BEGIN -------");
    debug("clientname: %s\n", h->client_name);
    debug("filename: %s\n", h->filename);
    debug("filesize: %ld\n", h->filesize);
    debug("checksum: %u\n", h->checksum);
    debug("%s\n\n", "------ HEADER END -------");
}

/**
 * calcula a hash nao criptografica crc32b para um buffer
 * @return a hash
 */
unsigned int crc32b(unsigned char *message, size_t size) {
    int i, j;
    unsigned int byte, crc;
    int mask;

    i = 0;
    crc = 0xFFFFFFFF;

    while (i < size) {
        byte = message[i];            // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }

    return ~crc;
}

/**
 * calcula a hash usando crc32b para um arquivo indicado por filename
 * @param filename: o arquivo sobre o qual se deseja calcular a hash
 * @return a checksum para esse arquivo
 */

unsigned int cksum(const char *filename){
    unsigned char *filebytes = NULL;

    unsigned long size = slurp(filename, &filebytes, 0);
    unsigned int cksum = crc32b(filebytes, size);

    debug("cksum for file %s with %ld bytes long was: %u\n", filename, size, cksum);

    return cksum;
}

/**
 * transforma um header encodificado numa string para a struct Header
 * malloca um Header, deve ser desalocado no caller
 *
 * @param str: string na forma: "<cliente>|<file>|<file_size>|<file_checksum>", espera-se um '\0' no final da string
 * @return um ponteiro para um Header isntanciado com os dados da string, já convertidos para os tipos devidos
 *
 */

Header *decodeHeader(const char *str){
    char client_name[265], file_name[255], file_size_str[64], checksum_str[64];
    __off_t file_size;
    long int checksum;

    int i = 0, break_point;

    while(str[i] != '|'){
        client_name[i] = str[i];
        i++;
    }

    client_name[i] = '\0';

    i++;

    break_point = i;

    while(str[i] != '|'){
        file_name[i - break_point] = str[i];
        i++;
    }

    file_name[i - break_point] = '\0';

    i++;

    break_point = i;

    while(str[i] != '|'){
        file_size_str[i - break_point] = str[i];
        i++;
    }

    file_size_str[i - break_point] = '\0';

    i++;

    break_point = i;

    while(str[i] != '\0'){
        checksum_str[i - break_point] = str[i];
        i++;
    }

    checksum_str[i - break_point] = '\0';


    file_size = atol(file_size_str);
    checksum = atol(checksum_str);

    return newheader(client_name, file_name, file_size, checksum);
}

/**
 * wrapper para printf, bom pra habilitar ou desabilitar o debug, eventualmente
 */

void debug(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fputs("D: ", stdout);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

/**
 * wrapper para fprintf(stderr, ...), bom pra habilitar ou desabilitar o debug, eventualmente
 */

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fputs("E: ", stderr);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fflush(stderr);
}

/**
 * Encodifica o Header apontado pelo ponteiro h em uma string na forma: "<cliente>|<file>|<file_size>|<file_checksum>"
 * A string resultante possui um '\0' no seu final
 */

void encodeHeader(Header *h, char *buf) {
    sprintf(buf, "%s|%s|%ld|%u", h->client_name, h->filename, h->filesize, h->checksum);
}

