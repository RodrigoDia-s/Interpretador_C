
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

			//Definição do conjuntos de sinais da língua-portuguesa.
		 	setlocale(LC_ALL, "Portuguese");
		 	system("COLOR 8f");


			char Func[MAX]; //criação da variavel que será responsável pela leitura dos comandos
			size_t len;    //variável para medir tamho de string

			char *dir = MostrarDir();  //Mostrando o diretório onde está o projeto
            Inicio();
			while(1){  //enquanto o usuário não pedir para fechar o programa, ele será execultado repetidas vezes


			printf("\n----------Interpretador de Comandos----------\n");
			printf(">>> ");

			//Recebimento do comando:
			fflush(stdin);
			fgets(Func, MAX, stdin);
			len = strlen(Func);
			if (Func[ len - 1] == '\n')
				Func[--len] = 0;

			if(strncmp(Func, "CRIAR", 5) == 0){ //caso for digitado a função criar
				strncpy(Func, &Func[6], len);

				//analise se é requesitado a criação de um arquivo
				if(strncmp(Func, "-a", 2) == 0){
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}

					CriarArquivo(Func); //chamando a função para criar um arquivo
				}
				else if(strncmp(Func, "-d", 2) == 0) //analise se é requesitado a criação de um diretorio
				{
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}
					CriarDiretorio(Func);  //chamando a função para criar um diretorio
				}
				else //caso for nenhum dos dois, é um comando inválido
				{
					printf("Comando não reconhecido");
				}
			}
			else if(strncmp(Func,"INSERIR", 7) == 0) //caso for digitado a função criar
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

				while(Inserir[i]!='"'){ //verifica até onde vai o texto
					i++;
					Cont++;
				}




				strncpy(copia, &Inserir[0], Cont); //copia o texto
				copia[Cont] = 0;

				len = strlen(Inserir);


				strncpy(arq, &Inserir[Cont+2], len-Cont+1); //copia o local onde será adicionado o texto

				len = strlen(arq);
				arq[len] = 0;

				InserirAquivo(arq, copia, Cont);    //chamando a função para inserir um texto

			}
			else if(strncmp(Func, "LISTAR", 6) == 0) //caso for digitado a função listar
			{
				if(Func[6] == ' '){ //caso tenha um diretorio especifico a ser listado
					strncpy(Func, &Func[7], len);
					Listar(Func);
				}
				else
					Listar("c:"); //caso não tenha, será listado a pesta do projeto
			}
			else if(strncmp(Func, "APAGAR", 6) == 0) //caso for digitado a função apagar
			{
				strncpy(Func, &Func[7], len);

				//verifica ser um diretório será apagado
				if(strncmp(Func, "-d", 2) == 0){
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}

					ApagarDiretorio(Func); //chamando a função para apagar diretório
				}
				else if(strncmp(Func, "-a", 2) == 0) //caso seja um arquivo que será apagado
				{
					for(int i = 0; i<len-2; i++)
					{
						Func[i] = Func[i+3];
					}
					ApagarArquivo(Func); //chama a função para apagar arquivo
				}
				else
				{
					printf("comando não reconhecido");
				}
			}
			else if(strncmp(Func, "RENOMEAR", 8) == 0) //caso for digitado a função renomear
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

				Renomear(Old, New); //chamando a função de renomear

			}
			else if(strncmp(Func, "MOVER", 5) == 0)   //caso for digitado a função mover
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
			else if(strncmp(Func, "DELETAR", 7) == 0) //caso for digitado a função deletar
			{
				strncpy(Func, &Func[8], len);
				Deletar(Func);
			}
			else if(strncmp(Func, "DATA", 4) == 0)  //caso for digitado a função data
				Data();
			else if(strncmp(Func, "HORA", 4) == 0) //caso for digitado a função hora
				Hora();
			else if(strncmp(Func, "AJUDA", 5) == 0) //caso for digitado a função ajuda
				Ajuda();
			else if(strncmp(Func, "LIMPAR", 6) == 0) //caso for digitado a função limpar
				Limpar();
			else if(strncmp(Func, "SAIR", 4) == 0)   //caso for digitado a função sair
				Sair();
			else if(strncmp(Func, "VER", 3) == 0)   //caso for digitado a função ver
				Ver();
			else                                    //caso for digitado nenhuma das funções acima
				printf("Comando não reconhecido");



			}
			return 0;
			}
