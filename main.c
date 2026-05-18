// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h"
#include <stdlib.h>
#include <string.h>
DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
 @objetivo
     Somar dois valores x e y e retonar o resultado da soma
     @entrada
         dois inteiros x e y
         @saida
             resultado da soma (x + y)
              */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
 @objetivo
     calcular o fatorial de um número
     @entrada
         um inteiro x
         @saida
             fatorial de x -> x!
              */
int fatorial(int x)
{ // função utilizada para testes
    int i, fat = 1;

    for (i = x; i > 1; i--)
        fat = fat * i;

    return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
 @objetivo
     Validar uma data
     @entrada
         uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano.
             dd e mm podem ter apenas um digito
                 , e aaaa podem ter apenas dois digitos.
                 @saida
                     0 -> se data inválida
                         1 -> se data válida
                          @restrições
                              Não utilizar funções próprias de string (ex: strtok)
                                  pode utilizar strlen para pegar o tamanho da string
                                   */
int q1(char data[])
{
    size_t tamanho = strlen(data);
    int dia = 0, mes = 0, ano = 0;
    int etapa = 0;        // 0=dia, 1=mes, 2=ano
    int digitosEtapa = 0; // quantos dígitos nessa etapa

    for (int i = 0; i <= (int)tamanho; i++)
    {
        char c = data[i];

        if (c == '/' || c == '\0')
        {
            // Chegou num separador ou fim da string

            // Campo vazio?
            if (digitosEtapa == 0)
                return 0;

            // Fim da string mas ainda faltam campos
            if (c == '\0' && etapa != 2)
                return 0;

            // Separador quando já estava no ano
            if (c == '/' && etapa == 2)
                return 0;

            // Validação de tamanho por etapa
            if (etapa == 0 && (digitosEtapa < 1 || digitosEtapa > 2))
                return 0;
            if (etapa == 1 && (digitosEtapa < 1 || digitosEtapa > 2))
                return 0;
            if (etapa == 2 && (digitosEtapa != 2 && digitosEtapa != 4))
                return 0;

            etapa++;
            digitosEtapa = 0;
        }
        else if (c >= '0' && c <= '9')
        {
            int digito = c - '0';

            if (etapa == 0)
            {
                dia = dia * 10 + digito;
                digitosEtapa++;
            }
            else if (etapa == 1)
            {
                mes = mes * 10 + digito;
                digitosEtapa++;
            }
            else if (etapa == 2)
            {
                ano = ano * 10 + digito;
                digitosEtapa++;
            }
            else
            {
                // Dígito após o fim dos 3 campos
                return 0;
            }
        }
        else
        {
            // Caractere inválido
            return 0;
        }
    }

    // Ajuste de ano com 2 dígitos
    if (ano >= 0 && ano <= 99)
    {
        ano += 2000;
    }

    if (mes < 1 || mes > 12)
        return 0;

    if (dia < 1)
        return 0;

    // Dias por mês
    int diasNoMes = 28;
    if (mes == 2)
    {

        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        diasNoMes = bissexto ? 29 : 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        diasNoMes = 30;
    }
    else
    {
        diasNoMes = 31;
    }

    if (dia > diasNoMes)
        return 0;

    return 1;
}

/*
 Q2 = diferença entre duas datas
  @objetivo
      Calcular a diferença em anos, meses e dias entre duas datas
       @entrada
           uma string datainicial, uma string datafinal.
            @saida
                Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
                    1 -> cálculo de diferença realizado com sucesso
                        2 -> datainicial inválida
                            3 -> datafinal inválida
                                4 -> datainicial > datafinal
                                    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
                                     */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;

    // 1. Validação das datas usando a sua função q1
    if (q1(datainicial) == 0)
    {
        dma.retorno = 2;
        return dma;
    }
    else if (q1(datafinal) == 0)
    {
        dma.retorno = 3;
        return dma;
    }

    // 2. Extração manual das datas (Igual fizemos na q1)
    int d1 = 0, m1 = 0, a1 = 0;
    int d2 = 0, m2 = 0, a2 = 0;
    int etapa = 0;

    // Lendo a Data Inicial
    for (int i = 0; datainicial[i] != '\0'; i++)
    {
        if (datainicial[i] == '/')
        {
            etapa++;
        }
        else if (datainicial[i] >= '0' && datainicial[i] <= '9')
        {
            if (etapa == 0)
                d1 = d1 * 10 + (datainicial[i] - '0');
            else if (etapa == 1)
                m1 = m1 * 10 + (datainicial[i] - '0');
            else if (etapa == 2)
                a1 = a1 * 10 + (datainicial[i] - '0');
        }
    }
    if (a1 >= 0 && a1 <= 99)
        a1 += 2000; // Ajuste de ano

    // Lendo a Data Final
    etapa = 0;
    for (int i = 0; datafinal[i] != '\0'; i++)
    {
        if (datafinal[i] == '/')
        {
            etapa++;
        }
        else if (datafinal[i] >= '0' && datafinal[i] <= '9')
        {
            if (etapa == 0)
                d2 = d2 * 10 + (datafinal[i] - '0');
            else if (etapa == 1)
                m2 = m2 * 10 + (datafinal[i] - '0');
            else if (etapa == 2)
                a2 = a2 * 10 + (datafinal[i] - '0');
        }
    }
    if (a2 >= 0 && a2 <= 99)
        a2 += 2000; // Ajuste de ano

    // 3. Verificar se a data inicial é MAIOR que a data final
    if (a1 > a2 || (a1 == a2 && m1 > m2) || (a1 == a2 && m1 == m2 && d1 > d2))
    {
        dma.retorno = 4;
        return dma;
    }

    // 4. Calcular a distância matemática (Subtração simples)
    int dias = d2 - d1;
    int meses = m2 - m1;
    int anos = a2 - a1;

    // 5. O Pulo do Gato: Regra do Empréstimo de Dias
    if (dias < 0)
    {
        meses--; // Tira 1 do saldo de meses

        // Descobrir qual era o mês ANTERIOR para saber quantos dias pegar emprestado
        int mesAnterior = m2 - 1;
        int anoMesAnterior = a2;

        // Se estávamos em Janeiro (1), o mês anterior é Dezembro (12) do ano passado!
        if (mesAnterior == 0)
        {
            mesAnterior = 12;
            anoMesAnterior--;
        }

        // Calcula os dias do mês anterior, considerando bissexto
        int bissexto = (anoMesAnterior % 4 == 0 && anoMesAnterior % 100 != 0) || (anoMesAnterior % 400 == 0);
        int dias_por_mes[] = {0, 31, 28 + bissexto, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Soma os dias emprestados para o saldo deixar de ser negativo
        dias += dias_por_mes[mesAnterior];
    }

    // 6. Regra do Empréstimo de Meses
    if (meses < 0)
    {
        anos--;      // Tira 1 do saldo de anos
        meses += 12; // 1 ano empresta 12 meses
    }

    // 7. Salvar e Retornar Sucesso!
    dma.qtdDias = dias;
    dma.qtdMeses = meses;
    dma.qtdAnos = anos;
    dma.retorno = 1;

    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0; // Achei mais sentido ser 0
    size_t tamanho = strlen(texto);

    // Variável para guardar a letra que  buscando
    char busca = c;
    
    // Se NÃO for case sensitive, forçamos a letra que BUSCADA a ser minúscula
    if (isCaseSensitive != 1) {
        if (busca >= 'A' && busca <= 'Z') {
            busca = busca + 32; // Tabela ASCII: +32 transforma maiúscula em minúscula 
        }
    }

    for (int i = 0; i < tamanho; i++)
    {
        char atual = texto[i];

        //  Ajuste de Maiúscula/Minúscula na letra do texto
        if (isCaseSensitive != 1) {
            if (atual >= 'A' && atual <= 'Z') {
                atual = atual + 32;
            }
        }

       
        // unsigned char impede que caracteres acentuados virem números negativos
        unsigned char u_atual = (unsigned char) atual;
        
        // Vogais minúsculas com acento para a versão limpa
        if (u_atual == 225 || u_atual == 224 || u_atual == 226 || u_atual == 227) atual = 'a'; 
        else if (u_atual == 233 || u_atual == 232 || u_atual == 234) atual = 'e'; 
        else if (u_atual == 237 || u_atual == 236 || u_atual == 238) atual = 'i'; 
        else if (u_atual == 243 || u_atual == 242 || u_atual == 244 || u_atual == 245) atual = 'o'; 
        else if (u_atual == 250 || u_atual == 249 || u_atual == 251) atual = 'u'; 
        
        // Vogais maiúsculas com acento
        if (isCaseSensitive == 1) {
            // Se importa o caseSensitive, limpa os acentos mas mantém as letras grandes
            if (u_atual == 193 || u_atual == 192 || u_atual == 194 || u_atual == 195) atual = 'A'; 
            else if (u_atual == 201 || u_atual == 200 || u_atual == 202) atual = 'E';
            else if (u_atual == 205 || u_atual == 204 || u_atual == 206) atual = 'I';
            else if (u_atual == 211 || u_atual == 210 || u_atual == 212 || u_atual == 213) atual = 'O';
            else if (u_atual == 218 || u_atual == 217 || u_atual == 219) atual = 'U';
        } else {
            
            // Maiúsculas com acento e jogamos pra minúscula limpa.
            if (u_atual == 193 || u_atual == 192 || u_atual == 194 || u_atual == 195) atual = 'a';
            else if (u_atual == 201 || u_atual == 200 || u_atual == 202) atual = 'e';
            else if (u_atual == 205 || u_atual == 204 || u_atual == 206) atual = 'i';
            else if (u_atual == 211 || u_atual == 210 || u_atual == 212 || u_atual == 213) atual = 'o';
            else if (u_atual == 218 || u_atual == 217 || u_atual == 219) atual = 'u';
        }

      
        if (atual == busca) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}


/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = -1;

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias;
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5])
{
    int achou;
    return achou;
}

DataQuebrada quebraData(char data[])
{
    DataQuebrada dq;
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int i;

    for (i = 0; data[i] != '/'; i++)
    {
        sDia[i] = data[i];
    }
    if (i == 1 || i == 2)
    {                   // testa se tem 1 ou dois digitos
        sDia[i] = '\0'; // coloca o barra zero no final
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    int j = i + 1; // anda 1 cada para pular a barra
    i = 0;

    for (; data[j] != '/'; j++)
    {
        sMes[i] = data[j];
        i++;
    }

    if (i == 1 || i == 2)
    {                   // testa se tem 1 ou dois digitos
        sMes[i] = '\0'; // coloca o barra zero no final
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    j = j + 1; // anda 1 cada para pular a barra
    i = 0;

    for (; data[j] != '\0'; j++)
    {
        sAno[i] = data[j];
        i++;
    }

    if (i == 2 || i == 4)
    {                   // testa se tem 2 ou 4 digitos
        sAno[i] = '\0'; // coloca o barra zero no final
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);

    dq.valido = 1;

    return dq;
}
