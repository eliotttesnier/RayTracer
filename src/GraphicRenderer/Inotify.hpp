/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** Inotify
*/

#ifndef INOTIFY_HPP_
#define INOTIFY_HPP_

#include <sys/inotify.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <stdexcept>

namespace RayTracer
{

class Inotify
{
    private:
        int _inotifyId = -1;
        int _watchDescriptor = -1;

    public:
        Inotify();
        ~Inotify();

        Inotify(const Inotify&) = delete;
        Inotify& operator=(const Inotify&) = delete;

        int addWatch(const std::string &filename);

        bool fileModified();
};

};

#endif /* !INOTIFY_HPP_ */
