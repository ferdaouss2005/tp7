# tp7
exercice1

<img width="347" height="322" alt="image" src="https://github.com/user-attachments/assets/8aec7c50-af50-4ad9-b424-03f5427f9c1b" />
<img width="290" height="133" alt="image" src="https://github.com/user-attachments/assets/95bf6124-2e50-449f-89cb-f753ee33a90a" />


Dans cet exercice, j’ai créé une classe abstraite `SortieAudio` contenant trois méthodes virtuelles pures : `ouvrir()`, `jouer()` et `fermer()`. Ensuite, j’ai créé trois classes dérivées : `HautParleur`, `CasqueBT` et `SortieHDMI`, chacune redéfinissant les trois méthodes selon son fonctionnement. J’ai également créé une fonction `tester()` qui utilise un pointeur vers la classe abstraite pour appeler les méthodes de manière polymorphe. Dans la fonction principale, j’ai utilisé un tableau dynamique de pointeurs vers `SortieAudio` pour stocker les différents périphériques, puis j’ai libéré la mémoire avec `delete`. Enfin, j’ai ajouté un destructeur virtuel dans la classe de base pour garantir la destruction correcte des objets dérivés. Cet exercice m’a permis de comprendre les classes abstraites, les méthodes virtuelles pures, le polymorphisme et la gestion dynamique de la mémoire.

exercice2

<img width="281" height="131" alt="image" src="https://github.com/user-attachments/assets/fc28cd43-5fa7-4faa-96ac-29d4ed1ab81d" />



Dans cet exercice, j’ai créé une classe abstraite `Lumiere` contenant une méthode virtuelle pure `intensite()`. J’ai ensuite implémenté trois classes dérivées : `LumiereDirectionnelle`, `LumierePonctuelle` et `LumiereSpot`, chacune avec sa propre méthode de calcul de l’intensité lumineuse. J’ai utilisé une structure `Vec3` pour représenter les positions et les directions dans l’espace 3D. Enfin, j’ai regroupé les différentes sources lumineuses dans un `vector<unique_ptr<Lumiere>>` et créé la fonction `calculerEclairage()` pour additionner les intensités de toutes les lumières en différents points. Cet exercice m’a permis de pratiquer le polymorphisme, les classes abstraites et la gestion automatique de la mémoire avec les pointeurs intelligents.
