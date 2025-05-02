set(CAMERA_FACTORY_SRC
    CameraFactory.cpp
)

set(CAMERA_FACTORY_INC
    CameraFactory.hpp
)

add_library(CameraFactory STATIC ${CAMERA_FACTORY_SRC} ${CAMERA_FACTORY_INC})
