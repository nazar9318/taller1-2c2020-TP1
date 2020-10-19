# Informe: Trabajo Práctico N°1: Crypto-Sockets
Alumno: Federico Elías

Padrón: 96105

Fecha de entrega: 20/10/2020

# Division de responsabilidades

Mains:

- Server y cliente:
		Inicializan el flujo del programa:
			-Crean un TDA server y cliente respectivamente
			pasándoles los argumentos recibidos por consola.
			-Llaman a los respectivos métodos que corren el programa.	
			-Liberan la memoria reservada para los TDAs y devuelven 0.
-	Pre condiciones:
		Ninguna
-	Post condiciones:
		Ninguna

Las responsabilidades del programa se dividieron en los siguientes TDAs:

- Server_usuario:
-	Descripción:
		Es el TDA encargado de ejecutar el programa desde el lado del server.
		El main de server le pasa todos los argumentos recibidos por consola,
		con el puerto crea un socket con el que se comunica con el cliente,
		luego crea un selector_t que recibe los otros argumentos para éste
		sepa cuáles son el método y la clave con los que se va a desencriptar
		el mensaje recibido por el socket. Por último crea un encoder_t que
		recibe el método y la clave del selector_t, el mensaje leído
		por el socket, y devuelve el mensaje traducido.
-	Pre condiciones:
		Ninguna.
-	Post condiciones:
		Imprime en pantalla el mensaje descifrado.

- Cliente_usuario:
-	Descripcion:
		Es el TDA encargado de ejecutar el programa desde el lado del cliente.
		El main del cliente le pasa todos los argumentos recibidos por consola,
		crea un socket, el host y el puerto, para comunicarse con el server,
		crea un file_reader para leer el archivo de entrada, ya sea que el
		archivo se reciba por entrada estándar o como un archivo de texto,
		el cual lee el contenido del archivo y lo devuelve en un arreglo
		de caracteres, luego crea un selector_t que recibe los otros argumentos
		para éste sepa cuáles son el método y la clave con los que se va a
		encriptar el mensaje a mandar a través del socket.
		Por último crea un encoder_t que recibe el método y la clave del
		selector_t, el mensaje leído, y devuelve el mensaje encriptado,
		luego se manda al server el mensaje encriptado a través del socket.
-	Pre condición:
		Ninguna.
-	Post condición:
		Ninguna.

- File_reader:
-	Descripción:
		Recibe un archivo previamente abierto y lo lee completo.
		Puede devolver el arreglo de caracteres leídos o el tamaño del mismo.
-	Pre condición:
		El archivo de entrada o bien viene por entrada estándar, o bien
		como un archivo de texto, no soporta lecturas de archivos binarios.
-	Post condición:
		Ninguna.

- Selector:
-	Descripción:
		Recibe el método y la clave de encriptación con el formato:
		'--metod=' para el método y '--key=' para la clave.
-	Pre condición:
		La lectura tanto del método como la clave es case sensitive.
-	Post condición:
		Ninguna.

- Encoder:
-	Descripción:
		Recibe el mensaje a codificar, el método y la clave correspondientes,
		y encripta o traduce de acuerdo a los argumentos recibidos.
-	Pre condición:
		Sólo soporta métodos Cesar, Vigenere y RC4.
-	Post condición:
		Ninguna.

- Socket:
-	Descripción:
		Recibe puerto si es server, o puerto y host si es cliente, y devuelve
		un socket con el que recibir o enviar mensajes respectivamente.
-	Pre condición:
		Ninguna.
-	Post condición:
		Ninguna.


- Diagrama que representa la división de responsabilidades de los TDAs:

![diagrama](https://github.com/nazar9318/taller1-2c2020-TP1/tree/master/assets/DiagramaTP1.png)
