#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

// Classe de base Product
class Product {
protected:
    long barcode;
    std::string name;

public:
    Product(long code = 0, const std::string& nom = "Unknown")
        : barcode(code), name(nom) {}

    Product(const Product& other)
        : barcode(other.barcode), name(other.name) {}

    virtual ~Product() {}

    long getCode() const { return barcode; }
    void setCode(long code) { barcode = code; }
    std::string getName() const { return name; }
    void setName(const std::string& nom) { name = nom; }

    virtual void scanner() {
        std::cout << "Entrez le code-barres : ";
        std::cin >> barcode;
        std::cout << "Entrez le nom du produit : ";
        std::cin.ignore();
        std::getline(std::cin, name);
    }

    virtual void printer() const {
        std::cout << "Code-barres : " << barcode << ", Nom : " << name << std::endl;
    }

    virtual double getPrice() const = 0;
};

// Classe dérivée PrepackedFood
class PrepackedFood : public Product {
private:
    double unitPrice;

public:
    PrepackedFood(long code = 0, const std::string& nom = "Unknown", double prix = 0.0)
        : Product(code, nom), unitPrice(prix) {}

    double getUnitPrice() const { return unitPrice; }
    void setUnitPrice(double prix) { unitPrice = prix; }

    void scanner() override {
        Product::scanner();
        std::cout << "Entrez le prix unitaire : ";
        std::cin >> unitPrice;
    }

    void printer() const override {
        Product::printer();
        std::cout << "Prix unitaire : " << unitPrice << std::endl;
    }

    double getPrice() const override {
        return unitPrice;
    }
};

// Classe dérivée FreshFood
class FreshFood : public Product {
private:
    double weight;
    double pricePerKilo;

public:
    FreshFood(long code = 0, const std::string& nom = "Unknown", double poids = 0.0, double prixKilo = 0.0)
        : Product(code, nom), weight(poids), pricePerKilo(prixKilo) {}

    double getWeight() const { return weight; }
    void setWeight(double poids) { weight = poids; }
    double getPricePerKilo() const { return pricePerKilo; }
    void setPricePerKilo(double prixKilo) { pricePerKilo = prixKilo; }

    void scanner() override {
        Product::scanner();
        std::cout << "Entrez le poids : ";
        std::cin >> weight;
        std::cout << "Entrez le prix par kilo : ";
        std::cin >> pricePerKilo;
    }

    void printer() const override {
        Product::printer();
        std::cout << "Poids : " << weight << ", Prix par kilo : " << pricePerKilo << std::endl;
    }

    double getPrice() const override {
        return weight * pricePerKilo;
    }
};

// Fonction globale isLowerCode
Product& isLowerCode(Product& p1, Product& p2) {
    return (p1.getCode() < p2.getCode()) ? p1 : p2;
}

// Fonction record pour enregistrer les produits achetés
void record(std::vector<Product*>& products) {
    char type;
    while (true) {
        std::cout << "Entrez 'p' pour un produit emballé ou 'f' pour un produit frais (ou 'q' pour quitter) : ";
        std::cin >> type;
        if (type == 'q') break;

        if (type == 'p') {
            PrepackedFood* pf = new PrepackedFood();
            pf->scanner();
            products.push_back(pf);
        } else if (type == 'f') {
            FreshFood* ff = new FreshFood();
            ff->scanner();
            products.push_back(ff);
        } else {
            std::cout << "Type de produit invalide." << std::endl;
        }
    }

    std::cout << "Liste des produits achetés :" << std::endl;
    double total = 0.0;
    for (const auto& product : products) {
        product->printer();
        total += product->getPrice();
    }
    std::cout << "Total : " << total << std::endl;
}

// Interface ElectronicsProduct
class ElectronicsProduct {
protected:
    int id;
    std::string name;
    double price;
    int stock;

public:
    ElectronicsProduct(int identifiant, const std::string& nom, double prix, int quantite)
        : id(identifiant), name(nom), price(prix), stock(quantite) {}

    virtual ~ElectronicsProduct() {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    virtual void afficherDetails() const = 0;
    virtual void acheter(int quantite) = 0;
};

// Classe dérivée ConsumerElectronics
class ConsumerElectronics : public Product, public ElectronicsProduct {
private:
    double screenSize;

public:
    ConsumerElectronics(long code, const std::string& nom, double prix, int quantite, double tailleEcran)
        : Product(code, nom), ElectronicsProduct(code, nom, prix, quantite), screenSize(tailleEcran) {}

    void afficherDetails() const override {
        std::cout << "ID : " << ElectronicsProduct::getId() << ", Nom : " << ElectronicsProduct::getName() << ", Prix : " << ElectronicsProduct::getPrice() << ", Stock : " << ElectronicsProduct::getStock() << ", Taille écran : " << screenSize << std::endl;
    }

