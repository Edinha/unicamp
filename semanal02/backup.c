// Nome : William Gonçalves da Cruz
// RA   : 188671

#include <stdio.h>

void sextaFeirasTreze() {
    int diaAtual,
        mesAtual,
        anoAtual, 
        diaNiver,
        mesNiver,
        diaSeguido,
        diaSemanaSeguido, 
        anoUltimo,
        qtdDiasMes,
        qtdMesesAno,
        diaSemana,
        diaSexta = 5,
        qtdFestival = 0;


    diaAtual = 1;
    mesAtual = 1;
    anoAtual = 2016;
    qtdDiasMes = 31;
    qtdMesesAno = 12;
    diaSemana = 5;
    anoUltimo = 2019;
    diaNiver = 14;
    mesNiver = 5;


    for (;;) {

        diaAtual++;
        diaSemana = ++diaSemana % 7;

        // è o dia do aniversário da cidade
        if (diaAtual == diaNiver && mesAtual == mesNiver) {
            qtdFestival++;
          
            diaSeguido = diaAtual + 1;
            diaSemanaSeguido = diaSemana + 1;

            // Há uma sexta feira treze no dia anterior ao dia do aniversário da cidade
            // logo, somaremos dois dias para "pular" a sexta treze, pois será a mesma água
            printf("Proximo dia : %d : %d\n", diaSeguido, diaSemanaSeguido);
            if (diaSeguido == 13 && diaSemanaSeguido == diaSexta) {
                diaAtual += 2;
                diaSemana  = (diaSemana + 2) % 7;
            }

            diaSeguido = diaAtual - 1;
            diaSemanaSeguido = diaSemana - 1;

            // Caso a sexta treze tenha sido um dia antes do Aniversário da Cidade, mesma água
            printf("Anterior dia : %d : %d\n", diaSeguido, diaSemanaSeguido);
            if (diaSeguido == 13 && diaSemanaSeguido == diaSexta) {
                qtdFestival -= 2;
            }
            
        } else if (diaSemana == diaSexta && diaAtual == 13) {
            qtdFestival++;
        }
        // Acima qualifica sexta feira Treze, porem preve a possibilidade do aniversario da cidade
        // Cair em uma sexta feira treze, não sendo preciso gastar mais água 

        // O mês chegou ao final
        if (diaAtual == qtdDiasMes) {
            diaAtual = 1;
            mesAtual = (mesAtual + 1) % 12;
           
            // Caso o mes seja 0, completou um ano
            if (mesAtual == 0) {
                mesAtual++;
                anoAtual++;

                // Caso seja o ano descrito pelo programa, parar a contagem de festivais
                if (anoAtual == anoUltimo)
                    break;
            }

            switch (mesAtual) {
                // Para o caso de ser Fevereiro
                case 2:  
                    if (anoAtual % 400 == 0) // Bissexto
                        qtdDiasMes = 29;
                    else if (anoAtual % 100 == 0)  // Não Bissexto
                        qtdDiasMes = 28;
                    else if (anoAtual % 4 == 0) // Bissexto
                        qtdDiasMes = 29;
                    else // Não Bissexto
                        qtdDiasMes = 29;

                    break;

                case 1: // Números dos Meses com 31 dias naquele Mes
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    qtdDiasMes = 31;
                    break;
                default:
                    qtdDiasMes = 30;
            }
        }
    }

    //printf("Quantidade festivais : %d\n", qtdFestival);
}

