// Nome : William Gonçalves da Cruz
// RA   : 188671

#include <stdio.h>

int main() {
    int numIlhas,
        diaAtual,
        mesAtual,
        anoAtual, 
        diaNiver,
        mesNiver,
        diaSeguido,
        diaSemanaSeguido, 
        anoUltimo,
        qtdDiasMes,
        diaSemana,
        qtdFestival,
        numFornecedores,
        capacidadeGalao,
        qtdGaloes,
        litros,
        i;

    double precoGalao,
           menorPreco,
           precoAtual,
           xAnterior,
           yAnterior,
           xProximo,
           yProximo,
           xPrimeiro,
           yPrimeiro,
           xMaiorBorda,
           yMaiorBorda,
           xMenorBorda,
           yMenorBorda,
           areaIlha,
           areaAtual,
           areaAgua,
           volume;

    
    areaIlha  = 0.0;
    
    // Começa a lógica de calculas o volume de água necessário na maquete
    scanf("%d", &numIlhas);

    // Para calcular a aŕea de um poligono a partir de suas coordenadas, User a formula de Shoelace
    // (Laço de cadarço), que consiste na multiplicação de 1/2 pelo módulo de uma somatórias 
    // envolvendo as coordenadas
    for (i = 0; i < numIlhas; i++) { 
        scanf(" (%lf , %lf)", &xPrimeiro, &yPrimeiro);

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
        for(areaAtual = 0.0;;) {
            scanf(" (%lf , %lf)", &xProximo, &yProximo);

            // Para calular a area, é preciso multiplicar o X da  coordenada atual com o 
            // Y da seguinte, Subtraindo o resultado com Y da seguinte multuplicado com X da atual, 
            // até chegarem nas ultimas coordenadas, onde as ultimas coordenadas sao multiplicadas
            // de acordo com a regra acima
            
            //printf("+ Resultado de %.2lf * %.2lf = %.2lf\n", xAnterior, yProximo, xAnterior*yProximo);
            areaAtual = areaAtual + (xAnterior * yProximo);
            //printf("- Resultado de %.2lf * %.2lf = %.2lf\n", xProximo, yAnterior, -yAnterior*xProximo);
            areaAtual = areaAtual - (yAnterior * xProximo);

            //Sequencia de condições para saber como distanciar 50 cm do x Mais distante das Ilhas
            if (xProximo > xMaiorBorda)
                xMaiorBorda = xProximo;

            if (xProximo < xMenorBorda)
                xMenorBorda = xProximo;

            if (yProximo > yMaiorBorda)
                yMaiorBorda = yProximo;

            if (yProximo < yMenorBorda)
                yMenorBorda = yProximo;
            
            if (xProximo == xPrimeiro && yProximo == yPrimeiro) 
                break; 

            // Atualiza o valor das Coordenadas anteriores
            yAnterior = yProximo;
            xAnterior = xProximo;
        }

        if(areaAtual < 0) // Modulo da área
            areaAtual = -areaAtual;

        areaIlha += 0.5 * areaAtual;
        //printf("\nArea Atual: %.2lf" , areaAtual);
    }

    // As bordas devem ficar a pelo menos 50 cm (0,5 metros) de distancia de todas as ilhas
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

    // inicialização das datas para uso no algoritmo'
    diaAtual = 1;
    mesAtual = 1;
    anoAtual = 2016;
    qtdDiasMes = 31;
    diaSemana = 0;
    qtdFestival = 0;

    // Começa a lógica de contar os dias de Festival
    scanf("%d/%d", &diaNiver, &mesNiver);
    
    // O final de um ano seria equivalente ao começo do proximo, portanto somo um para facilitar a logica
    scanf("%d", &anoUltimo);
    anoUltimo++;
    
    for (;; diaAtual++, diaSemana++) {

        // O mês chegou ao final
        if (diaAtual > qtdDiasMes) {
            diaAtual = 1;
            mesAtual++;
           
            // Caso o mes seja 0, completou um ano
            if (mesAtual > 12) {
                mesAtual = 1;
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
                        qtdDiasMes = 28;
                    
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
        } else {
            
            // è o dia do aniversário da cidade
            if (diaAtual == diaNiver && mesAtual == mesNiver) {
                qtdFestival++;
          
               diaSeguido = diaAtual + 1;
                diaSemanaSeguido = diaSemana + 1;

                // Há uma sexta feira treze no dia anterior ao dia do aniversário da cidade
                // logo, precisamos desconsiderar esse dia pois será usada a mesma água
                if (diaSeguido == 13 && diaSemanaSeguido % 7 == 0) {
                    qtdFestival--;
                 }
        

                diaSeguido = diaAtual - 1;
                diaSemanaSeguido = diaSemana - 1;

                // Caso a sexta treze tenha sido um dia antes do Aniversário da Cidade, mesma água
                if (diaSeguido == 13 && diaSemanaSeguido % 7 == 0) {
                    qtdFestival -= 2;
                }

            } else if (diaSemana % 7 == 0 && diaAtual == 13) {
                qtdFestival++;
            }
            // Acima qualifica sexta feira Treze, porem preve a possibilidade do aniversario da cidade
            // Cair em uma sexta feira treze, não sendo preciso gastar mais água 
        } 
    }
   
    // Começa a lógica de encontrar o melhor preço dos galões de água  
    scanf("%d", &numFornecedores);

    scanf("%d $%lf", &capacidadeGalao, &precoGalao);
    
    qtdGaloes = litros / capacidadeGalao;
    
    precoAtual = qtdGaloes * precoGalao * qtdFestival;
    menorPreco = precoAtual;

    for (i = 1; i < numFornecedores; i++) {

        printf("\nPreco Atual : %.lf\n", precoAtual);
        
        scanf("%d $%lf", &capacidadeGalao, &precoGalao);
        
        qtdGaloes = litros / capacidadeGalao;
       
        if (litros % capacidadeGalao != 0)
            qtdGaloes++;

        precoAtual = qtdGaloes * precoGalao * qtdFestival;

        if (precoAtual < menorPreco)
            menorPreco = precoAtual;
    }

    //printf("Festivais : %d \n", qtdFestival);
    printf("Litros de água : %.2f \n", litros);
    printf("Area da Ilha : %.2f \nArea da Agua : %.2lf\n", areaIlha, areaAgua);
    
    printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", menorPreco);
   
    return 0;
}

