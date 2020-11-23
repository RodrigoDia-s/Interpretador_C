	#include<stdio.h>
	#include <stdlib.h>
	#include<math.h>
	#include<dos.h>
	#include <conio.h>
	#include <locale.h>
	#include <string.h>
	#include <dirent.h>
	#include <unistd.h>
	#include <time.h>
	#include <direct.h>
	#include <windows.h>
	#define MAX 1000






    void Inicio()//Fun��o para mostrar se o usuario est� utilizando de dia, de tarde ou de noite
    {
        time_t s, val = 1;
    	struct tm* current_time;


    	s = time(NULL);
    	current_time = localtime(&s);

    	if(current_time->tm_hour >= 0 && current_time->tm_hour < 12)
		{
		    printf("\n ---------------------------------------------");
			printf("\n|                  bom dia                  |\n");
			printf(" ---------------------------------------------n");
		}
		else if(current_time->tm_hour >= 12 && current_time->tm_hour < 18){
            printf("\n ---------------------------------------------");
			printf("\n|                  boa tarde                  |\n");
            printf(" ---------------------------------------------\n");
		}
		else if(current_time->tm_hour >= 18){
            printf("\n ---------------------------------------------");
			printf("\n|                  boa noite                  |\n");
            printf(" ---------------------------------------------\n");
		}

    }


//-----------------------------------------------------------------------------------
	char* MostrarDir() //Fun��o para mostrar diret�rio do projeto
	{
		char diretorio[MAX], *aux;
		aux = _getcwd(diretorio, MAX);
		if(aux == NULL)
			return 0;
		else
			printf("%s", aux);

		free(aux);
	}
//-----------------------------------------------------------------------------------



	FILE* CriarArquivo(char *Func){//Fun��o de cria��o de arquivo
		FILE *arq;
		char *caminho = strcat(Func, ".txt"); //concatena��o da vari�vel passada com o formato .txt
		arq = fopen(caminho, "a");            //abertura do arquivo

		if(arq)                               //caso o arquivo tenha sido aberto
		{
			printf("Aquivo %s criado", caminho);
		}
		else                                  //caso o arquivo n�o tenha sido aberto
			printf("%s j� existe", caminho);


		fclose(arq);                          //fechando o arquivo
		return arq;

	}

//-----------------------------------------------------------------------------------

	void CriarDiretorio(char* Func) //fun��o de cria��o de diret�rio
	{
		char *diretorio = Func;
		int x;
		x = _mkdir(diretorio);      //x recebe o valor retornado pela cria��o do diret�rio
		if(x==0)                    //verifica se o diretorio foi criado
		{
			printf("Diret�rio %s criado", diretorio);
		}
		else{                       //caso n�o tenha sido criado, ele j� existe
			printf("%s j� existe", diretorio);
		}

	}

//-----------------------------------------------------------------------------------

FILE* InserirAquivo(char *Func, char *texto, int N) //fun��o de inser��o de um texto em um arquivo
	{
		char *caminho = strcat(Func,".txt");        //caminho recebendo o arquivo .txt
		FILE* arq = fopen(caminho, "a");            //abertura do arquivo
		for(int i = 0; i<N; i++)
			fprintf(arq, "%c", texto[i]);           //inser��o das letras da variavel texto no arquivo
		fprintf(arq, "\n");
		fprintf(stdout, "'%s' inserido em %s", texto, caminho ); //sendo mostrado o texto e o arquivo que ele foi inserido
		fclose(arq);                                //fechamento do arquivo
	}

//-----------------------------------------------------------------------------------

	void Listar(char* Func) //fun��o para listar os elementos dentro de um diret�rio
	{
		DIR *dir;           //cria��o de uma vari�vel do tipo DIR
    	struct dirent *lsdir;
    	dir = opendir(Func); //dir receber� a abertura do diret�rio

    	if(dir == 0)        //caso der 0, n�o foi poss�vel abrir o diretorio
    		printf("N�o foi poss�vel abrir o diret�rio");
    	while ( ( lsdir = readdir(dir) ) != NULL ) //analisa toda a pasta enquanto n�o chega no final e printa o nome dos arquivos
    	{
        	printf ("%s\n", lsdir->d_name);
    	}


    	closedir(dir);       //fechamento do diretorio


	}

