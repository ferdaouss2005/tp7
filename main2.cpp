
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// Structure pour representer un vecteur 3D
struct Vec3 {
    float x, y, z;

    Vec3(float a = 0, float b = 0, float c = 0)
        : x(a), y(b), z(c) {}
};

// Fonctions mathematiques
float produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float longueur(const Vec3& v) {
    return sqrt(produitScalaire(v, v));
}

Vec3 normaliser(const Vec3& v) {
    float l = longueur(v);

    if (l == 0)
        return Vec3();

    return Vec3(v.x / l, v.y / l, v.z / l);
}

Vec3 soustraire(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Classe abstraite Lumiere
class Lumiere {
public:
    virtual float intensite(const Vec3& position) const = 0;

    virtual ~Lumiere() {}
};

// Lumiere directionnelle
class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    Vec3 couleur;

public:
    LumiereDirectionnelle(Vec3 d, Vec3 c)
        : direction(normaliser(d)), couleur(c) {}

    float intensite(const Vec3& position) const override {
        (void)position;

        // Intensite moyenne de la couleur
        return (couleur.x + couleur.y + couleur.z) / 3.0f;
    }
};

// Lumiere ponctuelle
class LumierePonctuelle : public Lumiere {
private:
    Vec3 positionLumiere;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a)
        : positionLumiere(p), attenuation(a) {}

    float intensite(const Vec3& position) const override {
        Vec3 difference = soustraire(position, positionLumiere);
        float distance = longueur(difference);

        return 1.0f / (1.0f + attenuation * distance * distance);
    }
};

// Lumiere spot
class LumiereSpot : public Lumiere {
private:
    Vec3 positionLumiere;
    Vec3 direction;
    float angleOuverture;

public:
    LumiereSpot(Vec3 p, Vec3 d, float angle)
        : positionLumiere(p),
          direction(normaliser(d)),
          angleOuverture(angle) {}

    float intensite(const Vec3& position) const override {
        Vec3 versPoint = soustraire(position, positionLumiere);
        float distance = longueur(versPoint);

        if (distance == 0)
            return 1.0f;

        versPoint = normaliser(versPoint);

        float cosAngle = produitScalaire(direction, versPoint);
        float limite = cos(angleOuverture * 3.14159f / 360.0f);

        if (cosAngle < limite)
            return 0.0f;

        return 1.0f / (1.0f + 0.1f * distance * distance);
    }
};

// Additionner les intensites de toutes les lumieres
float calculerEclairage(
    const vector<unique_ptr<Lumiere>>& lumieres,
    const Vec3& point) {

    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}

int main() {
    vector<unique_ptr<Lumiere>> lumieres;

    // Ajouter les differentes sources lumineuses
    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumiereDirectionnelle(
                Vec3(0, -1, 0), Vec3(1.0f, 0.8f, 0.6f)
            )
        )
    );

    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumierePonctuelle(Vec3(1, 1, 0), 0.1f)
        )
    );

    lumieres.push_back(
        unique_ptr<Lumiere>(
            new LumiereSpot(
                Vec3(0, 0, 0), Vec3(1, 0, 0), 60.0f
            )
        )
    );

    // Tester avec plusieurs points
    Vec3 points[] = {
        Vec3(2, 0, 0),
        Vec3(0, 2, 0),
        Vec3(3, 1, 0)
    };

    cout << fixed << setprecision(2);

    for (int i = 0; i < 3; i++) {
        cout << "Eclairage du point " << i + 1 << " : ";
        cout << calculerEclairage(lumieres, points[i]);
        cout << endl;
    }

    return 0;
}
