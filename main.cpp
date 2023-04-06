#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Avem un string dat ca parametru(o parola) si vedem daca are caracterele ncesare: cel putin o litera mica, cel
 * putin o litera mare, cel putin o cifra
 * @param s-string, dat ca parametru
 * @return returnam un array in care mentionam care sunt caracterele necesare(litera mica, litera mare, cifra)
 * care nu se regasesc in sirul nostru de caractere
 */
short* neededCharacters(const string &s)
{
    ///caractere ce TREBUIE sa apara;
    /// mustC[1]=0-apare litera mica/1-nu apare litera mica
    /// mustC[2]=0-apare litera mare/1-nu apare litera mare
    /// mustC[3]=0-apare cifra      /1-nu apare cifra
    auto* mustC = new short[4];///mustC-vector alocat dinamic, in memoria HEAP, pentru a putea fi returnat si folosit
    ///initial, presupunem ca nu apar; VEDEM cand parcurgem s daca apar sau nu
    mustC[0] = mustC[1] = mustC[2] = mustC[3] = 1;
    for(char i : s)
    {
        if(i >= 'a' && i <= 'z')
            mustC[1] = 0;///avem litera mica
        if(i >= 'A' && i <= 'Z')
            mustC[2] = 0;///avem litera mare
        if(i >= '0' && i <= '9')
            mustC[3] = 0;///avem cifra

    }
    return mustC;
}
/**
 * Avem un string dat ca parametru(o parola) si vedem daca are numarul de caractere necesar pentru a fi OK
 * @param s-string, dat ca parametru
 * @return numarul de caractere MINIM ce trebuie adagate/sterse pentru a fi in schema
 */
int neededLength(const string &s)
{
    const int min = 6;///numarul minim de caractere al sirului s
    const int max = 20;///numarul maxim de caractere al siului s
    int nrOfChanges = 0;///numarul de schimbari ce trebuie facute pentru a avea o parola puternica
    if(s.size() < min)
        nrOfChanges += min - s.size();///trebui NEAPARAT sa inseram atatea caractere pentru a fi OK parola
    if(s.size() > max)
        nrOfChanges += s.size() - max;///trebuie NEAPARAT sa stergem atatea caractere pentru a fi ok parola
    return nrOfChanges;
}
/**
 *
 * @param s-Parola pe care o verificam daca este puternica sau nu
 * @return Numarul de schimbari necesare ce trebuie efectuate asupra parolei pentru a obtine una puternica
 * (stergerea, adaugarea sau schimbarea unui caracter sunt considerate O SINGURA SCHIMBARE) sau 0 IN
 * CAZ CONTRAR(parola e buna)
 */
