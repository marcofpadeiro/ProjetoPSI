#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESCOLA 5
#define MAX_UTILIZADOR 200
#define MAX_TRANSACAO 5000

#define ESCOLA 1
#define UTILIZADOR 2
#define TRANSACAO 3

#define TAMANHO_NOME_ESCOLA 60
#define TAMANHO_TIPO_TRANSACAO 10
#define TAMANHO_ABREVIATURA 5
#define TAMANHO_CAMPUS 10
#define TAMANHO_LOCALIZACAO 15
#define TAMANHO_NOME_UTILIZADOR 30
#define TAMANHO_TIPO_UTILIZADOR 10
#define TAMANHO_EMAIL 30


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
void limpa_array(t_principal* s_principal);
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
int verificar_se_existe(t_principal * s_principal, int index, int baseDados);
void limite_base_dados(t_principal* s_principal, int baseDados);
void menu_principal(t_principal* s_principal);
void menu_registar(t_principal* s_principal, int baseDados);
void menu_consultar(t_principal* s_principal, int baseDados);
void alterar_elemento(t_principal* s_principal, int index, int baseDados);
void apagar_elemento(t_principal* s_principal, int index, int baseDados);
void menu_estatisticas(t_principal* s_principal);
void menu_sair(t_principal* s_principal);
int receber_index();

