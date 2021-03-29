# automotive-stm32
## Za każdym razem, gdy zaczynamy pracę robimy:
```
git checkout main
git pull origin main
```
tworzymy nowy branch
```
git checkout -b add_linting
```
Stworzy to nowy branch o nazwie `add_linting`

Pracujemy, pracujemy... i gdy SKOŃCZYSZ SWOJĄ PRACE:

Przenosimy gałąź do zdalnego repo czyli githuba
```
git push origin add_linting
```
## Tworzymy rządanie
Korzystając ze swojej gałęzi funkcji na github, przejdź do projektu na github. Na stronie głównej powinieneś zobaczyć nowy mały pasek narzędzi, który pokazuje twoją gałąź funkcji i pyta, czy chcesz utworzyć z niej żądanie ściągnięcia.
![screen shot 2015-05-27 at 10 28 45 am](https://cloud.githubusercontent.com/assets/9369/7843160/ae17dcf2-045c-11e5-9f12-db8f4b197137.png)

## Znajdowanie żądań
![screen_shot_2015-05-27_at_8_57_48_am](https://cloud.githubusercontent.com/assets/9369/7841032/f1f4e220-044e-11e5-9f6e-c6aa19430457.png)

Przejrzyj, skomentuj, poczekaj na reakcje tłumu...

## Merging
Po kilku wiadomościach powinniśmy dojść do pożądanego +1 - co oznacza, że nadszedł czas, aby to połączyć.
Najpierw upewnij się, że masz najnowszą wersję master w lokalnym repozytorium.
```
git checkout main
git pull origin main
```
Następnie przełącz się z powrotem do gałęzi funkcji i scal z mainem
```
git checkout add_linting
git merge main
```
Modyfikuj kod, aż wszystkie konflikty zostaną rozwiązane. Następnie dodaj te pliki.
```
git add somefile.js
```
Reszta procesu scalania jest już w fazie przejściowej - więc teraz można zatwierdzić scalanie
```
git commit -m 'merged main'
```
I przełącz się z powrotem na maina, aby przyspieszyć tę zmianę
```
git checkout main
git merge --no-ff add_linting
git push origin master
```
## Usuwanie gałęzi
Tak czy inaczej, po scaleniu gałęzi do maina możemy usunąć zdalną gałąź - dzięki temu nasz projekt github będzie czysty.
![screen shot 2015-05-27 at 9 45 03 am](https://cloud.githubusercontent.com/assets/9369/7841987/339751e4-0455-11e5-8e5f-d2f0f3c4f3f9.png)
