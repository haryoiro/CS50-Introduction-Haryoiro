#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
typedef size_t SIZE;

int main(int argc, char *argv[])
{

    // 引数が不正な場合エラー
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *ptr = argv[1];
    FILE *infile = NULL;
    FILE *outfile = NULL;
    size_t size;
    long length = 0;
    BYTE *buffer;

    // 引数の文字列からファイルポインタをインプット
    // バイナリ読み込み書き込み
    infile = fopen(ptr, "r");
    if (infile == NULL)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // 
    if (fseek(infile, 0, SEEK_END) != 0)
    {
        fclose(infile);
        
        printf("Usage: ./recover image\n");
        return 1;
    }

    length = ftell(infile);
    if (fseek(infile, 0L, SEEK_SET) != 0)
    {
        fclose(infile);
        printf("Usage: ./recover image\n");
        return 1;
    }

    buffer = (BYTE *) malloc(length);
    if (buffer == NULL)
    {
        fclose(infile);
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    int rc = 0;
    int fsize = 0;
    char ofn[512] = "\0";
    for (int i = 0; i < length / 512; ++i)
    {
        fread(buffer, sizeof(BYTE), 512, infile);
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (rc != 0)
            {
                fclose(outfile);
            }
            sprintf(ofn, "%03i.jpg", rc);
            outfile = fopen(ofn, "w+");
            ++rc;
            fwrite(buffer, sizeof(BYTE), 512, outfile);
        }
        else if (rc >= 1)
        {
            fwrite(buffer, sizeof(BYTE), 512, outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
    
    free(buffer);

    return 0;
}
