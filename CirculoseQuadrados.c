//Trabalho de Caio de Souza Ortiz de Angelis
//AED 2
//RGM 47534



#include <gfx.h>
#include <stdio.h> 
#include <unistd.h>
void circulos(int x,int y,int xr,int yr,int nivel){
	
		double x1;
		double y1;
	
	
		gfx_set_color(255, 255, 255); 		//define cor
		gfx_ellipse(x, y, xr, yr);			//desenha os circulos

		y1 =y + yr/2 * sqrt(2)/2 ;
		x1 =x + xr/2 * sqrt(2)/2 ;			// calculo para fazer um auxiliar para faze-los ficarem no lugar certo
 		
   	 	

	if (nivel>0){
		circulos(x1,y1,xr/2,yr/2,nivel-1); 	 
	    circulos(x1,y1+(y-y1)*2,xr/2,yr/2,nivel-1);   
			
		circulos(x1 + (x - x1)*2,y1,xr/2,yr/2,nivel-1);
		circulos(x1 + (x - x1)*2,y1+(y-y1)*2,xr/2,yr/2,nivel-1);
	}
}
void retangulo(int x1,int x2,int y1,int y2,int nivel){
	//x1= direita
	//x2=esquerda
	//y1=cima
	//y2=baixo



	gfx_set_color(255, 255, 255);	//define cor
	gfx_rectangle(x1, y1, x2, y2); //faz os quadrados todos
	



		if (nivel>0){

			
			int aux = (x1-x2)/2;
			retangulo(x2,x2-aux,y1-(y1-y2)/4,y2+(y1-y2)/4,nivel-1);//esquerda
			retangulo(x1+aux,x1,y1-(y1-y2)/4,y2+(y1-y2)/4,nivel-1);//direita

			aux = (y1-y2)/2;

			retangulo (x1-(x1-x2)/4,x2+(x1-x2)/4,y2,y2-aux,nivel-1);//cima
			retangulo (x1-(x1-x2)/4,x2+(x1-x2)/4,y1+aux,y1,nivel-1);//baixo
			gfx_set_color(0, 0, 0);
			gfx_filled_rectangle(x1-1, y1-1, x2+1, y2+1); // esconde o quadrado dentro de outro pintando todos por dentro da mesma cor do fundo
	
		}
	}
	



	














int main()
{
	int menu,recursao;
	printf("Voce deseja fazer circulo ou retangulo?");
	printf("\n1-circulo\n2-retangulo");
	scanf("%d",&menu);
	while (menu!=1 && menu!=2){
		printf("\n1-circulo\n2-retangulo");
		scanf("%d",&menu);
	}
	printf("qual o nivel de recursao(de 1 a 10)");
	scanf("%d",&recursao);
	while (recursao>10 || recursao<0){
	printf("qual o nivel de recursao(de 1 a 10)");
	scanf("%d",&recursao);	
	}

	gfx_init(600,600, "Recursao geométrica");


	if (menu == 1)
	circulos(300,300,300,300,recursao);
	if (menu==2)
	retangulo(300+100,300-100,300+100,300-100,recursao);// achamos o meio 



	gfx_paint();
	sleep(5);
	gfx_quit();
	



	return 0;
}

