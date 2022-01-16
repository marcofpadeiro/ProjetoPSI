#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESCOLA 5
#define MAX_UTILIZADOR 200
#define MAX_TRANSACAO 5000

#define ESCOLA 1
#define UTILIZADOR 2
#define TRANSACAO 3

#define TAMANHO_NOME_ESCOLA 50
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
void limpa_elemento(t_principal* s_principal, int index, int baseDados);
void registar_informacao(t_principal* s_principal, int index, int baseDados);
void registar_escola(t_principal* s_principal, int index);
void registar_utilizador(t_principal* s_principal, int index);
void registar_transacao(t_principal* s_principal, int index);
int procurar_elemento_vazio(t_principal* s_principal, int baseDados);
int selecinar_base_dados();
void menu_principal(t_principal* s_principal);
void menu_registar(t_principal* s_principal);
void menu_consultar(t_principal* s_principal);
void menu_alterar(t_principal* s_principal);
void menu_apagar(t_principal* s_principal);
void menu_estatisticas(t_principal* s_principal);
void menu_sair(t_principal* s_principal);

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
            strcpy(s_principal->v_escola[index].nome_escola, '\0');
            strcpy(s_principal->v_escola[index].abreviatura, '\0');
            strcpy(s_principal->v_escola[index].campus, '\0');
            strcpy(s_principal->v_escola[index].localizacao, '\0');
            break;
        case UTILIZADOR:
            s_principal->v_utilizador[index].id_utilizador = 0;
            s_principal->v_utilizador[index].id_escola = 0;
            s_principal->v_utilizador[index].NIF = 0;
            s_principal->v_utilizador[index].saldo = 0;
            strcpy(s_principal->v_utilizador[index].nome_utilizador, '\0');
            strcpy(s_principal->v_utilizador[index].tipo_utilizador, '\0');
            strcpy(s_principal->v_utilizador[index].email, '\0');
            break;
        case TRANSACAO:
            s_principal->v_transacao[index].id_transacao = 0;
            s_principal->v_transacao[index].id_utilizador = 0;
            s_principal->v_transacao[index].valor = 0;
            strcpy(s_principal->v_transacao[index].tipo_transacao, '\0');
            s_principal->v_transacao[index].data = (t_data){ 0, 0, 0 }; 
            s_principal->v_transacao[index].hora = (t_hora){ 0, 0, 0 };
    }
}

int selecinar_base_dados() {
    int opcao;
    do {
        system("cls");
        printf("Selecione a base de dados que deseja manipular:\n\n");
        printf("1 - Escolas\n");
        printf("2 - Utilizadores\n");
        printf("3 - Transacoes\n");
        printf("0 - Voltar atras\n\n> ");
        scanf("%d", &opcao);
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
            for (int i = 0; i < MAX_UTILIZADOR; i++) {
                if (s_principal->v_transacao[i].id_transacao == 0) {
                    return i;
                }
            }
            break;
    }
}

