## Moralla_Billetes

PDF tutorial paso a paso de como armar esta maquina
https://drive.google.com/file/d/1STIBDis3MC1J_WjcIFt2KaZz-80KG3DJ/view?usp=sharing

Codigo para Maquina Morralla_Billetes_Monedas

####INDICE

######Introduccion a Morralla

######Partes empleadas de hardware

######Esquema de conexion para Leer pulsos del Monedero

######Codigo Leer Pulsos de Moneero

######Esquema de conexion para Leer pulsos del NV10USB

######Codigo Leer pulsos del NV10USB

######Esquema de conexion para Accionar Hopper con Modulo de Relevador

######Codigo Accionar Hopper con modulo

######Esquema de conexion para Leer pulsos del Sensor del Hopper expulsador de Monedas

######Codigo Leer pulsos del Sensor del Hopper

######Esquema de Morralla_V1 

######Codigo de Morralla_V1

######Libreria de Funciones empleadas 

######Nomenclatura del Codigo

######Videos & Ligas

######Contactame por estos medios
---
####INTRODUCCION

Hay una alta demanda de feria todos los dias para comerciantes y compradores, y una gran escazes de feria durante 2/3 del dia. Los metodos actuales para abastecerse de feria son incompetentes eh inciertos pues lo hacen de forma gratuita y de muy mala gana. Debido a este y a otros factores los negocios no cuentan con el suficiente cambio para cobrar por sus productos o servicios. Esto es un problema serio cuando ellos tienen que dejar ir una venta por no poder regresarle feria suficiente al cliente.

"Morralla" es un proyecto personal, donde intento crear una solucion funcional y factible para este problema que veo a diario a mi alrededor. Esta maquina te provee de una forma simple, automatizada, confiable y accesible a toda hora del dia una forma de obtener feria en monedas y billetes de tu eleccion, a cambio de una pequeña cuota por transacción. (10% sobre el Billete)

| Moneda    | Comission    | Recibes  |
| ------------- |:-------------:| -----:|
| $ 1.00 | -$ 0.00 | $ 1.00 |
| $ 2.00 | -$ 0.00 | $ 2.00 |
| $ 5.00 | -$ 0.00 | $ 5.00 |
| $10.00 | -$1.00 | $ 9.00 |

| Billete    | Comission    | Recibes  |
| ------------- |:-------------:| -----:|
| $ 20.00 | -$ 2.00 | $ 18.00 |
| $ 50.00 | -$ 5.00 | $ 45.00 |
| $100.00 | -$10.00 | $ 90.00 |
| $200.00 | -$20.00 | $180.00 |
| $500.00 | -$50.00 | $450.00 |
---
####HARDWARE EMPLEADO

La mayoria del hardware empleado es sacado de estas maquinas de apostar

