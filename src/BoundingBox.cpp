#include "BoundingBox.h"

#include <SFML/Graphics/Transform.hpp>

namespace Proto {

BoundingBox::BoundingBox(const sf::RectangleShape &shape)
{
    sf::Transform trans = shape.getTransform();
    sf::FloatRect local{ shape.getPosition(), shape.getSize() };

    points[0] = trans.transformPoint(0.f, 0.f);
    points[1] = trans.transformPoint(local.width, 0.f);
    points[2] = trans.transformPoint(local.width, local.height);
    points[3] = trans.transformPoint(0.f, local.height);
}

void BoundingBox::get_projection(const sf::Vector2f &axis, float &min, float &max)
{
    min = (points[0].x * axis.x + points[0].y * axis.y);
    max = min;

    for(int i = 1; i < 4; i++) {
        float projection = (points[i].x * axis.x + points[i].y * axis.y);

        if(projection < min)
            min = projection;
        if(projection > max)
            max = projection;
    }
}

bool BoundingBox::bb_test(const sf::RectangleShape &shape)
{
    BoundingBox b_box(shape);

    sf::Vector2f axes[4]
    {
        sf::Vector2f(
                this->points[1].x - this->points[0].x,
                this->points[1].y - this->points[0].y),
        sf::Vector2f(
                this->points[1].x - this->points[2].x,
                this->points[1].y - this->points[2].y),
        sf::Vector2f(
                b_box.points[0].x - b_box.points[3].x,
                b_box.points[0].y - b_box.points[3].y),
        sf::Vector2f(
                b_box.points[0].x - b_box.points[1].x,
                b_box.points[0].y - b_box.points[1].y)
    };

    for(int i = 0; i < 4; i++) {
        float min_this, max_this, min_b, max_b;

        this->get_projection(axes[i], min_this, max_this);
        b_box.get_projection(axes[i], min_b, max_b);

        if(!((min_b <= max_this) && (max_b >= min_this)))
            return false;
    }

    return true;
}

}
