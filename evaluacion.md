# The evaluation of the project has this checks:

philo code

Ensure the code of philo complies with the following requirements and ask for explanations.
Check there is one thread per philosopher.
	main: Cada filósofo tiene su propio hilo creado en un bucle.
Check there is only one fork per philosopher.
	init: Cada filósofo tiene dos punteros a mutexes de tenedores.
Check if there is a mutex per fork and that it's used to check the fork value and/or change it.
	philo routine: Los mutexes de los tenedores (left_fork y right_fork) se usan para sincronizar el acceso a los tenedores.
Check the outputs are never mixed up.
	La función log_status se asegura de que los mensajes de estado de los filósofos se impriman en orden.
Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time.
	La rutina de monitoreo verifica el tiempo de la última comida de cada filósofo y usa un mutex para proteger simulation_running y last_meal_time.


# Instrucciones de Prueba

philo testing

Do not test with more than 200 philosophers.

Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

## Test 1: Un filósofo que debería morir

./philo 1 800 200 200
Esperado: El filósofo no debería comer y debería morir después de 800 ms.

philosophers ./philo 1 800 200 200
0 1 is thinking
1 1 has taken a fork
802 1 died
^C

## Test 2: Cinco filósofos, ninguno debería morir

./philo 5 800 200 200
Esperado: Ningún filósofo debería morir.

## Test 3: Cinco filósofos, ninguno debería morir y la simulación debería detenerse después de que cada filósofo haya comido al menos 7 veces

./philo 5 800 200 200 7
Esperado: Ningún filósofo debería morir y la simulación debería detenerse cuando cada filósofo haya comido al menos 7 veces.

## Test 4: Cuatro filósofos, ninguno debería morir
./philo 4 410 200 200
Esperado: Ningún filósofo debería morir.

## Test 5: Cuatro filósofos, uno debería morir

./philo 4 310 200 100
Esperado: Un filósofo debería morir debido a la configuración del tiempo.

## Test 6: Dos filósofos y tiempos precisos

./philo 2 800 200 200
Esperado: Verificar que la muerte de un filósofo no se retrase más de 10 ms.

Validaciones Adicionales
Asegúrate de probar diferentes combinaciones de valores para verificar todos los requisitos, como asegurarte de que los filósofos mueran en el tiempo correcto, no roben tenedores, y más.
            
setarch `uname -m` -R $SHELL 