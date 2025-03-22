

/*
	800ms 200ms 200ms "5" -> 200eat + 200sleep = 400ms de rab, ne doit pas mourir -> cas ou boucle infini, "tous au moins manger 5 fois"
	1philo a 2 forks(utilise les 2 pour manger left + right) = 1 mutex
	deadtime = temps 2sec de plus + temps pour mourir
	thread superviser pour superviser l'ensemble de tous, process qui tourne en plus, check si philo meurt
	init tous les philos au depart, tous les creer pour les lancer sans avoir de decalage, car commence deja a tourner
	routine -> met son temps de base, fait att un peu pour que les autres threads s'init
	fn check qui regarde si peut manger / penser
	timer dans eat qui check si mange en tant de temps, 1 peux mourir pdt que 1 mange ou dort -> doit arreter le programme
	lock le mutex pour verif si 1 est mort, sinon return 0, return 1 si mort
	si nb philos est >= nb philo
	print unlock
	philo 1 peut aller plus vite pour faire telle action que les autres
	empeche le 2nd de manger car utilise les 2 forks
	(+1 % nb philos)
*/