void calcularArea() {
    int numIlhas,
        i;

    double xAnterior,
           yAnterior,
           xProximo,
           yProximo,
           xMargem,
           yMargem,
           xPrimeiro,
           yPrimeiro,
           xMaiorBorda,
           yMaiorBorda,
           xMenorBorda,
           yMenorBorda,
           areaIlha,
           areaAgua,
           volume,
           litros;

    areaIlha = 0.0;
    volume = 0.0;

    scanf("%d", &numIlhas);

    // Para calcular a aŕea de um poligono a partir de suas coordenadas, User a formula de Shoelace
    // (Laço de cadarço), que consiste na multiplicação de 1/2 pelo módulo de uma somatórias 
    // envolvendo as coordenadas
    for (i = 0; i < numIlhas; i++) { 
        scanf(" (%lf , %lf)", &xPrimeiro, &yPrimeiro);
        //printf("Primeira Coordenada (%.2lf , %.2lf ) \n", xPrimeiro, yPrimeiro);

        xAnterior = xPrimeiro;
        yAnterior = yPrimeiro;

        // Caso seja a primeira ilha, inicializa as coordenadas da borda para comparação
        if (i == 0) {
            yMenorBorda = yAnterior;
            yMaiorBorda = yAnterior;
            xMenorBorda = xAnterior;
            xMaiorBorda = xAnterior;
        }

        // Repetição para ler as coordenadas da Ilha atual
        for(;;) {
            scanf(" (%lf , %lf)", &xProximo, &yProximo);
            //printf("Proxima Coordenada (%.2lf , %.2lf ) \n", xProximo, yProximo);

            // Para calular a area, é preciso multiplicar o X da  coordenada atual com o 
            // Y da seguinte, Subtraindo o resultado com Y da seguinte multuplicado com X da atual, 
            // até chegarem nas ultimas coordenadas, onde as ultimas coordenadas sao multiplicadas
            // de acordo com a regra acima
            areaIlha += xAnterior * yProximo;
            areaIlha -= yAnterior * xProximo;

            if (xProximo == xPrimeiro && yProximo == yPrimeiro) 
                break; 
            
            //Sequencia de condições para saber como distanciar 50 cm do x Mais distante das Ilhas
            if (xProximo > xMaiorBorda)
                xMaiorBorda = xProximo;

            if (xProximo < xMenorBorda)
                xMenorBorda = xProximo;

            if (yProximo > yMaiorBorda)
                yMaiorBorda = yProximo;

            if (yProximo < yMenorBorda)
                yMenorBorda = yProximo;

            // Atualiza o valor das Coordenadas anteriores
            yAnterior = yProximo;
            xAnterior = xProximo;
        }
    }

    if (areaIlha < 0)  // Módulo da área
        areaIlha = -areaIlha;

    // Area Final do poligono pela formula do Shoelace 
    areaIlha = 0.5 * areaIlha;

    // As bordas devem ficar a pelo menos 0,5 cm de distancia de todas as ilhas
    xMenorBorda -= 0.5;
    yMenorBorda -= 0.5;
    xMaiorBorda += 0.5;
    yMaiorBorda += 0.5;

    // Calculando a área do retagulo de margem  
    areaAgua = (xMaiorBorda - xMenorBorda) * (yMaiorBorda - yMenorBorda);

    // Retirando os espaços das ilhas da area q será coberta com aǵua
    areaAgua = areaAgua - areaIlha;

    // Calculo do volume, área vezes 0,5 de profundidade
    volume = areaAgua * 0.5;

    // 1 m³ de água == 1000 Litros de aǵua
    litros = volume * 1000;

}

void melhorPreco() {
    int numFornecedores,
        capacidadeGalao,
        qtdGaloes,
        i;

    double precoGalao,
           menorPreco,
           precoAtual,
           litros = 7750,
           qtdFestival = 8;

    scanf("%d", &numFornecedores);

    scanf("%d $%lf", &capacidadeGalao, &precoGalao);
    
    qtdGaloes = litros / capacidadeGalao;
    
    precoAtual = qtdGaloes * precoGalao * qtdFestival;
    menorPreco = precoAtual;

    for (i = 1; i < numFornecedores; i++) {
        scanf("%d $%lf", &capacidadeGalao, &precoGalao);
        
        qtdGaloes = litros / capacidadeGalao;
        
        precoAtual = qtdGaloes * precoGalao * qtdFestival;
    
        if (precoAtual < menorPreco)
            menorPreco = precoAtual;
    }


    printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", menorPreco);
}


int main() {
    


    return 0;
}
