/**_________________________________________________________________________________________________________
 *                                                                                                          *
 *                                 -Código Planilha de Matrículas-                                          * 
 *                                       Autor: Joaquim Breno                                               *
 *                                      Matricula: 20200009907                                              * 
 * _________________________________________________________________________________________________________**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// CONSTANTES SIMBOLICAS
/** Tive que desenvolver uma gambiarrazinha para poder usar o comando System("cls") 
 * tanto no windows quanto no linux, 
 * assim a mensagem de BoasVindas pôde ser apagada do console. */
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif
/** Aqui é definido a qtd de caracteres para o array de caracteres que vai dar o nome da disciplina */
# define DISCIPLINA 52
/** Aqui é definido a qtd de caracteres para o array de caracteres que vai dar os nomes dos alunos */
# define NOMES 32
/** Aqui sao definidos os pesos */
# define peso1 6 
# define peso2 4
//

//FUNCOES
unsigned sleep();/** função para tornar a funcao sleep portavel */
void BoasVindas(); 
char * DeletaOsN(); /** Deleta o "\n" da string*/
double MediaFinal();
//

typedef struct {
    char nomesDosAlunos[NOMES]; /** array de strings com os nomes */ 
    char *situacao;/** string que guarda a situacao do aluno */
    char tracinho;/** variavel para o '-' do valor da recuperacao */
    int matriculas; /** array de inteiros com as matriculas */
    double notas[3], recupera; /** array de double com as notas e com a recuperacao*/
    double medias;/** guarda as medias iniciais e finais quando necessarias */

}tAlunos;