    void acheter(int quantite) override {
        if (quantite <= ElectronicsProduct::getStock()) {
            ElectronicsProduct::stock -= quantite;
            std::cout << "Achat réussi. Nouveau stock : " << ElectronicsProduct::getStock() << std::endl;
        } else {
            std::cout << "Stock insuffisant." << std::endl;
        }
    }

    double getPrice() const override {
        return ElectronicsProduct::getPrice();
    }
};

// Classe dérivée IndustrialElectronics
class IndustrialElectronics : public Product, public ElectronicsProduct {
private:
    std::string protectionLevel;

public:
    IndustrialElectronics(long code, const std::string& nom, double prix, int quantite, const std::string& niveauProtection)
        : Product(code, nom), ElectronicsProduct(code, nom, prix, quantite), protectionLevel(niveauProtection) {}

    void afficherDetails() const override {
        std::cout << "ID : " << ElectronicsProduct::getId() << ", Nom : " << ElectronicsProduct::getName() << ", Prix : " << ElectronicsProduct::getPrice() << ", Stock : " << ElectronicsProduct::getStock() << ", Niveau de protection : " << protectionLevel << std::endl;
    }

    void acheter(int quantite) override {
        if (quantite <= ElectronicsProduct::getStock()) {
            ElectronicsProduct::stock -= quantite;
            std::cout << "Achat réussi. Nouveau stock : " << ElectronicsProduct::getStock() << std::endl;
        } else {
            std::cout << "Stock insuffisant." << std::endl;
        }
    }

    double getPrice() const override {
        return ElectronicsProduct::getPrice();
    }
};

// Classe dérivée AutomotiveElectronics
class AutomotiveElectronics : public Product, public ElectronicsProduct {
private:
    double voltage;

public:
    AutomotiveElectronics(long code, const std::string& nom, double prix, int quantite, double tension)
        : Product(code, nom), ElectronicsProduct(code, nom, prix, quantite), voltage(tension) {}

    void afficherDetails() const override {
        std::cout << "ID : " << ElectronicsProduct::getId() << ", Nom : " << ElectronicsProduct::getName() << ", Prix : " << ElectronicsProduct::getPrice() << ", Stock : " << ElectronicsProduct::getStock() << ", Tension : " << voltage << std::endl;
    }

    void acheter(int quantite) override {
        if (quantite <= ElectronicsProduct::getStock()) {
            ElectronicsProduct::stock -= quantite;
            std::cout << "Achat réussi. Nouveau stock : " << ElectronicsProduct::getStock() << std::endl;
        } else {
            std::cout << "Stock insuffisant." << std::endl;
        }
    }

    double getPrice() const override {
        return ElectronicsProduct::getPrice();
    }
};

// Classe dérivée MedicalElectronics
class MedicalElectronics : public Product, public ElectronicsProduct {
private:
    std::string certification;

public:
    MedicalElectronics(long code, const std::string& nom, double prix, int quantite, const std::string& certif)
        : Product(code, nom), ElectronicsProduct(code, nom, prix, quantite), certification(certif) {}

    void afficherDetails() const override {
        std::cout << "ID : " << ElectronicsProduct::getId() << ", Nom : " << ElectronicsProduct::getName() << ", Prix : " << ElectronicsProduct::getPrice() << ", Stock : " << ElectronicsProduct::getStock() << ", Certification : " << certification << std::endl;
    }

    void acheter(int quantite) override {
        if (quantite <= ElectronicsProduct::getStock()) {
            ElectronicsProduct::stock -= quantite;
            std::cout << "Achat réussi. Nouveau stock : " << ElectronicsProduct::getStock() << std::endl;
        } else {
            std::cout << "Stock insuffisant." << std::endl;
        }
    }

    double getPrice() const override {
        return ElectronicsProduct::getPrice();
    }
};

// Classe Magasin pour gérer les produits électroniques
class Magasin {
private:
    std::vector<ElectronicsProduct*> produits;

public:
    void ajouterProduit(ElectronicsProduct* produit) {
        produits.push_back(produit);
    }

    void afficherCatalogue() const {
        for (const auto& produit : produits) {
            produit->afficherDetails();
        }
    }

    void acheterProduit(int id, int quantite) {
        for (auto& produit : produits) {
            if (produit->getId() == id) {
                produit->acheter(quantite);
                return;
            }
        }
        std::cout << "Produit non trouvé." << std::endl;
    }
};

// Classe ProductManager pour gérer les produits
class ProductManager {
private:
    std::vector<ElectronicsProduct*> produits;

public:
    void ajouterProduit(ElectronicsProduct* produit) {
        produits.push_back(produit);
    }

    void supprimerProduit(int id) {
        auto it = std::remove_if(produits.begin(), produits.end(), [id](ElectronicsProduct* produit) {
            return produit->getId() == id;
        });
        if (it != produits.end()) {
            delete *it;
            produits.erase(it, produits.end());
        }
    }