int StrongPassword(string s)
{
    ///cout << s.size() << endl;
    int nrOfChanges = neededLength(s);///vedem cata caractere trebuie sa mai adaugam/stergem din sirul s
    int opNedded = 0;///nr de operatii necesare
    short* neededC = neededCharacters(s);///ce inlocuiri de caractere TREBUIE facute pentru a avea car. necesare
    int lenS = s.length();///fictiv, vom face operatii de stergere si adaugare(daca e nevoie) asupra lui s
    int secvente3 = 0;///cate secvente de 3 caractere egale avem
    ///STERGEREA E PRIORITARA!!!; Daca sunt necesare si operatii de replace si de stergere(inserarea nu are cum),
    ///atunci prima data are loc stergerea; mai mult, vom incera sa stergem din secventele de minim 3 caractere
    ///egale; daca nu avem, atunci se vor sterge caractere random a.i sa ne incadram in interval(prin stergere
    ///si dupa replace, scapam poate de secvente de caractere egale si replace ul devine redundant; DAR, prin
    ///replace prima data, STERGEREA RAMANE NECESARA!!!
    if(lenS > 20)///trebuie neaparat facute stergeri
    {
        for (int i = 0; i < s.size() - 2 && nrOfChanges; i++)
        {
            if (s[i] == s[i + 1] && s[i + 1] == s[i + 2])
            {
                s.erase(s.begin() + i + 2);///stergem al 3-lea carcater
                i--;///nu trecem mai departe, fiindca ar putea sa urmeze iar un carcater egal
                lenS--;///lenS se modifica
                nrOfChanges--;///o operatie de stergere deja s-a facut
                opNedded++;///tinem cont ca s-a facut o operatie
            }
        }
    }
    const int lungime_sir = s.length();
    for(int i = 0; i < lungime_sir - 2; i++)
    {
        ///minim 3 caractere ce se repeta unul dupa altul; in caz ca vom avea mai multe astfel de caractere(o
        ///secventa de > 3; de ex 5), in loc sa stergem 3 caractere, e mai usor sa il inlocuim pe al 3 lea caracter
        ///din secventa(ultimul) cu un caracter astfel incat sa "distrugem" secventa de caractere egale;
        ///astfel, dupa fiecare secventa de 3 caractere, al 3 lea va fi inlocuit cu un caracter adecvat(sau sters,
        ///daca avem mai mult de 20 de caractere; observam ca operatia de stergere este independenta de cea de
        /// replace; stergerea si adaugarea sunt indep de replace daca SUNT NECESARE) astfel incat sa facem NUMAR MINIM
        /// de modificari ca sa nu avem
        ///3 caractere egale(caracterul, evident, poate fi inlocuit a.i sa nu se creeze o secenta de 3 car egale)
        if(s[i] == s[i + 1] && s[i] == s[i + 2])
        {
            ///caracterul s[i + 2] va vi diferit de s[i](dupa inlocuire), iar caracterul s[i + 3] va marca POSIBILUL
            ///inceput al unei secvente de 3 caractere egale; de accea, ne vom plasa, la finalul iteratiei curente din
            ///for, pe aceasta pozitie(i + 3)
            i = i + 2;
            ///daca vom avea mai multe secvente de caractere egale, vom prefera ca, pe rand, al 3-lea caracter
            ///sa il inlocuim cu CARACTERELE NECESARE ce trebuie sa apara intr o parola(daca acestea nu sunt
            ///se regasesc deja in parola); in caz contrar, daca nu avem suficiente secv de cate 3 car egale,
            ///din numarul de secv disponibil(daca avem, 1 sau 2), acolo vom inlocui nr de caractere necesar
            ///cu ce caractere ne trebuie
            secvente3++;
            if(neededC[1] == 1)///nu avem litera mica
            {
                ///trebuie neaparat sa aduagam un car; cum avem o secventa, LITERA MICA o inseram pe ultimul car
                ///din secventa
                ///nrOfChanges se modif; FACEM o op de adaugare
                if (lenS < 6)
                {
                    neededC[1] = 0;///inlocuim cu o litera mica
                    lenS++;
                    opNedded++;
                    nrOfChanges--;
                }
                else
                {
                    neededC[1] = 0;///facem doar un replace; atribuirea neddedC[1] = 0 se putea face o singura data
                    /// in if, dar am lasat o pentru o mai buna intelegere
                    opNedded++;
                }
            }
            else
            {
                if (neededC[2] == 1)///avem litera mica, dar nu avem MARE
                {
                    if (lenS < 6)
                    {
                        neededC[2] = 0;///inlocuim cu litera MARE
                        lenS++;
                        opNedded++;
                        nrOfChanges--;
                    }
                    else
                    {
                        ///facem doar un replace; atribuirea neddedC[2] = 0 se putea face o singura data
                        /// in if, dar am lasat o pentru o mai buna intelegere
                        neededC[2] = 0;
                        opNedded++;///facem un replace
                    }
                }
                else
                {
                    if (neededC[3] == 1)///avem litere MICI si MARI, dar nu avem cifre
                    {
                        if (lenS < 6) {
                            neededC[3] = 0;///inseram o cifra pe aceasta pozitie
                            lenS++;
                            opNedded++;
                            nrOfChanges--;
                        }
                        else
                        {
                            neededC[3] = 0;
                            opNedded++;///s-a facut o operatie diferita de add sau delete
                        }
                    }
                    else///toate caracterele DORITE apar, DAR noi tot trebuie sa inlocuim cu ceva
                    {
                        if (lenS < 6)
                        {
                            ///inseram aici un carcater oarecare
                            lenS++;
                            opNedded++;
                            nrOfChanges--;
                        }
                        else
                            nrOfChanges++;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= 3; i++)
        if(neededC[i] == 1)///nu am reusit sa completam aceste caractere din add-uri sau secvente, deci adaugam acm
        {
            if(lenS < 6)///trebuie neaparat add
            {
                opNedded++;
                nrOfChanges--;
                lenS++;
            }
            else
                opNedded++;

        }
        return opNedded + nrOfChanges;///add uri sau delete uri necesare
}
int main()
{
    string snul = "";
    assert(StrongPassword(snul) == 6);
    ///Some quick tests
    string s1 = "(((a1234567890123456789";
    assert(StrongPassword(s1) == 4);

    ///Some quick tests
    string s2 = "(((a(((";
    assert(StrongPassword(s2) == 2);

    ///Some quick tests
    string s3 = "(((a1234567890123456789";
    assert(StrongPassword(s3) == 4);

    ///Some quick tests
    string s4 = ".....";
    assert(StrongPassword(s4) == 3);

    ///Some quick tests
    string s5 = "(((((a(((";
    assert(StrongPassword(s5) == 2);

    ///Some quick tests
    string s6 = ".";
    assert(StrongPassword(s6) == 5);

    string s7= "..........a..........";
    assert(StrongPassword(s7) == 7);

    string s8 = "00000000000000000000";
    assert(StrongPassword(s8) == 6);

    string s9 = ".....................";
    assert(StrongPassword(s9) == 7);
    return 0;
}
