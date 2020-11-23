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






    void Inicio()//Função para mostrar se o usuario está utilizando de dia, de tarde ou de noite
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
	char* MostrarDir() //Função para mostrar diretório do projeto
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



	FILE* CriarArquivo(char *Func){//Função de criação de arquivo
		FILE *arq;
		char *caminho = strcat(Func, ".txt"); //concatenação da variável passada com o formato .txt
		arq = fopen(caminho, "a");            //abertura do arquivo

		if(arq)                               //caso o arquivo tenha sido aberto
		{
			printf("Aquivo %s criado", caminho);
		}
		else                                  //caso o arquivo não tenha sido aberto
			printf("%s já existe", caminho);


		fclose(arq);                          //fechando o arquivo
		return arq;

	}

//-----------------------------------------------------------------------------------

	void CriarDiretorio(char* Func) //função de criação de diretório
	{
		char *diretorio = Func;
		int x;
		x = _mkdir(diretorio);      //x recebe o valor retornado pela criação do diretório
		if(x==0)                    //verifica se o diretorio foi criado
		{
			printf("Diretório %s criado", diretorio);
		}
		else{                       //caso não tenha sido criado, ele já existe
			printf("%s já existe", diretorio);
		}

	}

//-----------------------------------------------------------------------------------

FILE* InserirAquivo(char *Func, char *texto, int N) //função de inserção de um texto em um arquivo
	{
		char *caminho = strcat(Func,".txt");        //caminho recebendo o arquivo .txt
		FILE* arq = fopen(caminho, "a");            //abertura do arquivo
		for(int i = 0; i<N; i++)
			fprintf(arq, "%c", texto[i]);           //inserção das letras da variavel texto no arquivo
		fprintf(arq, "\n");
		fprintf(stdout, "'%s' inserido em %s", texto, caminho ); //sendo mostrado o texto e o arquivo que ele foi inserido
		fclose(arq);                                //fechamento do arquivo
	}

//-----------------------------------------------------------------------------------

	void Listar(char* Func) //função para listar os elementos dentro de um diretório
	{
		DIR *dir;           //criação de uma variável do tipo DIR
    	struct dirent *lsdir;
    	dir = opendir(Func); //dir receberá a abertura do diretório

    	if(dir == 0)        //caso der 0, não foi possível abrir o diretorio
    		printf("Não foi possível abrir o diretório");
    	while ( ( lsdir = readdir(dir) ) != NULL ) //analisa toda a pasta enquanto não chega no final e printa o nome dos arquivos
    	{
        	printf ("%s\n", lsdir->d_name);
    	}


    	closedir(dir);       //fechamento do diretorio


	}

//-----------------------------------------------------------------------------------

	void ApagarDiretorio(char* Func)  //função para apagar o diretorio
	{
	    int x;
	    char *valor = Func;
		DIR *dir;
		char *arq;           //criação de uma variável do tipo DIR
    	struct dirent *lsdir;
    	dir = opendir(Func);

		x = _rmdir(valor);            //x recebe o valor dado pelo apagamento do diretorio
		if(x==0)                      // caso for 0, o diretório foi apagado
		{
			printf("%s apagado", Func);
		}
		else                           // caso não tenha sido apagado, o diretorio não existe
			if(dir != 0)
            {
                printf("Não é possivel apagar o diretório com os devidos arquivos dentro:");
               while ( ( lsdir = readdir(dir) ) != NULL ) //analisa toda a pasta enquanto não chega no final e printa o nome dos arquivos
                {
                    printf ("%s\n", lsdir->d_name);
                }

            }
            else
            {
                printf("%s não existe", Func);
            }
            closedir(dir);
		}


//-----------------------------------------------------------------------------------

	void ApagarArquivo(char* Func) //função para apagar um arquivo
	{
		char *arquivo= strcat(Func, ".txt");
		int x;
	    x = remove(arquivo);   //x recebe o valor dado pelo apagamento do arquivo
	    if(x == 0){            // caso for 0, o darquivo foi apagado
	        printf("%s apagado", Func);
		}
		else                            // caso não tenha sido apagado, o arquivo não existe
			printf("arquivo não existe");
	}

//-----------------------------------------------------------------------------------


	void Renomear(char *Old, char *New){  //Função para renomear um arquivo ou diretorio


		int aux;
		aux = rename(Old, New);  //aux recebe o valor da renomeação do elemento

		if(aux == 0) //caso aux = 0, o diretorio foi renomeado
		{
			printf("Diretório %s renomeado para %s com sucesso", Old, New);
		}
		else //senão, pode ter a possibilidade de ser um arquivo
		{
			strcat(Old, ".txt");  //os parametros são transformados em formato .txt
			strcat(New, ".txt");
			aux = rename(Old, New);   //aux recebe o valor da renomeação do elemento
			if(aux==0) //caso aux = 0, o arquivo foi renomeado
			{
				printf("Arquivo %s renomeado para %s com sucesso", Old, New);
			}
			else //se der diferente de 0, não foi renomeado nenhum elemento
			{
				printf("Erro ao renomear");
			}

		}



	}
