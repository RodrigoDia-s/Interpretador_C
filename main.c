
	#include <stdlib.h>
	#include <math.h>
	#include <dos.h>
	#include <conio.h>
	#include <locale.h>
	#include <string.h>
	#include <dirent.h>
	#include <time.h>
	#include <direct.h>
	#include "ProjFin.h"
	#define MAX 1000


	int main(){

			//Defini��o do conjuntos de sinais da l�ngua-portuguesa.
		 	setlocale(LC_ALL, "Portuguese");
		 	system("COLOR 8f");


			char Func[MAX]; //cria��o da variavel que ser� respons�vel pela leitura dos comandos
			size_t len;    //vari�vel para medir tamho de string

			char *dir = MostrarDir();  //Mostrando o diret�rio onde est� o projeto
            Inicio();
			while(1){  //enquanto o usu�rio n�o pedir para fechar o programa, ele ser� execultado repetidas vezes


			printf("\n----------Interpretador de Comandos----------\n");
			printf(">>> ");

			//Recebimento do comando:
			fflush(stdin);
			fgets(Func, MAX, stdin);
			len = strlen(Func);
			if (Func[ len - 1] == '\n')
				Func[--len] = 0;

			if(strncmp(Func, "CRIAR", 5) == 0){ //caso for digitado a fun��o criar
				strncpy(Func, &Func[6], len);

				//analise se � requesitado a cria��o de um arquivo
				if(strncmp(Func, "-a", 2) == 0){
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}

					CriarArquivo(Func); //chamando a fun��o para criar um arquivo
				}
				else if(strncmp(Func, "-d", 2) == 0) //analise se � requesitado a cria��o de um diretorio
				{
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}
					CriarDiretorio(Func);  //chamando a fun��o para criar um diretorio
				}
				else //caso for nenhum dos dois, � um comando inv�lido
				{
					printf("Comando n�o reconhecido");
				}
			}
			else if(strncmp(Func,"INSERIR", 7) == 0) //caso for digitado a fun��o criar
			{
				int Cont = 0, i = 0;
				char copia[MAX];
				char arq[MAX];
				copia[0] = '\0';
				arq[0] = '\0';

				strncpy(Func, &Func[9], len);

				len = strlen(Func);
				char Inserir[len];

				strcpy(Inserir, Func); //copia de Func em Inserir

				Func[0] = '\0';

				while(Inserir[i]!='"'){ //verifica at� onde vai o texto
					i++;
					Cont++;
				}




				strncpy(copia, &Inserir[0], Cont); //copia o texto
				copia[Cont] = 0;

				len = strlen(Inserir);


				strncpy(arq, &Inserir[Cont+2], len-Cont+1); //copia o local onde ser� adicionado o texto

				len = strlen(arq);
				arq[len] = 0;

				InserirAquivo(arq, copia, Cont);    //chamando a fun��o para inserir um texto

			}
			else if(strncmp(Func, "LISTAR", 6) == 0) //caso for digitado a fun��o listar
			{
				if(Func[6] == ' '){ //caso tenha um diretorio especifico a ser listado
					strncpy(Func, &Func[7], len);
					Listar(Func);
				}
				else
					Listar("c:"); //caso n�o tenha, ser� listado a pesta do projeto
			}
			else if(strncmp(Func, "APAGAR", 6) == 0) //caso for digitado a fun��o apagar
			{
				strncpy(Func, &Func[7], len);

				//verifica ser um diret�rio ser� apagado
				if(strncmp(Func, "-d", 2) == 0){
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}

					ApagarDiretorio(Func); //chamando a fun��o para apagar diret�rio
				}
				else if(strncmp(Func, "-a", 2) == 0) //caso seja um arquivo que ser� apagado
				{
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}
					ApagarArquivo(Func); //chama a fun��o para apagar arquivo
				}
				else
				{
					printf("comando n�o reconhecido");
				}
			}
			else if(strncmp(Func, "RENOMEAR", 8) == 0) //caso for digitado a fun��o renomear
			{
				strncpy(Func, &Func[9], len);
				char Old[MAX], New[MAX];
				Old[0] = '\0';
				New[0] = '\0';
				int  i = 0, cont = 0;
				len = strlen(Func);
				char Renome[len];
				strcpy(Renome, Func);
				Func[0] = '\0';

				while(Renome[i]!= ' ')
				{
					cont++;
					i++;
				}

				strncpy(Old, &Renome[0], cont); //nome antigo
				strncpy(New, &Renome[i+1], len); //nome novo

				Old[cont] = 0;
				New[len] = 0;

				Renomear(Old, New); //chamando a fun��o de renomear

			}
			else if(strncmp(Func, "MOVER", 5) == 0)   //caso for digitado a fun��o mover
			{

				strncpy(Func, &Func[6], len);
				char Old[MAX], New[MAX], New2[MAX];
				Old[0] = '\0';
				New[0] = '\0';
				int  i = 0, cont = 0;
				len = strlen(Func);
				char Move[len];
				strcpy(Move, Func);
				Func[0] = '\0';

				while(Move[i]!= ' ')
				{
					cont++;
					i++;
				}

				strncpy(Old, &Move[0], cont); //nome do arquivo
				strncpy(New, &Move[i+1], len); //local a ser movido

				Old[cont] = 0;
				New[len] = 0;
				strcpy(New2, New);
				Mover(Old, New, New2);

			}
			else if(strncmp(Func, "DELETAR", 7) == 0) //caso for digitado a fun��o deletar
			{
				strncpy(Func, &Func[8], len);
				Deletar(Func);
			}
			else if(strncmp(Func, "DATA", 4) == 0)  //caso for digitado a fun��o data
				Data();
			else if(strncmp(Func, "HORA", 4) == 0) //caso for digitado a fun��o hora
				Hora();
			else if(strncmp(Func, "AJUDA", 5) == 0) //caso for digitado a fun��o ajuda
				Ajuda();
			else if(strncmp(Func, "LIMPAR", 6) == 0) //caso for digitado a fun��o limpar
				Limpar();
			else if(strncmp(Func, "SAIR", 4) == 0)   //caso for digitado a fun��o sair
				Sair();
			else if(strncmp(Func, "VER", 3) == 0)   //caso for digitado a fun��o ver
				Ver();
			else                                    //caso for digitado nenhuma das fun��es acima
				printf("Comando n�o reconhecido");



			}
			return 0;
			}
