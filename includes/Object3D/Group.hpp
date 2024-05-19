#pragma once

#include <Object3D/BasicObject.hpp>
#include <Core/Renderable.hpp>

/**
 * @class Group
 * @brief Class representing a group of objects.
 * 
 * The Group class represents a collection of objects. It provides methods to add, remove, and retrieve objects
 * from the group, as well as clearing the group.
 */
class Group : public BasicObject, public Renderable {
public:
    /**
     * @brief Default constructor for the Group class.
     */
    Group() = default;

    /**
     * @brief Adds an object to the group.
     * 
     * @param object The object to add to the group.
     */
    void add(Renderable *object);

    /**
     * @brief Removes an object from the group.
     * 
     * @param object The object to remove from the group.
     */
    void remove(const Renderable *object);

    /**
     * @brief Clears the group by removing all objects.
     */
    void clear();

    /**
     * @brief Retrieves the object at the specified index in the group.
     * 
     * @param index The index of the object to retrieve.
     * @return The object at the specified index.
     */
    Renderable& getObject(unsigned int index);

    /**
     * @brief Retrieves the number of children objects in the group.
     * 
     * @return The number of children objects in the group.
     */
    size_t getNumberOfChildren() const;

    /**
     * @brief Retrieves a vector containing pointers to the children objects in the group.
     * 
     * @return A vector containing pointers to the children objects in the group.
     */
    std::vector<Renderable*> getChildrens();

    /**
     * @brief Renders the group of objects.
     * 
     * Renders all the children objects of the group using the specified parent model matrix, and shader program.
     * 
     * @param parentModelMatrix The parent model matrix representing the transformation of the parent object.
     * @param shaderProgram The shader program to use for rendering.
     */
    void render(const glm::mat4 parentModelMatrix, const Renderer& renderer) override;

    /**
     * @brief Checks if this group is equal to another group.
     * 
     * Two groups are considered equal if they have the same children objects.
     * 
     * @param other The other group to compare with.
     * @return True if the groups are equal, false otherwise.
     */
    bool operator==(const Group& other) const;

private:
    std::vector<Renderable*> childrens;   ///< Vector containing the children objects of the group.
};