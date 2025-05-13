README: Tower Defense Game

Introducere: O Poveste Fantasy
Într-o țară îndepărtată, unde cerurile sunt pictate în nuanțele magiei și pământul tremură sub pașii hoardelor monstruoase, un regat stă pe marginea distrugerii. Regatul, cândva pașnic, este sub asediu din partea unor valuri de creaturi înspăimântătoare—zombi, orci si goblini. Singura speranță se află în mâinile unui jucător curajos, care trebuie să plaseze strategic și să îmbunătățească turnuri pentru a apăra ultima fortăreață a regatului.

Tu, jucătorul, ești eroul ales. Înarmat cu aur și curaj, trebuie să construiești și să gestionezi o serie de turnuri—Turnuri de Arcași, Turnuri cu Tunuri, Turnuri Magice și Turnuri de Gheață—pentru a respinge valurile neîncetate de monștri. Vei face față provocării și vei salva regatul, sau monștrii vor copleși apărarea ta?

Cum Funcționează Jocul


Obiectiv: Apără-ți turnurile de valurile de monștri. Fiecare val aduce inamici mai puternici. Supraviețuiește prin mai multe runde pentru a câștiga jocul.

Turnuri: Plasează și îmbunătățește turnuri pentru a ataca monștri. Fiecare tip de turn are abilități și raze de atac unice.

Monștri: Monștrii se îndreaptă spre turnurile tale. Dacă ajung la un turn, îl atacă. Dacă HP-ul unui turn scade la zero, acesta este distrus.

Jucător: Gestionează-ți cu înțelepciune aurul pentru a îmbunătăți turnurile și a-ți păstra apărarea puternică. Dacă prea mulți monștri trec prin apărare, pierzi vieți—și în cele din urmă, jocul.


Caracteristici Cheie și Implementare

Structura Codului

Codul este organizat în fișiere separate de antet (.h) și sursă (.cpp) pentru claritate și modularitate. De exemplu:

tower.h și tower.cpp definesc clasa Tower și clasele derivate din aceasta.

monster.h și monster.cpp definesc clasa Monstru și clasele derivate din aceasta.

player.h și player.cpp definesc clasa Player.


Moștenire
Jocul utilizează o ierarhie robustă de moștenire:

Clasa de Bază: Tower și Monstru sunt clase de bază.

Clase Derivate:

Tower are patru clase derivate: ArcherTower, CannonTower, MagicTower și IceTower.

Monstru are cinci clase derivate: Zombie, FastZombie, TankZombie, Orc și Goblin.
Fiecare clasă derivată suprascrie comportamente specifice, cum ar fi mecanismele de atac pentru turnuri și tiparele de mișcare pentru monștri.

Funcții Virtuale
Jocul folosește funcții virtuale pure pentru a impune comportamente specifice în clasele derivate:

Tower::attack(Monstru&) este o funcție virtuală pură, implementată diferit în fiecare tip de turn.

Monstru::move() este o funcție virtuală pură care definește tipare unice de mișcare pentru fiecare tip de monstru.
Aceste funcții sunt apelate prin smart pointers la clasa de bază, asigurând comportament polimorfic.

Constructori Virtuali (Clone)
Fiecare clasă implementează o metodă clone() pentru a crea copii ale obiectelor dinamic. De exemplu:
std::unique_ptr<Tower> ArcherTower::clone() const permite crearea unei copii a unui obiect ArcherTower.

Excepții:

Jocul definește o ierarhie personalizată de excepții derivată din std::exception:

GameException: Clasa de bază pentru toate excepțiile legate de joc.

InvalidNameException: Aruncată atunci când jucătorul introduce un nume invalid.

NotEnoughGoldException: Aruncată atunci când jucătorul încearcă să cheltuiască mai mult aur decât are.

InvalidActionException: Aruncată pentru acțiuni invalide în gameplay.
Excepțiile sunt folosite semnificativ, de exemplu, aruncând InvalidNameException în constructorul Player și capturând-o în main.

Smart Pointers

Jocul folosește smart pointers (std::shared_ptr și std::unique_ptr) pentru a gestiona memoria dinamică în siguranță:
Turnurile și monștrii sunt stocați ca std::shared_ptr sau std::unique_ptr în vectori, asigurând o curățare corectă și evitând scurgerile de memorie.

Funcții și Atribute Statice

Atribute și funcții statice sunt folosite acolo unde este cazul. De exemplu:

Player gestionează atribute statice pentru starea jocului comună, cum ar fi numărul total de vieți.

Utilizarea STL

Jocul folosește extensiv Biblioteca Standard de Șabloane (STL):

std::vector este folosit pentru a gestiona colecțiile de turnuri și monștri.

Funcțiile std::algorithm, cum ar fi std::remove_if, sunt folosite pentru operațiuni eficiente, cum ar fi eliminarea monștrilor morți.

Corectitudinea Const

Codul pune accent pe corectitudinea const pentru a asigura imutabilitatea acolo unde este aplicabil:
Multe funcții membre, cum ar fi Tower::getLevel() și Monstru::isAlive(), sunt marcate cu const.

Funcții de Nivel Înalt

Jocul minimizează utilizarea getter-elor și setter-elor de nivel jos, folosind funcții de nivel înalt. De exemplu:

Tower::upgrade(Player&) gestionează atât verificarea dacă jucătorul are suficient aur, cât și îmbunătățirea turnului într-o funcție coerentă.

Cum să Joci

Începe Jocul: Rulează programul și introduce numele tău de jucător.

Apără-ți Turnurile: Privește cum valurile de monștri se apropie. Turnurile vor ataca automat monștrii din raza lor.

Faza de Îmbunătățire: După fiecare val, folosește aurul pentru a îmbunătăți turnurile și a-ți întări apărarea.

Câștigă sau Pierzi: Supraviețuiește tuturor rundelor pentru a câștiga jocul. Dacă pierzi toate viețile, jocul se încheie.

