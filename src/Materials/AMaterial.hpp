/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
#define AMATERIAL_HPP_

#include "IMaterial.hpp"

namespace RayTracer::Materials {

class AMaterial : public IMaterial {
    protected:
        std::shared_ptr<IMaterial> _wrappee;

    public:
        void setWrappee(std::shared_ptr<IMaterial> wrappee) override;

        AMaterial() = default;
        virtual ~AMaterial();
};

};

#endif /* !AMATERIAL_HPP_ */