//-----------------------------------------------------------------------------------

	void ApagarDiretorio(char* Func)  //fun��o para apagar o diretorio
	{
	    int x;
	    char *valor = Func;
		DIR *dir;
		char *arq;           //cria��o de uma vari�vel do tipo DIR
    	struct dirent *lsdir;
    	dir = opendir(Func);

		x = _rmdir(valor);            //x recebe o valor dado pelo apagamento do diretorio
		if(x==0)                      // caso for 0, o diret�rio foi apagado
		{
			printf("%s apagado", Func);
		}
		else                           // caso n�o tenha sido apagado, o diretorio n�o existe
			if(dir != 0)
            {
                printf("N�o � possivel apagar o diret�rio com os devidos arquivos dentro:");
               while ( ( lsdir = readdir(dir) ) != NULL ) //analisa toda a pasta enquanto n�o chega no final e printa o nome dos arquivos
                {
                    printf ("%s\n", lsdir->d_name);
                }

            }
            else
            {
                printf("%s n�o existe", Func);
            }
            closedir(dir);
		}


//-----------------------------------------------------------------------------------

	void ApagarArquivo(char* Func) //fun��o para apagar um arquivo
	{
		char *arquivo= strcat(Func, ".txt");
		int x;
	    x = remove(arquivo);   //x recebe o valor dado pelo apagamento do arquivo
	    if(x == 0){            // caso for 0, o darquivo foi apagado
	        printf("%s apagado", Func);
		}
		else                            // caso n�o tenha sido apagado, o arquivo n�o existe
			printf("arquivo n�o existe");
	}

//-----------------------------------------------------------------------------------


	void Renomear(char *Old, char *New){  //Fun��o para renomear um arquivo ou diretorio


		int aux;
		aux = rename(Old, New);  //aux recebe o valor da renomea��o do elemento

		if(aux == 0) //caso aux = 0, o diretorio foi renomeado
		{
			printf("Diret�rio %s renomeado para %s com sucesso", Old, New);
		}
		else //sen�o, pode ter a possibilidade de ser um arquivo
		{
			strcat(Old, ".txt");  //os parametros s�o transformados em formato .txt
			strcat(New, ".txt");
			aux = rename(Old, New);   //aux recebe o valor da renomea��o do elemento
			if(aux==0) //caso aux = 0, o arquivo foi renomeado
			{
				printf("Arquivo %s renomeado para %s com sucesso", Old, New);
			}
			else //se der diferente de 0, n�o foi renomeado nenhum elemento
			{
				printf("Erro ao renomear");
			}

		}



	}
//-----------------------------------------------------------------------------------
	void Mover(char *arquivo, char *local, char *local2 ) //fun��o para mover um diretorio ou arquivo
	{
		int aux;
		char *arq = arquivo;
		char *loc = local;
		strcat(loc, "\\"); //ocorre a concateniza��o do segundo parametro para ser transformado em um local de envio
		strcat(loc, arq);  //concatena o local com o diretorio
		aux = rename (arq, loc); //muda o nome do arquivo para o local que ele ser� enviado
		if(aux == 0)  //caso aux = 0, o diretorio foi movido
		{
			printf("%s foi movido para %s", arquivo, local);
		}
		else //sen�o, pode ser um arquivo que est� sendo movido
		{
			strcat(arq, ".txt"); //transforma o primeiro parametro em um arquivo formato .txt
			char *loc = local2;  //loc recebe local2, que � o mesmo que local antes de todas as concateniza�oes
			strcat(loc, "\\");
			strcat(loc, arq);
			aux = rename (arq, loc);
			if(aux == 0)    //caso aux = 0, o arquivo foi movido
			{
				printf("%s foi movido para %s", arquivo, local);
			}
			else //sen�o deu erro na tentativa de mover
			{
				printf("Erro a mover");
			}
		}
	}
//-----------------------------------------------------------------------------------

	void Deletar(char *Func) //Fun��o para deletar um arquivo ou diretorio
	{
		int aux;
		aux = RemoveDirectory(Func); //aux recebe o valor do deletamento do diretorio
		if(aux==1) //caso aux = 1 o diretorio foi deletado
			printf("%s deletado", Func);
		else //sen�o, pode ser um arquivo que est� sendo deletado
		{
			strcat(Func, ".txt");
			aux =  unlink(Func);  //aux recebe o valor do deletamento do arquivo
			if(aux==0)            //caso aux = 0 o arquivo foi deletado
				printf("%s deletado", Func);
			else //sen�o, ocorreu erro ao deletar
				printf("Erro ao deletar");
		}
	}





