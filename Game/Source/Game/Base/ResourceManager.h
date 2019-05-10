#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;

class ShaderProgram;
class Mesh;

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, ShaderProgram*> m_pShaders;
    std::map<std::string, GLuint> m_pTextures;
	std::map<std::string, Material*> m_pMaterials;
    std::map<std::string, SoundPlayer*> m_pSoundPlayer;
    std::map<std::string, SoundObject*> m_pSoundObject;
    


public:
    ResourceManager();
    virtual ~ResourceManager();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);

    void AddMesh(const char* name, Mesh* pMesh) { m_pMeshes[name] = pMesh; }
    void AddShader(const char* name, ShaderProgram* pShader)
    { 
        assert(m_pShaders[name] == 0);
        m_pShaders[name] = pShader;
    }
    void AddTexture(const char* name, GLuint texturehandle) 
    {
        //assert(m_pTextures[name] == 0);
        m_pTextures[name] = texturehandle; 
    }
    void AddMaterial(const char* name, Material* pMaterial) { m_pMaterials[name] = pMaterial; }
    void AddSoundPlayer(const char* name, SoundPlayer* pSound) { m_pSoundPlayer[name] = pSound; }
    void AddSoundObject(const char* name, SoundObject* pSound) { m_pSoundObject[name] = pSound; }



    Mesh* GetMesh(const char* name) { return m_pMeshes[name]; }
    ShaderProgram* GetShader(const char* name) { return m_pShaders[name]; }
    GLuint GetTexture(const char* name) { return m_pTextures[name]; }
    Material* GetMaterial(const char* name) { return m_pMaterials[name]; }
    SoundPlayer* GetSoundPlayer(const char* name) { return m_pSoundPlayer[name]; }
    SoundObject* GetSoundObj(const char* name) { return m_pSoundObject[name]; }


    Mesh* GetMesh(std::string name) { return m_pMeshes[name]; }
    ShaderProgram* GetShader(std::string name) { return m_pShaders[name]; }
    GLuint GetTexture(std::string name) { return m_pTextures[name]; }
    Material* GetMaterial(std::string name) { return m_pMaterials[name]; }
    SoundPlayer* GetSoundPlayer(std::string name) { return m_pSoundPlayer[name]; }
    SoundObject* GetSoundObj(std::string name) { return m_pSoundObject[name]; }
};

#endif //__ResourceManager_H__
