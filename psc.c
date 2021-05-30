#include <stdio.h>
#include <math.h>
#define L (int) (1024+2) /*lembrar de reajustar o sorteio*/
#define Ra (int) ((16*4)+2) /*lado do quadrado da secao*/
#define Ra2 (int) 8
#define TAL (int)1 /*valor de 4 tal=524288 6tal=786432 metade do raio*/
#define Eo (float)0.25 /*epsulom*/
#define Pi (double)4294967294.9999 /*valor maximo*/
#define pp (double)0.1 /*prob de dissolver*/
#define n (int)100 /*prob de passos extras*/
#define Rmax (double) 100 /*numero de repeticoes do evento*/

/*modelo oficial de difusao em meio composto com random walk*/
/*falta verificar o formato final do poro e o sorteio*/
/*programa para u maiores que 1*/

int main()
{

        char nome[40];
        unsigned int i,j,k,chave,map[L+L+1][Ra][Ra],xyz[3],prob,prob2,dir,sent,c,contp,contdiss,rep,x2,l2,PP,raio1,raio2;
        register unsigned int r,r2,r3,viz;
        double percent[L+L],pcmedia[L+L];
        long int Dissmax,tmed,contpmed;
        FILE *pont,*pont2;

        PP=(int)1/pp;
        snprintf(nome,40,"porosimples/U%dp1s%dtal%d",n,PP,TAL);
        pont=fopen(nome,"w");
        snprintf(nome,40,"%sinfo",nome);
        pont2=fopen(nome,"w");

        r=11111111;
        r2=11111111;
        r3=11111111;

        tmed=contpmed=0;
        Dissmax=TAL*(((Ra-2)/4)*4*(L-2))+(Ra2*4*(L-2));

        for(rep=0;rep<Rmax;rep++)
        {
                contdiss=0;
                contp=0;
                x2=25;
                l2=30;
                chave=1;

                /*formacao do poro*/
                for(i=0;i<L+L;i++) /*preenche a borda com 2 e todos os poros com 1*/
                {
                        for(j=0;j<Ra;j++) map[i][0][j]=map[i][j][0]=map[i][j][(Ra-1)]=map[i][(Ra-1)][j]=2;
                        for(j=1;j<(Ra-1);j++) for(k=1;k<(Ra-1);k++) map[i][j][k]=1;
                }

                raio1=((Ra-2)*.375)+1;
                for(i=0;i<L;i++) /*preenche os vazios do maior poro*/
                {
                        for(j=raio1;j<((Ra-2)-raio1+2);j++) for(k=raio1;k<((Ra-2)-raio1+2);k++) map[i][j][k]=0;
                }

                for(i=L;i<L+L;i++) /*preenche os vazios do menor poro*/
                {
                        for(j=(Ra-2)/2-Ra2/2+1;j<(Ra-2)/2+Ra2/2+1;j++) for(k=(Ra-2)/2-Ra2/2+1;k<(Ra-2)/2+Ra2/2+1;k++) map[i][j][k]=0;
                }

                raio1=((Ra-2)*.375)+1;
                for(contp=0;contp<5;contp++) /*faz a escada da transicao entre os poros*/
                {
                        for(i=L-4+contp;i<=L;i++)
                        {

                                raio2=((Ra-2)-raio1+1);
                                for(j=raio1;j<=raio2;j++) map[i][raio1][j]=map[i][j][raio1]=map[i][raio2][j]=map[i][j][raio2]=1;
                        }
                        raio1++;
                }
                contp=0;
        for(i=1;i<Ra;i++)
        {
                for(j=1;j<Ra;j++) printf("%d ",map[L-3][i][j]);
                printf("\n");
        }

return(0);
                for(i=0;i<Ra;i++) for(j=0;j<Ra;j++) map[0][i][j]=map[L+L][i][j]=2;
                /*fim da formacao do poro*/

resort:         viz=0; /*resort tem que ficar junto com viz=0*/
                        while(viz<2)
                        {
                                viz=0;
                                xyz[0]=xyz[1]=xyz[2]=0;
                                r*=65539;
                                r2*=16807;
                                r3*=1101513973;
                                xyz[0]=(r2>>29)+((r>>28)<<3)+((r3>>28)<<7);
                                xyz[0]+=1;
                                r*=1101513973;
                                r2*=1101513973;
                                xyz[1]=(r2>>29)+((r>>l2)<<3);
                                xyz[1]+=x2;
                                r2*=65539;
                                r3*=65539;
                                xyz[2]=(r3>>29)+((r2>>l2)<<3);
                                xyz[2]+=x2;
                                if(map[xyz[0]+1][xyz[1]][xyz[2]]==0) viz=1;
                                else if(map[xyz[0]-1][xyz[1]][xyz[2]]==0) viz=1;
                                if(map[xyz[0]][xyz[1]+1][xyz[2]]==0) viz=1;
                                else if(map[xyz[0]][xyz[1]-1][xyz[2]]==0) viz=1;
                                if(map[xyz[0]][xyz[1]][xyz[2]+1]==0) viz=1;
                                else if(map[xyz[0]][xyz[1]][xyz[2]-1]==0) viz=1;
                                if(map[xyz[0]][xyz[1]][xyz[2]]==1) viz++; /*verifica se eh um solido*/
                        }
                        if((xyz[1]>=48||xyz[1]<=19||xyz[2]>=48||xyz[2]<=19)&&chave) {x2=1;l2=30;chave=0;/*printf("hit");*/}
                        /*inicio prob dissolucao*/
                        viz=0;
                        if(map[xyz[0]+1][xyz[1]][xyz[2]]>0) viz++; /*prob em funcao do numero de vizinhos*/
                        if(map[xyz[0]][xyz[1]+1][xyz[2]]>0) viz++;
                        if(map[xyz[0]][xyz[1]][xyz[2]+1]>0) viz++;
                        if(map[xyz[0]-1][xyz[1]][xyz[2]]>0) viz++;
                        if(map[xyz[0]][xyz[1]-1][xyz[2]]>0) viz++;
                        if(map[xyz[0]][xyz[1]][xyz[2]-1]>0) viz++;
                        r*=65539;
                        r2*=16807;
                        r3*=1101513973;
                        prob=(r3>>22)+((r2>>22)<<10)+((r>>15)<<22);
				    prob2=(unsigned int)(4294967294.9999*pow(Eo,viz));
                        if(prob>prob2) goto resort;
                        contdiss++;
                        /*fim prob dissolucao*/

                        /*passo inicial*/
                        for(c=0;c<1;r*=16807)
                        {
                                for (dir=3;dir==3;r3*=1101513973) dir=(r3>>30);
                                sent=(r>>31);
                                xyz[dir]+=((2*sent)-1);
                                if(map[xyz[0]][xyz[1]][xyz[2]]==2)
                                {
                                        if(xyz[0]<1) {xyz[dir]-=((2*sent)-1);c++;}
                                        else
                                        {
                                                xyz[dir]-=(2*sent)-1;
                                                map[xyz[0]][xyz[1]][xyz[2]]=0;
                                                contp++;
                                                goto resort;
                                        }
                                }
                                else if(map[xyz[0]][xyz[1]][xyz[2]]==0)
                                {
                                        map[xyz[0]][xyz[1]][xyz[2]]=1;
                                        xyz[dir]-=((2*sent)-1);
                                        map[xyz[0]][xyz[1]][xyz[2]]=0;
                                        xyz[dir]+=((2*sent)-1);
                                        c++;
                                }
                                else if(map[xyz[0]][xyz[1]][xyz[2]]==1) xyz[dir]-=((2*sent)-1);
                        }
                        /*fim passo inicial*/

                        map[xyz[0]][xyz[1]][xyz[2]]=0;
                        for(c=1;c>0;r*=16807)
                        {
                                /*sorteio da direcao e sentido*/
                                for(dir=3;dir==3;r2*=65539) dir=(r2>>30);
                                sent=r>>31;
                                xyz[dir]+=(2*sent)-1; /*adiciona o passo na direcao escolhida*/
                               /*fim do sorteio*/

                                /*contato com as bordas limites*/
                                if(map[xyz[0]][xyz[1]][xyz[2]]==2)
                                {
                                        if(xyz[0]==0) xyz[0]-=(2*sent)-1;
                                        else
                                        {
                                                contp++;
                                                goto resort;
                                        }
                                }
                                /*fim do contato com borda limite*/

                                else
                                {
                                        if(map[xyz[0]][xyz[1]][xyz[2]]==1) xyz[dir]-=(2*sent)-1; /*verifica se possui obstaculo no passo*/

                                        /*passo extra na direcao do fluxo*/
                                        for(i=1;i<=n;i++)
                                        {
                                                xyz[0]++;
                                                if(map[xyz[0]][xyz[1]][xyz[2]]==2)
                                                {
                                                        contp++;
                                                        goto resort;
                                                }
                                                if(map[xyz[0]][xyz[1]][xyz[2]]==1)  /*verifica se possui obstaculo no passo*/
                                                {
                                                        xyz[0]-=1;
                                                        i=n;
                                                }
                                        }
                                        /*fim do passo extra*/

                                        /*verifica a precipitacao*/
                                        viz=0;
                                        if(map[xyz[0]+1][xyz[1]][xyz[2]]==1) viz=1;
                                        if(map[xyz[0]][xyz[1]+1][xyz[2]]==1) viz=1;
                                        if(map[xyz[0]][xyz[1]][xyz[2]+1]==1) viz=1;
                                        if(map[xyz[0]-1][xyz[1]][xyz[2]]==1) viz=1;
                                        if(map[xyz[0]][xyz[1]-1][xyz[2]]==1) viz=1;
                                        if(map[xyz[0]][xyz[1]][xyz[2]-1]==1) viz=1;
                                        if(viz)
                                        {
                                                r2*=16807;
                                                if((double)r2<(double)(Pi*(double)pp))
                                                {
                                                        map[xyz[0]][xyz[1]][xyz[2]]=1;
                                                        c=0;
                                                        goto resort;
                                                }
                                        }
                                        /*final da precipitacao*/

                                }
                                if(contdiss>Dissmax) break;
                        }
                        if(contdiss<Dissmax) goto resort;

                        contpmed+=contp;
                        tmed+=contdiss;


                        for(i=1;i<(L+L-2);i++)
                        {
                                percent[i]=0;
                                for(j=1;j<(Ra-1);j++)
                                {
                                        for(k=1;k<(Ra-1);k++) if(map[i][j][k]==0) percent[i]++;
                                }
                                percent[i]/=(((Ra-2)/4)*((Ra-2)/4));
                                pcmedia[i]+=percent[i];
                        }

        }

        for(i=1;i<(L+L-2);i++) fprintf(pont,"%d %lf\n",i,(pcmedia[i]/Rmax));


        fprintf(pont2,"Tmedio = %lf Media de P.perdidas = %lf Part. Dissolv. = %li",(double)tmed,(contpmed/Rmax),Dissmax);
        fclose(pont);fclose(pont2);

        return (0);
}


