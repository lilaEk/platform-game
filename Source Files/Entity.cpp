#include "../Headers/Entity.hpp"

Entity::Entity() {

    allEntities.push_back(this);
//    addEntityToVec(allEntities, this);
}

//void addEntityToVec(std::vector<Entity*> &allEntities, Entity *&entity){
//    allEntities.push_back(entity);
//}