#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
    Level();

    int getNbComponents();
    Entity* getLevelComponents();

protected:
    Entity* levelComponents;
    int nbComponents;

};

#endif // LEVEL_H
