/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Mobius
*/

#include <cmath>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <typeinfo>
#include "Mobius.hpp"

namespace RayTracer::primitive {

Mobius::Mobius()
{
    _name = "mobius";
    _position = Math::Point3D(0, 0, 0);
    _rotation = Math::Vector3D(0, 0, 0);
    _majorRadius = 1.0;
    _minorRadius = 0.25;
    _twist = 1.0;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    double totalRadius = _majorRadius + _minorRadius;
    _boundingBox.min = Math::Point3D(-totalRadius, -_minorRadius, -totalRadius);
    _boundingBox.max = Math::Point3D(totalRadius, _minorRadius, totalRadius);
}

Mobius::Mobius(const Math::Point3D &position, double majorRadius, double minorRadius, double twist)
{
    _name = "mobius";
    _position = position;
    _rotation = Math::Vector3D(0, 0, 0);
    _majorRadius = majorRadius;
    _minorRadius = minorRadius;
    _twist = twist;
    _anchorPoint = Math::Vector3D(0, 0, 0);
    _boundingBox = AABB();
    double totalRadius = _majorRadius + _minorRadius;
    _boundingBox.min = Math::Point3D(-totalRadius, -_minorRadius, -totalRadius);
    _boundingBox.max = Math::Point3D(totalRadius, _minorRadius, totalRadius);
}

double Mobius::getMajorRadius() const
{
    return _majorRadius;
}

void Mobius::setMajorRadius(double radius)
{
    _majorRadius = radius;
    double totalRadius = _majorRadius + _minorRadius;
    _boundingBox.min._x = -totalRadius;
    _boundingBox.min._z = -totalRadius;
    _boundingBox.max._x = totalRadius;
    _boundingBox.max._z = totalRadius;
}

double Mobius::getMinorRadius() const
{
    return _minorRadius;
}

void Mobius::setMinorRadius(double radius)
{
    _minorRadius = radius;
    double totalRadius = _majorRadius + _minorRadius;
    _boundingBox.min._x = -totalRadius;
    _boundingBox.min._y = -_minorRadius;
    _boundingBox.min._z = -totalRadius;
    _boundingBox.max._x = totalRadius;
    _boundingBox.max._y = _minorRadius;
    _boundingBox.max._z = totalRadius;
}

double Mobius::getTwist() const
{
    return _twist;
}

void Mobius::setTwist(double twist)
{
    _twist = twist;
}

Math::Vector3D Mobius::normalAt(const Math::Point3D& point) const
{
    Math::Point3D localPoint = transformPointToLocal(point);
    const double epsilon = 0.0001;
    double dx = SDF(Math::Point3D(localPoint._x + epsilon, localPoint._y, localPoint._z)) -
                SDF(Math::Point3D(localPoint._x - epsilon, localPoint._y, localPoint._z));
    double dy = SDF(Math::Point3D(localPoint._x, localPoint._y + epsilon, localPoint._z)) -
                SDF(Math::Point3D(localPoint._x, localPoint._y - epsilon, localPoint._z));
    double dz = SDF(Math::Point3D(localPoint._x, localPoint._y, localPoint._z + epsilon)) -
                SDF(Math::Point3D(localPoint._x, localPoint._y, localPoint._z - epsilon));

    Math::Vector3D localNormal(dx, dy, dz);
    localNormal.normalize();

    return transformNormalToWorld(localNormal);
}

double Mobius::SDF(const Math::Point3D& point) const
{
    // Coordonnées du point
    double x = point._x;
    double y = point._y;
    double z = point._z;
    
    // Distance minimale initialisée à une grande valeur
    double minDistance = std::numeric_limits<double>::max();
    
    // Paramètres du ruban
    const int numAngles = 128;  // Nombre de positions angulaires (cercles dans le bracelet)
    const int numWidths = 10;   // Nombre de lignes sur la largeur
    
    // Pour chaque position angulaire (chaque cercle du bracelet)
    for (int i = 0; i < numAngles; i++) {
        double theta = 2.0 * M_PI * i / numAngles;
        
        // Pour un ruban de Möbius, nous avons besoin d'une demi-torsion sur 360°
        // Cette demi-torsion doit se faire sur le 3ème axe
        
        // Position de base sur le cercle principal
        double circle_x = _majorRadius * std::cos(theta);
        double circle_z = _majorRadius * std::sin(theta);
        
        // Calculer les extrémités gauche et droite du ruban à cette position angulaire
        // La torsion se fait sur l'axe Z (le 3ème axe)
        double halfTwist = theta * _twist / 2.0;
        
        // Tracer une ligne horizontale (sur l'axe X) à cette position angulaire
        // Avec une rotation progressive qui dépend de theta
        for (int j = 0; j <= numWidths; j++) {
            // t varie de -1 à 1 (de gauche à droite du ruban)
            double t = -1.0 + 2.0 * j / numWidths;
            
            // Calculer la position avec la torsion de Möbius
            // La torsion fait que lorsqu'on fait le tour complet, gauche devient droite et vice versa
            
            // Position sur le ruban à cet angle et cette largeur
            // La largeur du ruban reste constante (_minorRadius)
            double ribbon_x = circle_x;
            double ribbon_y = t * _minorRadius * std::cos(halfTwist);
            double ribbon_z = circle_z + t * _minorRadius * std::sin(halfTwist);
            
            // Si nous ne sommes pas au premier cercle, calculer la distance aux segments
            // qui relient ce cercle au précédent
            if (i > 0) {
                // Angle du cercle précédent
                double prevTheta = 2.0 * M_PI * (i - 1) / numAngles;
                double prevHalfTwist = prevTheta * _twist / 2.0;
                
                // Position sur le cercle précédent
                double prev_x = _majorRadius * std::cos(prevTheta);
                double prev_z = _majorRadius * std::sin(prevTheta);
                
                // Position sur le ruban au cercle précédent
                double prevRibbon_x = prev_x;
                double prevRibbon_y = t * _minorRadius * std::cos(prevHalfTwist);
                double prevRibbon_z = prev_z + t * _minorRadius * std::sin(prevHalfTwist);
                
                // Calculer la distance du point au segment entre les deux positions
                Math::Vector3D segVec(ribbon_x - prevRibbon_x, ribbon_y - prevRibbon_y, ribbon_z - prevRibbon_z);
                double segLength = segVec.length();
                
                segVec.normalize();
                
                Math::Vector3D pointToSeg(x - prevRibbon_x, y - prevRibbon_y, z - prevRibbon_z);
                
                double proj = pointToSeg.dot(segVec);
                
                double segDist;
                if (proj <= 0) {
                    segDist = Math::Vector3D(x - prevRibbon_x, y - prevRibbon_y, z - prevRibbon_z).length();
                } else if (proj >= segLength) {
                    segDist = Math::Vector3D(x - ribbon_x, y - ribbon_y, z - ribbon_z).length();
                } else {
                    Math::Vector3D closestPoint = Math::Vector3D(
                        prevRibbon_x + segVec._x * proj,
                        prevRibbon_y + segVec._y * proj,
                        prevRibbon_z + segVec._z * proj
                    );
                    segDist = Math::Vector3D(x - closestPoint._x, y - closestPoint._y, z - closestPoint._z).length();
                }
                
                minDistance = std::min(minDistance, segDist);
            }
        }
        
        // Connecter également le dernier cercle au premier pour fermer la boucle
        if (i == numAngles - 1) {
            for (int j = 0; j <= numWidths; j++) {
                double t = -1.0 + 2.0 * j / numWidths;
                
                // Position sur le dernier cercle
                double lastTheta = theta;
                double lastHalfTwist = lastTheta * _twist / 2.0;
                double last_x = circle_x;
                double last_y = t * _minorRadius * std::cos(lastHalfTwist);
                double last_z = circle_z + t * _minorRadius * std::sin(lastHalfTwist);
                
                // Position sur le premier cercle
                double firstTheta = 0.0;
                double firstHalfTwist = firstTheta * _twist / 2.0;
                double first_x = _majorRadius;  // cos(0) = 1
                double first_y = t * _minorRadius * std::cos(firstHalfTwist);
                double first_z = 0.0;  // sin(0) = 0
                
                // La torsion de Möbius implique que t devient -t après un tour complet
                // Donc le bord gauche du dernier cercle se connecte au bord droit du premier
                if (_twist == 1.0) {
                    first_y = -t * _minorRadius * std::cos(firstHalfTwist);
                    first_z = 0.0 + -t * _minorRadius * std::sin(firstHalfTwist);
                }
                
                // Calculer la distance au segment qui ferme la boucle
                Math::Vector3D closeVec(first_x - last_x, first_y - last_y, first_z - last_z);
                double closeLength = closeVec.length();
                
                closeVec.normalize();
                
                Math::Vector3D pointToClose(x - last_x, y - last_y, z - last_z);
                
                double closeProj = pointToClose.dot(closeVec);
                
                double closeDist;
                if (closeProj <= 0) {
                    closeDist = Math::Vector3D(x - last_x, y - last_y, z - last_z).length();
                } else if (closeProj >= closeLength) {
                    closeDist = Math::Vector3D(x - first_x, y - first_y, z - first_z).length();
                } else {
                    Math::Vector3D closestPoint = Math::Vector3D(
                        last_x + closeVec._x * closeProj,
                        last_y + closeVec._y * closeProj,
                        last_z + closeVec._z * closeProj
                    );
                    closeDist = Math::Vector3D(x - closestPoint._x, y - closestPoint._y, z - closestPoint._z).length();
                }
                
                minDistance = std::min(minDistance, closeDist);
            }
        }
    }
    
    // Épaisseur du ruban (très fine comme une feuille de papier)
    const double thickness = 0.01;
    
    return minDistance - thickness;
}

Math::hitdata_t Mobius::intersect(const Math::Ray &ray)
{
    Math::Ray localRay = transformRayToLocal(ray);

    Math::hitdata_t hitData;
    hitData.hit = false;
    hitData.color = _color;

    if (!_boundingBox.intersect(localRay))
        return hitData;

    const int MAX_STEPS = 100;
    const double EPSILON = 0.001;
    const double MAX_DIST = 100.0;
    
    // Start ray marching
    double t = 0.01;
    for (int i = 0; i < MAX_STEPS && t < MAX_DIST; i++) {
        Math::Point3D localPoint(
            localRay.origin._x + t * localRay.direction._x,
            localRay.origin._y + t * localRay.direction._y,
            localRay.origin._z + t * localRay.direction._z
        );

        double dist = SDF(localPoint);

        if (dist < EPSILON) {
            hitData.hit = true;
            hitData.distance = t;
            hitData.point = transformPointToWorld(localPoint);
            hitData.normal = normalAt(hitData.point);
            break;
        }
        
        // Use a smaller step size for more accuracy
        t += dist * 0.5;
    }

    return hitData;
}

Graphic::color_t Mobius::getColor(
    Math::hitdata_t hitData,
    Math::Ray ray,
    std::vector<std::shared_ptr<ILight>> lights,
    std::vector<std::shared_ptr<IPrimitive>> primitives
)
{
    return _material->calculateColor(
        *this,
        hitData,
        ray,
        lights,
        primitives
    );
}

}  // namespace RayTracer::primitive