#include <stdio.h>
#include <unistd.h>

float definirW1deVetor();
float definirW2deVetor();
float porcentTest(int escolha,float w1,float w2);

int main(void){

    char linha[100];

    float x1[30], x2[30], y[30];
    float taxa = 0.01;
    int escolha = 3; 

    printf("Digite 1 para A_l ou Digite 2 para B_l :\n");
    while(escolha<1 || escolha>2){
        scanf("%d",&escolha);
    }

    FILE *arquivo;
    if(escolha == 1)
        arquivo = fopen("A_l.txt", "r");
    else
       arquivo = fopen("B_l.txt", "r"); 
    
    if(arquivo == NULL) {
        printf("Arquivo informado não está correto.\n");
        return 0;
    }

    float w1 = definirW1deVetor();
    float w2 = definirW2deVetor();
    
    int i = 0;
    
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        fscanf(arquivo,"%f %f %f", &x1[i], &x2[i], &y[i]);
        i++;
    }
    
    for(i = 0; i < 30; i++){
    printf("c=%d %.2f %.2f %.2f\n", i, x1[i], x2[i], y[i]);
    }
    
    fclose(arquivo);
    
    int c = 0;
    float yr = 0;
    
    while(c < 30){
        yr = (w1*x1[c]) + (w2*x2[c]);
        
        if(yr >= 0){
            yr = 1;
        } else if(yr < 0){
            yr = 0;
        }

        float d = y[c] - yr;
        
        if(d == 0){
            c++;
        } else if (d != 0){
            w1 = (taxa*d*x1[c]) + w1;
            w2 = (taxa*d*x2[c]) + w2;      
            c = 0;
        }

        yr = 0;
        ///printf("%d  w1: %.2f w2: %.2f d:%.2f\n",c,w1,w2,d);
    }
    sleep(2);
    printf("\nVetor W descoberto!\nw1:%.2f  w2:%.2f.\n",w1,w2);
    sleep(2);
    printf("\nAgora sera calculado a taxa de acerto do vetor W, com respectivo arquivo de Teste.\n");
    sleep(2);
    
    porcentTest(escolha,w1,w2);
      return 0;
}

float  definirW1deVetor(){
    float w1;

    printf("Informe o valor para a primeira coordenada do vetor inicial: ");
    scanf("%f", &w1);

    return w1;
}

float definirW2deVetor(){
    float w2;

    printf("Informe o valor da segunda coordenada do vetor inicial: ");
    scanf("%f", &w2);

    return w2;
}

float porcentTest(int escolha,float w1,float w2){
    
    char linha[100];
    float x1[30], x2[30], y[30];
    
    FILE *arquivo;
        if(escolha == 1)
        arquivo = fopen("A_t.txt", "r");
    else
       arquivo = fopen("B_t.txt", "r");
    if(arquivo == NULL) {
        printf("\narquivo desconhecido - nome_do_arquivo.txt\n");
        return 0;
    }
    int i=0;
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        fscanf(arquivo,"%f %f %f", &x1[i], &x2[i], &y[i]);
        i++;
    }   
    fclose(arquivo);
    i=0;
    int d = 0;
    int acerto=0;
    printf("\n");
    sleep(1);
    for(i=0;i<30;i++){
        float yr=0.0;
        d = 0;
        yr = (w1*x1[i])+(w2*x2[i]);
        printf("Yr é %.2f  e Y[i] : %0.2f\n",yr,y[i]);
        if(yr >=0){
            yr=1;
        }
        else if(yr<0){
            yr=0;
        }
        d = y[i] - yr;
        printf("C = %d e D = %d\n", i,d);
        if(d==0){
            acerto++;
        }else
            printf("ta errado\n");
    }
    float porcAcerto;
    porcAcerto = acerto*100/i;
    sleep(2);
    printf("\nTaxa de acerto foi : %.2f\n", porcAcerto);

    return 0;
}
