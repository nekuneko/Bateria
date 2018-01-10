# Bateria
 Clase para la medición de baterías de LiPo mediante divisor de tensión 


   Una batería de LiPo tiene un voltaje máximo que es capaz de entregar y un voltaje mínimo 
	    del que no hay que bajar nunca, ya que de lo contrario se estropea la batería.
	
	    ¡CUIDADO! Si se provoca un cortocircuito en una batería de este tipo puede EXPLOTAR.
	
	    El Arduino por cualquiera de sus entradas analógicas (tomaremos por ejemplo la entrada A0), 
	    es capaz de leer con la instrucción analogRead(pinBateria) valores continuos en un rango 
	    de 0v a 5v y convertirlos a una escala digital de 0 a 1023. Por este motivo hay que utilizar 
	    un divisor de tensión que rebaje la tensión máxima de la batería a algo menos de 5v para que 
	    sea posible realizar la lectura de la carga de la batería sin estropear nuestra placa.
	
	    Este divisor de tensión consta de dos resistencias colocadas de este modo:
	
	    (Vin) | +12.57v - 7.4v    // Voltaje de la batería
	          w
	          w   27KΩ (R1)       // Resistencia limitadora de tensión
	          |
	          ------- A0 (Vout)   // Entrada del arduino
	          |
	          w   12KΩ (R2)       // Resistencia Pull-Down
	          w
	          | GND               // Toma tierra
	
	    Y en el que tenemos que:
	    Vout = R2 / (R1 + R2) * Vin
	
	    Si tenemos una batería con las siguientes características:
	        - Voltaje máximo: 12.56 Voltios
	        - Voltaje mínimo: 9.9   Voltios // Esto se deduce de....
	        - Corriente:      2200  mAH
	
	    Y la conectamos al divisor de tensión anterior, entonces, por la expresión matemática 
	    (Vout = R2 / (R1 + R2) * Vin), tendremos las siguientes tensiones en la entrada analógica:
	    
	    A0 = 12kΩ / (27kΩ + 12kΩ) * 12.57v = 3.867v cuando la tensión es MÁXIMA
	    A0 = 12kΩ / (27kΩ + 12kΩ) * 9.9v   = 3.046v cuando la tensión es MÍNIMA
	
	    Esto es así desde el punto de vista teórico, pero las resistencias no tienen en realidad esos
	    valores, por eso es mejor guiarnos por los siguientes valores reales medidos con un polímetro:
	
	        - El voltaje máximo que entrega directamente la batería cuando está cargada (12.57v).
	        - El voltaje máximo que entrega el divisor de tensión cuando la batería está cargada (3.80v).
	    
	    Como se puede apreciar hay diferencias respecto a los valores teóricos, que en la práctica
	    pueden ser importantes y ocasionar mediciones de batería incorrectas.
	
	    Ahora pues habremos de escalar estos valores analógicos a valores digitales:
	    Si a 5v le corresponde el valor 1023, entonces, por regla de tres, a 3.867v le corresponde 
	    el valor digital 791. Análogamente, el valor digital mínimo significativo que leerá la entrada 
	    A0 de nuestro divisor de tensión será 623.
	
	    Así tendremos que cuando en la entrada A0 se lea un valor superior a 791, nuestra batería
	    estará al 99% de carga, mientras que cuando se lea un valor inferior a 623, nuestra batería
	    estará al 0% de carga y será necesario, a toda costa, interrumpir la alimentación con la misma
	    para evitar su deterioro.
	
	    Para calcular el porcentaje de carga en un momento dado simplemente habrá que aplicar
	    otra regla de tres sobre el valor obtenido por la entrada analógica A0.
	   
	    Para una batería de LiPo de 7.4v, obtenemos:
	    7.4v -> 4.2v -> 859 -> 99% (maxVoltaje -> maxVolReg -> maxVolDigital -> porcentajeC)
	    3.3v -> 3.3v -> 675 -> 0%  (minVoltaje -> minVolReg -> minVolDigital -> porcentajeC)