void main() {
    t_principal s_principal;
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
void limpa_array(t_principal* s_principal) {
    int index;
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
    switch (baseDados) {
        case ESCOLA:
            for (int i = 0; i < MAX_ESCOLA; i++) {
                if (s_principal->v_escola[i].id_escola == 0) {
                    return i;
                }
            }
            break;
        case UTILIZADOR:
            for (int i = 0; i < MAX_UTILIZADOR; i++) {
                if (s_principal->v_utilizador[i].id_utilizador == 0) {
                    return i;
                }
            }
            break;
        case TRANSACAO:
            for (int i = 0; i < MAX_TRANSACAO; i++) {
                if (s_principal->v_transacao[i].id_transacao == 0) {
                    return i;
                }
            }
            break;
    }
}
void limite_base_dados(t_principal* s_principal, int baseDados){
    int opcao = 0;
    printf("A base de dados atingiu o limite\n\n");
    opcao = obter_input(0, 2, "\n\nA base de dados atingiu o limite!!!\n", "1 - Apagar elementos\n", "2 - Editar elementos\n", "0 - Voltar atras", "\0", "\0");
    switch(opcao){
        case 1: apagar_elemento(s_principal, receber_index(), baseDados); break;
        case 2: alterar_elemento(s_principal, receber_index(), baseDados); break;
        case 0: menu_principal(s_principal); break;
    }
}
void registar_informacao(t_principal* s_principal, int index, int baseDados) {
    switch (baseDados) {
        case ESCOLA:
            if(index <= MAX_ESCOLA){
                registar_escola(s_principal, index);
            } else {
                limite_base_dados(s_principal, baseDados);
            }
            break;
        case UTILIZADOR:
            if(index <= MAX_UTILIZADOR){
                registar_utilizador(s_principal, index);
            } else {
                limite_base_dados(s_principal, baseDados);
            }
           
            break;
        case TRANSACAO:
             if(index <= MAX_TRANSACAO){
                registar_transacao(s_principal, index);
            } else {
                limite_base_dados(s_principal, baseDados);
            }
            break;
    }
}
void registar_escola(t_principal* s_principal, int index) {
    int validacao_escolas[5];                
    t_escola v_aux_escola[MAX_ESCOLA]; 

    /* VERRY BIG PROBLEM INSERTING DATA MAN */
    do {
        printf("Identificador Escola: ");   
        scanf("%d", &v_aux_escola[index].id_escola);
        validacao_escolas[0] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[0] == 0) { printf("\nEste numero precisa de ser de 1 a 5!\n\n");}
    } while (validacao_escolas[0] == 0);
    do {
        fflush(stdin);
        printf("Nome Escola: ");
        scanf("%[^\n]s", v_aux_escola[index].nome_escola);
        validacao_escolas[1] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[1] == 0) { printf("\nO nome da escola tem que!\n\n");}
    } while (validacao_escolas[1] == 0);
    do {
        fflush(stdin);
        printf("Abreviatura: ");
        scanf("%[^\n]s", v_aux_escola[index].abreviatura);
        validacao_escolas[2] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[2] == 0) { printf("\nA abreviatura pode ter no maximo 5 digitos!!\n\n");}
    } while (validacao_escolas[2] == 0);
    do {
        fflush(stdin);
        printf("Campus: ");
        scanf("%[^\n]s", v_aux_escola[index].campus);
        validacao_escolas[3] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[3] == 0) { printf("\nEste campo precisa de ser no formato 'Campus *numero*'!!\n\n");}
    } while (validacao_escolas[3] == 0);
    do {
        fflush(stdin);
        printf("Localizacao: ");
        scanf("%[^\n]s", v_aux_escola[index].localizacao);
        validacao_escolas[4] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[4] == 0) { printf("\nA localizacao tem que !!!\n\n");}
    } while (validacao_escolas[4] == 0);
    if (validacao_escolas[0] == 1 && validacao_escolas[1] == 1 && validacao_escolas[2] == 1 && validacao_escolas[3] == 1 && validacao_escolas[4] == 1)
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
        validacao_utilizadores[0] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[0] == 0) { printf("\nEste numero precisa de ser de 1 a 2000!\n\n");}
    } while (validacao_utilizadores[0] == 0);
    do {
        printf("Identificador Escola: ");
        scanf("%d", &v_aux_utilizador[index].id_escola);
        validacao_utilizadores[1] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[1] == 0) { printf("\nEste numero precisa de ser de 1 a 5!\n\n");}
    } while (validacao_utilizadores[1] == 0);
    do {
        fflush(stdin);
        printf("Nome Utilizador: ");
        scanf("%[^\n]s", v_aux_utilizador[index].nome_utilizador);
        validacao_utilizadores[2] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[2] == 0) { printf("\nO nome do utilizador tem que !\n\n");}
    } while (validacao_utilizadores[2] == 0);
    do {
        printf("NIF: ");
        scanf("%d", &v_aux_utilizador[index].NIF);
        validacao_utilizadores[3] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[3] == 0) { printf("\nO NIF tem que ter 9 caracteres!\n\n");}
    } while (validacao_utilizadores[3] == 0);
    do{
        fflush(stdin);
        printf("Tipo Utilizador: ");
        scanf("%s", v_aux_utilizador[index].tipo_utilizador);
        validacao_utilizadores[4] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[4] == 0) { printf("\nO tipo de utilizador tem que ser 'Docente', 'Estudante' ou 'Funcionario'!\n\n");}
    } while (validacao_utilizadores[4] == 0);
    do {
        fflush(stdin);
        printf("Email: ");
        scanf("%s", v_aux_utilizador[index].email);
        validacao_utilizadores[5] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[5] == 0) { printf("\nO email tem que ser valido! Tem que ter um '@' e nao pode ter caracteres especiais [#, !, $, &, ...]!!\n\n");}
    } while (validacao_utilizadores[5] == 0);
    do {
        printf("Saldo: ");
        scanf("%f", &v_aux_utilizador[index].saldo);
        validacao_utilizadores[6] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[6] == 0) { printf("\nO saldo tem que ser positivo !!\n\n");}
    } while (validacao_utilizadores[6] == 0);
    if (validacao_utilizadores[0] == 1 && validacao_utilizadores[1] == 1 && validacao_utilizadores[2] == 1 && validacao_utilizadores[3] == 1 && validacao_utilizadores[4] == 1 && validacao_utilizadores[5] == 1 && validacao_utilizadores[6] == 1)
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
    do {
        printf("Identificador Transacao: ");
        scanf("%d", &v_aux_transacao[index].id_transacao);
        validacao_transacoes[0] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[0] == 0) { printf("\nO numero tem que ser entre 1 e 5000!!\n\n");}
    } while (validacao_transacoes[0] == 0);
    do {
        printf("Identificador Utilizador: ");
        scanf("%d", &v_aux_transacao[index].id_utilizador);
        validacao_transacoes[1] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[1] == 0) { printf("\nO numero tem que ser entre 1 e 2000!!\n\n");}
    } while (validacao_transacoes[1] == 0);
    do {
        fflush(stdin);
        printf("Tipo Transacao: ");
        scanf("%s", v_aux_transacao[index].tipo_transacao);
        validacao_transacoes[2] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[2] == 0) { printf("\nO tipo tem que ser 'Carregamento' ou 'Pagamento'!!\n\n");}
    } while (validacao_transacoes[2] == 0);
    do {
        printf("Valor Transacao: ");
        scanf("%d", &v_aux_transacao[index].valor);
        validacao_transacoes[3] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[3] == 0) { printf("\nO valor da transacao tem de ser positivo!!\n\n");}
    } while (validacao_transacoes[3] == 0);
    do {
        printf("Dia: ");
        scanf("%d", &v_aux_transacao[index].data.dia);
        printf("Mes: ");
        scanf("%d", &v_aux_transacao[index].data.mes);
        printf("Ano: ");
        scanf("%d", &v_aux_transacao[index].data.ano);
        validacao_transacoes[4] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[4] == 0) { printf("\nA data tem que ser valida!!\n\n");}
    } while (validacao_transacoes[4] == 0);
    do {
        printf("Hora: ");
        scanf("%d", &v_aux_transacao[index].hora.hora);
        printf("Minutos: ");
        scanf("%d", &v_aux_transacao[index].hora.minuto);
        printf("Segundos: ");
        scanf("%d", &v_aux_transacao[index].hora.segundo);
        validacao_transacoes[5] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_transacoes[5] == 0) { printf("\nA hora tem que ser valida!!\n\n");}
    } while (validacao_transacoes[5] == 0);
    if (validacao_transacoes[0] == 1 && validacao_transacoes[1] == 1 && validacao_transacoes[2] == 1 && validacao_transacoes[3] == 1 && validacao_transacoes[4] == 1 && validacao_transacoes[5] == 1)
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
            printf("Consulta de Escolas: \n\n");
            cabecalho_apresentar_dados(baseDados);
            for(index = 0; index < MAX_ESCOLA; index++){
                if(s_principal->v_escola[index].id_escola != 0){
                    apresentar_dados(s_principal, index, ESCOLA);
                }
            }
            break;
        case UTILIZADOR:
            printf("Consulta de Utilizadores: \n\n");
            cabecalho_apresentar_dados(baseDados);
            for(index = 0; index < MAX_UTILIZADOR; index++){
                if(s_principal->v_utilizador[index].id_utilizador != 0){
                    apresentar_dados(s_principal, index, UTILIZADOR);
                }
            }
            break;
        case TRANSACAO:
            printf("Consulta de Transacao: \n\n");
            cabecalho_apresentar_dados(baseDados);
            for(index = 0; index < MAX_TRANSACAO; index++){
                if(s_principal->v_transacao[index].id_transacao != 0){
                    apresentar_dados(s_principal, index, TRANSACAO);
                }
            }
            break;
    }
    
}
void cabecalho_apresentar_dados(int baseDados){
    switch(baseDados){
        case ESCOLA:
            printf("# | Identificador Escola | Nome Escola | Abreviatura | Campus | Localizacao\n");
            break;
        case UTILIZADOR:
            printf("# | Identificador Utilizador | Identificador Escola | Nome Utilizador | NIF | Tipo Utilizador | E-Mail | Saldo\n");
            break;
        case TRANSACAO:
            printf("# | Identificador Transacao | Identificador Utilizador | Tipo Transacao | Valor Transacao | Data | Hora\n");
            break;
    }
}
void apresentar_dados(t_principal* s_principal, int index, int baseDados){
    t_escola v_aux_escola = s_principal->v_escola[index];
    t_utilizador v_aux_utilizador = s_principal->v_utilizador[index];
    t_transacao v_aux_transacao = s_principal->v_transacao[index];
    switch(baseDados){
        case ESCOLA:
            printf("%d ; %d ; %s ; %s ; %s ; %s\n", index, v_aux_escola.id_escola, v_aux_escola.nome_escola, v_aux_escola.abreviatura, v_aux_escola.campus, v_aux_escola.localizacao);
            break;
        case UTILIZADOR:
            printf("%d ; %d ; %d ; %s ; %d ; %s ; %s ; %.2f\n", index, v_aux_utilizador.id_utilizador, v_aux_utilizador.id_escola, v_aux_utilizador.nome_utilizador, v_aux_utilizador.NIF, v_aux_utilizador.tipo_utilizador, v_aux_utilizador.email, v_aux_utilizador.saldo);
            break;
        case TRANSACAO:
            printf("%d ; %d ; %d ; %s ; %.2f ; %d/%d/%d ; %d:%d:%d\n", index, v_aux_transacao.id_transacao, v_aux_transacao.id_utilizador, v_aux_transacao.tipo_transacao, v_aux_transacao.valor, v_aux_transacao.data.dia, v_aux_transacao.data.mes, v_aux_transacao.data.ano, v_aux_transacao.hora.hora, v_aux_transacao.hora.minuto, v_aux_transacao.hora.segundo);
            break;
    }
        

}

