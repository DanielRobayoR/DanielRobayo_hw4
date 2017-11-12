import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.io.wavfile import write

def procesar(data):
	matriz = np.zeros((101, 101))
	contador = 0
	for i in range(0,101):
		for j in range(0,101):
			contador = contador+1
			matriz[i][j]=data[contador-1]
	return matriz

DatosIniciales1D = np.genfromtxt('cond_ini_cuerda.dat')
DatosIniciales2D = np.genfromtxt('cond_ini_tambor.dat')

Datos1d_NodoEsp = np.genfromtxt('Datos1d_NodoEsp.txt')
T = Datos1d_NodoEsp[:,0]

Datos1d_t1Fijo = np.genfromtxt('Datos1d_t1Fijo.txt')
Datos1d_t2Fijo = np.genfromtxt('Datos1d_t2Fijo.txt')
Datos1d_t3Fijo = np.genfromtxt('Datos1d_t3Fijo.txt')

Datos1d_t1Pertu = np.genfromtxt('Datos1d_t1Pertu.txt')
Datos1d_t2Pertu = np.genfromtxt('Datos1d_t2Pertu.txt')
Datos1d_t3Pertu = np.genfromtxt('Datos1d_t3Pertu.txt')

X = Datos1d_t1Fijo[:,0]

Datos2d_t1Noprocesado = np.genfromtxt('Datos2d_t1.txt')
Datos2d_t1 = procesar(Datos2d_t1Noprocesado)
Datos2d_t2Noprocesado = np.genfromtxt('Datos2d_t2.txt')
Datos2d_t2 = procesar(Datos2d_t2Noprocesado)
Datos2d_t3Noprocesado = np.genfromtxt('Datos2d_t3.txt')
Datos2d_t3 = procesar(Datos2d_t3Noprocesado)


#Grafica para 1D Sin perturbacion
phi_a1 = DatosIniciales1D[:,1] # t=0
phi_a2 = Datos1d_t1Fijo[:,1] # t=1/8T
phi_a3 = Datos1d_t2Fijo[:,1] # t=1/4T
phi_a4 = Datos1d_t3Fijo[:,1] # t=1/2T

plt.figure()
plt.plot(X,phi_a1, label='t=0', c='red')
plt.plot(X,phi_a2, label='t=1/8T', c='green')
plt.plot(X,phi_a3, label='t=1/4T', c='blue')
plt.plot(X,phi_a4, label='t=1/2T', c='orange')
plt.title('Caso Cuerda Sin Perturbacion')
plt.legend()
plt.xlabel('Distancia (mts)')
plt.ylabel('Phi')
plt.savefig("figuras1d_caso1.png")


#Grafica para 1D Con perturbacion
phi_A1 = DatosIniciales1D[:,1] # t=0
phi_A2 = Datos1d_t1Pertu[:,1] # t=1/8T
phi_A3 = Datos1d_t2Pertu[:,1] # t=1/4T
phi_A4 = Datos1d_t3Pertu[:,1] # t=1/2T

plt.figure()
plt.plot(X,phi_A1, label='t=0', c='red')
plt.plot(X,phi_A2, label='t=1/8T', c='green')
plt.plot(X,phi_A3, label='t=1/4T', c='blue')
plt.plot(X,phi_A4, label='t=1/2T', c='orange')
plt.title('Caso Cuerda Con Perturbacion')
plt.legend()
plt.xlabel('Distancia (mts)')
plt.ylabel('Phi')
plt.savefig("figuras1d_caso2.png")

#Evolucion nodo de la mitad para 1D (Archivo de Sonido)
phi_ANud = Datos1d_NodoEsp[:,1]
norma = np.int16(phi_ANud/np.max(np.abs(phi_ANud)) * 32767)
write('sonido.wav',44100,norma) 

#Grafica para 2D

plt.figure()
x = np.arange(0, 0.5, 0.005)
y = np.arange(0, 0.5, 0.005)
X, Y = np.meshgrid(x, y)
fxy = DatosIniciales2D
plt.imshow(fxy);
plt.colorbar();
plt.savefig("figuras2d_Condi_Inicial.png")


plt.figure()
x = np.arange(0, 0.5, 0.005)
y = np.arange(0, 0.5, 0.005)
X, Y = np.meshgrid(x, y)
fxy = Datos2d_t1
plt.imshow(fxy);
plt.colorbar();
plt.savefig("figuras_2d_Temp1.png")


plt.figure()
x = np.arange(0, 0.5, 0.005)
y = np.arange(0, 0.5, 0.005)
X, Y = np.meshgrid(x, y)
fxy = Datos2d_t2
plt.imshow(fxy);
plt.colorbar();
plt.savefig("figuras_2d_Temp2.png")


plt.figure()
x = np.arange(0, 0.5, 0.005)
y = np.arange(0, 0.5, 0.005)
X, Y = np.meshgrid(x, y)
fxy = Datos2d_t3 
plt.imshow(fxy);
plt.colorbar();
plt.savefig("figuras_2d_Temp3.png")





