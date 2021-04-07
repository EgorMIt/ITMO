#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

int main() {
    FILE* fileInputStream = fopen("Ex1.exe", "rb");
    FILE* fileOutputStreamTxt = fopen("D:\\outputinfo.txt", "w");  
    FILE* fileOutputStreamCode = fopen("D:\\code.txt", "wb");

    if (!fileInputStream) {
        printf("File not found");
        return 1;
    }

    IMAGE_DOS_HEADER DosHeader = { 0 };
    IMAGE_NT_HEADERS PeHeader = { 0 };
    IMAGE_SECTION_HEADER SectionHeader = { 0 };
    IMAGE_SECTION_HEADER TxtSectionHeader = { 0 };

    fread(&DosHeader, sizeof DosHeader, 1, fileInputStream);

    if (DosHeader.e_magic != 0x5a4d) {
        printf("file should be PE");
    }


    fseek(fileInputStream, DosHeader.e_lfanew, 0);
    fread(&PeHeader, sizeof(IMAGE_NT_HEADERS), 1, fileInputStream);
    fprintf(fileOutputStreamTxt, "Signature:\t\t %lx \n", PeHeader.Signature);

    fprintf(fileOutputStreamTxt, "Numbers of sections:\t %d\n", PeHeader.FileHeader.NumberOfSections);
   

    fprintf(fileOutputStreamTxt, "Entry point address:\t %08lu\n\n", PeHeader.OptionalHeader.AddressOfEntryPoint);

    for (int i = 0; i < PeHeader.FileHeader.NumberOfSections; ++i) {

        fread(&SectionHeader, sizeof(IMAGE_SECTION_HEADER), 1, fileInputStream);
        fprintf(fileOutputStreamTxt, "-------------------------------\n");
        fprintf(fileOutputStreamTxt, "%2d %s VirtSize:\t  %08lx\n\n", i + 1, SectionHeader.Name, SectionHeader.Misc.VirtualSize);
        fprintf(fileOutputStreamTxt, "%s %08lx\n", "VirtualAddress:\t\t", SectionHeader.VirtualAddress);
        fprintf(fileOutputStreamTxt, "%2s %08lx\n", "Raw data offset:\t", SectionHeader.PointerToRawData);
        fprintf(fileOutputStreamTxt, "%2s %08lx\n", "Size of raw data:\t", SectionHeader.SizeOfRawData);
        fprintf(fileOutputStreamTxt, "%2s %08lx\n", "Relocation offset:\t", SectionHeader.PointerToRelocations);
        fprintf(fileOutputStreamTxt, "%2s %08x\n", "Relocations number:\t", SectionHeader.NumberOfRelocations);
        fprintf(fileOutputStreamTxt, "%2s %08lx\n", "Line offset:\t\t", SectionHeader.PointerToLinenumbers);
        fprintf(fileOutputStreamTxt, "%2s %08x\n", "Lines number:\t\t", SectionHeader.NumberOfLinenumbers);
        fprintf(fileOutputStreamTxt, "%2s %08lx\n\n", "Characteristics:\t", SectionHeader.Characteristics);

        if (strcmp((const char*)SectionHeader.Name, ".text") == 0) {
            TxtSectionHeader = SectionHeader;
        }

    }

    fseek(fileInputStream, TxtSectionHeader.PointerToRawData, 0);

    char* data = malloc(TxtSectionHeader.SizeOfRawData);

    fread(data, sizeof(char), TxtSectionHeader.SizeOfRawData, fileInputStream);
    fwrite(data, sizeof(char), TxtSectionHeader.SizeOfRawData, fileOutputStreamCode);
    free(data);


    fclose(fileOutputStreamTxt);
    fclose(fileInputStream);
    fclose(fileOutputStreamCode);

    printf("Section data is written in outputinfo.txt\nBinary code is written to code.txt\nShutting down...\n\n");
    return 0;
}