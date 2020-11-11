# Taller de Programación I - Cátedra Veiga - FIUBA
# Trabajo Práctico III 

<h2 align="right">Jonathan David Rosenblatt</h2>
<h2 align="right">104105</h2>

Introducción

Este es el tercer trabajo práctico de la materia en el que se debe entregar un producto programado y documentado. El mismo fue programado en C++ y requiere conocimientos en este lenguaje, además de conocimientos en la programación multi-hilos para implementar un sistema cliente-servidor. Este implementa, de forma reducida, un sistema cliente-servidor de gestión de petitorios HTTP. Aquí cada petitorio que recibe el servidor desde algún cliente sea procesado por un hilo en particular. Esto nos da un boost en eficiencia temporal gracias a la concurrencia.

## Configuración del Proyecto

Para configurar y ejecutar el código lo primero que se debe hacer es clonar el repositorio. Luego para compilar y enlazar se debe ejecutar el Makefile incluido (ejecutando ```make```). En caso de tener errores con el compilador o el enlazador se verán escritos por stderr.

Se debe ejecutar el servidor con:  

```
./server <PORT> <ROOTFILE>
```

Y el cliente con:

```
./client <IP> <PORT>
```

Siendo:

- ```<IP>```: La IPV4 del servidor al cual nos queremos conectar ***desde el lado del cliente***.
- ```<PORT>```: El puerto designado para conectarse.
- ```<ROOTFILE>```: El archivo raíz que leerá el cliente para responder a los petitorios.

***Se pueden ejecutar varios clientes y estos serán atendidos en paralelo, gracias a nuestra implementación que permite generar respuestas de forma concurrente como consecuencia del uso de Threads.***

## Diseño y Clases

<br><p align="center"><img src="img/classdiag.png"/></p> 

<br><p align="center"><img src="img/seqdiagclient.png"/></p> 

<br><p align="center"><img src="img/seqdiagserver.png"/></p> 

## Herramientas Utilizadas

Las herramientas más utilizadas en este tp fueron:

- ***Valgrind***: el glorioso programa que tanto nos ayuda a debuggear el código. Con flags como ```--track-origins=yes``` para ver donde se nos generan variables no inicializadas que puedan causar problemas; ```--leak-check=full``` para detectar donde se generan variables no inicializadas; y ```--track-fds=yes``` para verificar que no estamos dejando ningún fd abierto de más; entre otros.

- ***Gdb***: el debugger de GNU, súper útil para revisar con detalle el código y encontrar más facilmente la causa de problemas como segmentation faults, loops infinitos, entre otros.

- ***Tiburoncín***: herramienta desarrollada por la cátedra. Muy útil para rastrear el paso de los datos de cliente a servidor y viceversa. Nos permite potencialmente discernir si un problema viene del lado del servidor o del cliente.
