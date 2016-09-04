## Moralla_Billetes
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
IMAGEN AQUI
Le llamaremos a esta maquina la Maquina de Frutitas y esta viene con todas estas partes:
IMAGEN DE PARTES AQUI
El hardware que no viene incluido en estas maquinas y que puedes conseguir por mercadolibre o alguna otra pagina web es el siguiente:

+ Monedero Electrónico de Múltiples Monedas
+ Arduino MEGA
+ Relevador de 5v
+ Lector de Billetes NV10USB
+ Fuente 12v 3A para Lector de Billetes NV10USB
+ Cable (2-3 mts)

---
####LEER PULSOS DE MONEDERO

PARTE 001: Leer Pulsos del Monedero Electrónico
Queremos que la maquina lea distintas monedas y según estas monedas, expulse una cantidad de pesos. El
monedero que viene con la maquina de tragamonedas de fruititas solo lee un tipo de moneda, este monedero no nos sirve, a
menos que metamos uno de estos para cada tipo de moneda. Por el precio de $650, podemos emplear un solo
monedero electrónico que se le puede configurar para que lea hasta 4 diferentes tipos de moneda.
![alt text][monedero]
[monedero]:https://www.dropbox.com/s/7k0sx4jpy3zcu6v/Screen%20Shot%202015-11-26%20at%208.23.59%20PM.png?dl=0 "Imagen del Monedero Electronico"

![alt text](https://www.dropbox.com/s/7k0sx4jpy3zcu6v/Screen%20Shot%202015-11-26%20at%208.23.59%20PM.png?dl=0)
