//cc Ondas.c -o Ondas.x -lm
//./Ondas.x
#include <stdio.h>
#include<math.h>
int main(){

//Resolvemos en 1 dimension con condicion de frontera no variante (Condi = 0) o variante (Condi = 1) 
int Dim1(float Tfin, int Condi, int Nud, float delta_t, int Nombre)
{
	//Leer archivos
	FILE *Datos;
	Datos = fopen("cond_ini_cuerda.dat", "r");   //Abrimos  el archivo
	float * Condi_Ini = malloc(258*sizeof(float));
	float * Condi_Ini_New = malloc(129*sizeof(float));  
	float * X_New = malloc(129*sizeof(float));
	int i;
	for(i=0;i<259;i++)                                   
	{
	fscanf(Datos, "%f", &Condi_Ini[i]); 
	}
	int cont = 0;
	int j;
	for(j=0;j<259;j++)                                   
	{
	if (j<129){X_New[j]=0.005000*j;}
	if ( j % 2 != 0 ){
		Condi_Ini_New[cont]= Condi_Ini[j];
		cont = cont + 1;}
	}
	fclose(Datos);
	//printf("%f \n", Condi_Ini_New[76]); En este punto, Condi_Ini_New ya contiene los datos que necesito
	int N = 128; //Puesto que el ultimo nodo siempre es constante
	float delta_x= 0.005;
	int t;
	int p;
	float L=0.64;
	float pi=3.14159265;
	float val = pi / 180 ;
	float c = 250;
	float lamda = (pow(c,2)*pow(delta_t,2))/(pow(delta_x,2));
	float * Variante = malloc(129*sizeof(float));
	float * tempo_anterior = malloc(129*sizeof(float));
	float * nodo_especif = malloc(((Tfin/delta_t) + 1) *sizeof(float)); //Toca sumarle 1 porque corresponde al tiempo en 0
	float * tempo_nodo_especif = malloc(((Tfin/delta_t)+1)*sizeof(float)); 
	nodo_especif[0]=Condi_Ini_New[Nud];
	tempo_nodo_especif[0]= 0.000000;
	int Ultimo_T=(Tfin/delta_t);
	float phi_next;
	for(t=1; t<=Ultimo_T; t++){ //Me recorrera el tiempo, solo me sirve para que calcule hasta el tiempo que se requiere
		tempo_nodo_especif[t]=delta_t*t;
		if(Condi==1){
		Condi_Ini_New[0]= sin((((2*pi*c)/L)*(t*delta_t))*val);
		Variante[0]= Condi_Ini_New[0];} //Este If es para que hayan condicones de frontera variables 
		if(Condi==0){
		Variante[0]= Condi_Ini_New[0];} 
		for(p=1; p<N; p++){ //Me recorrera los nodos
			if(t==1){for(i=0; i<129; i++){tempo_anterior[i]= 0.000000;}}
			phi_next = ((Condi_Ini_New[p-1]-2*Condi_Ini_New[p]+Condi_Ini_New[p+1])*lamda)+(2*Condi_Ini_New[p]-tempo_anterior[p]); 
			Variante[p]=phi_next;
			if(p==Nud){nodo_especif[t]=phi_next;}
		}
		Variante[128]=0.000000;
		for (i=0; i<=128;i++){tempo_anterior[i]=Condi_Ini_New[i];}  // Lleno tempo_anterior con los varlores de Condi_Ini_New para mantener los valores en el tiempo anterior
		for (i=0; i<=128;i++){Condi_Ini_New[i]=Variante[i];}  // Lleno Condi_Ini_New con los varlores de variante
	//Al final de todo el vector que tendra los datos que necesito seria Condi_Ini_New (Para graficar)
	}
	if(Nombre==0){
	FILE* out1 = fopen("Datos1d_NodoEsp.txt","w");
	for(i=0;i<=(Tfin/delta_t);i++){fprintf(out1,"%f %f \n",tempo_nodo_especif[i],nodo_especif[i]);} 
	}
	if(Nombre==1){
	FILE* out2 = fopen("Datos1d_t1Fijo.txt","w");
	for(i=0;i<129;i++){fprintf(out2,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
	if(Nombre==2){
	FILE* out3 = fopen("Datos1d_t2Fijo.txt","w");
	for(i=0;i<129;i++){fprintf(out3,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
	if(Nombre==3){
	FILE* out4 = fopen("Datos1d_t3Fijo.txt","w");
	for(i=0;i<129;i++){fprintf(out4,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
	if(Nombre==4){
	FILE* out5 = fopen("Datos1d_t1Pertu.txt","w");
	for(i=0;i<129;i++){fprintf(out5,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
	if(Nombre==5){
	FILE* out6 = fopen("Datos1d_t2Pertu.txt","w");
	for(i=0;i<129;i++){fprintf(out6,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
	if(Nombre==6){
	FILE* out7 = fopen("Datos1d_t3Pertu.txt","w");
	for(i=0;i<129;i++){fprintf(out7,"%f %f \n",X_New[i],Condi_Ini_New[i]);} 
	}
return 0;
}

//Caso extremos fijos

Dim1(0.001, 0, 0, 0.00001, 1); //(float Tfin, int Condi, int Nud, float delta_t, nombre)
Dim1(0.004, 0, 0, 0.00001, 2);
Dim1(0.008, 0, 0, 0.00001, 3);

//Caso Pertubacion
Dim1(0.001, 1, 0, 0.00001, 4);
Dim1(0.004, 1, 0, 0.00001, 5);
Dim1(0.008, 1, 0, 0.00001, 6);

// Caso Nodo Espesifico (Nodo de la mitdad)

Dim1(0.441, 0, 64, 0.00001, 0); // 64 corresponde a la mitad de la cuerda

 

int Dim2(float Tfin, float delta_t, int Nombre)
{
	int N = 100; 
	float delta_x= 0.005; // Delta x = Delta y
	float delta_y= 0.005;
	int t;
	int px;
	int py;
	float L=0.5;
	float c = 250;
	float lamda = (pow(c,2)*pow(delta_t,2))/(pow(delta_x,2));
	//Leer datos
	int i;
	int j;
	int cambio=0;
	float * ArrregloBruto = malloc(10201*sizeof(float));
	FILE *Load;
	Load = fopen("cond_ini_tambor.dat", "r");

	for(i=0;i<10201;i++){
		fscanf(Load, "%f", &ArrregloBruto[i]); 
		}

	float matriz[101][101];

	for(i=0;i<101;i++){
		for(j=0;j<101;j++){
		cambio = cambio +1;
		matriz[i][j]= ArrregloBruto[cambio-1];
		}
	}
	
	fclose(Load);

	float Variante[101][101];
	float tempo_anterior[101][101];
	int Ultimo_T=(Tfin/delta_t);
	float phi_next;
	for(i=0; i<101; i++){
		for(j=0; j<101; j++){ 
			Variante[0][j]= matriz[0][j];  
			Variante[N][j]= matriz[N][j];
			Variante[i][0]= matriz[i][0];
			Variante[i][N]= matriz[i][N];
			tempo_anterior[i][j]= 0.000000;
		}
	}

	for(t=1; t<=Ultimo_T; t++){ 
		for(px=1; px<N; px++){  //Me recorrera la posicion en x
			for(py=1; py<N; py++){ //Me recorrera la posicion en y
				phi_next = ((matriz[px][py+1]-4*matriz[px][py]+matriz[px][py-1]+matriz[px+1][py]+matriz[px-1][py])*lamda)+(2*matriz[px][py]-tempo_anterior[px][py]); 
				Variante[px][py]=phi_next;
			}
		}
			for(i=0; i<101; i++){for(j=0; j<101; j++){tempo_anterior[i][j]=matriz[i][j];}}  // Lleno tempo_anterior con los varlores de Condi_Ini_New para mantener los valores en el tiempo anterior

			for(i=0; i<101; i++){for(j=0; j<101; j++){matriz[i][j]=Variante[i][j];}}  // Lleno Condi_Ini_New con los varlores de variante

	//Al final de todo el vector que tendra los datos que necesito seria matriz (Para graficar)
	}
	if(Nombre==1){
	FILE* out1 = fopen("Datos2d_t1.txt","w");
	for(i=0;i<101;i++){for(j=0;j<101;j++){fprintf(out1,"%f     ", matriz[i][j]);}printf("\n");} 
	}
	if(Nombre==2){
	FILE* out2 = fopen("Datos2d_t2.txt","w");
	for(i=0;i<101;i++){for(j=0;j<101;j++){fprintf(out2,"%f     ", matriz[i][j]);}printf("\n");} 
	}
	if(Nombre==3){
	FILE* out3 = fopen("Datos2d_t3.txt","w");
	for(i=0;i<101;i++){for(j=0;j<101;j++){fprintf(out3,"%f     ", matriz[i][j]);}printf("\n");} 
	}
	
return 0;
}

Dim2(0.001, 0.00001, 1); //float Tfin, float delta_t, int Nombre
Dim2(0.006, 0.00001, 2);
Dim2(0.008, 0.00001, 3);




return 0;

}

