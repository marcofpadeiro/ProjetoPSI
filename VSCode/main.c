/* 
    Autores: Marco Padeiro (2211868), Tomas Moura (2211866)          | GRUPO 7-PL2 |
    Escola: Escola Superior de Tecnologia e Gestão (ESTG)
    Curso: TESP de Programação de Sistemas de Informação (Diurno) - Ano 1
    Unidade Curricular: Fundamentos de Programação (FP)
    Ano Letivo: 2021/2022
    Docente(s): 
        José Vítor Martins Ramos
        Roberto Aguiar Ribeiro

    Objetivos da Aplicação: 
        Efetuar a gestão das operações de  carregamento e pagamento (transações)
        do sistema SIGA nos bares e cantinas do Politécnico de Leiria.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LIMITE DE ELEMENTOS NA BASE DE DADOS
#define MAX_ESCOLA 5
#define MAX_UTILIZADOR 200
#define MAX_TRANSACAO 5000

// FACILITAR LEITURA DO CODIGO
#define SUCESSO 0
#define INSUCESSO 1

#define ESCOLA 1
#define UTILIZADOR 2
#define TRANSACAO 3

#define BASE_DADOS_CHEIA -1

#define IGUAL 0
#define MAIOR 1
#define MENOR 2

// TAMANHO MAXIMO DE CADA STRING
#define TAMANHO_NOME_ESCOLA 60
#define TAMANHO_TIPO_TRANSACAO 30
#define TAMANHO_ABREVIATURA 10
#define TAMANHO_CAMPUS 20
#define TAMANHO_LOCALIZACAO 30
#define TAMANHO_NOME_UTILIZADOR 30
#define TAMANHO_TIPO_UTILIZADOR 20
#define TAMANHO_EMAIL 30

// MESES
#define JANEIRO 1
#define FEVEREIRO 2
#define MARCO 3
#define ABRIL 4
#define MAIO 5
#define JUNHO 6
#define JULHO 7
#define AGOSTO 8
#define SETEMBRO 9
#define OUTUBRO 10
#define NOVEMBRO 11
#define DEZEMBRO 12


typedef struct {
    int dia, mes, ano;
} t_data;
typedef struct {
    int hora, minuto, segundo;
} t_hora;
typedef struct {
    int id_escola;
    char nome_escola[TAMANHO_NOME_ESCOLA], abreviatura[TAMANHO_ABREVIATURA], campus[TAMANHO_CAMPUS], localizacao[TAMANHO_LOCALIZACAO];
} t_escola;
typedef struct {
    int id_utilizador, id_escola, NIF;
    float saldo;
    char nome_utilizador[TAMANHO_NOME_UTILIZADOR], tipo_utilizador[TAMANHO_TIPO_UTILIZADOR], email[TAMANHO_EMAIL];
} t_utilizador;
typedef struct {
    int id_transacao, id_utilizador;
    char tipo_transacao[TAMANHO_TIPO_TRANSACAO];
    float valor;
    t_data data;
    t_hora hora;
} t_transacao;
typedef struct {
    t_escola v_escola[MAX_ESCOLA];
    t_utilizador v_utilizador[MAX_UTILIZADOR];
    t_transacao v_transacao[MAX_TRANSACAO];
} t_principal;

// Funções responsaveis pela manipulação de ficheiros
void ler_ficheiro(t_principal * s_principal);              // le a informação no ficheiro e insere no endereço da variavel passada por parametro
void gravar_no_ficheiro(t_principal* s_principal);         // guarda a informação do parametro no ficheiro

// Funções responsaveis por mostrar menus e informações
void menu_principal(t_principal* s_principal);
void menu_registar(t_principal* s_principal, int baseDados);
void menu_consultar(t_principal* s_principal, int baseDados);
void apresentar_dados(t_principal* s_principal, int index, int baseDados);
void apresentar_escolas(t_principal* s_principal, int index, int baseDados);
void apresentar_utilizadores(t_principal* s_principal, int index, int baseDados);
void apresentar_transacoes(t_principal* s_principal, int index, int baseDados);
void cabecalho_apresentar_dados(int index);
void menu_estatisticas(t_principal* s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
void escrever_elemento_tabela_estatisticas(t_principal * s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[], int index);
void menu_sair(t_principal* s_principal);
void limite_base_dados(t_principal* s_principal, int baseDados);

// Funções responsaveis por manipular a base de dados armazenada na memoria
void limpa_array(t_principal* s_principal, int baseDados);
void limpa_elemento(t_principal* s_principal, int index, int baseDados);
int registar_informacao(t_principal* s_principal, int index, int baseDados);
int registar_escola(t_principal* s_principal, int index);
int registar_utilizador(t_principal* s_principal, int index);
int registar_transacao(t_principal* s_principal, int index);
void consultar_informacao(t_principal* s_principal, int baseDados);
void alterar_elemento(t_principal* s_principal, int index, int baseDados);
void apagar_elemento(t_principal* s_principal, int index, int baseDados);

// Funções responsaveis por obter input do utilizador
int selecinar_base_dados();
int receber_index();
int obter_input(int minimo, int maximo, char texto1[], char texto2[], char texto3[], char texto4[], char texto5[], char texto6[]);
void obter_data(int * dia, int * mes, int * ano);
void obter_hora(int * hora, int * minuto, int * segundo);
void obter_int(int * numero, int minimo, int maximo);
void obter_string(char string[], char string_a_comparar_1[], char string_a_comparar_2[], char string_a_comparar_3[], int maxDiff, int palavraDiferente);
void obter_identificador(t_principal * s_principal, int * identificador, int baseDados, int existe);
void obter_email(char email[]);
void escrever_filtos(t_principal *s_principal);

// Funções responsaveis por fazer calculos e pesquisas na base de dados
int procurar_elemento_vazio(t_principal* s_principal, int baseDados);                // devolve o elemento vazio
int conta_caracteres_numero(int numero);                                             // devolve quantos caracteres um numero tem
void calcula_numero_de_espacos(char espacos[], int numero_espacos_normalmente, int tamanho_palavra); // calcula o numero de espaços entre uma palavra e outra (utilizado na tabela)
int verificar_se_existe(t_principal * s_principal, int index, int baseDados);        // verifica se o elemento ja existe na base de dados
float calcula_total_faturado_por_escola(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
int calcula_percentagem_transacoes(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
int calcula_total_transacoes_escola(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
int verifica_se_utilizador_pertence_escola(t_principal * s_principal, int id_utilizador, int id_escola); // verifica se um utilizador pertence a certa escola
int verifica_mes(int mes);  // Função responsavel por devolver o maximo de dias de cada mes (EX: Fevereiro: 28 dias)
int verifica_tipo_utilizador(t_principal * s_principal, int id_utilizador, char tipoUtilizador[]); // verifica se 
int verifica_se_data_esta_dentro(t_data dataInserida,t_data dataComparar); // verifica se a data está entre os parametros introduzidos
int diferenca_caracteres(char string1[], char string2[]); // devole quantos caracteres são diferentes entre a string1 e string2
int validar_valor(t_principal * s_principal, t_transacao v_transacao);

void main() { // 4 linhas
    t_principal s_principal;                     // cria uma variavel responsavel por armazenar a base de dados na memoria
    limpa_array(&s_principal, 0);                // define todos os valores da base de dados para 0 ou vazio            // prevenção de erros 
    ler_ficheiro(&s_principal);                  // le a informação do ficheiro e insere no endereço da base de dados da memoria
    menu_principal(&s_principal);                // Apresenta o menu principal
}


//********************
//*    FICHEIROS     *
//********************
void ler_ficheiro(t_principal* s_principal) { // 9 linhas
    FILE* ficheiro;                                             // cria uma variavel do tipo FILE que armazena o ficheiro   
    ficheiro = fopen("baseDados.bin", "rb");                    // abre o ficheiro no modo READONLY em binário
    if (ficheiro == NULL) {                                     // verifica se o ficheiro existe
        printf("!!!AVISO!!! Ficheiro nao encontrado!!\n\n");    
    }else {                                                     // caso exista
        fread(s_principal, sizeof(t_principal), 1, ficheiro);   // insere a informação do ficheiro na variavel passada por parametro "s_principal", que neste caso é a base de dados na memoria
    }
    fflush(ficheiro);                                           // limpa o buffer do ficheiro
    fclose(ficheiro);                                           // fecha o ficheiro
}
void gravar_no_ficheiro(t_principal* s_principal) {  // 5 linhas
    FILE* ficheiro;                                         // cria uma variavel do tipo FILE que armazena o ficheiro
    ficheiro = fopen("BaseDados.bin", "wb");                // abre o ficheiro no modo WRITEONLY em binário
    fwrite(s_principal, sizeof(t_principal), 1, ficheiro);  // escreve a informação da base de dados na memoria para o ficheiro
    fflush(ficheiro);                                       // limpa o buffer do ficheiro
    fclose(ficheiro);                                       // fecha o ficheiro
}
//***********************
//*    FIM FICHEIRO     *
//***********************


//****************
//*    MENUS     *
//****************
void menu_principal(t_principal* s_principal) { // 25 linhas
    system("cls");
    int opcao = 0, index; float total_faturado = 0; char espacos[100]; t_data dataInicial = {0, 0, 0}, dataFinal = {0, 0, 0};

    // escreve as estatisticas de cada escola
    printf(" #  | ID Escola | Nome Escola                                       | Total faturado |\n");
    printf("--------------------------------------------------------------------------------------\n");
    for(index = 0; index < MAX_ESCOLA; index++){                     
        if(s_principal->v_escola[index].id_escola != 0){
            total_faturado = 0;
            total_faturado = calcula_total_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, dataInicial, dataFinal, "\0");
            calcula_numero_de_espacos(espacos, 5, conta_caracteres_numero(index));
            printf(" %d%s", index, espacos);
            calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(s_principal->v_escola[index].id_escola));
            printf("%d%s", s_principal->v_escola[index].id_escola, espacos);
            calcula_numero_de_espacos(espacos, 52, strlen(s_principal->v_escola[index].nome_escola));
            printf("%s%s", s_principal->v_escola[index].nome_escola, espacos);
            printf("%.2f\n", total_faturado);
        }
    }

    // mostra o menu e as suas opções e obtem o input do utilizador
    opcao = obter_input(0, 4, "\n\nMenu Principal\n\n", "1 - Registar informacao\n", "2 - Consultar informacao\n", "3 - Estatisticas\n", "4 - Gravar no ficheiro\n", "0 - Sair da aplicacao");
    switch (opcao) {
        case 1: menu_registar(s_principal, selecinar_base_dados()); break;           // para registar informacao
        case 2: menu_consultar(s_principal, selecinar_base_dados()); break;          // para consultar informacao
        case 3: menu_estatisticas(s_principal, dataInicial, dataFinal, "\0"); break; // para consultar estatisticas
        case 4: gravar_no_ficheiro(s_principal); menu_principal(s_principal); break; // para gravar a base de dados da memoria no ficheiro
        case 0: menu_sair(s_principal); break;                                       // para sair da aplicação
        default: menu_principal(s_principal); break;
    }
}
void menu_registar(t_principal* s_principal, int baseDados) {     // 22 linhas
    system("cls");
    int opcao = 0, index = procurar_elemento_vazio(s_principal, baseDados), sucesso = INSUCESSO;

    // para definir o titulo da base de dados que está a inserir
    char titulo[13];
    switch(baseDados){
        case ESCOLA: strcpy(titulo, "Escolas"); break;
        case UTILIZADOR: strcpy(titulo, "Utilizadores"); break;
        case TRANSACAO: strcpy(titulo, "Transacoes"); break;
    }
    
    // Apresenta o menu registar
    printf("Menu Registar - %s\n", titulo);
    printf("-----------------------------------------\n");
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){// caso a base de dados inserida no parametro seja valida
        sucesso = registar_informacao(s_principal, index, baseDados);    // pede input para registar a informação na base de dados enviada por parametro
        printf("\n");
        // mostra a informação inserida pelo utilizador e pede a confirmação se quer inserir mais elementos
        if(sucesso == SUCESSO){
            cabecalho_apresentar_dados(baseDados);
            apresentar_dados(s_principal, index, baseDados);
            opcao = obter_input(1, 3, "\nDeseja introduzir mais elementos?", "\n1 - Sim", "\n2 - Nao", "\n3 - Mudar base de dados", "\0", "\0");
        } else {opcao = obter_input(1, 3, "\nDeseja tentar outra vez?", "\n1 - Sim", "\n2 - Nao", "\n3 - Mudar base de dados", "\0", "\0");}
        switch (opcao){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: menu_principal(s_principal); break;
            case 3: menu_registar(s_principal, selecinar_base_dados()); break;
        }
    }   
}
void menu_consultar(t_principal* s_principal, int baseDados) { // 21 linhas
    system("cls");
    int opcao = 0, max_elementos = 0;

    // para definir o titulo da base de dados que está a inserir
    char titulo[13];
    switch(baseDados){
        case ESCOLA: strcpy(titulo, "Escolas"); max_elementos = MAX_ESCOLA; break;
        case UTILIZADOR: strcpy(titulo, "Utilizadores"); max_elementos = MAX_UTILIZADOR; break;
        case TRANSACAO: strcpy(titulo, "Transacoes"); max_elementos = MAX_TRANSACAO; break;
    }
    printf("Menu Consultar - %s\n\n", titulo);
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){ // caso a base de dados inserida no parametro seja valida
        cabecalho_apresentar_dados(baseDados);
        consultar_informacao(s_principal, baseDados); // apresenta a todos os elementos da respetiva base de dados

        // ofecere varias opções ao utilizador e espera pelo seu input
        opcao = obter_input(0, 4, "\n1 - Apagar elemento", "\n2 - Alterar elemento", "\n3 - Mudar base de dados", "\n4 - Limpar base de dados", "\n0 - Voltar Atras", "\0");
        switch (opcao){
            case 1: apagar_elemento(s_principal, receber_index(), baseDados); break;
            case 2: alterar_elemento(s_principal, receber_index(), baseDados); break;
            case 3: menu_consultar(s_principal, selecinar_base_dados()); break;
            case 4: limpa_array(s_principal, baseDados);  menu_consultar(s_principal, baseDados);break;
            case 0: menu_principal(s_principal); break;
        }
    } else { menu_principal(s_principal); }
}
void apresentar_dados(t_principal* s_principal, int index, int baseDados){ // 12 linhas
    char espacos[100];
    switch(baseDados){
        case ESCOLA: ;
            apresentar_escolas(s_principal, index, baseDados);
            break;
        case UTILIZADOR: ;
            apresentar_utilizadores(s_principal, index, baseDados);
            break;
        case TRANSACAO: ;
            apresentar_transacoes(s_principal, index,  baseDados);
            break;
    }
}
void apresentar_escolas(t_principal* s_principal, int index, int baseDados){ // 13 linhas
    char espacos[100];
    t_escola v_aux_escola = s_principal->v_escola[index];
    calcula_numero_de_espacos(espacos, 5, conta_caracteres_numero(index));
    printf(" %d%s", index, espacos);
    calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(v_aux_escola.id_escola));
    printf("%d%s", v_aux_escola.id_escola, espacos);
    calcula_numero_de_espacos(espacos, 52, strlen(v_aux_escola.nome_escola));
    printf("%s%s", v_aux_escola.nome_escola, espacos);
    calcula_numero_de_espacos(espacos, 15, strlen(v_aux_escola.abreviatura));
    printf("%s%s", v_aux_escola.abreviatura, espacos);
    calcula_numero_de_espacos(espacos, 13, strlen(v_aux_escola.campus));
    printf("%s%s", v_aux_escola.campus, espacos);
    printf("%s\n", v_aux_escola.localizacao);
}
void apresentar_utilizadores(t_principal* s_principal, int index, int baseDados){ // 17 linhas
    char espacos[100];
    t_utilizador v_aux_utilizador = s_principal->v_utilizador[index];
    calcula_numero_de_espacos(espacos, 4, conta_caracteres_numero(index));
    printf(" %d%s", index, espacos);
    calcula_numero_de_espacos(espacos, 16, conta_caracteres_numero(v_aux_utilizador.id_utilizador));
    printf("%d%s", v_aux_utilizador.id_utilizador, espacos);
    calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(v_aux_utilizador.id_escola));
    printf("%d%s", v_aux_utilizador.id_escola, espacos);
    calcula_numero_de_espacos(espacos, 22, strlen(v_aux_utilizador.nome_utilizador));
    printf("%s%s", v_aux_utilizador.nome_utilizador, espacos);
    calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(v_aux_utilizador.NIF));
    printf("%d%s", v_aux_utilizador.NIF, espacos);
    calcula_numero_de_espacos(espacos, 18, strlen(v_aux_utilizador.tipo_utilizador));
    printf("%s%s", v_aux_utilizador.tipo_utilizador, espacos);
    calcula_numero_de_espacos(espacos, 24, strlen(v_aux_utilizador.email));
    printf("%s%s", v_aux_utilizador.email, espacos);
    printf("%.2f\n", v_aux_utilizador.saldo);    
}
void apresentar_transacoes(t_principal* s_principal, int index, int baseDados){ // 17 linhas
    char espacos[100];
    t_transacao v_aux_transacao = s_principal->v_transacao[index];
    calcula_numero_de_espacos(espacos, 6, conta_caracteres_numero(index));
    printf(" %d%s", index, espacos);
    calcula_numero_de_espacos(espacos, 17, conta_caracteres_numero(v_aux_transacao.id_transacao));
    printf("%d%s", v_aux_transacao.id_transacao, espacos);
    calcula_numero_de_espacos(espacos, 19, conta_caracteres_numero(v_aux_transacao.id_utilizador));
    printf("%d%s", v_aux_transacao.id_utilizador, espacos);
    calcula_numero_de_espacos(espacos, 19, strlen(v_aux_transacao.tipo_transacao));
    printf("%s%s", v_aux_transacao.tipo_transacao, espacos);
    calcula_numero_de_espacos(espacos, 21, conta_caracteres_numero(v_aux_transacao.valor) + 3);
    printf("%.2f%s", v_aux_transacao.valor, espacos);
    calcula_numero_de_espacos(espacos, 16, 10);
    printf("%02d/%02d/%04d%s", v_aux_transacao.data.dia, v_aux_transacao.data.mes, v_aux_transacao.data.ano, espacos);
    printf("%02d:%02d:%02d\n", v_aux_transacao.hora.hora, v_aux_transacao.hora.minuto, v_aux_transacao.hora.segundo);  
}
void cabecalho_apresentar_dados(int baseDados){ // 14 linhas
    // apresenta diferentes cabeçalhos dependendo da base de dados inserida
    switch(baseDados){
        case ESCOLA:
            printf(" #  | ID Escola | Nome Escola                                       | Abreviatura |  Campus   |   Localizacao         |\n");
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
            break;
        case UTILIZADOR:
            printf(" # | ID Utilizador | ID Escola | Nome Utilizador     | NIF       | Tipo Utilizador | E-Mail                | Saldo    |\n");
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
            break;
        case TRANSACAO:
            printf(" #  |  ID Transacao  |  ID Utilizador   |  Tipo Transacao  |  Valor Transacao  |   Data        |   Hora       |\n");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            break;
    }
}
void menu_estatisticas(t_principal* s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){ // 23 linhas
    system("cls");
    float total_faturado = 0;
    int index = 0, opcao = 0;
    char espacos[100];
    // apresenta o menu
    printf("Visualizar Estatisticas\n\n");
    if(dataInicial.dia != 0){ printf("Data Inicial: %d/%d/%d\n", dataInicial.dia, dataInicial.mes, dataInicial.ano); } // apresenta a data inicial do filtro (caso seja 0 nao apresenta)
    else { printf("Data Inicial: \n"); }
    if(dataFinal.dia != 0){ printf("Data Final: %d/%d/%d\n", dataFinal.dia, dataFinal.mes, dataFinal.ano); } // apresenta a data inicial do filtro (caso seja 0 nao apresenta)
    else { printf("Data Final: \n"); }

    // apresenta o menu das estatisticas
    printf("Tipo de utilizador: %s\n\n", tipoUtilizador);
    printf(" #  | ID Escola | Nome Escola                                       | Total faturado |  N%c pagamentos  |  %% pagamentos |\n", 248);
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    // apresenta todas as escolas
    for(index = 0; index < MAX_ESCOLA; index++){
        if(s_principal->v_escola[index].id_escola != 0){
            escrever_elemento_tabela_estatisticas(s_principal, dataInicial, dataFinal, tipoUtilizador, index);
        }
    }
    // obtem input do utilizador
    opcao = obter_input(0, 1, "\n\n\n1 - Filtros","\n0 - Voltar atras", "\0", "\0", "\0", "\0");
    switch(opcao){
        case 1: escrever_filtos(s_principal); break;
        case 0: menu_principal(s_principal); break;
        default: menu_principal(s_principal);
    }
}
void escrever_elemento_tabela_estatisticas(t_principal * s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[], int index){ // 17 linhas
    // apresenta todas as informações de cada escola
    float total_faturado = 0;
    char espacos[100];
    int total_transacoes_percentagem = 0, total_transacoes = 0;
    total_faturado = calcula_total_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, dataInicial, dataFinal, tipoUtilizador);
    total_transacoes_percentagem = calcula_percentagem_transacoes(s_principal, s_principal->v_escola[index].id_escola, dataInicial, dataFinal, tipoUtilizador);
    total_transacoes = calcula_total_transacoes_escola(s_principal, s_principal->v_escola[index].id_escola, dataInicial, dataFinal, tipoUtilizador);
    calcula_numero_de_espacos(espacos, 5, conta_caracteres_numero(index));
    printf(" %d%s", index, espacos);
    calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(s_principal->v_escola[index].id_escola));
    printf("%d%s", s_principal->v_escola[index].id_escola, espacos);
    calcula_numero_de_espacos(espacos, 52, strlen(s_principal->v_escola[index].nome_escola));
    printf("%s%s", s_principal->v_escola[index].nome_escola, espacos);
    calcula_numero_de_espacos(espacos, 18, conta_caracteres_numero(total_faturado) + 3);
    printf("%.2f%s", total_faturado, espacos);
    calcula_numero_de_espacos(espacos, 19, conta_caracteres_numero(total_transacoes));
    printf("%d%s", total_transacoes, espacos);
    printf("%d%%\n", total_transacoes_percentagem);
}
void limite_base_dados(t_principal* s_principal, int baseDados){ // 7 linhas
    // apresenta um menu a dizer que a base de dados chegou ao limite
    int opcao = 0;
    opcao = obter_input(0, 2, "A base de dados atingiu o limite!!!\n\n", "1 - Apagar elementos\n", "2 - Editar elementos\n", "0 - Voltar atras", "\0", "\0");
    switch(opcao){
        case 1: apagar_elemento(s_principal, receber_index(), baseDados); break;
        case 2: alterar_elemento(s_principal, receber_index(), baseDados); break;
        case 0: menu_principal(s_principal); break;
    }
}
void menu_sair(t_principal* s_principal) { // 16 linhas
    // menu para sair da aplicação
    int opcao = 0;
    system("cls");
    opcao = obter_input(0, 2, "Sair da aplicacao\n\n", "Deseja guardar a informacao registada?\n", "1 - Guardar\n", "2 - Nao guardar\n", "0 - Voltar atras", "\0");
    switch(opcao){
        case 1:                                                 // caso queira guardar a informação
            gravar_no_ficheiro(s_principal);
            system("cls");
            printf("Sair da Aplicacao\n\n");
            printf("Informacao guardada com sucesso!\n");
            printf("\n\nPrima qualquer tecla para sair da aplicacao");
            getchar();
            exit(1);
            break;
        case 2: exit(1); break;                                // caso nao queira guardar informação
        case 0: menu_principal(s_principal);                   // caso queira voltar atras
        default: menu_sair(s_principal);
    }
}
//****************
//*   FIMMENUS   *
//****************


//******************************
//*   MANIPULAÇÃO BASE DADOS   *
//******************************
void limpa_array(t_principal* s_principal, int baseDados) { // 25 linhas
    int index = 0;
    // vai por um ciclo que apaga a base de dados introduzida por parametro
    switch(baseDados){
        case ESCOLA:
            for (index = 0; index < MAX_ESCOLA; index++) {
                limpa_elemento(s_principal, index, ESCOLA);
            }break;
        case UTILIZADOR:
            for (index = 0; index < MAX_UTILIZADOR; index++) {
                limpa_elemento(s_principal, index, UTILIZADOR);
            }break;
        case TRANSACAO:
            for (index = 0; index < MAX_TRANSACAO; index++) {
                limpa_elemento(s_principal, index, TRANSACAO);
            }break;
        default:  // caso nao se introduza nenhuma base de dados valida, apaga todas as bases de dados
            for (index = 0; index < MAX_ESCOLA; index++) {
                limpa_elemento(s_principal, index, ESCOLA);
            }
            for (index = 0; index < MAX_UTILIZADOR; index++) {
                limpa_elemento(s_principal, index, UTILIZADOR);
            }
            for (index = 0; index < MAX_TRANSACAO; index++) {
                limpa_elemento(s_principal, index, TRANSACAO);
            }
    }
}
void limpa_elemento(t_principal* s_principal, int index, int baseDados) { // 25 linhas
    // apaga o elemento inserido por parametro (depende de index e base de dados)
    switch(baseDados){
        case ESCOLA:
            s_principal->v_escola[index].id_escola = 0;
            strcpy(s_principal->v_escola[index].nome_escola, "\0");
            strcpy(s_principal->v_escola[index].abreviatura, "\0");
            strcpy(s_principal->v_escola[index].campus, "\0");
            strcpy(s_principal->v_escola[index].localizacao, "\0");
            break;
        case UTILIZADOR:
            s_principal->v_utilizador[index].id_utilizador = 0;
            s_principal->v_utilizador[index].id_escola = 0;
            s_principal->v_utilizador[index].NIF = 0;
            s_principal->v_utilizador[index].saldo = 0;
            strcpy(s_principal->v_utilizador[index].nome_utilizador, "\0");
            strcpy(s_principal->v_utilizador[index].tipo_utilizador, "\0");
            strcpy(s_principal->v_utilizador[index].email, "\0");
            break;
        case TRANSACAO:
            s_principal->v_transacao[index].id_transacao = 0;
            s_principal->v_transacao[index].id_utilizador = 0;
            s_principal->v_transacao[index].valor = 0;
            strcpy(s_principal->v_transacao[index].tipo_transacao, "\0");
            s_principal->v_transacao[index].data = (t_data){ 0, 0, 0 };
            s_principal->v_transacao[index].hora = (t_hora){ 0, 0, 0 };
    }
}
int registar_informacao(t_principal* s_principal, int index, int baseDados) { // 9 linhas
    int sucesso = INSUCESSO;
    if(index != BASE_DADOS_CHEIA){ // caso a base de dados nao esteja cheia
        switch (baseDados) {
            case ESCOLA: sucesso = registar_escola(s_principal, index); break;            // insere escolas
            case UTILIZADOR: sucesso = registar_utilizador(s_principal, index); break;    // insere utilizadores
            case TRANSACAO: sucesso = registar_transacao(s_principal, index); break;      // insere transacoes
        }
    } else { // caso a base de dados esteja cheia
        limite_base_dados(s_principal, baseDados);  // chama o menu que diz que a base de dados está cheia
    }
    return sucesso;
}
int registar_escola(t_principal* s_principal, int index) { // 19 linhas
    // obtem o input do utilizador, valida-o e caso esteja tudo valido, insere na base de dados na memoria
    t_escola v_aux_escola[MAX_ESCOLA];
    printf("Identificador Escola: ");
    obter_identificador(s_principal, &v_aux_escola[index].id_escola, ESCOLA, 0);
    fflush(stdin);
    printf("Nome Escola: ");
    scanf("%[^\n]s", v_aux_escola[index].nome_escola);
    fflush(stdin);
    printf("Abreviatura: ");
    scanf("%[^\n]s", v_aux_escola[index].abreviatura);
    printf("Campus: ");
    obter_string(v_aux_escola[index].campus, "Campus 1", "\0", "\0", 2, 0);
    fflush(stdin);
    printf("Localizacao: ");
    scanf("%[^\n]s", v_aux_escola[index].localizacao);
    s_principal->v_escola[index].id_escola = v_aux_escola[index].id_escola;
    strcpy(s_principal->v_escola[index].nome_escola, v_aux_escola[index].nome_escola);
    strcpy(s_principal->v_escola[index].abreviatura, v_aux_escola[index].abreviatura);
    strcpy(s_principal->v_escola[index].campus, v_aux_escola[index].campus);
    strcpy(s_principal->v_escola[index].localizacao, v_aux_escola[index].localizacao);
    return SUCESSO;
}
int registar_utilizador(t_principal* s_principal, int index) { // 25 linhas
    // obtem o input do utilizador, valida-o e caso esteja tudo valido, insere na base de dados na memoria
    t_utilizador v_aux_utilizador[MAX_UTILIZADOR];
    fflush(stdin);
    printf("Identificador Utilizador: ");
    obter_identificador(s_principal, &v_aux_utilizador[index].id_utilizador, UTILIZADOR, 0);
    printf("Identificador Escola: ");
    obter_identificador(s_principal, &v_aux_utilizador[index].id_escola, ESCOLA, 1);
    fflush(stdin);
    printf("Nome Utilizador: ");
    scanf("%[^\n]s", v_aux_utilizador[index].nome_utilizador);
    printf("NIF: ");
    obter_int(&v_aux_utilizador[index].NIF, 10000000, 999999999);
    printf("Tipo Utilizador: ");
    obter_string(v_aux_utilizador[index].tipo_utilizador, "Docente", "Estudante", "Funcionario", 3, 1);
    fflush(stdin);
    printf("Email: ");
    obter_email(v_aux_utilizador[index].email);
    printf("Saldo: ");
    scanf("%f", &v_aux_utilizador[index].saldo);
    s_principal->v_utilizador[index].id_utilizador = v_aux_utilizador[index].id_utilizador;
    s_principal->v_utilizador[index].id_escola = v_aux_utilizador[index].id_escola;
    strcpy(s_principal->v_utilizador[index].nome_utilizador, v_aux_utilizador[index].nome_utilizador);
    s_principal->v_utilizador[index].NIF = v_aux_utilizador[index].NIF;
    strcpy(s_principal->v_utilizador[index].tipo_utilizador, v_aux_utilizador[index].tipo_utilizador);
    strcpy(s_principal->v_utilizador[index].email, v_aux_utilizador[index].email);
    s_principal->v_utilizador[index].saldo = v_aux_utilizador[index].saldo; return SUCESSO;
}
int registar_transacao(t_principal* s_principal, int index) { // 25 linhas
    // obtem o input do utilizador, valida-o e caso esteja tudo valido, insere na base de dados na memoria
    int sucesso = SUCESSO;
    t_transacao v_aux_transacao[MAX_TRANSACAO];
    fflush(stdin);
    printf("Identificador Transacao: ");
    obter_identificador(s_principal, &v_aux_transacao[index].id_transacao, TRANSACAO, 0);
    printf("Identificador Utilizador: ");
    obter_identificador(s_principal, &v_aux_transacao[index].id_utilizador, UTILIZADOR, 1);
    printf("Tipo Transacao: ");
    obter_string(v_aux_transacao[index].tipo_transacao, "Pagamento", "Carregamento", "\0", 3, 1);
    printf("Valor Transacao: ");
    scanf("%f", &v_aux_transacao[index].valor);
    printf("Data (FORMATO dd/mm/yyyy): ");
    obter_data(&v_aux_transacao[index].data.dia, &v_aux_transacao[index].data.mes, &v_aux_transacao[index].data.ano);
    printf("Hora (FORMATO hh:mm:ss): ");
    obter_hora(&v_aux_transacao[index].hora.hora, &v_aux_transacao[index].hora.minuto, &v_aux_transacao[index].hora.segundo);
    sucesso = validar_valor(s_principal, v_aux_transacao[index]);
    if(sucesso == SUCESSO){
        s_principal->v_transacao[index].id_transacao = v_aux_transacao[index].id_transacao;
        s_principal->v_transacao[index].id_utilizador = v_aux_transacao[index].id_utilizador;
        strcpy(s_principal->v_transacao[index].tipo_transacao, v_aux_transacao[index].tipo_transacao);
        s_principal->v_transacao[index].valor = v_aux_transacao[index].valor;
        s_principal->v_transacao[index].data = (t_data){ v_aux_transacao[index].data.dia, v_aux_transacao[index].data.mes, v_aux_transacao[index].data.ano };
        s_principal->v_transacao[index].hora = (t_hora){ v_aux_transacao[index].hora.hora, v_aux_transacao[index].hora.minuto, v_aux_transacao[index].hora.segundo };
    }
    return sucesso;
}
void consultar_informacao(t_principal* s_principal, int baseDados) { // 24 linhas
    int index = 0;
    // verifica qual a base de dados inserida por parametro
    switch (baseDados) {
        // cria um ciclo que apresenta todos os elementos que NAO estejam vazios
        case ESCOLA:
            for(index = 0; index < MAX_ESCOLA; index++){
                if(s_principal->v_escola[index].id_escola != 0){
                    apresentar_dados(s_principal, index, ESCOLA);
                }
            }
            break;
        case UTILIZADOR:
            for(index = 0; index < MAX_UTILIZADOR; index++){
                if(s_principal->v_utilizador[index].id_utilizador != 0){
                    apresentar_dados(s_principal, index, UTILIZADOR);
                }
            }
            break;
        case TRANSACAO:
            for(index = 0; index < MAX_TRANSACAO; index++){
                if(s_principal->v_transacao[index].id_transacao != 0){
                    apresentar_dados(s_principal, index, TRANSACAO);
                }
            }
            break;
    }
}
void apagar_elemento(t_principal* s_principal, int index, int baseDados){ // 25 linhas
    system("cls");
    if(verificar_se_existe(s_principal, index, baseDados) == 1){ // caso o elemento exista
        printf("Tem a certeza que quer apagar este elemento?\n\n\n");
        cabecalho_apresentar_dados(baseDados);
        apresentar_dados(s_principal, index, baseDados);
        int opcao = obter_input(0, 3, "\n\n1 - Sim", "\n2 - Nao", "\n3 - Escolher outro elemento", "\n0 - Voltar atras", "\0", "\0");
        switch(opcao){
            case 1:  // Sim
                limpa_elemento(s_principal, index, baseDados);
                menu_consultar(s_principal, baseDados);break;
            case 2: menu_consultar(s_principal, baseDados); break; //Nao
            case 3: apagar_elemento(s_principal, receber_index(), baseDados); break; // Escolher outro elemento
            case 0: menu_principal(s_principal); break;// Voltar atras
        }
    } else{             // caso o elemento nao exista
        printf("\nO elemento com index %d nao existe na nossa base de dados!\n", index);
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento\n", "2 - Escolher outro elemento\n", "0 - Voltar atras\n", "\0", "\0", "\0");
        switch(opcao_1){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: alterar_elemento(s_principal, receber_index(), baseDados);
            case 0: menu_consultar(s_principal, baseDados); break;
        }
    }
}
void alterar_elemento(t_principal* s_principal, int index, int baseDados) { // 24 linhas
    system("cls");
    if(verificar_se_existe(s_principal, index, baseDados) == 1){  // caso o elemento exista
        printf("\n\nPretende alterar este elemento?\n\n");
        cabecalho_apresentar_dados(baseDados);
        apresentar_dados(s_principal, index, baseDados);
        int opcao = obter_input(0, 3, "\n\n1 - Sim", "\n2 - Nao", "\n3 - Escolher outro elemento", "\n0 - Voltar atras", "\0", "\0");
        switch(opcao){
            case 1:  // Sim
                registar_informacao(s_principal, index, baseDados);
                menu_consultar(s_principal, baseDados);
                break;
            case 2: menu_consultar(s_principal, baseDados); break;// Nao
            case 3: apagar_elemento(s_principal, receber_index(), baseDados); break; // Escolher outro elemento
            case 0: menu_principal(s_principal); break;// Voltar atras
        }
    } else{                                                     // caso e elemento nao exista
        printf("\nO elemento com index %d nao existe na nossa base de dados!\n", index);
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento\n", "2 - Escolher outro elemento\n", "0 - Voltar atras", "\0", "\0", "\0");
        switch(opcao_1){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: alterar_elemento(s_principal, receber_index(), baseDados);
            case 0: menu_consultar(s_principal, baseDados); break;
        }
    }
}
//**********************************
//*   FIM MANIPULAÇÃO BASE DADOS   *
//**********************************


//*************
//*   INPUT   *
//*************
int selecinar_base_dados() { // 7 linhas
    int opcao;
    // obtem uma base de dados           Escolas || Utilizadores || Transações 
    do {
        system("cls");
        opcao = obter_input(0, 3, "Selecione a base de dados que deseja manipular:\n\n", "1 - Escolas\n", "2 - Utilizadores\n", "3 - Transacoes\n", "0 - Voltar atras", "\0");

    } while (opcao < 0 && opcao > 3);
    return opcao;
}
int receber_index(){ // 5 linhas
    int index = 0;
    // obtem um index
    printf("\n\n    INDEX (#)  --->   ");
    scanf("%d", &index);
    return index;
}
int obter_input(int minimo, int maximo, char texto1[], char texto2[], char texto3[], char texto4[], char texto5[], char texto6[]){ // 24 linhas
    char textos[6][100];          // criação de array para facilitar o uso de ciclos
    int escrever = SUCESSO, opcao = -1, index = 0;
    strcpy(textos[0], texto1);   // atribuição do valor dos parametros ao array
    strcpy(textos[1], texto2);
    strcpy(textos[2], texto3);
    strcpy(textos[3], texto4);
    strcpy(textos[4], texto5);
    strcpy(textos[5], texto6);
    for(index = 0; index < 6; index++){                     // repete um ciclo que vai por todos os textos
        if(textos[index] != "\0" && escrever == SUCESSO){         // caso um texto nao seja vazio e caso o programa possa escrever
            printf("%s", textos[index]);                    // escreve esse texto
        } else {                                            // caso o texto seja vazio ou o programa tenha de parar
            escrever = INSUCESSO;                                   // muda a variavel escrever, que é responsavel por escrever caso tenha o valor de 0
        }
    }
    do{
        printf("\n\n> ");
        fflush(stdin);
        scanf("%d", &opcao);                              // recebe uma int
        if(opcao < minimo || opcao > maximo){
            printf("Tem de ser entre %d e %d!!", minimo, maximo);
        }
    } while(opcao < minimo || opcao > maximo);                  // valores que devem ser introduzidos pelo utilizador
    return opcao;                                               // devolve a opcao escolhida
}
void obter_data(int * dia, int * mes, int * ano){ // 25 linhas
    int max_dia = 0, sucesso = INSUCESSO; char stringData[15]; t_data auxiliar;
    do{
        scanf("%s", stringData);                             // obtem uma string
        if(stringData[2] == '/' && stringData[5] == '/'){    // verifica sem tem barras com o seguinte format xx/xx/xxxx
            if((stringData[0] >= '0' && stringData[0] <= '9') && (stringData[1] >= '0' && stringData[1] <= '9')){  // verifica se os primeiros dois caracteres (dias) sao numeros
                if((stringData[3] >= '0' && stringData[3] <= '9') && (stringData[4] >= '0' && stringData[4] <= '9')){ // verifica se os caracteres 4 e 5 (meses) sao numero 
                    if((stringData[6] >= '0' && stringData[6] <= '9') && (stringData[7] >= '0' && stringData[7] <= '9') && (stringData[8] >= '0' && stringData[8] <= '9') && stringData[9] >= '0' && stringData[9] <= '9'){ // verifica se os caracteres 7,8,9 e 10 (ano) sao numero
                        auxiliar.dia = ((stringData[0] - '0') * 10) + (stringData[1] - '0');        // converte char para int
                        auxiliar.mes = ((stringData[3] - '0') * 10) + (stringData[4] - '0');        // converte char para int
                        auxiliar.ano = (stringData[6] - '0') * 1000 + (stringData[7] - '0') * 100 + (stringData[8] -'0') * 10 + (stringData[9] - '0'); // converte char para int
                        if(auxiliar.ano >= 1900 && auxiliar.ano <= 2022){  // valida o ano inserido
                            if(auxiliar.mes >= 1 && auxiliar.mes <= 12){ max_dia = verifica_mes(auxiliar.mes); // valida o mes inserido e determina o maximo de dias desse mes
                                if(auxiliar.dia >= 1 && auxiliar.dia <= max_dia){ // valida o dia inserido
                                    *dia = auxiliar.dia;               // caso sejam todos validos insere no endereço da variavel de parametro
                                    *mes = auxiliar.mes;
                                    *ano = auxiliar.ano;
                                    sucesso = SUCESSO;
                                } else { printf("\nDia invalido! Tem de ser entre 1 e %d!\n\nData (FORMATO dd/mm/yyyy): ", max_dia);}
                            } else { printf("\nMes invalido! Tem de ser entre 1 e 12!\n\nData (FORMATO dd/mm/yyyy): ");}
                        } else { printf("\nAno invalido! Tem de ser entre 1900 e 2022!\n\nData (FORMATO dd/mm/yyyy): ");}
                    }else { printf("\nAno invalido! Tem de ser entre 1900 e 2022!\n\nData (FORMATO dd/mm/yyyy): ");}
                } else { printf("\nMes invalido! Tem de ser entre 1 e 12!\n\nData (FORMATO dd/mm/yyyy): ");}
            } else { printf("\nDia invalido! Tem de ser entre 1 e 31!\n\nData (FORMATO dd/mm/yyyy): ");}
        } else { printf("\nFormato de data invalido  (FORMATO dd/mm/yyy)\n\nData (FORMATO dd/mm/yyyy): ");}
    } while (sucesso == INSUCESSO);
}
void obter_hora(int * hora, int * minuto, int * segundo){ // 25 linhas
    int sucesso = INSUCESSO; char stringData[15]; t_hora auxiliar;
    do{
        scanf("%s", stringData);
        if(stringData[2] == ':' && stringData[5] == ':'){  // verifica se está no formato correto xx:xx:xx
            if((stringData[0] >= '0' && stringData[0] <= '9') && (stringData[1] >= '0' && stringData[1] <= '9')){   // verifica se sao numeros
                if((stringData[3] >= '0' && stringData[3] <= '9') && (stringData[4] >= '0' && stringData[4] <= '9')){
                    if((stringData[6] >= '0' && stringData[6] <= '9') && (stringData[7] >= '0' && stringData[7] <= '9')){
                        auxiliar.hora = ((stringData[0] - '0') * 10) + (stringData[1] - '0');   // conversao char para int
                        auxiliar.minuto = ((stringData[3] - '0') * 10) + (stringData[4] - '0'); // conversao char para int
                        auxiliar.segundo = (stringData[6] - '0') * 10 + (stringData[7] - '0');  // conversao char para int
                        if(auxiliar.segundo >= 0 && auxiliar.segundo <= 59){                    // valida os segundos   
                            if(auxiliar.minuto >= 0 && auxiliar.minuto <= 59){                  // valida os minutos
                                if(auxiliar.hora >= 0 && auxiliar.hora <= 23){                  // valida as horas
                                    *hora = auxiliar.hora;         // caso sejam todos validos, insere no endereço da variavel inserida como parametro
                                    *minuto = auxiliar.minuto;
                                    *segundo = auxiliar.segundo;
                                    sucesso = SUCESSO; // acaba o ciclo
                                } else { printf("\nHora invalida! Tem de ser entre 00 e 23!\n\nHora (FORMATO hh:mm:ss): ");}
                            } else { printf("\nMinutos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                        } else { printf("\nSegundos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                    }else { printf("\nSegundos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                } else { printf("\nMinutos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
            } else { printf("\nHora invalida! Tem de ser entre 0 e 23!\n\nHora (FORMATO hh:mm:ss): ");}
        } else { printf("\nFormato de hora invalido  (FORMATO hh:mm:ss)\n\nHora (FORMATO hh:mm:ss): ");}
    } while (sucesso == INSUCESSO);
}
void obter_int(int * numero, int minimo, int maximo){ // 8 linhas
    int auxiliar = 0;
    // recebe um valor e valida dependendo do minimo e maximo introduzido por paramentro
    do{
        scanf("%d", &auxiliar);
        if(auxiliar >= maximo || auxiliar < minimo){
            printf("\n\nValor tem de ser entre %d e %d!\n\n> ", minimo, maximo);
        }
    } while(auxiliar > maximo || auxiliar < minimo);
    *numero = auxiliar;
}
void obter_identificador(t_principal * s_principal, int * identificador, int baseDados, int existe){ // 25 linhas  existe = 0 (que nao existe)   |  existe = 1 (existe)
    int auxiliar = 0, index = 0, sucesso = INSUCESSO;
    // obtem um int e valida de acordo com o parametro "existe", caso o parametro seja 0 é porque nao se quer identificadores repetidos, caso seja 1 é porque necessita que exista na base de dados
    do{
        scanf("%d", &auxiliar);
        switch(baseDados){
            case ESCOLA:
                for(index = 0; index < MAX_ESCOLA; index++){
                    if(existe == 0){if(auxiliar != s_principal->v_escola[index].id_escola){sucesso = SUCESSO;}else{sucesso=INSUCESSO;break;}}
                    else{if(auxiliar == s_principal->v_escola[index].id_escola){sucesso = SUCESSO;}}
                } break;
            case UTILIZADOR:
                for(index = 0; index < MAX_UTILIZADOR; index++){
                    if(existe == 0){if(auxiliar != s_principal->v_utilizador[index].id_utilizador){sucesso = SUCESSO;}else{sucesso=INSUCESSO;break;}}
                    else{if(auxiliar == s_principal->v_utilizador[index].id_utilizador){sucesso = SUCESSO;}}
                } break;
            case TRANSACAO:
            for(index = 0; index < MAX_TRANSACAO; index++){
                    if(existe == 0){if(auxiliar != s_principal->v_transacao[index].id_transacao){sucesso = SUCESSO;}else{sucesso=INSUCESSO;break;}}
                    else{if(auxiliar == s_principal->v_transacao[index].id_transacao){sucesso = SUCESSO;}}
                } break;
        }
        if(sucesso == INSUCESSO){
            if(existe == 0){printf("\nO identificador %d ja existe na base de dados!\n\n> ", auxiliar);}else{printf("\nO identificador %d nao existe na base de dados!\n\n> ", auxiliar);}
        }
    } while(sucesso != SUCESSO);
    if(sucesso == SUCESSO){*identificador = auxiliar;}
}
void obter_string(char string[], char string_a_comparar_1[], char string_a_comparar_2[], char string_a_comparar_3[], int maxDiff, int palavraDiferente){ // 24 linhas
    char auxiliar[80]; int index = 0, caracteres_diferentes = 0, palavra_encontrada = INSUCESSO;
    // obtem uma string e compara com as strings inseridas nos parametros, caso tenha menos do que a maxDiff de caracteres, valida o input
    do{
        fflush(stdin);
        scanf("%[^\n]s", auxiliar);
        if(strcmp(string_a_comparar_1, "\0") != 0){
            if(diferenca_caracteres(auxiliar, string_a_comparar_1) <= maxDiff){
                palavra_encontrada = SUCESSO;
                if(palavraDiferente == 0){strcpy(string, auxiliar);}
                else {strcpy(string, string_a_comparar_1);}
            } else if(strcmp(string_a_comparar_2, "\0") != 0){printf("\0");
                if(diferenca_caracteres(auxiliar, string_a_comparar_2) <= maxDiff){ 
                    palavra_encontrada = SUCESSO;
                    if(palavraDiferente == 0){strcpy(string, auxiliar);}
                    else {strcpy(string, string_a_comparar_2);}
                } else if(strcmp(string_a_comparar_3, "\0") != 0){printf("\0");
                    if(diferenca_caracteres(auxiliar, string_a_comparar_3) <= maxDiff){ 
                        palavra_encontrada = SUCESSO;
                        if(palavraDiferente == 0){strcpy(string, auxiliar);}
                        else {strcpy(string, string_a_comparar_3);}
                    } else {printf("\nA palavra tem de ser %s ou %s ou %s!\n\n> ", string_a_comparar_1, string_a_comparar_2, string_a_comparar_3);}
                } else {printf("\nA palavra tem de ser %s ou %s!\n\n> ", string_a_comparar_1, string_a_comparar_2);}
            } else {printf("\nA palavra tem de ser %s!\n\n> ", string_a_comparar_1, string_a_comparar_2, string_a_comparar_3);}
        }
    } while(palavra_encontrada != SUCESSO);
}
void obter_email(char email[]){ // 15 linhas
    char auxiliar[100];
    int index = 0, sucesso = INSUCESSO;
    // obtem uma string e valida a ver se tem um @
    do{
        fflush(stdin);
        scanf("%s", auxiliar);
        for(index = 0; index < 100; index++){
            if(auxiliar[index] == '@'){
                sucesso = SUCESSO;
            }
        }
        if(sucesso != SUCESSO){
            printf("\nO email precisa de ser valido!\n\n> ");
        }
    } while(sucesso != SUCESSO);
    strcpy(email, auxiliar);
}
void escrever_filtos(t_principal *s_principal){ // 9 linhas
    // obtem os filtros para o menu de estatisticas
    t_data dataInicial, dataFinal;
    char tipoUtilizador[20];
    printf("Data Inicial (FORMATO dd/mm/yyyy): ");
    obter_data(&dataInicial.dia, &dataInicial.mes, &dataInicial.ano);
    printf("Data Final (FORMATO dd/mm/yyyy): ");
    obter_data(&dataFinal.dia, &dataFinal.mes, &dataFinal.ano);
    printf("Tipo de Utilizador: ");
    scanf("%s", tipoUtilizador);
    menu_estatisticas(s_principal, dataInicial, dataFinal, tipoUtilizador);
}
//***************
//*   FIMINPUT  *
//***************


//***************************
//*   CALCULOS E PESQUISA   *
//***************************
int procurar_elemento_vazio(t_principal* s_principal, int baseDados) { // 22 linhas
    int index = 0;
    // procura um elemento vazio na base de dados introduzida por parametro
    switch (baseDados) {
        case ESCOLA:
            for (index = 0; index < MAX_ESCOLA; index++) {
                if (s_principal->v_escola[index].id_escola == 0) {
                    return index;
                }
            }break;
        case UTILIZADOR:
            for (index = 0; index < MAX_UTILIZADOR; index++) {
                if (s_principal->v_utilizador[index].id_utilizador == 0) {
                    return index;
                }
            }break;
        case TRANSACAO:
            for (int index = 0; index < MAX_TRANSACAO; index++) {
                if (s_principal->v_transacao[index].id_transacao == 0) {
                    return index;
                }
            }break;
    }
    return BASE_DADOS_CHEIA;
}
int conta_caracteres_numero(int numero){ // 6 linhas
    // conta quantos caracteres um int tem        EX: 12345 = 5
    int count = 1;
    while (numero > 9) {
        numero = numero / 10;
        count++;
    }
    return count;
}
void calcula_numero_de_espacos(char espacos[], int numero_espacos_normalmente, int tamanho_palavra){  // 8 linhas
    // calcula o numero de espaços dependendo do tamanho da palavra e dos espaços que normalmente teria se a palavra estivesse vazio
    int index = 0;
    char auxiliar[100];
    for(index = 0; index < 100; index++){
        espacos[index] = '\0';
    }
    for(index = 0; index < numero_espacos_normalmente - tamanho_palavra; index++){
        espacos[index] = ' ';
    }
}
int verificar_se_existe(t_principal * s_principal, int index, int baseDados){ // 21 linhas
    int i = 0, existe = 0;
    switch(baseDados){
        // verifica se o elemento existe na base de dados inserida no parametro
        case ESCOLA:
            do{
                existe = s_principal->v_escola[index].id_escola != 0 ? 1 : 0;
                i++;
            } while(existe != 1 || i < MAX_ESCOLA);
            break;
        case UTILIZADOR:
            do{
                existe = s_principal->v_utilizador[index].id_utilizador != 0 ? 1 : 0;
                index++;
            } while(existe != 1 || i < MAX_UTILIZADOR);
            break;
        case TRANSACAO:
            do{
                existe = s_principal->v_transacao[index].id_transacao != 0 ? 1 : 0;
                i++;
            } while(existe != 1 || i < MAX_TRANSACAO);
    }
    return existe;
}
float calcula_total_faturado_por_escola(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){ // 22 linhas
    int index = 0;
    float total_faturado = 0;
    for(index = 0; index < MAX_TRANSACAO; index++) { // vai por todas as transacoes
        if(s_principal->v_transacao[index].id_transacao != 0) { // se nao estiver vazio
            if(strcmp(s_principal->v_transacao[index].tipo_transacao, "Pagamento") == 0){
                if(verifica_se_utilizador_pertence_escola(s_principal, s_principal->v_transacao[index].id_utilizador, id_escola) == SUCESSO){
                    if(dataInicial.dia != 0){
                            if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataInicial) == MAIOR){
                                if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataFinal) == MENOR){
                                    for(int i = 0; i < MAX_UTILIZADOR; i++){
                                        if(s_principal->v_utilizador[i].id_utilizador == s_principal->v_transacao[index].id_utilizador){
                                            if(strcmp(s_principal->v_utilizador[index].tipo_utilizador, tipoUtilizador) == 0){ total_faturado += s_principal->v_transacao[index].valor; }
                                        }
                                    }
                                }
                            }
                        } else { total_faturado += s_principal->v_transacao[index].valor; }
                    }
            }
        }
    }
    return total_faturado;
}
int calcula_percentagem_transacoes(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){  // 23 linhas
    int percentagem_transacoes = 0, index = 0, total_transacoes = 0, transacoes_escola = 0;
    for(index = 0; index < MAX_TRANSACAO; index++) { // vai por todas as transacoes
        if(s_principal->v_transacao[index].id_transacao != 0) { // se nao estiver vazio
            if(strcmp(s_principal->v_transacao[index].tipo_transacao, "Pagamento") == 0){
                total_transacoes++;
                if(verifica_se_utilizador_pertence_escola(s_principal, s_principal->v_transacao[index].id_utilizador, id_escola) == SUCESSO){
                    if(dataInicial.dia != 0){
                        if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataInicial) == MAIOR){
                            if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataFinal) == MENOR){
                                for(int i = 0; i < MAX_UTILIZADOR; i++){
                                    if(s_principal->v_utilizador[i].id_utilizador == s_principal->v_transacao[index].id_utilizador){
                                        if(strcmp(s_principal->v_utilizador[index].tipo_utilizador, tipoUtilizador) == 0){ transacoes_escola++; }
                                    }
                                }
                            }
                        }
                    } else { transacoes_escola++; }
                }  
            }   
        }
    }
    percentagem_transacoes = (transacoes_escola * 100) / total_transacoes;
    return percentagem_transacoes;
}
int calcula_total_transacoes_escola(t_principal * s_principal, int id_escola, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){ // 22 linhas
    int transacoes_escola = 0;
    int index = 0;
    for(index = 0; index < MAX_TRANSACAO; index++) { // vai por todas as transacoes
        if(s_principal->v_transacao[index].id_transacao != 0) { // se nao estiver vazio
            if(strcmp(s_principal->v_transacao[index].tipo_transacao, "Pagamento") == 0){
                if(verifica_se_utilizador_pertence_escola(s_principal, s_principal->v_transacao[index].id_utilizador, id_escola) == SUCESSO){
                    if(dataInicial.dia != 0){
                        if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataInicial) == MAIOR){
                            if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataFinal) == MENOR){
                                for(int i = 0; i < MAX_UTILIZADOR; i++){
                                    if(s_principal->v_utilizador[i].id_utilizador == s_principal->v_transacao[index].id_utilizador){
                                        if(strcmp(s_principal->v_utilizador[index].tipo_utilizador, tipoUtilizador) == 0){ transacoes_escola++; }
                                    }
                                }
                            }
                        }
                    } else { transacoes_escola++; }
                } 
            }
        }
    }
    return transacoes_escola;
}
int verifica_se_data_esta_dentro(t_data dataInserida,t_data dataComparar){ // 17 linhas
    int verificador = IGUAL;
    if(dataInserida.ano < dataComparar.ano){
        verificador = MENOR;
    } else if(dataInserida.ano > dataComparar.ano){
        verificador = MAIOR;
        } else if(dataInserida.mes < dataComparar.mes){
            verificador = MENOR;
            } else if (dataInserida.mes > dataComparar.mes) {
                verificador = MAIOR;
                } else if(dataInserida.dia < dataComparar.dia){
                    verificador = MENOR;
                    } else if(dataInserida.dia > dataComparar.dia){
                        verificador = MAIOR;
                        } else {
                            verificador = IGUAL;
                        }
             
    
    return verificador;
}
int verifica_se_utilizador_pertence_escola(t_principal * s_principal, int id_utilizador, int id_escola){ // 12 linhas
    int index, sucesso;
    for(index = 0; index < MAX_UTILIZADOR; index++){                                // vai à procura do utilizador com o id inserido no parametro
        if(s_principal->v_utilizador[index].id_utilizador == id_utilizador){        // se achar esse utilizador
            if (s_principal->v_utilizador[index].id_escola == id_escola){           // verifica se o id_escola inserido como parametro é o mesmo do utilizador
                sucesso = SUCESSO;                                                  // caso seja, define que teve sucesso
            }
            else {
                sucesso = INSUCESSO;                                                // senao, define que nao teve sucesso
            }
        }
    }
    return sucesso;
}
int verifica_tipo_utilizador(t_principal * s_principal, int id_utilizador, char tipoUtilizador[]){ // 11 linhas
    int index, sucesso;
    for(index = 0; index < MAX_UTILIZADOR; index++){                                // vai à procura do utilizador com o id inserido no parametro
        if(s_principal->v_utilizador[index].id_utilizador == id_utilizador){        // se achar esse utilizador
            if (strcmp(s_principal->v_utilizador[index].tipo_utilizador, tipoUtilizador) == 0){           // verifica se o id_escola inserido como parametro é o mesmo do utilizador
                sucesso = SUCESSO;                                                  // caso seja, define que teve sucesso
            }else {
                sucesso = INSUCESSO;                                                // senao, define que nao teve sucesso
            }
        }
    }
    return sucesso;
}
int verifica_mes(int mes){ // 22 linhas
    int max_dia;
    switch(mes){
        case JANEIRO:
        case MARCO:
        case MAIO:
        case JULHO:
        case AGOSTO:
        case OUTUBRO:
        case DEZEMBRO:
            max_dia = 31;
            break;
        case ABRIL:
        case JUNHO:
        case SETEMBRO:
        case NOVEMBRO:
            max_dia = 30;
            break;
        case FEVEREIRO:
            max_dia = 28;
            break;
    }
    return max_dia;
}
int diferenca_caracteres(char string1[], char string2[]){ // 10 linhas
    int numero_char_diferente = 0, tamanho, index = 0;
    for(int i = 0; i < 10; i++){
        if(string1[i] != '\0'){tamanho++;} // obtem o tamanho da string
    }
    for(index = 0; index < tamanho; index++){   // vai por um ciclo que adiciona se o caracter da string1 for diferente do string2
        if(string1[index] != string2[index]){
            numero_char_diferente++;
        }
    }
    return numero_char_diferente;
}
int validar_valor(t_principal * s_principal, t_transacao v_transacao){ // 16 linhas
    int sucesso = SUCESSO;
    for(int i = 0; i < MAX_UTILIZADOR; i++){
        if(s_principal->v_utilizador[i].id_utilizador == v_transacao.id_utilizador){
            if(strcmp(v_transacao.tipo_transacao, "Pagamento") == 0){
                if(s_principal->v_utilizador[i].saldo >= v_transacao.valor){
                    s_principal->v_utilizador[i].saldo -= v_transacao.valor;
                } else {
                    printf("\n\nO utilizador nao tem saldo suficiente para a transacao!");
                    sucesso = INSUCESSO;
                }
            } else if(strcmp(v_transacao.tipo_transacao, "Carregamento") == 0){
                s_principal->v_utilizador[i].saldo += v_transacao.valor;
            }
        }
    }
    return sucesso;
}
//******************************
//*  FIM CALCULOS E PESQUISA   *
//******************************




