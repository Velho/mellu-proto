#ifndef PROTO_AABB_H
#define PROTO_AABB_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>

namespace Proto {

/*!
 *\brief ConvexObject class
 * Represents Object for separated axis theorem
 * collision calculation. Simplifies the collision check
 * for different shapes where user can construct ConvexObject
 * from different SFML shape objects.
 */
class ConvexObject {
public:
    ConvexObject() :
        ConvexObject{ sf::Vector2f(0, 0), sf::Vector2f(0, 0), .0f }
    { }

    ConvexObject(sf::Vector2f pos, sf::Vector2f sz, float ang) :
        position{ pos }, size{ sz }, angle{ ang }
    { }

    /* Construct ConvexObject out of SFML classes.
     * Constructing from sf::RectangleShape is simpler,
     * because position and size is retrieved much easier where
     * sf::Sprite is constructed from .getTextureRect().
     */
    ConvexObject(const sf::RectangleShape&);
    ConvexObject(const sf::Sprite&);

    sf::Vector2f get_position() const { return position; }
    sf::Vector2f get_size() const { return size; }
    float get_angle() const { return angle; }
private:
    sf::Vector2f position;
    sf::Vector2f size;
    float angle;
};

/*!
 *\brief Projection class
 * Projects ConvexObject to axes for overlap check.
 * ConvexObjects are primarily represented on 4 different
 * axes.
 */
class Projection {
public:

private:
};

/*!
 *\brief BoundingBox class
 * Calculates AABB based collision.
 * Supports rotated and scaled sprites/shapes.
 */
class BoundingBox {
public:
    BoundingBox(const sf::RectangleShape&);
    //BoundingBox(const sf::FloatRect&);

    bool bb_test(const sf::RectangleShape&);

    sf::Vector2f points[4];

    void get_projection(const sf::Vector2f&, float&, float&);

private:
    std::vector<sf::Vector2f> bb_points;
    std::array<sf::Vector2f, 4> arr_points;
};

}

#endif