void menu_principal(t_principal* s_principal) {
    int opcao = 0;
    system("cls");
    opcao = obter_input(0, 4, "Menu Principal\n\n", "1 - Registar informacao\n", "2 - Consultar informacao\n", "3 - Estatisticas\n", "4 - Gravar no ficheiro\n", "0 - Sair da aplicacao");
    switch (opcao) {
        case 1: menu_registar(s_principal, selecinar_base_dados()); break;
        case 2: menu_consultar(s_principal, selecinar_base_dados()); break;
        case 3: menu_estatisticas(s_principal); break;
        case 4: gravar_no_ficheiro(s_principal); menu_principal(s_principal); break;
        case 0: menu_sair(s_principal); break;
        default: menu_principal(s_principal); break;
    }
}
int obter_input(int minimo, int maximo, char texto1[], char texto2[], char texto3[], char texto4[], char texto5[], char texto6[]){
    char textos[6][50];          // criação de array para facilitar o uso de ciclos
    int escrever = 0, opcao = 0, index = 0;                
    strcpy(textos[0], texto1);   // atribuição do valor dos parametros ao array
    strcpy(textos[1], texto2);
    strcpy(textos[2], texto3);
    strcpy(textos[3], texto4);
    strcpy(textos[4], texto5);
    strcpy(textos[5], texto6);
    do{                                                         // enquanto o input nao for valido
        for(index = 0; index < 6; index++){                     // repete um ciclo que vai por todos os textos
            if(textos[index] != "\0" && escrever == 0){         // caso um texto nao seja vazio e caso o programa possa escrever
                printf("%s", textos[index]);                    // escreve esse texto
            } else {                                            // caso o texto seja vazio ou o programa tenha de parar
                escrever = 1;                                   // muda a variavel escrever, que é responsavel por escrever caso tenha o valor de 0
            }
        }
        printf("\n\n> ");   
        scanf("%d", &opcao);
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
    printf("Menu registar - %s\n", titulo);
    printf("-----------------------------------------\n");
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){
        registar_informacao(s_principal, index, baseDados);
        printf("-----------------------------------------\n");
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
    int opcao = 0, index = procurar_elemento_vazio(s_principal, baseDados);
    char titulo[13];
    switch(baseDados){
        case ESCOLA: strcpy(titulo, "Escolas"); break;
        case UTILIZADOR: strcpy(titulo, "Utilizadores"); break;
        case TRANSACAO: strcpy(titulo, "Transacoes"); break;
    }
    system("cls");
    printf("Menu registar - %s\n\n", titulo);
    if(baseDados == ESCOLA || baseDados == UTILIZADOR || baseDados == TRANSACAO){
        //registar_informacao(s_principal, index, baseDados);
        //cabecalho_apresentar_dados(baseDados);
        //apresentar_dados(s_principal, index, baseDados);
        opcao = obter_input(0, 4, "\n\n1 - Procurar elemento", "\n2 - Apagar informacao", "\n3 - Alterar", "\n4 - Mudar base de dados", "\n0 - Voltar atras", "\0");
        switch (opcao){
            case 1: /*procurar_elemento(s_principal, baseDados);*/ break;
            case 2: apagar_elemento(s_principal, receber_index(), baseDados); break;
            case 3: alterar_elemento(s_principal, receber_index(), baseDados); break;
            case 4: menu_consultar(s_principal, selecinar_base_dados()); break;
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
        printf("\n\nTem a certeza que quer apagar este elemento?\n");
        printf("-----------------------------------------\n");
        // mostra o elemento
        printf("\n-----------------------------------------\n");
        int opcao = obter_input(0, 3, "\n1 - Sim", "\n2 - Nao", "\n3 - Escolher outro elemento", "\n0 - Voltar atras", "\0", "\0");
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
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento", "2 - Escolher outro elemento", "0 - Voltar atras", "\0", "\0", "\0");
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
        printf("\n\nÉ este o elemento que deseja alterar?\n");
        printf("-----------------------------------------\n");
        // mostra o elemento
        printf("\n-----------------------------------------\n");
        int opcao = obter_input(0, 3, "\n1 - Sim", "\n2 - Nao", "\n3 - Escolher outro elemento", "\n0 - Voltar atras", "\0", "\0");
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
        int opcao_1 = obter_input(0, 2, "1 - Registar elemento", "2 - Escolher outro elemento", "0 - Voltar atras", "\0", "\0", "\0");
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
void menu_estatisticas(t_principal* s_principal) {
    int i;
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
