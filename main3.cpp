
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

// Classe abstraite Plugin
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    // Factory interne
    static unique_ptr<Plugin> creerPlugin(const string& type);
};

// Plugin CorrecteurOrthographique
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur Orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        size_t pos;

        // Correction de quelques fautes simples
        while ((pos = resultat.find("bonjor")) != string::npos) {
            resultat.replace(pos, 6, "bonjour");
        }

        while ((pos = resultat.find("salu")) != string::npos) {
            resultat.replace(pos, 4, "salut");
        }

        while ((pos = resultat.find("mercie")) != string::npos) {
            resultat.replace(pos, 6, "merci");
        }

        return resultat;
    }
};

// Plugin TraducteurAnglais
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur Anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        size_t pos;

        while ((pos = resultat.find("bonjour")) != string::npos) {
            resultat.replace(pos, 7, "hello");
        }

        while ((pos = resultat.find("merci")) != string::npos) {
            resultat.replace(pos, 5, "thank you");
        }

        while ((pos = resultat.find("chat")) != string::npos) {
            resultat.replace(pos, 4, "cat");
        }

        while ((pos = resultat.find("maison")) != string::npos) {
            resultat.replace(pos, 6, "house");
        }

        return resultat;
    }
};

// Plugin AnalyseurStyle
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de Style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        int phrasesLongues = 0;
        int longueurPhrase = 0;

        for (size_t i = 0; i < texte.length(); i++) {
            char c = texte[i];

            if (c == '.' || c == '!' || c == '?') {
                if (longueurPhrase > 50) {
                    phrasesLongues++;
                }

                longueurPhrase = 0;
            } else if (c != '\n') {
                longueurPhrase++;
            }
        }

        // Verifier la derniere phrase
        if (longueurPhrase > 50) {
            phrasesLongues++;
        }

        resultat += "\n\nAnalyse du style : ";

        if (phrasesLongues == 0) {
            resultat += "Aucune phrase trop longue.";
        } else {
            resultat += to_string(phrasesLongues);
            resultat += " phrase(s) trop longue(s). Essayez de les raccourcir.";
        }

        return resultat;
    }
};

// Implementation de la factory
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return unique_ptr<Plugin>(new CorrecteurOrthographique());
    }

    if (type == "traducteur") {
        return unique_ptr<Plugin>(new TraducteurAnglais());
    }

    if (type == "analyseur") {
        return unique_ptr<Plugin>(new AnalyseurStyle());
    }

    return nullptr;
}

int main() {
    string texte;

    cout << "Entrez votre texte : ";
    getline(cin, texte);

    // Vecteur de plugins
    vector<unique_ptr<Plugin>> plugins;

    // Simulation du chargement dynamique
    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    // Application successive des plugins
    for (const auto& plugin : plugins) {
        if (plugin != nullptr) {
            texte = plugin->traiter(texte);

            cout << "\nPlugin applique : " << plugin->nom() << endl;
            cout << "Texte transforme :\n" << texte << endl;
        }
    }

    return 0;
}
