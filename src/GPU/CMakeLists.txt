if(CUDA_FOUND)
    # Ajouter les fichiers source CUDA
    cuda_add_library(GPU STATIC
        CUDAKernel.cu
        GPURenderer.cpp
    )
    
    # Inclure les en-têtes CUDA
    target_include_directories(GPU PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CUDA_INCLUDE_DIRS}
    )
    
    # Lier avec les bibliothèques CUDA
    target_link_libraries(GPU
        ${CUDA_LIBRARIES}
        Core
        Primitives
        Lights
        Materials
        Math
        Graphic
    )
else()
    # Version factice si CUDA n'est pas disponible
    add_library(GPU STATIC
        GPURenderer.cpp
    )
    
    target_include_directories(GPU PUBLIC
        ${CMAKE_SOURCE_DIR}/src
    )
    
    target_link_libraries(GPU
        Core
        Primitives
        Lights
        Materials
        Math
        Graphic
    )
endif()