void registar_informacao(t_principal* s_principal, int index, int baseDados) {
    switch (baseDados) {
        case ESCOLA:
            printf("Registo de Escolas: \n\n");
            registar_escola(s_principal, index);
            break;
        case UTILIZADOR:
            printf("Registo de Utilizadores: \n\n");
            registar_utilizador(s_principal, index);
            break;
        case TRANSACAO:
            printf("Registo de Transacoes: \n\n");
            registar_transacao(s_principal, index);
            break;
    }
    gravar_no_ficheiro(s_principal);
}
void registar_escola(t_principal* s_principal, int index) {
    int validacao_escolas[5];                // 0 == false || 1 == true
    t_escola v_aux_escola[MAX_ESCOLA];
    fflush(stdin);
    do {
        printf("Identificador Escola: ");   
        scanf("%d", &v_aux_escola[index].id_escola);
        validacao_escolas[0] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[0] == 0) { printf("\nEste numero precisa de ser de 1 a 5!\n\n");}
    } while (validacao_escolas[0] == 0);
    do {
        printf("Nome Escola: ");
        scanf("%s", v_aux_escola[index].nome_escola);
        validacao_escolas[1] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[1] == 0) { printf("\nO nome da escola tem que!\n\n");}
    } while (validacao_escolas[1] == 0);
    do {
        printf("Abreviatura: ");
        scanf("%s", v_aux_escola[index].abreviatura);
        validacao_escolas[2] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[2] == 0) { printf("\nA abreviatura pode ter no maximo 5 digitos!!\n\n");}
    } while (validacao_escolas[2] == 0);
    do {
        printf("Campus: ");
        scanf("%s", v_aux_escola[index].campus);
        validacao_escolas[3] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_escolas[3] == 0) { printf("\nEste campo precisa de ser no formato 'Campus *numero*'!!\n\n");}
    } while (validacao_escolas[3] == 0);

    do {
        printf("Localizacao: ");
        scanf("%s", v_aux_escola[index].localizacao);
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
        printf("Nome Utilizador: ");
        scanf("%s", v_aux_utilizador[index].nome_utilizador);
        validacao_utilizadores[2] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[2] == 0) { printf("\nO nome do utilizador tem que !\n\n");}
    } while (validacao_utilizadores[2] == 0);
    do {
        printf("NIF: ");
        scanf("%d", &v_aux_utilizador[index].NIF);
        validacao_utilizadores[3] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[3] == 0) { printf("\nO NIF tem que ter 9 caracteres!\n\n");}
    } while (validacao_utilizadores[3] == 0);
    do {
        printf("Tipo Utilizador: ");
        scanf("%s", v_aux_utilizador[index].tipo_utilizador);
        validacao_utilizadores[4] = 1; // mais tarde mudar para uma validacao correta
        if(validacao_utilizadores[4] == 0) { printf("\nO tipo de utilizador tem que ser 'Docente', 'Estudante' ou 'Funcionario'!\n\n");}
    } while (validacao_utilizadores[4] == 0);
    do {
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

void menu_principal(t_principal* s_principal) {
    int opcao = 6;
    do {
        system("cls");
        printf("Menu Principal\n\n");
        printf("1 - Registar informacao\n");
        printf("2 - Consultar informacao\n");
        printf("3 - Alterar informacao\n");
        printf("4 - Apagar informacao\n");
        printf("5 - Estatisticas\n");
        printf("0 - Sair da aplicacao\n\n> ");
        scanf("%d", &opcao);
    } while(opcao < 0 || opcao > 5);
    switch (opcao) {
        case 1: 
            menu_registar(s_principal); break;
        case 2: 
            menu_consultar(s_principal); break;
        case 3: 
            menu_alterar(s_principal); break;
        case 4: 
            menu_apagar(s_principal); break;
        case 5: 
            menu_estatisticas(s_principal); break;
        case 0: 
            menu_sair(s_principal); break;
    }
}
void menu_registar(t_principal* s_principal) {
    int opcao = selecinar_base_dados();
    if (opcao != 0) {
        system("cls");
        int index = procurar_elemento_vazio(s_principal, opcao);
        registar_informacao(s_principal, index, opcao);
        //consultar_informacao(s_principal, index);
    }
    else {
        menu_principal(s_principal);
    }
}
void menu_consultar(t_principal* s_principal) {
    int i;
}
void menu_alterar(t_principal* s_principal) {
    int i;
}
void menu_apagar(t_principal* s_principal) {
    int i;
}
void menu_estatisticas(t_principal* s_principal) {
    int i;
}
void menu_sair(t_principal* s_principal) {
    int opcao;
    do {
        system("cls");
        printf("Sair da Aplicacao\n\n");
        printf("Deseja guardar a informacao registada?\n");
        printf("1 - Guardar\n");
        printf("2 - Nao guardar\n");
        printf("0 - Voltar atras\n\n> ");
        scanf("%d", &opcao); 
    } while (opcao < 0 || opcao > 2);
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
    }
    
}
