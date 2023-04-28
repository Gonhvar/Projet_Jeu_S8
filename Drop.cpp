#include "Drop.hpp"

Drop::Drop() : Killable() {}

Drop::Drop(std::string& spriteName) : Killable(spriteName) {}

void Drop::mort() {}