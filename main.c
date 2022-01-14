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
void ler_ficheiro(t_principal * s_principal) {
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
void gravar_no_ficheiro(t_principal* s_principal) {
    FILE* ficheiro;
    ficheiro = fopen("BaseDados.bin", "wb");
    fwrite(s_principal, sizeof(t_principal), 1, ficheiro);
    fflush(ficheiro);
    fclose(ficheiro);
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
        case 5: break;
            menu_estatisticas(s_principal); break;
        case 0: break;
            menu_sair(s_principal); break;
    }
}
void menu_registar(t_principal* s_principal) {
    int i;
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
    int i;
}