int main(void){
    char nomeDaDisciplina[DISCIPLINA];
    int qtdAlunos, i;
    

    // MOMENTO BOAS VINDAS
    CLEAR_SCREEN;/** Limpa a tela */
    BoasVindas();/** Chama a função que emite a mensagem de boas vindas */
    //

    // ENTRADA DO NOME DA DISCIPLINA E DA QUANTIDADE DE ALUNOS
    puts("----------------------------------------------------");
    puts("Digite o nome da disciplina(máximo de 50 caracteres): ");
    fgets(nomeDaDisciplina, DISCIPLINA, stdin);
    DeletaOsN(nomeDaDisciplina);

    puts("------------------------------------------------------");   
    puts("Digite o numero de alunos(máximo de 30 caracteres): ");
    scanf("%d%*c", &qtdAlunos);
        if(qtdAlunos>30){
            qtdAlunos=30; /** A condição limita a quantidade de alunos, impedindo entradas incovenientes */
        }
    CLEAR_SCREEN;
    // 

    // ENTRADA DOS DADOS E DAS NOTAS DOS ALUNOS
    tAlunos dadosAlunos[qtdAlunos];/** Define uma estrutura de dados com tipo tAlunos que congrega os dados dos alunos */
    

        for (i = 0; i < qtdAlunos; i++){ /** para cada aluno (i) será lido os dados do aluno*/
            
            printf("Digite o numero de matricula do %dº aluno(maximo 4 numeros): ", i+1);
            scanf("%d%*c", &dadosAlunos[i].matriculas); /** Lê o numero de matricula */

            printf("\nDigite o nome do %dº aluno(maximo de 30 caracteres): ", i+1);
            fgets(dadosAlunos[i].nomesDosAlunos, NOMES, stdin); /** Lê o nome */
            DeletaOsN(dadosAlunos[i].nomesDosAlunos);/* Deleta o \n */

            printf("\nDigite a primeira nota da(o) %s: ", dadosAlunos[i].nomesDosAlunos);
            scanf("%lf%*c", &dadosAlunos[i].notas[0]); /** Lê a primeira nota do aluno corrente */

            printf("Digite a segunda nota da(o) %s: ", dadosAlunos[i].nomesDosAlunos);
            scanf("%lf%*c", &dadosAlunos[i].notas[1]); /** Lê a segunda nota do aluno corrente */

            printf("Digite a terceira nota da(o) %s: ", dadosAlunos[i].nomesDosAlunos);
            scanf("%lf%*c", &dadosAlunos[i].notas[2]); /** Lê a terceira nota do aluno corrente */
            
            dadosAlunos[i].medias=(dadosAlunos[i].notas[0]+dadosAlunos[i].notas[1]+dadosAlunos[i].notas[2])/3; /** calcula a media aritmetica das notas do aluno corrente e armazena no array media*/


                dadosAlunos[i].tracinho='-';/** o tracinho e definido inicialmente como '-' */

                if(dadosAlunos[i].medias>=7){/** verifica se a media foi acima de 4 ou acima de 7, indicando a siuacao do aluno.*/
                    dadosAlunos[i].situacao = "Aprovada(o)";
                }
                else if(dadosAlunos[i].medias<4){
                    dadosAlunos[i].situacao = "Reprovada(o)";/** se a nota da media inicial for menor que 4, aluno reprovado */
                }
                else{/** se a media for apenas acima de 4 e igual a 4, e adicionada uma nota de recuperacao que é ponderada com a nota da media */
                    printf("\nA media inicial foi %.2lf, insuficiente para ser aprovada(o) ", dadosAlunos[i].medias);
                    printf("\nDigite a nota de recuperacao da(o) %s: ", dadosAlunos[i].nomesDosAlunos);
                    scanf("%lf%*c", &dadosAlunos[i].recupera); /** Lê a nota de recuperacao do aluno corrente */    

                    dadosAlunos[i].medias = MediaFinal(&dadosAlunos[i]); /** calcula a nova media final efetuando a media ponderada com peso 6 para a media anterior e peso 4 para a nota de recuperacao */
                    if(dadosAlunos[i].medias>=5){
                        dadosAlunos[i].situacao = "Aprovada(o)";/** se a nova media final for maior igual a 5 o aluno esta aprovado */
                    }
                    else{
                        dadosAlunos[i].situacao = "Reprovada(o)";/** senao, nao esta */
                    }
                    dadosAlunos[i].tracinho=' ';/** quando ha nota de recuperacao, o '-' torna-se ' ' */
                }


            CLEAR_SCREEN;
        }
    //

    // SAIDA DOS DADOS E DAS NOTAS DOS ALUNOS

        
        // n o m e  da disciplina
        printf("Nome da disciplina: %s\n", nomeDaDisciplina);/** Cabeçalho */
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");
        printf("|             |                                |            |           |           |           |            |              |\n");
        printf("|  MATRICULA  |  Nome:                         |   Nota 1:  |  Nota 2:  |  Nota 3:  |  Rec:     |   Media:   |   Situacao:  |\n");
        printf("|             |                                |            |           |           |           |            |              |\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");
        // d a d o s dos alunos
            for( i = 0; i < qtdAlunos; i++){
 
                /** O printf abaixo recebe a matricula, nome, notas. media, recuperacao e situacao do aluno... No nome e nas notas adicionei um limite de espaçamento "%-30" ou "%-5" */
                if(dadosAlunos[i].tracinho==' '){ /** aqui ele verifica se não há tracinho e imrpime o valor da recuperacao tambem */
                printf("   %04d\t\t %-30s\t   %-5.2lf       %-5.2lf\t   %-5.2lf       %-5.2lf\t    %-5.2lf\t %s  \n", dadosAlunos[i].matriculas, dadosAlunos[i].nomesDosAlunos, dadosAlunos[i].notas[0], dadosAlunos[i].notas[1], dadosAlunos[i].notas[2], dadosAlunos[i].recupera, dadosAlunos[i].medias, dadosAlunos[i].situacao);    
                }
                else{
                    printf("   %04d\t\t %-30s\t   %-5.2lf       %-5.2lf\t   %-5.2lf       %-5c\t    %-5.2lf\t %s  \n", dadosAlunos[i].matriculas, dadosAlunos[i].nomesDosAlunos, dadosAlunos[i].notas[0], dadosAlunos[i].notas[1], dadosAlunos[i].notas[2], dadosAlunos[i].tracinho, dadosAlunos[i].medias, dadosAlunos[i].situacao);
                }       
            }
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");
        printf("|             |                                |            |           |           |           |            |              |\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");                      

    //


    return 0;
}

unsigned sleep(unsigned x){
    time_t t0=time(0); 
    while (difftime(time(0),t0)<x); 
    return 0;
}
void BoasVindas(){
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf(" Seja Bem Vinda(o) à planilha de notas, calcularei as notas para você.\n \tAdicione os dados e deixe o resto comigo ;D. \n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");   
    sleep(4);
    CLEAR_SCREEN; /** Limpa a tela */
    return;
}
char * DeletaOsN(char str[]){
    if(str[strlen(str)-1]=='\n'){ /** Procura o "\n" na penultima posição de toda a array */
        str[strlen(str)-1]='\0'; /** troca por "\0" */
    }
}
double MediaFinal(const tAlunos *dadosAlunos){
    return ((peso1*dadosAlunos->medias)+(peso2*dadosAlunos->recupera))/(peso1+peso2);
}
