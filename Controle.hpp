#ifndef CONTROLE_HPP
#define CONTROLE_HPP

class Controle {
public:
    virtual void zDown() {};
    virtual void zUp() {};
    virtual void sDown() {};
    virtual void sUp() {};
    virtual void qDown() {};
    virtual void qUp() {};
    virtual void dDown() {};
    virtual void dUp() {};
    virtual void spaceDown() {};
    virtual void spaceUp() {};
};
#endif