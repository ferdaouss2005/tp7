
#include <iostream>
#include <string>
using namespace std;

// Classe abstraite
class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    virtual ~SortieAudio() {
        cout << "Destructeur SortieAudio" << endl;
    }
};

// Classe HautParleur
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Haut-parleur ouvert." << endl;
    }

    void jouer(const string& son) override {
        cout << "Haut-parleur joue : " << son << endl;
    }

    void fermer() override {
        cout << "Haut-parleur ferme." << endl;
    }

    ~HautParleur() {
        cout << "Destructeur HautParleur" << endl;
    }
};

// Classe CasqueBT
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Casque Bluetooth connecte." << endl;
    }

    void jouer(const string& son) override {
        cout << "Casque Bluetooth joue : " << son << endl;
    }

    void fermer() override {
        cout << "Casque Bluetooth deconnecte." << endl;
    }

    ~CasqueBT() {
        cout << "Destructeur CasqueBT" << endl;
    }
};

// Classe SortieHDMI
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI activee." << endl;
    }

    void jouer(const string& son) override {
        cout << "Sortie HDMI joue : " << son << endl;
    }

    void fermer() override {
        cout << "Sortie HDMI desactivee." << endl;
    }

    ~SortieHDMI() {
        cout << "Destructeur SortieHDMI" << endl;
    }
};

// Fonction polymorphe
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique de test");
    sortie->fermer();
}

int main() {
    SortieAudio* sorties[3];

    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        cout << "\n===== TEST PERIPHERIQUE " << i + 1 << " =====" << endl;
        tester(sorties[i]);
    }

    cout << "\n===== LIBERATION DE LA MEMOIRE =====" << endl;

    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}
