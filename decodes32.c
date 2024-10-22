#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lista de registradores
char *registers[] = {"eax", "ebx", "ecx", "esi", "edi", "ebp", "esp", "[ebx]", "[esi]", "[edi]", "[ebp]", "[esp]","0x10000000"};
// Lista de instruções
char *instructions[] = {"mov", "add", "sub",  "and", "or","xor"};
// Valor a ser utilizado nas operações
char *value = "0x1000";

// Função para gerar o arquivo assembly, compilar e testar
void generate_assembly_and_test(char *instruction, char *reg, char *reg2) {
    FILE *asm_file;
    char asm_file_path[] = "/tmp/out.asm";
    char bin_file_path[] = "/tmp/out";
    char output_file_path[] = "out.txt";
    char command[256];

    // Abrir o arquivo asm para escrita
    asm_file = fopen(asm_file_path, "w");
    if (asm_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo /tmp/out.asm\n");
        exit(1);
    }

    // Escrever conteúdo no arquivo .asm
    fprintf(asm_file, "org 0x100\n%s %s, %s\n", instruction, reg, reg2);
    fclose(asm_file);
    asm_file = fopen(output_file_path, "a");
    if (asm_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo /tmp/out.asm\n");
        exit(1);
    }

    // Escrever conteúdo no arquivo .asm
    fprintf(asm_file, "%s %s, %s | ", instruction, reg, reg2);
    fclose(asm_file);
    // Executar o comando NASM
    sprintf(command, "nasm %s -o %s >> %s 2>&1", asm_file_path, bin_file_path, output_file_path);
    int nasm_result = system(command);

    // Verificar se houve erro no NASM
    if (nasm_result == 0) {
        // Se compilou corretamente, gerar o hexdump do binário com xxd
        sprintf(command, "xxd %s >> %s", bin_file_path, output_file_path);
        system(command);
    } else {
        // Escrever no arquivo que houve um erro
        FILE *output_file = fopen(output_file_path, "a");
        fprintf(output_file, "\nErro ao compilar %s %s, %s\n", instruction, reg, value);
        fclose(output_file);
    }
}

int main() {
    char output_file_path[] = "out.txt";

    // Limpar o conteúdo do arquivo out.txt no início
    FILE *output_file = fopen(output_file_path, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", output_file_path);
        exit(1);
    }
    fclose(output_file);

    // Testar todas as combinações de instruções e registradores
    int num_instructions = sizeof(instructions) / sizeof(char*);
    int num_registers = sizeof(registers) / sizeof(char*);

    for (int i = 0; i < num_instructions; i++) {
        for (int j = 0; j < num_registers; j++) {
            for (int n = 0; n < num_registers; n++) {
                printf( "%s %s, %s\n", instructions[i], registers[j],  registers[n]);
                generate_assembly_and_test(instructions[i], registers[j],  registers[n]);
            }
        }
    }

    // Abrir o arquivo final com gedit
    system("gedit out.txt");

    return 0;
}