//-----------------------------------------------------------------------------------
	void Mover(char *arquivo, char *local, char *local2 ) //função para mover um diretorio ou arquivo
	{
		int aux;
		char *arq = arquivo;
		char *loc = local;
		strcat(loc, "\\"); //ocorre a concatenização do segundo parametro para ser transformado em um local de envio
		strcat(loc, arq);  //concatena o local com o diretorio
		aux = rename (arq, loc); //muda o nome do arquivo para o local que ele será enviado
		if(aux == 0)  //caso aux = 0, o diretorio foi movido
		{
			printf("%s foi movido para %s", arquivo, local);
		}
		else //senão, pode ser um arquivo que está sendo movido
		{
			strcat(arq, ".txt"); //transforma o primeiro parametro em um arquivo formato .txt
			char *loc = local2;  //loc recebe local2, que é o mesmo que local antes de todas as concatenizaçoes
			strcat(loc, "\\");
			strcat(loc, arq);
			aux = rename (arq, loc);
			if(aux == 0)    //caso aux = 0, o arquivo foi movido
			{
				printf("%s foi movido para %s", arquivo, local);
			}
			else //senão deu erro na tentativa de mover
			{
				printf("Erro a mover");
			}
		}
	}
//-----------------------------------------------------------------------------------

	void Deletar(char *Func) //Função para deletar um arquivo ou diretorio
	{
		int aux;
		aux = RemoveDirectory(Func); //aux recebe o valor do deletamento do diretorio
		if(aux==1) //caso aux = 1 o diretorio foi deletado
			printf("%s deletado", Func);
		else //senão, pode ser um arquivo que está sendo deletado
		{
			strcat(Func, ".txt");
			aux =  unlink(Func);  //aux recebe o valor do deletamento do arquivo
			if(aux==0)            //caso aux = 0 o arquivo foi deletado
				printf("%s deletado", Func);
			else //senão, ocorreu erro ao deletar
				printf("Erro ao deletar");
		}
	}





//-----------------------------------------------------------------------------------

	void Ajuda() //função ajuda responsável por mostrar todas as funcionalidades que o sistema possui
    {



		printf("\nMenu de funções:\n"
	"-----------------------------------------------------------------------------\n"
		" Comandos   |     Descrição da Atividade     |     Exemplo de Execução"
	"\n-----------------------------------------------------------------------------\n"
		"                                                     CRIAR -d pasta_1\n"
		" CRIAR        Cria um arquivo ou diretório           CRIAR -d pasta_3\n"
		"                                                     CRIAR -a arquivo_1"
	"\n-----------------------------------------------------------------------------\n"
		" INSERIR      Insere um texto em um arquivo.         INSERIR “Texto1...” arquivo_1"
	"\n-----------------------------------------------------------------------------\n"
		" LISTAR       Lista arquivos e diretórios da pasta.  LISTAR pasta_1"
	"\n-----------------------------------------------------------------------------\n"
		" APAGAR      Apaga um arquivo ou diretório           APAGAR -d pasta_1 "
	"\n-----------------------------------------------------------------------------\n"
		" RENOMEAR    Renomeia um arquivo ou diretório        RENOMEAR pasta_1 pasta_2 "
    "\n-----------------------------------------------------------------------------\n"
		" MOVER       Move um arquivo ou diretório.           MOVER pasta_2 pasta_3 "
	"\n-----------------------------------------------------------------------------\n"
		" DELETAR     Deleta um arquivo ou diretório.         DELETAR pasta_3       "
	"\n-----------------------------------------------------------------------------\n"
		" AJUDA       Lista todos os comandos desta tabela    AJUDA                  \n"
		"             juntamente com descrições.                                      "
	"\n-----------------------------------------------------------------------------\n"
		" VER         Imprime a versão do sistema operacional VER                     "
	"\n-----------------------------------------------------------------------------\n"
		" DATA        Imprime a data do sistema operacional   DATA                    "
	"\n-----------------------------------------------------------------------------\n"
		" HORA        Imprime a hora do sistema operacional   HORA                    "
	"\n-----------------------------------------------------------------------------\n"
		" LIMPAR      Limpa o conteúdo atual da tela.         LIMPAR                  "
	"\n-----------------------------------------------------------------------------\n"
		" SAIR        Finaliza o programa                     SAIR"
	"\n-----------------------------------------------------------------------------\n");
	}

//-----------------------------------------------------------------------------------

	void Ver() //Função para ver que sistema operacional está utilizando
	{


        #if defined(_WIN32) || defined(_WIN64)//caso for windows 32bits ou 64bits
            const char* os = "Sistema Windows";
        #else
        #ifdef __linux //caso for linux
            const char* os = "Sistema Linux";
        #else  //caso não for conhecido
            const char* os = "Desconhecido";
        #endif
        #endif

        printf("%s", os);
	}

//-----------------------------------------------------------------------------------

	void Data() //função para mostrar a data
	{
		time_t s, val = 1;
    	struct tm* current_time;


    	s = time(NULL);
    	current_time = localtime(&s);

    		printf("A data do sistema é: \n%02d/%02d/%04d", current_time->tm_mday, current_time->tm_mon+1, current_time->tm_year+1900);
	}

//-----------------------------------------------------------------------------------

	void Hora() //função para mostrar as horas
	{
		time_t s, val = 1;
    	struct tm* current_time;


    	s = time(NULL);
    	current_time = localtime(&s);
		printf("A hora do sistema é: \n%02d:%02d:%02d", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
	}

//-----------------------------------------------------------------------------------

	void Limpar(){ //função para limpar a tela
		system("@cls||clear");
	}

//-----------------------------------------------------------------------------------

	void Sair() //função para fechar o programa
	{
		exit(1);
	}

//-----------------------------------------------------------------------------------

