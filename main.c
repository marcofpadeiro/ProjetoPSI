#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESCOLA 5
#define MAX_UTILIZADOR 200
#define MAX_TRANSACAO 5000
#define SUCESSO 0
#define INSUCESSO 1
#define ESCOLA 1
#define UTILIZADOR 2
#define TRANSACAO 3

#define TAMANHO_NOME_ESCOLA 60
#define TAMANHO_TIPO_TRANSACAO 30
#define TAMANHO_ABREVIATURA 10
#define TAMANHO_CAMPUS 20
#define TAMANHO_LOCALIZACAO 30
#define TAMANHO_NOME_UTILIZADOR 30
#define TAMANHO_TIPO_UTILIZADOR 20
#define TAMANHO_EMAIL 30
#define BASE_DADOS_CHEIA -1

#define IGUAL 0
#define MAIOR 1
#define MENOR 2

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

void ler_ficheiro(t_principal * s_principal);
void gravar_no_ficheiro(t_principal* s_principal);
void limpa_array(t_principal* s_principal, int baseDados);
int obter_input(int minimo, int maximo, char texto1[], char texto2[], char texto3[], char texto4[], char texto5[], char texto6[]);
void limpa_elemento(t_principal* s_principal, int index, int baseDados);
void registar_informacao(t_principal* s_principal, int index, int baseDados);
void registar_escola(t_principal* s_principal, int index);
void registar_utilizador(t_principal* s_principal, int index);
void registar_transacao(t_principal* s_principal, int index);
void consultar_informacao(t_principal* s_principal, int baseDados);
void apresentar_dados(t_principal* s_principal, int index, int baseDados);
void cabecalho_apresentar_dados(int index);
int procurar_elemento_vazio(t_principal* s_principal, int baseDados);
int pesquisa_elemento(t_principal* s_principal, int identificador, int baseDados);
int selecinar_base_dados();
int conta_caracteres_string(char string[], int tamanho);
int conta_caracteres_numero(int numero);
void calcula_numero_de_espacos(char espacos[], int numero_espacos_normalmente, int tamanho_palavra);
int verificar_se_existe(t_principal * s_principal, int index, int baseDados);
void limite_base_dados(t_principal* s_principal, int baseDados);
void menu_principal(t_principal* s_principal);
void menu_registar(t_principal* s_principal, int baseDados);
void menu_consultar(t_principal* s_principal, int baseDados);
void alterar_elemento(t_principal* s_principal, int index, int baseDados);
void apagar_elemento(t_principal* s_principal, int index, int baseDados);
void menu_estatisticas(t_principal* s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
void menu_sair(t_principal* s_principal);
float calcula_percentagem_faturado_por_escola(t_principal * s_principal, int id_escola, int objetivo, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]);
int verifica_se_utilizador_pertence_escola(t_principal * s_principal, int id_utilizador, int id_escola);
int receber_index();
void escrever_filtos(t_principal *s_principal);
void obter_data(int * dia, int * mes, int * ano);
void obter_hora(int * hora, int * minuto, int * segundo);
int verifica_mes(int mes);
int verifica_tipo_utilizador(t_principal * s_principal, int id_utilizador, char tipoUtilizador[]);
int verifica_se_data_esta_dentro(t_data dataInserida,t_data dataComparar);
void obter_int(int * numero, int minimo, int maximo);

