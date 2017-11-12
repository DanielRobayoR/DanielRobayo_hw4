Resultados_hw4.pdf : Resultados_hw4.tex figuras1d_caso1.png figuras1d_caso2.png figuras2d_Condi_Inicial.png figuras_2d_Temp1.png figuras_2d_Temp2.png figuras_2d_Temp3.png 
	pdflatex Resultados_hw4.tex

figuras1d_caso1.png figuras1d_caso2.png figuras2d_Condi_Inicial.png figuras_2d_Temp1.png figuras_2d_Temp2.png figuras_2d_Temp3.png sonido.wav : Plots.py Datos1d_t1Fijo.txt Datos1d_t2Fijo.txt Datos1d_t3Fijo.txt Datos1d_t1Pertu.txt Datos1d_t2Pertu.txt Datos1d_t3Pertu.txt Datos2d_t1.txt Datos2d_t2.txt Datos2d_t3.txt Datos1d_NodoEsp.txt
	python Plots.py

Datos1d_t1Fijo.txt Datos1d_t2Fijo.txt Datos1d_t3Fijo.txt Datos1d_t1Pertu.txt Datos1d_t2Pertu.txt Datos1d_t3Pertu.txt Datos2d_t1.txt Datos2d_t2.txt Datos2d_t3.txt : Ondas.x
	./Ondas.x

Ondas.x : Ondas.c
	cc Ondas.c -o Ondas.x -lm 




