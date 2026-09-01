#include <stdio.h>
#include <stdlib.h>
typedef unsigned char byte;
typedef unsigned char stack_type;
#define err(text) (puts(text), exit(1))

#define CODE_SIZE 65536
#define ST_SIZE 256

int words[256], top = 0, size = 0;
stack_type stack[ST_SIZE];
byte std[] = "ip -\n^\\$@@\n!p1p1-=\nnp0-\n#^^\n<#>!@@=!&\n";
byte code[CODE_SIZE];

void push(stack_type el) { (top >= ST_SIZE) ? err("Error stack overflow") : (void)(stack[top++] = el); }
stack_type pop() { return (top <= 0) ? err("Error stack underflow"), 0 : stack[--top]; }
void init() {for (int i = 0; i < 256; i++) words[i] = -1;}
void compile() {
    for (int i = -1; i < size; i++) {
        if (i < 0 || code[i] == '\n') {
            if (i + 2 >= size) return;
            words[(byte)code[i+1]] = i+2;
            i++;
        }
    }
}
void eval(int addr) {
    stack_type x,y,z = 0;
    for (int i = addr; i < size && code[i] != '\n'; i++) {
        switch (code[i]) {
            case 'p': if (size <= i + 1) err("Error get byte from code"); push((unsigned char)code[i+1]); i++; break;
            case '?': if (!pop()) i++; break;
            case '$': x = pop(); push(x); push(x); break;
            case '%': pop(); break;
            case '\\': x = pop(); y = pop(); push(x); push(y); break;
            case '@': x = pop(); y = pop(); z = pop(); push(y); push(x); push(z); break;
            case '>': x = pop(); y = pop(); push(y>x); break;
            case '=': x = pop(); y = pop(); push(y==x); break;
            case '&': x = pop(); y = pop(); push(y&&x); break;
            case '+': x = pop(); y = pop(); push(y+x); break;
            case '-': x = pop(); y = pop(); push(y-x); break;
            case '/': x = pop(); y = pop(); if (!x) err("Error div zero"); push(y/x); break;
            case '*': x = pop(); y = pop(); push(y*x); break;
            case '.': printf("%hu", pop()); break;
            case ',': printf("%c", pop()); break;
            default:
                if (words[(unsigned char)code[i]] != -1) {eval(words[(unsigned char)code[i]]);}
                else printf("Warn: unexpected word %c\n", code[i]);
                break;
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) {printf("Open arg with %s filename\n", argv[0]); return 1;}
    FILE *file = fopen(argv[1], "rb");
    if (!file) err("Error open file");
    int std_size = sizeof(std) - 1;
    for (int i = 0; i < std_size; i++) code[i] = std[i];
    size = std_size + fread(code + std_size, 1, CODE_SIZE - std_size, file);
    if (!feof(file)) err("Error code too large");
    fclose(file);
    
    init();
    compile();
    if (words['m'] == -1) err("Error main not found");
    eval(words['m']);
}