void main() {
    t_principal s_principal;
    limpa_array(&s_principal, 0);
    system("cls");
    ler_ficheiro(&s_principal);
    menu_principal(&s_principal);
}
void ler_ficheiro(t_principal* s_principal) {
    FILE* ficheiro;
    ficheiro = fopen("baseDados.bin", "rb");
    if (ficheiro == NULL) {
        printf("!!!AVISO!!! Ficheiro nao encontrado!!\n\n");
    }
    else {
        fread(s_principal, sizeof(t_principal), 1, ficheiro);
    }
    fflush(ficheiro);
    fclose(ficheiro);
}
void gravar_no_ficheiro(t_principal* s_principal) {
    FILE* ficheiro;
    ficheiro = fopen("BaseDados.bin", "wb");
    fwrite(s_principal, sizeof(t_principal), 1, ficheiro);
    fflush(ficheiro);
    fclose(ficheiro);
}
void limpa_array(t_principal* s_principal, int baseDados) {
    int index;
    switch(baseDados){
        case ESCOLA:
            for (index = 0; index < MAX_ESCOLA; index++) {
                limpa_elemento(s_principal, index, ESCOLA);
            }
            break;
        case UTILIZADOR:
            for (index = 0; index < MAX_UTILIZADOR; index++) {
                limpa_elemento(s_principal, index, UTILIZADOR);
            }
            break;
        case TRANSACAO:
            for (index = 0; index < MAX_TRANSACAO; index++) {
                limpa_elemento(s_principal, index, TRANSACAO);
            }
            break;
        default: 
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
void limpa_elemento(t_principal* s_principal, int index, int baseDados) { 
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

int selecinar_base_dados() {
    int opcao;
    do {
        system("cls");
        opcao = obter_input(0, 3, "Selecione a base de dados que deseja manipular:\n\n", "1 - Escolas\n", "2 - Utilizadores\n", "3 - Transacoes\n", "0 - Voltar atras", "\0");
        
    } while (opcao < 0 && opcao > 3);
    return opcao;
}
int procurar_elemento_vazio(t_principal* s_principal, int baseDados) {
     int index = 0;
    switch (baseDados) {
        case ESCOLA:
            for (index = 0; index < MAX_ESCOLA; index++) {
                if (s_principal->v_escola[index].id_escola == 0) {
                    return index;
                } 
            }
            break;
        case UTILIZADOR:
            for (index = 0; index < MAX_UTILIZADOR; index++) {
                if (s_principal->v_utilizador[index].id_utilizador == 0) {
                    return index;
                } 
            }
            break;
        case TRANSACAO:
            for (int index = 0; index < MAX_TRANSACAO; index++) {
                if (s_principal->v_transacao[index].id_transacao == 0) {
                    return index;
                } 
            }
            break;
    }
    return BASE_DADOS_CHEIA;
}
void limite_base_dados(t_principal* s_principal, int baseDados){
    int opcao = 0;
    opcao = obter_input(0, 2, "A base de dados atingiu o limite!!!\n\n", "1 - Apagar elementos\n", "2 - Editar elementos\n", "0 - Voltar atras", "\0", "\0");
    switch(opcao){
        case 1: apagar_elemento(s_principal, receber_index(), baseDados); break;
        case 2: alterar_elemento(s_principal, receber_index(), baseDados); break;
        case 0: menu_principal(s_principal); break;
    }
}
void registar_informacao(t_principal* s_principal, int index, int baseDados) {
    if(index != BASE_DADOS_CHEIA){
        switch (baseDados) {
            case ESCOLA: registar_escola(s_principal, index); break;
            case UTILIZADOR: registar_utilizador(s_principal, index); break;
            case TRANSACAO: registar_transacao(s_principal, index); break;
        }
    } else {
        limite_base_dados(s_principal, baseDados);
    }
}
void registar_escola(t_principal* s_principal, int index) {
    int validacao_escolas[5];                
    t_escola v_aux_escola[MAX_ESCOLA]; 

    /* VERRY BIG PROBLEM INSERTING DATA MAN */
    do {
        printf("Identificador Escola: ");   
        scanf("%d", &v_aux_escola[index].id_escola);
        validacao_escolas[0] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[0] == INSUCESSO) { printf("\nEste numero precisa de ser de 1 a 5!\n\n");}
    } while (validacao_escolas[0] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Nome Escola: ");
        scanf("%[^\n]s", v_aux_escola[index].nome_escola);
        validacao_escolas[1] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[1] == INSUCESSO) { printf("\nO nome da escola tem que!\n\n");}
    } while (validacao_escolas[1] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Abreviatura: ");
        scanf("%[^\n]s", v_aux_escola[index].abreviatura);
        validacao_escolas[2] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[2] == INSUCESSO) { printf("\nA abreviatura pode ter no maximo 5 digitos!!\n\n");}
    } while (validacao_escolas[2] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Campus: ");
        scanf("%[^\n]s", v_aux_escola[index].campus);
        validacao_escolas[3] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[3] == INSUCESSO) { printf("\nEste campo precisa de ser no formato 'Campus *numero*'!!\n\n");}
    } while (validacao_escolas[3] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Localizacao: ");
        scanf("%[^\n]s", v_aux_escola[index].localizacao);
        validacao_escolas[4] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[4] == INSUCESSO) { printf("\nA localizacao tem que !!!\n\n");}
    } while (validacao_escolas[4] == INSUCESSO);
    if (validacao_escolas[0] == SUCESSO && validacao_escolas[1] == SUCESSO && validacao_escolas[2] == SUCESSO && validacao_escolas[3] == SUCESSO && validacao_escolas[4] == SUCESSO)
    {
        s_principal->v_escola[index].id_escola = v_aux_escola[index].id_escola;
        strcpy(s_principal->v_escola[index].nome_escola, v_aux_escola[index].nome_escola);
        strcpy(s_principal->v_escola[index].abreviatura, v_aux_escola[index].abreviatura);
        strcpy(s_principal->v_escola[index].campus, v_aux_escola[index].campus);
        strcpy(s_principal->v_escola[index].localizacao, v_aux_escola[index].localizacao);   
    }
}
void registar_utilizador(t_principal* s_principal, int index) {
    int validacao_utilizadores[7];
    t_utilizador v_aux_utilizador[MAX_UTILIZADOR];
    fflush(stdin);
    do {
        printf("Identificador Utilizador: ");
        scanf("%d", &v_aux_utilizador[index].id_utilizador);
        validacao_utilizadores[0] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[0] == INSUCESSO) { printf("\nEste numero precisa de ser de 1 a 2000!\n\n");}
    } while (validacao_utilizadores[0] == INSUCESSO);
    do {
        printf("Identificador Escola: ");
        scanf("%d", &v_aux_utilizador[index].id_escola);
        validacao_utilizadores[1] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[1] == INSUCESSO) { printf("\nEste numero precisa de ser de 1 a 5!\n\n");}
    } while (validacao_utilizadores[1] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Nome Utilizador: ");
        scanf("%[^\n]s", v_aux_utilizador[index].nome_utilizador);
        validacao_utilizadores[2] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[2] == INSUCESSO) { printf("\nO nome do utilizador tem que !\n\n");}
    } while (validacao_utilizadores[2] == INSUCESSO);
    do {
        printf("NIF: ");
        scanf("%d", &v_aux_utilizador[index].NIF);
        validacao_utilizadores[3] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[3] == INSUCESSO) { printf("\nO NIF tem que ter 9 caracteres!\n\n");}
    } while (validacao_utilizadores[3] == INSUCESSO);
    do{
        fflush(stdin);
        printf("Tipo Utilizador: ");
        scanf("%s", v_aux_utilizador[index].tipo_utilizador);
        validacao_utilizadores[4] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[4] == INSUCESSO) { printf("\nO tipo de utilizador tem que ser 'Docente', 'Estudante' ou 'Funcionario'!\n\n");}
    } while (validacao_utilizadores[4] == INSUCESSO);
    do {
        fflush(stdin);
        printf("Email: ");
        scanf("%s", v_aux_utilizador[index].email);
        validacao_utilizadores[5] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[5] == INSUCESSO) { printf("\nO email tem que ser valido! Tem que ter um '@' e nao pode ter caracteres especiais [#, !, $, &, ...]!!\n\n");}
    } while (validacao_utilizadores[5] == INSUCESSO);
    do {
        printf("Saldo: ");
        scanf("%f", &v_aux_utilizador[index].saldo);
        validacao_utilizadores[6] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[6] == INSUCESSO) { printf("\nO saldo tem que ser positivo !!\n\n");}
    } while (validacao_utilizadores[6] == INSUCESSO);
    if (validacao_utilizadores[0] == SUCESSO && validacao_utilizadores[1] == SUCESSO && validacao_utilizadores[2] == SUCESSO && validacao_utilizadores[3] == SUCESSO && validacao_utilizadores[4] == SUCESSO && validacao_utilizadores[5] == SUCESSO && validacao_utilizadores[6] == SUCESSO)
    {
        s_principal->v_utilizador[index].id_utilizador = v_aux_utilizador[index].id_utilizador;
        s_principal->v_utilizador[index].id_escola = v_aux_utilizador[index].id_escola;
        strcpy(s_principal->v_utilizador[index].nome_utilizador, v_aux_utilizador[index].nome_utilizador);
        s_principal->v_utilizador[index].NIF = v_aux_utilizador[index].NIF;
        strcpy(s_principal->v_utilizador[index].tipo_utilizador, v_aux_utilizador[index].tipo_utilizador);
        strcpy(s_principal->v_utilizador[index].email, v_aux_utilizador[index].email);
        s_principal->v_utilizador[index].saldo = v_aux_utilizador[index].saldo;
    }
}
void registar_transacao(t_principal* s_principal, int index) {
    int validacao_transacoes[6];
    t_transacao v_aux_transacao[MAX_TRANSACAO];
    fflush(stdin);
    printf("Identificador Transacao: ");
    obter_int(&v_aux_transacao[index].id_transacao, 0, 5000);
    printf("Identificador Utilizador: ");
    obter_int(&v_aux_transacao[index].id_utilizador, 0, 99999999);
    do {
        printf("Tipo Transacao: ");
        scanf("%s", &v_aux_transacao[index].tipo_transacao);
        validacao_transacoes[3] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[3] == INSUCESSO) { printf("\nO valor da transacao tem de ser positivo!!\n\n");}
    } while (validacao_transacoes[3] == INSUCESSO);
    do {
        printf("Valor Transacao: ");
        scanf("%f", &v_aux_transacao[index].valor);
        validacao_transacoes[3] = SUCESSO; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[3] == INSUCESSO) { printf("\nO valor da transacao tem de ser positivo!!\n\n");}
    } while (validacao_transacoes[3] == INSUCESSO);
    printf("Data (FORMATO dd/mm/yyyy): ");
    obter_data(&v_aux_transacao[index].data.dia, &v_aux_transacao[index].data.mes, &v_aux_transacao[index].data.ano);    
    printf("Hora (FORMATO hh:mm:ss): ");
    obter_hora(&v_aux_transacao[index].hora.hora, &v_aux_transacao[index].hora.minuto, &v_aux_transacao[index].hora.segundo);   

    if (validacao_transacoes[3] == SUCESSO)
    {
        s_principal->v_transacao[index].id_transacao = v_aux_transacao[index].id_transacao;
        s_principal->v_transacao[index].id_utilizador = v_aux_transacao[index].id_utilizador;
        strcpy(s_principal->v_transacao[index].tipo_transacao, v_aux_transacao[index].tipo_transacao);
        s_principal->v_transacao[index].valor = v_aux_transacao[index].valor;
        s_principal->v_transacao[index].data = (t_data){ v_aux_transacao[index].data.dia, v_aux_transacao[index].data.mes, v_aux_transacao[index].data.ano };
        s_principal->v_transacao[index].hora = (t_hora){ v_aux_transacao[index].hora.hora, v_aux_transacao[index].hora.minuto, v_aux_transacao[index].hora.segundo };
    }
}

