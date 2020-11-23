#ifndef PROJFIN_H_INCLUDED
#define PROJFIN_H_INCLUDED
#include <stdio.h>
char* MostrarDir();
void Inicio();
FILE* CriarArquivo(char *Func);
void CriarDiretorio(char* Func);
FILE* InserirAquivo(char *Func, char *texto, int N);
void Listar(char* Func);
void ApagarDiretorio(char* Func);
void ApagarArquivo(char* Func);
void Renomear(char *Old, char *New);
void Mover(char *Arquivo, char* local, char *local2);
void Deletar();
void Ajuda();
void Ver();
void Data();
void Hora();
void Limpar();
void Sair();

#endif // PROJFIN_H_INCLUDED