//-----------------------------------------------------------------------------------

	void Ajuda() //fun��o ajuda respons�vel por mostrar todas as funcionalidades que o sistema possui
    {



		printf("\nMenu de fun��es:\n"
	"-----------------------------------------------------------------------------\n"
		" Comandos   |     Descri��o da Atividade     |     Exemplo de Execu��o"
	"\n-----------------------------------------------------------------------------\n"
		"                                                     CRIAR -d pasta_1\n"
		" CRIAR        Cria um arquivo ou diret�rio           CRIAR -d pasta_3\n"
		"                                                     CRIAR -a arquivo_1"
	"\n-----------------------------------------------------------------------------\n"
		" INSERIR      Insere um texto em um arquivo.         INSERIR �Texto1...� arquivo_1"
	"\n-----------------------------------------------------------------------------\n"
		" LISTAR       Lista arquivos e diret�rios da pasta.  LISTAR pasta_1"
	"\n-----------------------------------------------------------------------------\n"
		" APAGAR      Apaga um arquivo ou diret�rio           APAGAR -d pasta_1 "
	"\n-----------------------------------------------------------------------------\n"
		" RENOMEAR    Renomeia um arquivo ou diret�rio        RENOMEAR pasta_1 pasta_2 "
    "\n-----------------------------------------------------------------------------\n"
		" MOVER       Move um arquivo ou diret�rio.           MOVER pasta_2 pasta_3 "
	"\n-----------------------------------------------------------------------------\n"
		" DELETAR     Deleta um arquivo ou diret�rio.         DELETAR pasta_3       "
	"\n-----------------------------------------------------------------------------\n"
		" AJUDA       Lista todos os comandos desta tabela    AJUDA                  \n"
		"             juntamente com descri��es.                                      "
	"\n-----------------------------------------------------------------------------\n"
		" VER         Imprime a vers�o do sistema operacional VER                     "
	"\n-----------------------------------------------------------------------------\n"
		" DATA        Imprime a data do sistema operacional   DATA                    "
	"\n-----------------------------------------------------------------------------\n"
		" HORA        Imprime a hora do sistema operacional   HORA                    "
	"\n-----------------------------------------------------------------------------\n"
		" LIMPAR      Limpa o conte�do atual da tela.         LIMPAR                  "
	"\n-----------------------------------------------------------------------------\n"
		" SAIR        Finaliza o programa                     SAIR"
	"\n-----------------------------------------------------------------------------\n");
	}

//-----------------------------------------------------------------------------------

	void Ver() //Fun��o para ver que sistema operacional est� utilizando
	{


        #if defined(_WIN32) || defined(_WIN64)//caso for windows 32bits ou 64bits
            const char* os = "Sistema Windows";
        #else
        #ifdef __linux //caso for linux
            const char* os = "Sistema Linux";
        #else  //caso n�o for conhecido
            const char* os = "Desconhecido";
        #endif
        #endif

        printf("%s", os);
	}

//-----------------------------------------------------------------------------------

	void Data() //fun��o para mostrar a data
	{
		time_t s, val = 1;
    	struct tm* current_time;


    	s = time(NULL);
    	current_time = localtime(&s);

    		printf("A data do sistema �: \n%02d/%02d/%04d", current_time->tm_mday, current_time->tm_mon+1, current_time->tm_year+1900);
	}

//-----------------------------------------------------------------------------------

	void Hora() //fun��o para mostrar as horas
	{
		time_t s, val = 1;
    	struct tm* current_time;


    	s = time(NULL);
    	current_time = localtime(&s);
		printf("A hora do sistema �: \n%02d:%02d:%02d", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
	}

//-----------------------------------------------------------------------------------

	void Limpar(){ //fun��o para limpar a tela
		system("@cls||clear");
	}

//-----------------------------------------------------------------------------------

	void Sair() //fun��o para fechar o programa
	{
		exit(1);
	}

//-----------------------------------------------------------------------------------

