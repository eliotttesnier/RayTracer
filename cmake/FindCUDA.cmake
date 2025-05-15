# FindCUDA.cmake
# Script auxiliaire pour détecter et configurer CUDA
# Adapté aux projets raytracer

# Recherche des composants CUDA
find_package(CUDA QUIET)

if(CUDA_FOUND)
  message(STATUS "CUDA trouvé: ${CUDA_VERSION}")
  message(STATUS "CUDA include: ${CUDA_INCLUDE_DIRS}")
  message(STATUS "CUDA libraries: ${CUDA_LIBRARIES}")
  
  # Configuration des flags de compilation CUDA
  set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-O3;-arch=sm_60;--use_fast_math)
  
  # Pour les cartes RTX 3050, nous utilisons l'architecture Ampere (sm_86)
  set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-arch=sm_86)
  
  # Activer la compilation séparée pour accélérer la compilation
  set(CUDA_SEPARABLE_COMPILATION ON)
  
  # Gérer les limites d'enregistrement
  set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};--default-stream=per-thread)
else()
  message(WARNING "CUDA non trouvé. La compilation se fera pour CPU uniquement.")
endif()