![screen shot 2017-06-20 at 11 39 34 am](https://user-images.githubusercontent.com/11970000/27344793-293dda00-55ad-11e7-9671-a24830ffa0db.png)

Le llamaremos a esta maquina la Maquina de Frutitas y esta viene con todas estas partes:

[IMG Hardware MercadoLibre]

![screen shot 2017-06-20 at 11 15 55 am](https://user-images.githubusercontent.com/11970000/27343855-e5577d6c-55a9-11e7-930f-0d63ee7ae30a.png)

El hardware que no viene incluido en estas maquinas y que puedes conseguir por mercadolibre o alguna otra pagina web es el siguiente:

+ Monedero Electrónico de Múltiples Monedas
+ Arduino MEGA
+ Modeulo Relevador de 5v para Arduino
+ Lector de Billetes NV10USB
+ Fuente 12v 3A para Lector de Billetes NV10USB
+ Cable (2-3 mts)

El arduino Mega, es el que empleo para leer las señales de pulsos, de tanto el lector de monedas, como el lector de billetes, asi como los pulsos de cada sensor de hopper, que me indicant cuando sale una moneda. Este tambien me permite encender mediante el relevador los hoppers.
---
####LEER PULSOS DE MONEDERO

PARTE 001: Leer Pulsos del Monedero Electrónico

Queremos que la maquina lea distintas monedas y según estas monedas, expulse una cantidad de pesos. El monedero que viene con la maquina de tragamonedas de fruititas solo lee un tipo de moneda, este monedero no nos sirve, a menos que metamos uno de estos para cada tipo de moneda. Por el precio de $650, podemos emplear un solo monedero electrónico que se le puede configurar para que lea hasta 4 diferentes tipos de moneda.

[IMG Monedero]
![screen shot 2017-06-20 at 11 19 04 am](https://user-images.githubusercontent.com/11970000/27343992-5da77240-55aa-11e7-91cc-49ed89b92087.png)

Hay que configurar el monedero con las monedas que queremos que lea, así como la cantidad de pulsos que queremos que emita al leer dicha moneda, no entrare en detalle de cómo hacer esto, dejare una liga a un video-tutorial para configurar el monedero: 

https://www.youtube.com/watch?v=G_ubo3hjXhI

Vamos a configurar la moneda de $10 para que emita #9 pulsos, la moneda de $5 para que emita #5 pulsos, y la moneda de $2 para que emita #2 pulsos y la moneda de $1 que emita #1 pulso. 

Una vez configurado el monedero múltiple, necesitamos calar que este monedero funcione, introduzca una moneda de $10, el monedero deberá de mostrar en el “Display” del monedero, el numero de pulsos que usted le designo al configurarlo, en este caso #9 para esa moneda.
Repita este procedimiento para cada moneda, de no leer un tipo de moneda o no mostrar los pulsos deseados, regrese al video y repita el procedimiento.

| Moneda    |   $1.00  | $5.00  | $10.00  |
| ------------- | -----:| -----:| -----:|
| Pulsos | 1 | 5 | 10 |


Una vez seguro de que el monedero esta pre configurado correctamente, falta hacer que podamos leer y contar estos pulsos con el Arduino Mega. A continuación conectaremos el monedero como sigue, empleando la fuente de la maquina de tragamonedas, conectaremos el cable rojo del monedero a la salida de la fuente de 12v, conectaremos el cable blanco del monedero a el pin #2 del arduino mega, conectaremos el cable negro a GND de la fuente de la maquina de tragamonedas, los cables grises, vienen 2, son para un contador electrónico, estos los dejaremos solos. Hay que conectar el arduino mega a la fuente de la maquina tragamonedas con salida de 5v, al pin que dice “5v” y el cable de tierra GND de la fuente de poder de la maquina tragamonedas al pin del arduino mega que dice GND. Dibuje un diagrama de cómo debería de quedar.

[IMG de Fuente de poder Perla Oriente 5v 8v 12v SSR]

![screen shot 2017-06-20 at 11 31 04 am](https://user-images.githubusercontent.com/11970000/27344469-fc4efde0-55ab-11e7-8d7a-bcd386a041cb.png)

Empleo los pins en de 12v, 5v, GND, y SSR. El de 8v no lo uso. Conecto el lector de monedas a los 12v y a GND de esta fuente. Conecto el arduino a los 5v y a GND de la fuente. Conecto el relevador a el pin de SSR, que acciona al jalarlo a tierra como el boton negro (Cuadro Verde) Basicamente el relebador conectado al arduino actua como un boton push, pues conecta el cable que sale de pin SSR de la fuente a el mismo cable de de la fuente GND. Prendiendo el hopper. Inicialmente queria conectar el Hopper a la luz, y mandarle corriente con el relevador, pero como se calentaba y el arduino me leria mucha basura emitiendo del sensor del hopper, opte por hacerlo asi pues de esta forma no leeia basura y tampoco se calentaba.

[IMG Diagrama Arduino Monedero Fuente]
![screen shot 2017-06-20 at 11 20 26 am](https://user-images.githubusercontent.com/11970000/27344025-7f6d4ecc-55aa-11e7-881d-78b99bf4d669.png)

Una vez este conectado el hardware, hay que escribir un programa con el Arduino IDE para leer los pulsos emitidos por el monedero al introducir una moneda.

Yo escribí este programa “test_leer_pulsos_monedero.ino” se lo adjuntare en el correo junto con este archivo si falta pídamelo yo se lo vuelvo a enviar, espero le resulte útil, usted esta libre de escribir el suyo, le advierto este código a veces cuenta pulsos de mas, y este bug hasta hoy no lo eh podido arreglar. Espero que compartiendo y comentado el código pueda ver la falla, o me pueda ayudar usted a generar otro código para leer los pulsos.

Copie y pegue el siguiente programa en el IDE del arduino, guárdelo en su compu, verifique que este este bien, compilandolo con el icono de la palomita, luego conecte el arduino mega, verifique que el COM y el tipo de placa sean los corectos, para poder cargar el programa al arduino mega.

Una vez cargado, abra la consola (icono lupa), espere a que carge el programa, encienda el monedero electrónico, (asegurese de que este todo conectado como en la imagen anterior) eh introduzca una moneda, este programa debería de mostrarle el siguiente mensaje en consola “Nueva moneda detectada” y luego la cantidad de pulsos asignados a esa moneda.

{CODIGO LEER PULSOS MONEDERO}
---
###PARTE 002: Leer pulsos del Lector NV10USB

Este es el lector que uso, hay una version mas simple y barata, el NV20, yo no lo pude conseguir, y compre este. Viene con diferentes funciones, yo lo puse en modo de pulsos, para comunicarlo con el arduino, pero tiene la opcion de conectarlo a un compu (lo recomendado y mas seguro)

![screen shot 2017-06-20 at 11 35 55 am](https://user-images.githubusercontent.com/11970000/27344638-aa4c6586-55ac-11e7-9291-f14d6c1b48dd.png)

Este lector lo compre en mercadolibre. Qualmex vende de estos tambien, pero no se que precio manejen, seguro y es menos que los $2850
http://articulo.mercadolibre.com.mx/MLM-539822865-lector-de- billetes-nv10-maquinas-de-casino-gamers-vending-_JM 

Abajo esta el lector de $700 USD lo vende Qualmex, y es el lector segun ellos, que nesecito para que una maquina reciba y expulse billetes. Ellos me venderian esta pieza, y darian asesoria tecnica asi como algunas librerias de programas ya hechos para poder meter este lector a una compu.

http://www.qualmex.com/producto/444

Empleo la fuente que venia con la maquina tragamonedas, pero aun falta darle poder al lector de billetes, y este requiere mayor amperaje que los que requieren el arduino, el monedero, y el relevador. No se si se pueda emplear una fuente especial para conectar todos a una, mientras yo ocupo 2 fuentes. OJO: los pins de la fuente varían de orden, así vienen en las fuentes que yo tengo, estas pueden no ser las mismas para su fuente, normalmente vienen etiquetadas, pero si no, hay que medir cuanto voltaje emite cada una, no se como xD creo que con un multímetro.

Para leer los billetes, hay que poner el lector de billetes en modo de pulsos. Para esto primero nesecitas conectar el NV10USB a una fuente de poder de 12v y 3.5 Amps. Me sugirieron usara una fuente de poder de computadora pero tenia una fuente extra y use una fuente de 12v 3.5 Amps en vez de una de Compu. 

[IMG Requerimientos de Fuente d epoder - Al menos 2.5 Amps]

![screen shot 2017-06-20 at 11 49 12 am](https://user-images.githubusercontent.com/11970000/27345237-8c8648c6-55ae-11e7-88e0-26df5d2cdc62.png)

El que me vendio el NV10USB me incluyo el cable USB. Si no tienes este cable te dejo una imagen de como puedes armar el tuyo. Recomiendo se lo pidas a quien te lo venda, pues es dificil de hacer. 

![screen shot 2017-06-20 at 12 01 11 pm](https://user-images.githubusercontent.com/11970000/27345672-2ff775f6-55b0-11e7-8fe1-459d9e12d3b0.png)

El NV10USB viene con un boton a su costado, con ese boton podremos poner manualmente el lector de billetes en modo de pulsos. 

![screen shot 2017-06-20 at 12 07 09 pm](https://user-images.githubusercontent.com/11970000/27345934-0573bc08-55b1-11e7-9492-1e05ef73f8c2.png)

PROGRAMAR EL NV10USB en modo de PULSOS

El NV10USB tiene diferentes Interfaces, cuando compre esto, ya tenia el codigo para leer pulsos del monedero, y una maquina funcionando. Queria solo copiar y pegar adaptar un poco y que el lector de billetes hiciera lo mismo que el lectro de monedas. Asi que opte por ponerlo en modo de pulsos. Para esto ocpuas primero manualmente poner el NV10USB en modo de programado (SSP) luego conectar el NV10USB a una compu con el programa para cargar nuevos billetes y para cambiar la cantidad de pulsos y el modo en que va a operar.

Para esto hay una guia en pdf que podran seguir. 

[Liga a PDF Aqui]

Una vez instalen el programa en la compu, se van a configurar, y ponen el NV10USB en modo de pulsos. Ahi mismo les paraeceran por defualt la cantidad de puslso que vienen para cada billetes (Esto suponiendo que ya te vendieron el NV10USB con los billetes pre cargados) Si no tienes los billetes precargados, ocupas esta guia.

[liga pdf precargar billetes a NV10USB modo interfaz de pc]

[Liga a drivers NV10USB]

Primero ocupo que le aplanes el boton 2 veces seguidas por mas de un segundo, osea de forma lenta. Para que el NV10USB se ponga en modo SSP programador. Una vez el NV10USB este conectado a la compu, y en modo SSP, puedes acceder al programa y ponerlo en modo de pulsos. Asi como el configurar cuantos pulsos ocupas para cada billete. 

| Billete    |   $20.00  | $50.00  | $100.00  | $200.00  |
| ------------- | -----:| -----:| -----:| -----:|
| Pulsos | 18 | 45 | 90 | 180 |

![screen shot 2017-06-20 at 12 02 35 pm](https://user-images.githubusercontent.com/11970000/27345790-7e5baac8-55b0-11e7-96d7-f6e69a45d3be.png)

Una vez en modo de pulsos hay que poner los pins como sigue.

![screen shot 2017-06-20 at 11 59 54 am](https://user-images.githubusercontent.com/11970000/27345625-0538b0c8-55b0-11e7-8683-d82366c1696f.png)

-El pin #1 del NV10USB al pin #3 del Arduino Mega (para que se le pueda agregar la función de AtachInterrupt() este debe de estar en pins específicos según el modelo de Arduino ya empleamos el #2, para este emplearemos el siguiente pin #3)
-Los Pins #5 NV10USB, #6 NV10USB, #7 NV10USB, #8 NV10USB van a tierra, (para que el NV10USB lea los 4 tipos de billetes, $20,$50,$100,$200 en modo de pulsos sino se ponen estos no va a leer ningún billete en modo de pulsos, este detalle me falto cuando adqueri el NV10USB para que funcionara sin uso de la compu)
-El pin #15 NV10USB a los 12v y 3amps de la fuente externa
-El pin #16 NV10USB a GND de la fuente externa.

[IMG Diagrama Fuente monedero billetero arduino]
![screen shot 2017-06-20 at 11 21 26 am](https://user-images.githubusercontent.com/11970000/27344055-a2a6235a-55aa-11e7-931d-a37ad7d9e21e.png)

Yo uso dos fuentes, pero creo que usted me podría ayudar a solo emplear 1 sola fuente para alimentar todo. Aun no eh calado conectar el arduino a la fuente de PC. Creo que tiene demasiado Amperaje y podría quemar el arduino. No estoy seguro.

{CODIGO LEER PULSOS MONEDEOR & BILLETERO}
---
###PARTE 003: Leer Pulsos del Sensor de Hopper
Ok, entonces ya podemos leer y contar pulsos tanto del lector de billetes como del monedero electrónico. Ya tenemos 2 fuentes de input, ahora para hacer el output, emplearemos el Hopper de la maquina de apostar, prenderemos este motorsito y con los pulsos del sensor en el Hopper sabremos cuando apagar el motorsito.
Este sensor emite un pulso cuando pasa una moneda eh interrumpe la señal del Led infrarojo. Los 4 Pins en morado van de Izquierda a derecha 1---à4

1. Entreda de 5v para encender sensor
2. Salida de pulsos -> #18 Arduino Mega
3. A Tierra GND
4. Este no le pongo nada
5. NC [+][+][ ] NO
OJO: estos valores los saque a modo de prueba y error, pueden estar mal jajajaja pero asi detecta pulsos y asi los deje.

[IMG SENSOR DEL HOPPER]

![screen shot 2017-06-20 at 11 22 16 am](https://user-images.githubusercontent.com/11970000/27344088-be289928-55aa-11e7-9120-8d3d3b1d91f5.png)

[Diagrama del Circuito del Sensor]

![screen shot 2015-11-21 at 11 40 38 pm](https://user-images.githubusercontent.com/11970000/27344392-beaae6b6-55ab-11e7-8897-ce512d27e5d4.png)

[IMG Del Hopper]

![screen shot 2015-11-21 at 11 38 44 pm](https://user-images.githubusercontent.com/11970000/27344357-a39171b0-55ab-11e7-936b-bc8d06e3ba5d.png)

Mas acerca del Hopper
Fuente: http://vyr-entretenimiento.blogspot.mx/2013/12/hooper-para- maquinas-de-pinball-tipo.html

Primero leeremos y contaremos los pulsos del sensor del Hopper de la misma forma que hicimos con los pulso del lector de monedas y billetes. Pero como aun no conectamos el relevador de 5v al Hopper para accionar remotamente y en automático el motor del Hopper, emplearemos el botón verde (en la imagen, en la fuente es negro) que dice SSR. Este botón al presionarlo y teniendo el cable del Hopper conectado a la fuente Perla, accionara el motor del Hopper manualmente.
Este motor prendera siempre y cuando ese botón SSR este presionado.
Para contar y leer los pulsos del sensor del Hopper, hay que descargar el siguiente programa al Arduino MEGA, dejar minimo 15 a 20 monedas en el Hopper y manualmente presionar el botón SSR para accionar el motor.
Si todo funciona bien, el programa leera y mostrara en consola las veces que la función AtachInterrupt detecto un cambio, llamara a la función pulsoCont++() y aumentara el contador de pulsos para el sensor. Habremos completado esta parte.

[IMG DIAGRAMA HOPPER FUENTE SENSOR ARUDINO]
![screen shot 2017-06-20 at 11 22 45 am](https://user-images.githubusercontent.com/11970000/27344111-d30551ec-55aa-11e7-952a-671caf4576ec.png)

{CODIGO LEER PULSOS DEL SENSOR DEL HOPPER}
---
###PARTE 004: Activar Relevador para Accionar Hopper con la ayuda de la fuente
Bueno ahora que ya podemos leer y contar todos los pulsos entrantes al arduino, los del monedero, los del lector de billetes, y los del sensor del Hopper, toca poder prender el Hopper con el arduino para que este expulse las monedas en función a los pulsos detectados por el sensor del Hopper.
Para esto emplearemos un relevador de 5v, como el que le mande por correo. Este no lo usaremos para conectar la luz hacia el Hopper, y accionarlo con el arduino como debería de usarse un relevador, sino mas bien lo emplearemos para actuar como un botón que jale a GND el pin del SSR de la fuente, que hará lo mismo que usted estaba haciendo manualmente al presionar el botón. Esto por que? Pues no supe como hacer prender el Hopper sin la fuente, intente empleando el relevador y conectándolo a la luz pero el Hopper se calentaba como plancha y solo funcionaba 3 de cada 5 veces. Eso no es bueno, así que decidí hacer lo de antes porque funciona.
Entonces conectamos el relevador de 5v como sigue, el pin de 5v a los 5v de la fuente perla, el pin de IN1 al pin del arduino Mega #4, el pin de GND del relevador al pin de GND de la fuente perla, y del lado derecho conectamos el pin NO (normalmente abierto) a GND de la fuente perla, y el pin COM (comun) a el pin SSR del la fuente perla.

[IMG DIAGRAMA HOPPER RELEVADOR ARUDINO]
![screen shot 2017-06-20 at 11 23 22 am](https://user-images.githubusercontent.com/11970000/27344135-e9747408-55aa-11e7-926d-b4869031ee6a.png)

El primer programa solo es para calar que el relevador funcione, lo único que hace es accionar el relevador, con accionar me refiero a conectar COM con NO para jalar el pin SSR de la fuente a GND, es como si aplanara el botón. El programa ocupara de que usted en consola, tecle la letra “p” para prender, y “a” para apagar.
El siguiente programa empleara la consola del arudino mega, como input, es decir haremos que esta recibiendo pulsos del monedero o del lector de billetes, introduciendo manualmente un numero en la consola del Arduino ide, para que este se meta a una función switch y según el numero de pulsos, accione el motor del Hopper hasta que el arduino lea y cuente pulsos del sensor del hopper menores a los que ocupa expulsar en monedas. Esto para meterle un delay, al final para que agarre suficiente momentum para expulsar la ultima moneda pero no demasiado para que expulse una moneda de mas. Por eso lo paramos 1 moneda antes. Este es el gran problema que no me permite trabajar con estas maquinas aun, a veces da de menos, pues el Hopper se detiene y expulsa una moneda de menos, y a veces tarda en detenerse y expulsa monedas de mas. Una moneda, rara vez expulsa mas de una o menos de una. Quisiera que lo probara y me
ayudara a pulir esta parte en especial, o a crear una nueva forma para controlar mejor las salidas de las monedas.

{CODIGO ACTIVAR RELEVADOR}
---
[IMG Diagrama de mueble]
![morralla mueble](https://user-images.githubusercontent.com/11970000/27344290-6b30302c-55ab-11e7-8ae2-5600500f3f49.png)
