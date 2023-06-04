#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "Inc.hpp"

class Serializable {
public:
	virtual std::string serialize(std::string& toWrite) = 0;
    virtual std::istringstream& deSerialize(std::istringstream& toRead) = 0;
    /*
    Toutes les classes voulant être enregistrées doivent implémenter l'interface Serializable.
    Si une classe parent l'implémente cela marche aussi. Mais il faut tout de même redéfinir les 2 méthodes
    si l'on veut que les paramètres de la classe enfant soit enregistrés. Au début de la fonction redéfinie,
    il faudra appeller la methode eponyme du parent le plus proche (redéfinissant la méthode).
    Une classe qui n'a pas de paramètres à enregistrer (soit parce qu'elle n'en a pas, soit parce que
    tous ses paramètres sont initialisés dans le constructeur) n'a pas besoin de redéfinir les 2 méthodes de Serializable
    L'écriture et la lecteur dans la chaîne de caratère doit respecter très soigneusement le format.
    Il faut faire attention à lire autant de paramètres qu'on en écrit.

    Cette approche a de gros défauts mais au moins je l'ai faite moi-même et elle est accessible à tous ceux qui ont
    télécharger ce programme.
    Pour ce qui est de l'optimisation, on part du principe que ces méthodes seront appellées seuleuement de manière occasionnelle.
    */
};

#endif