void consultar_informacao(t_principal* s_principal, int baseDados) {
    int index = 0;
    switch (baseDados) {
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
int conta_caracteres_numero(int numero){     
    int count = 1;
    while (numero > 9) {                     
        numero = numero / 10;
        count++;
    }
    return count;
}
void calcula_numero_de_espacos(char espacos[], int numero_espacos_normalmente, int tamanho_palavra){
    int index = 0;
    char auxiliar[100];
    for(index = 0; index < 100; index++){
        espacos[index] = '\0';
    }
    for(index = 0; index < numero_espacos_normalmente - tamanho_palavra; index++){
        espacos[index] = ' ';
    }
    
}
void cabecalho_apresentar_dados(int baseDados){
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
void apresentar_dados(t_principal* s_principal, int index, int baseDados){  
    char espacos[100];
    switch(baseDados){
        case ESCOLA: 
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
            printf("%s\n", v_aux_escola.localizacao);  break;
        case UTILIZADOR: 
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
            printf("%.2f\n", v_aux_utilizador.saldo); break;
        case TRANSACAO: 
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
            calcula_numero_de_espacos(espacos, 15, conta_caracteres_numero(v_aux_transacao.data.dia) + conta_caracteres_numero(v_aux_transacao.data.mes) + conta_caracteres_numero(v_aux_transacao.data.ano) + 2); 
            printf("%02d/%02d/%04d%s", v_aux_transacao.data.dia, v_aux_transacao.data.mes, v_aux_transacao.data.ano, espacos);
            printf("%02d:%02d:%02d\n", v_aux_transacao.hora.hora, v_aux_transacao.hora.minuto, v_aux_transacao.hora.segundo);  break;
    }
}

void menu_principal(t_principal* s_principal) {
    system("cls");
    int opcao = 0, index; float total_faturado; char espacos[100];
    t_data dataInicial = {0, 0, 0}, dataFinal = {0, 0, 0};
    dataInicial.dia = 0;
    
    printf(" #  | ID Escola | Nome Escola                                       | Total faturado |\n");
    printf("--------------------------------------------------------------------------------------\n");
    for(index = 0; index < MAX_ESCOLA; index++){
        if(s_principal->v_escola[index].id_escola != 0){
            total_faturado = calcula_percentagem_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, 2, dataInicial, dataFinal, "\0");
            calcula_numero_de_espacos(espacos, 5, conta_caracteres_numero(index));
            printf(" %d%s", index, espacos);
            calcula_numero_de_espacos(espacos, 12, conta_caracteres_numero(s_principal->v_escola[index].id_escola));
            printf("%d%s", s_principal->v_escola[index].id_escola, espacos);
            calcula_numero_de_espacos(espacos, 52, strlen(s_principal->v_escola[index].nome_escola));
            printf("%s%s", s_principal->v_escola[index].nome_escola, espacos);
            printf("%.2f\n", total_faturado);
        }
    }
    opcao = obter_input(0, 4, "\n\nMenu Principal\n\n", "1 - Registar informacao\n", "2 - Consultar informacao\n", "3 - Estatisticas\n", "4 - Gravar no ficheiro\n", "0 - Sair da aplicacao");
    switch (opcao) {
        case 1: menu_registar(s_principal, selecinar_base_dados()); break;
        case 2: menu_consultar(s_principal, selecinar_base_dados()); break;
        case 3: menu_estatisticas(s_principal, dataInicial, dataFinal, "\0"); break;
        case 4: gravar_no_ficheiro(s_principal); menu_principal(s_principal); break;
        case 0: menu_sair(s_principal); break;
        default: menu_principal(s_principal); break;
    }
}
int obter_input(int minimo, int maximo, char texto1[], char texto2[], char texto3[], char texto4[], char texto5[], char texto6[]){
    char textos[6][100];          // criação de array para facilitar o uso de ciclos
    int escrever = SUCESSO, opcao = -1, index = 0;
    char opcao_string[6];
    strcpy(textos[0], texto1);   // atribuição do valor dos parametros ao array
    strcpy(textos[1], texto2);
    strcpy(textos[2], texto3);
    strcpy(textos[3], texto4);
    strcpy(textos[4], texto5);
    strcpy(textos[5], texto6);
                                                           // enquanto o input nao for valido
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
        
        scanf("%d", &opcao);                              // recebe uma string
        if(opcao < minimo || opcao > maximo){
            printf("Tem de ser entre %d e %d!!", minimo, maximo);
        }
        

    } while(opcao < minimo || opcao > maximo);                  // valores que devem ser introduzidos pelo utilizador
    return opcao;                                               // devolve a opcao escolhida
}
void menu_registar(t_principal* s_principal, int baseDados) {
    int opcao = 0, index = procurar_elemento_vazio(s_principal, baseDados);
    char titulo[13];
    switch(baseDados){
        case ESCOLA: strcpy(titulo, "Escolas"); break;
        case UTILIZADOR: strcpy(titulo, "Utilizadores"); break;
        case TRANSACAO: strcpy(titulo, "Transacoes"); break;
    }
    system("cls");
    printf("Menu Registar - %s\n", titulo);
    printf("-----------------------------------------\n");
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){
        registar_informacao(s_principal, index, baseDados);
        printf("\n");
        cabecalho_apresentar_dados(baseDados);
        apresentar_dados(s_principal, index, baseDados);
        opcao = obter_input(1, 3, "\nDeseja introduzir mais elementos?", "\n1 - Sim", "\n2 - Nao", "\n3 - Mudar base de dados", "\0", "\0");
        switch (opcao){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: menu_principal(s_principal); break;
            case 3: menu_registar(s_principal, selecinar_base_dados()); break;
        }
    } else { menu_principal(s_principal); }
}
void menu_consultar(t_principal* s_principal, int baseDados) {
    int opcao = 0, max_elementos = 0, i = 0, index = procurar_elemento_vazio(s_principal, baseDados);
    char titulo[13];
    switch(baseDados){
        case ESCOLA: strcpy(titulo, "Escolas"); max_elementos = MAX_ESCOLA; break;
        case UTILIZADOR: strcpy(titulo, "Utilizadores"); max_elementos = MAX_UTILIZADOR; break;
        case TRANSACAO: strcpy(titulo, "Transacoes"); max_elementos = MAX_TRANSACAO; break;
    }
    system("cls");
    printf("Menu Consultar - %s\n\n", titulo);
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){
        cabecalho_apresentar_dados(baseDados);
        consultar_informacao(s_principal, baseDados);
        opcao = obter_input(0, 5, "\n\n1 - Procurar elemento", "\n2 - Apagar elemento", "\n3 - Alterar elemento", "\n4 - Mudar base de dados", "\n5 - Limpar base de dados", "\n0 - Voltar Atras");
        switch (opcao){
            case 1: /*procurar_elemento(s_principal, baseDados);*/ break;
            case 2: apagar_elemento(s_principal, receber_index(), baseDados); break;
            case 3: alterar_elemento(s_principal, receber_index(), baseDados); break;
            case 4: menu_consultar(s_principal, selecinar_base_dados()); break;
            case 5: limpa_array(s_principal, baseDados);  menu_consultar(s_principal, baseDados);break;
            case 0: menu_principal(s_principal); break;
        }
    } else { menu_principal(s_principal); }
}
int receber_index(){
    int index = 0;
    printf("\n\n    INDEX (#)  --->   ");
    scanf("%d", &index);
    return index;    
}
void apagar_elemento(t_principal* s_principal, int index, int baseDados){
    system("cls");
    if(verificar_se_existe(s_principal, index, baseDados) == 1){
        printf("Tem a certeza que quer apagar este elemento?\n\n\n");
        cabecalho_apresentar_dados(baseDados);
        apresentar_dados(s_principal, index, baseDados);
        int opcao = obter_input(0, 3, "\n\n1 - Sim", "\n2 - Nao", "\n3 - Escolher outro elemento", "\n0 - Voltar atras", "\0", "\0");
        switch(opcao){
            case 1:  // Sim
                limpa_elemento(s_principal, index, baseDados);
                menu_consultar(s_principal, baseDados);
                break;
            case 2: menu_consultar(s_principal, baseDados); // Nao
                break;
            case 3: apagar_elemento(s_principal, receber_index(), baseDados); break; // Escolher outro elemento
                break;
            case 0: menu_principal(s_principal); break;// Voltar atras
        }
    } else{
        printf("\nO elemento com index %d nao existe na nossa base de dados!\n", index);
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento\n", "2 - Escolher outro elemento\n", "0 - Voltar atras\n", "\0", "\0", "\0");
        switch(opcao_1){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: alterar_elemento(s_principal, receber_index(), baseDados);
            case 0: menu_consultar(s_principal, baseDados); break;
        }
    }
}
void alterar_elemento(t_principal* s_principal, int index, int baseDados) {
    system("cls");
    if(verificar_se_existe(s_principal, index, baseDados) == 1){
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
    } else{
        printf("\nO elemento com index %d nao existe na nossa base de dados!\n", index);
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento\n", "2 - Escolher outro elemento\n", "0 - Voltar atras", "\0", "\0", "\0");
        switch(opcao_1){
            case 1: menu_registar(s_principal, baseDados); break;
            case 2: alterar_elemento(s_principal, receber_index(), baseDados);
            case 0: menu_consultar(s_principal, baseDados); break;
        }
    }
    
}
int verificar_se_existe(t_principal * s_principal, int index, int baseDados){
    int indexFor = 0, existe = 0;
    switch(baseDados){
        case ESCOLA:
            for(indexFor = 0; indexFor < MAX_ESCOLA; indexFor++){
                existe = s_principal->v_escola[index].id_escola != 0 ? 1 : 0;
            }
            break;
        case UTILIZADOR:
            for(indexFor = 0; indexFor < MAX_UTILIZADOR; indexFor++){
                existe = s_principal->v_utilizador[index].id_utilizador != 0 ? 1 : 0;
            }
            break;
        case TRANSACAO:
            for(indexFor = 0; indexFor < MAX_TRANSACAO; indexFor++){
                existe = s_principal->v_transacao[index].id_transacao != 0 ? 1 : 0;
            }
    }
    return existe;
}
int pesquisa_elemento(t_principal* s_principal, int identificador, int baseDados){
    /*int index = 0;
    switch(baseDados){
        case ESCOLA:
            for(index = 0; index < MAX_ESCOLA; index++){
                if(s_principal->v_escola[index].id_escola == identificador){
                    return index;
                }
            }
            break;
        case UTILIZADOR:
            for(index = 0; index < MAX_UTILIZADOR; index++){
                if(s_principal->v_utilizador[index].id_utilizador == identificador){
                    return index;
                }
            }
            break;
        case TRANSACAO:
            for(index = 0; index < MAX_TRANSACAO; index++){
                if(s_principal->v_transacao[index].id_transacao == identificador){
                    return index;
                }
            }
    }*/
}
void menu_estatisticas(t_principal* s_principal, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){
    system("cls");
    int index = 0, opcao;
    float total_faturado;
    int total_transacoes_percentagem, total_transacoes;
    char espacos[100];
    printf("Visualizar Estatisticas\n\n");
    if(dataInicial.dia != 0){printf("Data Inicial: %d/%d/%d\n", dataInicial.dia, dataInicial.mes, dataInicial.ano);} 
    else {printf("Data Inicial: \n");}
    if(dataFinal.dia != 0){printf("Data Final: %d/%d/%d\n", dataFinal.dia, dataFinal.mes, dataFinal.ano);}
    else {printf("Data Final: \n");}
    printf("Tipo de utilizador: %s\n\n", tipoUtilizador);
    printf(" #  | ID Escola | Nome Escola                                       | Total faturado |  N%c pagamentos  |  %% pagamentos |\n", 248);
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    for(index = 0; index < MAX_ESCOLA; index++){ 
        if(s_principal->v_escola[index].id_escola != 0){
            total_faturado = calcula_percentagem_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, 2, dataInicial, dataFinal, tipoUtilizador);
            total_transacoes_percentagem = (int)calcula_percentagem_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, 0, dataInicial, dataFinal, tipoUtilizador);
            total_transacoes = (int)calcula_percentagem_faturado_por_escola(s_principal, s_principal->v_escola[index].id_escola, 1, dataInicial, dataFinal, tipoUtilizador);
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
    }
    opcao = obter_input(0, 1, "\n\n\n1 - Filtros","\n0 - Voltar atras", "\0", "\0", "\0", "\0");
    switch(opcao){
        case 1: escrever_filtos(s_principal); break;
        case 0: menu_principal(s_principal); break;
        default: menu_principal(s_principal); 
    }
}
void escrever_filtos(t_principal *s_principal){
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
void obter_data(int * dia, int * mes, int * ano){
    int max_dia = 0, sucesso = INSUCESSO; char stringData[15]; t_data auxiliar;
    do{
        scanf("%s", stringData);
        if(stringData[2] == '/' && stringData[5] == '/'){
            if((stringData[0] >= '0' && stringData[0] <= '9') && (stringData[1] >= '0' && stringData[1] <= '9')){
                if((stringData[3] >= '0' && stringData[3] <= '9') && (stringData[4] >= '0' && stringData[4] <= '9')){
                    if((stringData[6] >= '0' && stringData[6] <= '9') && (stringData[7] >= '0' && stringData[7] <= '9') && (stringData[8] >= '0' && stringData[8] <= '9') && stringData[9] >= '0' && stringData[9] <= '9'){
                        auxiliar.dia = ((stringData[0] - '0') * 10) + (stringData[1] - '0');
                        auxiliar.mes = ((stringData[3] - '0') * 10) + (stringData[4] - '0');
                        auxiliar.ano = (stringData[6] - '0') * 1000 + (stringData[7] - '0') * 100 + (stringData[8] -'0') * 10 + (stringData[9] - '0');
                        if(auxiliar.ano >= 1900 && auxiliar.ano <= 2022){
                            if(auxiliar.mes >= 1 && auxiliar.mes <= 12){
                                max_dia = verifica_mes(auxiliar.mes);
                                if(auxiliar.dia >= 1 && auxiliar.dia <= max_dia){
                                    *dia = auxiliar.dia;
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
void obter_hora(int * hora, int * minuto, int * segundo){
    int sucesso = INSUCESSO; char stringData[15]; t_hora auxiliar;
    do{
        scanf("%s", stringData);
        if(stringData[2] == ':' && stringData[5] == ':'){
            if((stringData[0] >= '0' && stringData[0] <= '9') && (stringData[1] >= '0' && stringData[1] <= '9')){
                if((stringData[3] >= '0' && stringData[3] <= '9') && (stringData[4] >= '0' && stringData[4] <= '9')){
                    if((stringData[6] >= '0' && stringData[6] <= '9') && (stringData[7] >= '0' && stringData[7] <= '9')){
                        auxiliar.hora = ((stringData[0] - '0') * 10) + (stringData[1] - '0');
                        auxiliar.minuto = ((stringData[3] - '0') * 10) + (stringData[4] - '0');
                        auxiliar.segundo = (stringData[6] - '0') * 10 + (stringData[7] - '0');
                        if(auxiliar.segundo >= 0 && auxiliar.segundo <= 59){
                            if(auxiliar.minuto >= 0 && auxiliar.minuto <= 59){
                                if(auxiliar.hora >= 0 && auxiliar.hora <= 23){
                                    *hora = auxiliar.hora;
                                    *minuto = auxiliar.minuto;
                                    *segundo = auxiliar.segundo;
                                    sucesso = SUCESSO;
                                } else { printf("\nHora invalida! Tem de ser entre 00 e 23!\n\nHora (FORMATO hh:mm:ss): ");}
                            } else { printf("\nMinutos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                        } else { printf("\nSegundos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                    }else { printf("\nSegundos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
                } else { printf("\nMinutos invalidos! Tem de ser entre 0 e 59!\n\nHora (FORMATO hh:mm:ss): ");}
            } else { printf("\nHora invalida! Tem de ser entre 0 e 23!\n\nHora (FORMATO hh:mm:ss): ");}
        } else { printf("\nFormato de hora invalido  (FORMATO hh:mm:ss)\n\nHora (FORMATO hh:mm:ss): ");}
    } while (sucesso == INSUCESSO);
}
void obter_int(int * numero, int minimo, int maximo){
    int auxiliar = 0;
    do{
        scanf("%d", &auxiliar);
        if(auxiliar >= maximo || auxiliar < minimo){
            printf("\n\nValor tem de ser entre %d e %d!\n\n> ", minimo, maximo);
        }
    } while(auxiliar > maximo || auxiliar < minimo);
    *numero = auxiliar;
}
int verifica_mes(int mes){
    int max_dia;
    switch(mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            max_dia = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_dia = 30;
            break;
        case 2:
            max_dia = 28;
            break;
    }
    return max_dia;
}
float calcula_percentagem_faturado_por_escola(t_principal * s_principal, int id_escola, int objetivo, t_data dataInicial, t_data dataFinal, char tipoUtilizador[]){
    int percentagem_total_faturado = 0, total_transacoes = 0, transacoes_escola = 0;
    int index;
    float total_faturado;
    for(index = 0; index < MAX_TRANSACAO; index++) { // vai por todas as transacoes
        if(s_principal->v_transacao[index].id_transacao != 0) { // se nao estiver vazio
            if(strcmp(s_principal->v_transacao[index].tipo_transacao, "Pagamento") == 0){
               // if(dataInicial.dia == 0){
                    total_transacoes++;
                    if(verifica_se_utilizador_pertence_escola(s_principal, s_principal->v_transacao[index].id_utilizador, id_escola) == SUCESSO){ 
                        transacoes_escola++;
                        total_faturado += s_principal->v_transacao[index].valor;
                    } 
                /*} else {
                    if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataInicial) == MAIOR){
                        if(verifica_se_data_esta_dentro(s_principal->v_transacao[index].data, dataInicial) == MENOR){
                            if(verifica_tipo_utilizador(s_principal, s_principal->v_transacao[index].id_utilizador, tipoUtilizador) == 0){
                                total_transacoes++;
                                if(verifica_se_utilizador_pertence_escola(s_principal, s_principal->v_transacao[index].id_utilizador, id_escola) == SUCESSO){ 
                                    transacoes_escola++;
                                    total_faturado += s_principal->v_transacao[index].valor;
                                }  
                            }
                        }
                    } 
                }*/
            }
        }
    }
    percentagem_total_faturado = (transacoes_escola * 100) / total_transacoes;
    if(objetivo == 0){
        return (float)percentagem_total_faturado;  
    } else if (objetivo == 1){
        return (float)transacoes_escola;
    } else if (objetivo == 2){
        return total_faturado;
    }
    
}
int verifica_se_data_esta_dentro(t_data dataInserida,t_data dataComparar){
    int verificador = IGUAL;
    if(dataInserida.ano < dataComparar.ano){
        verificador = MENOR;
    } else if(dataInserida.ano > dataComparar.ano){
        verificador = MAIOR;
    } else {
        if(dataInserida.mes < dataComparar.mes){
            verificador = MENOR;
        } else if (dataInserida.mes > dataComparar.mes) {
            verificador = MAIOR;
        } else {
            if(dataInserida.dia < dataComparar.dia){
                verificador = MENOR;
            } else if(dataInserida.dia > dataComparar.dia){
                verificador = MAIOR;
            } else {
                verificador = IGUAL;
            }
        }
    }
    return verificador;
}
int verifica_se_utilizador_pertence_escola(t_principal * s_principal, int id_utilizador, int id_escola){
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
int verifica_tipo_utilizador(t_principal * s_principal, int id_utilizador, char tipoUtilizador[]){
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
void menu_sair(t_principal* s_principal) {
    int opcao = 0;
    system("cls");
    opcao = obter_input(0, 2, "Sair da aplicacao\n\n", "Deseja guardar a informacao registada?\n", "1 - Guardar\n", "2 - Nao guardar\n", "0 - Voltar atras", "\0");
    switch(opcao){
        case 1: 
            gravar_no_ficheiro(s_principal);
            system("cls");
            printf("Sair da Aplicacao\n\n");
            printf("Informacao guardada com sucesso!\n");
            printf("\n\nPrima qualquer tecla para sair da aplicacao");
            getchar();
            exit(1);
            break;
        case 2: exit(1); break;
        case 0: menu_principal(s_principal);
        default: menu_sair(s_principal);
    }
}