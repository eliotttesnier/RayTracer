/*
** EPITECH PROJECT, 2025
** rayTracer
** File description:
** Inotify
*/

#include <string>
#include <iostream>

#include "Inotify.hpp"

namespace RayTracer
{

Inotify::Inotify()
{
    _inotifyId = inotify_init1(IN_NONBLOCK);
    if (_inotifyId == -1) {
        throw std::runtime_error("inotify_init failed");
    }
}

Inotify::~Inotify()
{
    if (_inotifyId != -1)
        close(_inotifyId);
}

int Inotify::addWatch(const std::string &filename)
{
    _watchDescriptor = inotify_add_watch(_inotifyId, filename.c_str(), IN_MODIFY);
    if (_watchDescriptor == -1) {
        close(_inotifyId);
        _inotifyId = -1;
        throw std::runtime_error("inotify_add_watch failed");
    }
    return _watchDescriptor;
}

bool Inotify::fileModified()
{
    static const size_t kEventBufferLength = 4096;
    char buffer[kEventBufferLength];
    ssize_t length = read(_inotifyId, buffer, kEventBufferLength);
    if (length < 0) {
        if (errno == EAGAIN) {
            usleep(100 * 1000);
        } else {
            std::cerr << "read inotifyId failed" << std::endl;
        }
        return false;
    }
    for (char *ptr = buffer; ptr < buffer + length;) {
        struct inotify_event *event = (struct inotify_event *)ptr;
        if (event->mask & IN_MODIFY) {
            return true;
        }
        ptr += sizeof(struct inotify_event) + event->len;
    }
    return false;
}

}
