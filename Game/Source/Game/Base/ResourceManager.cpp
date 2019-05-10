#include "GamePCH.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMeshes )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        glDeleteTextures( 1, &object.second );

    for( auto object: m_pMaterials )
        delete object.second;

    for (auto object : m_pSoundPlayer)
        delete object.second;

    for (auto object : m_pSoundObject)
        delete object.second;
}

void ResourceManager::OnSurfaceChanged(unsigned int width, unsigned int height)
{
}