    ElectronicsProduct* rechercherProduit(int id) const {
        for (const auto& produit : produits) {
            if (produit->getId() == id) {
                return produit;
            }
        }
        return nullptr;
    }

    void trierParPrix() {
        std::sort(produits.begin(), produits.end(), [](ElectronicsProduct* a, ElectronicsProduct* b) {
            return a->getPrice() < b->getPrice();
        });
    }

    void afficherProduits() const {
        for (const auto& produit : produits) {
            produit->afficherDetails();
        }
    }

    std::vector<ElectronicsProduct*> getProduits() const {
        return produits;
    }

    void acheterProduit(int id, int quantite) {
        for (auto& produit : produits) {
            if (produit->getId() == id) {
                produit->acheter(quantite);
                return;
            }
        }
        std::cout << "Produit non trouvé." << std::endl;
    }
};

// Fonction pour obtenir une quantité valide
int getValidQuantity() {
    int quantite;
    while (true) {
        std::cout << "Entrez la quantité : ";
        std::cin >> quantite;
        if (std::cin.fail() || quantite <= 0) {
            std::cin.clear(); // clear input buffer to restore cin to a usable state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore last input
            std::cout << "Quantité invalide. Veuillez entrer un nombre positif." << std::endl;
        } else {
            break;
        }
    }
    return quantite;
}

// Fonction principale avec menu interactif
int main() {
    ProductManager manager;
    int choice;

    while (true) {
        std::cout << "\n****************Menu****************\n" << std::endl;
        std::cout << "1. Ajouter un produit" << std::endl;
        std::cout << "2. Supprimer un produit" << std::endl;
        std::cout << "3. Rechercher un produit" << std::endl;
        std::cout << "4. Trier les produits par prix" << std::endl;
        std::cout << "5. Afficher les produits" << std::endl;
        std::cout << "6. Acheter un produit" << std::endl;
        std::cout << "7. Quitter\n" << std::endl;
        std::cout << "Choisissez une option : ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int type;
                std::cout << "Entrez le type de produit (1: Consumer, 2: Industrial, 3: Automotive, 4: Medical) : ";
                std::cin >> type;
                long code;
                std::string nom;
                double prix;
                int quantite = getValidQuantity();

                std::cout << "Entrez le code-barres : ";
                std::cin >> code;
                std::cout << "Entrez le nom du produit : ";
                std::cin.ignore();
                std::getline(std::cin, nom);
                std::cout << "Entrez le prix en TND: ";
                std::cin >> prix;

                if (type == 1) {
                    double tailleEcran;
                    std::cout << "Entrez la taille de l'écran : ";
                    std::cin >> tailleEcran;
                    manager.ajouterProduit(new ConsumerElectronics(code, nom, prix, quantite, tailleEcran));
                } else if (type == 2) {
                    std::string niveauProtection;
                    std::cout << "Entrez le niveau de protection : ";
                    std::cin >> niveauProtection;
                    manager.ajouterProduit(new IndustrialElectronics(code, nom, prix, quantite, niveauProtection));
                } else if (type == 3) {
                    double tension;
                    std::cout << "Entrez la tension : ";
                    std::cin >> tension;
                    manager.ajouterProduit(new AutomotiveElectronics(code, nom, prix, quantite, tension));
                } else if (type == 4) {
                    std::string certif;
                    std::cout << "Entrez la certification : ";
                    std::cin >> certif;
                    manager.ajouterProduit(new MedicalElectronics(code, nom, prix, quantite, certif));
                } else {
                    std::cout << "Type de produit invalide." << std::endl;
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "Entrez l'ID du produit à supprimer : ";
                std::cin >> id;
                manager.supprimerProduit(id);
                break;
            }
            case 3: {
                int id;
                std::cout << "Entrez l'ID du produit à rechercher : ";
                std::cin >> id;
                ElectronicsProduct* produitTrouve = manager.rechercherProduit(id);
                if (produitTrouve) {
                    std::cout << "Produit trouve :" << std::endl;
                    produitTrouve->afficherDetails();
                } else {
                    std::cout << "Produit non trouve." << std::endl;
                }
                break;
            }
            case 4: {
                manager.trierParPrix();
                std::cout << "Produits tries par prix :" << std::endl;
                manager.afficherProduits();
                break;
            }
            case 5: {
                manager.afficherProduits();
                break;
            }
            case 6: {
                int id;
                std::cout << "Entrez l'ID du produit à acheter : ";
                std::cin >> id;
                int quantite = getValidQuantity();
                manager.acheterProduit(id, quantite);
                break;
            }
            case 7: {
                // Libération de la mémoire
                for (auto& produit : manager.getProduits()) {
                    delete produit;
                }
                return 0;
            }
            default: {
                std::cout << "Option invalide." << std::endl;
                break;
            }
        }
    }

    return 0;
}
