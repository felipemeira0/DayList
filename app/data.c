/*
 * DayList DataBase Service
 * Used to store database for person accounts, such as names and others
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct task {
    char date[20]; // Data, como 2021-10-28, que e recomendavel
    char *tname; // Nome da Agenda, como medicamentos
    int finish; // Finalizar
};

struct person {
    char name[20]; // Primeiro Nome
    char surname[50]; // Sobre Nome
    char borndate[10]; // Em formato YYYY-MM-DD, como 2003-04-30
    char cpf[15]; // CPF, Ignore, e um exemplo
    struct task book; // Agenda
};

struct persondata {
    int size;
    struct person *data;
};

int main() {
    // TODO code an database containing person account
    return 0;
}